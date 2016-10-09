function plot_bldg(u,optParams)

distbs = [optParams.disturbances.d1'; optParams.disturbances.d2'; ...
    optParams.disturbances.d3'];

z = SimBldg(u,optParams);

figure(4)
hold all;
plot(z(4,:),'linewidth',2);
grid on;
%%
 P = Polyhedron('lb',[10 22],'ub',[19 28]);
 hold on;
 plot(P,'Color','green','Alpha',0.6);
 legend('Initial','Method','SQP','SA','Comfort temp. (and occupancy time)')
%%
figure(1)
for i = 411:414
    subplot(i)
plot(z(i-410,:));
grid on;
end
grid on;
figure(2)
for i = 411:414
    subplot(i)
    if(i==411)
        plot(u);
        grid on;
    else
        j = i-411;
        stairs(distbs(j,:));
        grid on;
    end
end
grid on;

%%
   I1 = optParams.I1; 
   figure(1);
   subplot(414)
   hold on;
   plot(optParams.I1,-1*optParams.P1_comfort.b(1)*ones(numel(I1),1),'r-');
   hold on
   plot(optParams.I1,1*optParams.P1_comfort.b(2)*ones(numel(I1),1),'r-');
