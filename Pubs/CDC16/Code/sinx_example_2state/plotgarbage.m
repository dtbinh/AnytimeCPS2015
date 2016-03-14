%%
clear err
x2=x2_min:0.01:x2_max;
for j = 1:1000
    clear Txe Tx
    e = -deg2rad(1.3) + deg2rad(2.6)*(rand(1,numel(x2)));
    Me = a*cos(x2).*e;
    x2h = x2+e;
    for i = 1:numel(x2h)
        Txe(1:2,i) = T_diffeo([0;x2h(i)],a);
        Tx(1:2,i) = T_diffeo([0;x2(i)],a);
    end
    
    Txe = Txe(2,:);
    Tx = Tx(2,:);
    for i = 1:numel(x2h)
        err(i,j) = norm(Txe(i)-(Tx(i)+Me(i)))/(norm(Tx(i)));
    end
end
err = sum(err,2)/100;
%%
figure
plot(x2,err)
axis([min(x2) max(x2) min(err) max(err)])
grid on;
h = xlabel('$x_2$');
set(h,'Interpreter','latex');
h = ylabel('$E_e\big[|(T_2(x_2+e_2) - (T_2(x_2)+M_{22}(x_2)e_2))/T_2(x_2+e_2)|\big]$');
set(h,'Interpreter','latex');

%% 
mg = deg2rad(mag);
mg = [deg2rad(2.3);deg2rad(1.3)];
subplot(211)
plot(1:k,z_true(1,1:k),'linewidth',2);
hold all;
plot(1:k,z_true(1,1:k)+(-mg(1)+(2*mg(1).*rand(1,k))),'-.','linewidth',2);
grid on;
h  =legend('${z_{1k}}$','${\hat{z}_{1k}}$');
set(h,'Interpreter','latex');


subplot(212)
plot(1:k,z_true(2,1:k),'linewidth',2);
hold all;
plot(1:k,z_true(2,1:k)+(-mg(1)+(2*mg(1).*rand(1,k))),'-.','linewidth',2);
hold all;
plot(1:k,x_true(2,1:k),'linewidth',2);
hold all;
plot(1:k,x_true(2,1:k)+(-mg(1)+(2*mg(1).*rand(1,k))),'-.','linewidth',2);
grid on;
h  =legend('${z_{2k}}$','${\hat{z}_{2k}}$','${x_{2k}}$','${\hat{x}_{2k}}$');
set(h,'Interpreter','latex');


