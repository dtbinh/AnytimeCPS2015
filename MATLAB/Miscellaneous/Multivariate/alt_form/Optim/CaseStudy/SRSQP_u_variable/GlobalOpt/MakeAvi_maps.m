%myavi = avifile('avidemo_map1.avi','FPS',25);
%% describe sets and their signed dist approxs


%%
load('Data/Traj_75steps.mat'); %z(5,:)
Nx = optParams.dim_x;
Nu = optParams.dim_u;
N = optParams.len;
map_name = 'maps/map1.txt';
map = load_map(map_name, .5, .5, 0);

for j = 1:1
    if(j==1)
        close all;
        figure(1);
        Terminal = Polyhedron('lb',goal.stop-goal.ds,'ub',goal.stop+goal.ds);
        %plot_path(map,[]);
        for i = 1:size(obs,1)
           temp_poly = Polyhedron('lb',obs{i}.lb,'ub',obs{i}.ub);
           plot(temp_poly,'alpha',0.8,'color','gray');
           hold on;
           axis('equal');
        end
        
        hold on;
        plot(Terminal,'alpha',0.2,'color','green');
        title('Trajectory 1','FontSize',20);
         
        pos_1 = path_opt';
        inp_1 = reshape(u_opt,Nu,N-1);
        pause;
    end
    
    
    
    clear p1 p2
    for i = 1:size(pos_1,2)
        if(exist('p1','var'))
        delete(p1);
        delete(p2);
        end
        
        hold on
        %p1 = plot3(pos_1(1,i),pos_1(2,i),pos_1(3,i),'b*','MarkerSize',12);
        hold on;
        %p2 = plot3(pos_2(1,i),pos_2(2,i),pos_2(3,i),'ko','MarkerSize',12);
        quad1 = Quad_ccta(pos_1(1,i),pos_1(2,i),pos_1(3,i),0,0,0);% for i = 1
        %quad2 = Quad_ccta(pos_2(1,i),pos_2(2,i),pos_2(3,i),0,0,0);
        str1 = 'Time= ';
        str2 = num2str(i*0.05,'%2.4f');
        
        title(strcat(str1,str2),'FontSize',20); 
        if(i>1)
           quad1 = Quad_ccta(pos_1(1,i),pos_1(2,i),pos_1(3,i),0,rad2deg(inp_1(2,i-1)),rad2deg(inp_1(1,i-1)));
           %quad2 = Quad_ccta(pos_2(1,i),pos_2(2,i),pos_2(3,i),0,rad2deg(inp_2(1,i-1)),rad2deg(inp_2(2,i-1)));
           hold on;
           plot3(pos_1(1,1:i),pos_1(2,1:i),pos_1(3,1:i),'b-.','linewidth',2);
           hold on;
           %plot3(pos_2(1,1:i),pos_2(2,1:i),pos_2(3,1:i),'k-.');
           % delete prev quads
           delete(out_b1.p);
           %delete(out_b2.p);
           delete(out_b1.q);
           %delete(out_b2.q);
           delete(out_a1.p);
           %delete(out_a2.p);
           delete(out_a1.q);
           %delete(out_a2.q);
        end
        hold on;
        quad1.drawBody()
        out_b1 = ans;
        quad1.drawArms()
        out_a1 = ans;
        hold on;
        %quad2.drawBody()
        %out_b2 = ans;
        %quad2.drawArms()
        %out_a2 = ans;
        hold on;
        pause(0.05);
        %drawnow;
  %      myavi = addframe(myavi,gca);
    end
    
%     for j = 1:1
%         j
%         pause;
%         for i = 1:5 %final snaps
%    %         myavi = addframe(myavi,gca);
%         end
%     end
end
%myavi = close(myavi);
disp('fin');
% figure(1)
% hold all;
% plot3(pos_1(1,:),pos_1(2,:),pos_1(3,:),'*','linewidth',2,'MarkerSize',8)
% hold all;
% plot3(pos_2(1,:),pos_2(2,:),pos_2(3,:),'o','linewidth',2,'MarkerSize',8)
