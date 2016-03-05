function [E_tilde_jgk,Z_k_reach,X_k_reach,V_inner_local] = getAllErrorSets(x_k,X_k,Z_k,X,Z,E,W,U,V_inner_global,A_d,B_d,K_lqr_d,params,N)
%% get all error sets till horizon from starting set X_k

X_k_reach{1} = X_k;
if(isempty(Z_k))
    z_k = T_diffeo(x_k,params);
    etilde_k = get_E_tilde_bound(X_k,E,params);
    Z_k_reach{1} = plus(z_k,etilde_k,'fourier');
    Z_k_reach{1}.minHRep;
else
    Z_k_reach{1} = Z_k;
end
V_inner_local{1} = getLocalVInner_interval(X_k_reach{1},U,params);
for j = 2:N+1
    %j
    %'computing reach sets'
    [Z_k_reach{j},X_k_reach{j}] = getReachSetsViaZ(Z_k_reach{j-1},V_inner_local{j-1},A_d,B_d,Z,X,W,params);
    %[Z_k_reach{j},X_k_reach{j}] = getReachSetsViaZ(Z_k_reach{j-1},V_inner_global,A_d,B_d,Z,X,W,a);
    %'got reach sets, inner approx now'
    V_inner_local{j} = getLocalVInner_interval(X_k_reach{j},U,params);
    %'got inner approx'
    if(Z_k_reach{j}.isEmptySet|| X_k_reach{j}.isEmptySet || ~Z_k_reach{j}.isFullDim)
        'Some reach set does not intersect with safe set or is not full dim'
        keyboard;
    end
end
%% plots debug, needs to be run as a standalone, not a function
debug = 1;
if(debug) %plot if you feel like it
    figure(1);
    %plot(Z);
    for j = 1:N+1
        hold on;
        [Zbox,~,~] = getRect(Z_k_reach{j}.projection(1:2));
        %if(j>0)
        %Zbox.plot('Color','yellow');
        %end
        hold on
        Z_k_reach{j}.projection(1:2).plot('Color','green');%pause;
        
        j;
    end
end
%%
debug1 = 0;
if(debug1)
x_k = T_diffeo(x_k,a); %is z_0 really
hold on
plot(x_k(1),x_k(2),'k*');
for i = 1:N
    u = -(K_lqr_d*x_k);
%     if(i<=N)
         u = u*(u<=V_inner_local{i}.b(2) && u>=-V_inner_local{i}.b(1)) ...
             + V_inner_local{i}.b(2)*(u>V_inner_local{i}.b(2)) ...
             - V_inner_local{i}.b(1)*(u<-V_inner_local{i}.b(1));
%     else
%         u = u*(u<=V_inner_global.b(2) && u>=-V_inner_global.b(1)) ...
%            + V_inner_global.b(2)*(u>V_inner_global.b(2)) ...
%            - V_inner_global.b(1)*(u<-V_inner_global.b(1));
%     end
    x_k = (A_d*x_k+B_d*u);
    i
    
    Z_k_reach{i+1}.isInside(x_k)
    hold on;
    plot(x_k(1),x_k(2),'k*');pause;
end
hold on;
Z_f_worst.projection(1:2).plot('Color','gray');
end
%%
for j = 1:N+1
    E_tilde_jgk{j} = get_E_tilde_bound(X_k_reach{j},E,params);
end