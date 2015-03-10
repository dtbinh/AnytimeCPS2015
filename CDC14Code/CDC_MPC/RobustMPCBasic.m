%straightforward robust MPC with fixed delay/error;



PlantModel2DTracking;

%
Tsim=10;
Horizon=10;

%variables for state/input
x_trajectory=zeros(size(A,1),Tsim);
u_applied=zeros(size(B1,2),Tsim);
x_trajectory_actual=zeros(size(A,1),Tsim);

%disturbance set (inf norm bound)
norm_e_inf=1 ; %bound
disturbance.A=[eye(size(A,1));-eye(size(A,1))];
disturbance.b=norm_e_inf*[ones(size(A,1),1);ones(size(A,1),1)];

Dset=Polyhedron('A',disturbance.A,'B',disturbance.b);

%Feasible set (initial) of states
x_max=100*[2;2;2;2];
x_min=100*[-2;-2;-2;-2];

feasible.A=[eye(size(A,1));-eye(size(A,1))];
feasible.b=[x_max;-x_min];

Xset=Polyhedron('A',feasible.A,'B',feasible.b);
Xorig=Xset;

%Lifted representation of system
A_lift=[A B1;zeros(size(B1,2),size(B1,2)+size(A,2))];
B_lift=[B2;eye(size(B2,2))];


[K]=-dlqr(A_lift,B_lift,eye(size(A_lift,1)),eye(size(B_lift,2)),zeros(size(A_lift,1),size(B_lift,2))); %A+BK is stable in DT sense

Acl=(A_lift+B_lift*K);
Acl=Acl(1:size(A,1),1:size(A,2));

%note: Disturbance, feasibility only on original states, not lifted system,
%so check constraints accordingly

%initial states
x0=[10;0;10;0];
u0=zeros(size(B2,2),1);
uminus1=zeros(size(B2,2),1);
xLo=[x0;u0];
c0=zeros(size(B2,2),1);
L=eye(size(A));
L0=L;
xtrue=xLo;
%begin MPC


for t=1:Tsim %all time
   clc; 
   %inside horizon
   
   cvx_begin quiet
   
   variable x_lift(size(A_lift,1),Horizon);
   variable u(size(B1,2),Horizon);
   variable c(size(B1,2),Horizon); %u=Kx+c
   
   minimise sum(sum(abs(x_lift)))+sum(sum(abs(u))) %1-norm min
   
   for i=1:Horizon
       clc;
       if(i==1)
          x_lift(:,i) == (A_lift + B_lift*K)*xLo + B_lift*c0; %dynamics
          W = Dset +(-A)*Dset; %dist set W
          Xset=minus(Xorig,L0*W);%tigten set
          Xorig=Xset; %new Xorig for next MPC horizon
          L=Acl*L0; %update L
          Q=computeHRep(Xset);
          Q.A*x_lift(1:size(A,1),i)<=Q.b; %tightened state constraints
          
       else
          x_lift(:,i) == (A_lift + B_lift*K)*x_lift(:,i-1) + B_lift*c(:,i-1);  
          u(:,i-1) == K*x_lift(:,i-1) + c(:,i-1); 
          W = Dset +(-A)*Dset; %dist set W
          Xset=minus(Xset,L*W);
          L=Acl*L;  
          Q=computeHRep(Xset);
          Q.A*x_lift(1:size(A,1),i)<=Q.b; %tightened state constraints
       end
       
       
       
   end
   cvx_end 
   %apply and store/update
   xtrue=(A_lift+B_lift*K)*xtrue + B_lift*c(:,1); %true dynamaics
   
   %update
   %xLo=x_lift(:,1);
   xLo=xtrue + ([1-2*rand(size(A,1),1);zeros(size(B1,2),1)])*norm_e_inf; %corrupt estimate (only original states)
   c0=c(:,1);
   
   %store
   x_trajectory(:,t)=xLo(1:size(A,1)); 
   x_trajectory_actual=xtrue(1:size(A,1),1);
   u_applied(:,t)=u(:,1); 
    
    
    
    
    
    
end

% x_trajectory(:,t+1:end)=x_lift(1:size(A,1),2:end);
% u_applied(:,t+1:end)=u(:,2:end);
%compute actual trajectory as well, do it

%cost
cost=0;
for i=1:Tsim
   
    cost=cost + norm(x_trajectory(:,i)) + norm(u_applied(:,i));
    
    
    
end








