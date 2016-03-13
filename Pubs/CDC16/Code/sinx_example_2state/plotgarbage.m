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
        err(i,j) = norm(Txe(i)-(Tx(i)+Me(i)))/(norm(Txe)+eps);
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
h = ylabel('$E_e\big[|T_2(x_2+e_2) - (T_2(x_2)+M_{22}(x_2)e_2)|\big]$');
set(h,'Interpreter','latex');