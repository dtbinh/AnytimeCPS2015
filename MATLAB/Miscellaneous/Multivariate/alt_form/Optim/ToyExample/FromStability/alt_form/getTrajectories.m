function [Traj_all,U_all] = getTrajectories(A,B,x_lb,x_ub,u_lb,u_ub,Nx,Nu,len,Ntrials)

Traj_all = zeros(Nx,len,Ntrials);
U_all = zeros(Nx,len-1,Ntrials);
traj = zeros(Nx,len);


for i = 1:Ntrials

%gen trajectory
x0 = [x_lb] + [x_ub-x_lb]*rand(Nx,1);
U = u_lb + (u_ub-u_lb)*rand(Nu,len-1);
%with point mass dynamics only:
for k = 1:len
if(k==1)
traj(:,k) = x0;
else
traj(:,k) = A*traj(:,k-1) + B*U(:,k-1);

for dim=1:Nx
if(traj(dim,k)>x_ub)
traj(dim,k) = x_ub;
end %endif
if(traj(dim,k)<x_lb)
traj(dim,k) = x_lb;
end %endif

end %endfor

end %endif
end %endfor
Traj_all(:,:,i) = traj;
U_all(:,:,i) = U;

end %endfor
