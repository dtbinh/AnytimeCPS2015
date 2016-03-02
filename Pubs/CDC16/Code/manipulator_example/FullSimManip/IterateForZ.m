function Z_final = IterateForZ(X,shrink_factor,grow_factor,params)

%%
ndims  = size(X.A,2); %dimension of X
Z = T_diffeo(X,params);
[~,z_mx,z_mn] = getRect(Z);
X_obt = T_inv_diffeo(Z,params);
x_new_mx = zeros(ndims,1);
x_new_mn = zeros(ndims,1);

[~,x_mx,x_mn] = getRect(X);
diff = X_obt\X;
iter = 0;

while(sum(~diff.isEmptySet)>=1) %X_obt is larger than X
    'shizzle'
    iter = iter + 1
    [~,x_obt_mx,x_obt_mn] = getRect(X_obt);
    % for dim = 1:ndims
    %     if(x_obt_mx(dim)>x_mx(dim)) % if that dim is larger than real safe set's
    %         z_mx(dim) = z_mx(dim)/shrink_factor; %shrink Z in that dim
    %     else
    %         z_mx(dim) = z_mx(dim); %useless stamement now
    %     end
    %     if(x_obt_mn(dim)<x_mn(dim)) %if smaller than actual lower bound (negative)
    %         z_mn(dim) = z_mn(dim)/shrink_factor;
    %     else
    %         z_mn(dim) = z_mn(dim); %useless stamement now
    %     end
    % end
    %shit method
    z_mn = z_mn/shrink_factor;
    z_mx = z_mx/shrink_factor;
    
    Z_new = Polyhedron('lb',z_mn,'ub',z_mx); %make new Z
    X_obt = T_inv_diffeo(Z_new,params); %obtain new X estimated
    [~,x_obt_mx,x_obt_mn] = getRect(X_obt)
    diff =  X_obt\X; %set diff for inclusion or not
    
end
Z_orig = Z_new;
z_mn_orig = z_mn;
z_mx_orig = z_mx;
%%

%grow if room
z_mx = z_mx_orig;
z_mn = z_mn_orig;
iters=0;
temp = 0;
% z_mn = z_mn_orig*(grow_factor)^(1/(iters+1));
% z_mx = z_mx_orig*(grow_factor)^(1/(iters+1));
% Z_new = Polyhedron('lb',z_mn,'ub',z_mx); %make new Z
% X_obt = T_inv_diffeo(Z_new,params); %obtain new X estimated
% [~,x_obt_mx,x_obt_mn] = getRect(X_obt)
% diff =  X_obt\X; %set diff for inclusion or not

while(~temp)%(sum(~diff.isEmptySet)>=1)
    iters = iters+1
    z_mx = z_mx*(grow_factor);%
    z_mn = z_mn*(grow_factor);%^(1/(iters+1));
    Z_new = Polyhedron('lb',z_mn,'ub',z_mx); %make new Z
    X_obt = T_inv_diffeo(Z_new,params); %obtain new X estimated
    [~,x_obt_mx,x_obt_mn] = getRect(X_obt);
    diff =  X_obt\X; %set diff for inclusion or not
    temp = sum(~diff.isEmptySet)>=1;
end
if(iters>1)
    z_mx_final = z_mx/(grow_factor);
    z_mn_final = z_mn/(grow_factor);
    Z_final = Polyhedron('lb', z_mn_final, 'ub',z_mx_final);
else %if no growth possible with this factor
    Z_final = Z_orig;
end
%% plot
plotyes = 1;
if plotyes

    figure;
    plot(Z.projection(1:2),'Color','lightblue');
    hold on;
    plot(X.projection(1:2));
    hold on
    plot(Z_final.projection(1:2),'Color','blue');
    hold on
    plot(Z_orig.projection(1:2),'Color','black');
    legend('Zout','X','Zshrinkgrow','Zshrink');
    
    figure;
    plot(Z.projection(3:4),'Color','lightblue');
    hold on;
    plot(X.projection(3:4));
    hold on
    plot(Z_final.projection(3:4),'Color','blue');
    hold on
    plot(Z_orig.projection(3:4),'Color','black');
    legend('Zout','X','Zshrinkgrow','Zshrink');

end