myavi = avifile('avidemo_CCTA.avi','FPS',5);
%% describe sets and their signed dist approxs


%%
load('Case_20_u_nofevlim.mat'); %z(5,:)
Nx = optParams.dim_x;
Nu = optParams.dim_u;
N = optParams.len;


for j = 1:3
    if(j==1)
        close all;
        figure(1);
        drawsets;
        title('Trajectory 1','FontSize',20);
        load('Case_20_u_nofevlim.mat'); %z(5,:)
        X = optParams.A_x0_nQuad*optParams.x0 + optParams.B_U_nQuad*u_opt; %get states
        state_1 = reshape(X(1:Nx*N),Nx,N);
        state_2 = reshape(X(Nx*N+1:end),Nx,N);        
        pos_1 = state_1(4:6,:);
        pos_2 = state_2(4:6,:);
        pause;
    end
    
    if(j==2)
        close all;
        figure(1);
        drawsets;
        title('Trajectory 2','FontSize',20);
        load('Case_20_u_zmax.mat'); %-z(6,:)
        X = optParams.A_x0_nQuad*optParams.x0 + optParams.B_U_nQuad*u_opt; %get states
        state_1 = reshape(X(1:Nx*N),Nx,N);
        state_2 = reshape(X(Nx*N+1:end),Nx,N);        
        pos_1 = state_1(4:6,:);
        pos_2 = state_2(4:6,:);
        pause;
    end
    
    if(j==3)
        close all;
        figure(1);
        drawsets;
        title('Trajectory 3','FontSize',20);
        load('Case_20_u_0.mat'); %-z(4,:)
        X = optParams.A_x0_nQuad*optParams.x0 + optParams.B_U_nQuad*u_opt; %get states
        state_1 = reshape(X(1:Nx*N),Nx,N);
        state_2 = reshape(X(Nx*N+1:end),Nx,N);        
        pos_1 = state_1(4:6,:);
        pos_2 = state_2(4:6,:);
        pause;
    end
    clear p1 p2
    for i = 1:size(pos_1,2)
        if(exist('p1','var'))
        delete(p1);
        delete(p2);
        end
        
        hold on
        p1 = plot3(pos_1(1,i),pos_1(2,i),pos_1(3,i),'b*','MarkerSize',12);
        hold on;
        p2 = plot3(pos_2(1,i),pos_2(2,i),pos_2(3,i),'ko','MarkerSize',12);
        if(i>1)
           hold on;
           plot3(pos_1(1,1:i),pos_1(2,1:i),pos_1(3,1:i),'b-.');
           hold on;
           plot3(pos_2(1,1:i),pos_2(2,1:i),pos_2(3,1:i),'k-.');
        end
        
        pause(0.2);
        %drawnow;
        myavi = addframe(myavi,gca);
    end
    
    for j = 1:3
        pause;
        for i = 1:5
            myavi = addframe(myavi,gca);
        end
    end
end
myavi = close(myavi);
disp('fin');
% figure(1)
% hold all;
% plot3(pos_1(1,:),pos_1(2,:),pos_1(3,:),'*','linewidth',2,'MarkerSize',8)
% hold all;
% plot3(pos_2(1,:),pos_2(2,:),pos_2(3,:),'o','linewidth',2,'MarkerSize',8)