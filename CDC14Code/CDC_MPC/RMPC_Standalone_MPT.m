%straightforward robust MPC with fixed delay/error;



PlantModel2DTracking;

%
Tsim=10;
Horizon=1; %3 works for h=0.25

%variables for state/input
x_trajectory=zeros(size(A,1),Tsim);
u_applied=zeros(size(B1,2),Tsim);
x_trajectory_actual=zeros(size(A,1),Tsim);

%disturbance set (inf norm bound)
norm_e_inf=.1 ; %bound
disturbance.A=[eye(size(A,1));-eye(size(A,1))];
disturbance.b=norm_e_inf*[ones(size(A,1),1);ones(size(A,1),1)];

Dset=Polyhedron('A',disturbance.A,'B',disturbance.b);
Dset_prev=Dset; %hardwire for now, we are dealing with only one mode

%Feasible set (initial) of states and inputs
x_max=100*[2;2;2;2];
x_min=100*[-2;-2;-2;-2];

feasible.A=[eye(size(A,1));-eye(size(A,1))];
feasible.b=[x_max;-x_min];

Xset=Polyhedron('A',feasible.A,'B',feasible.b); 


u_max=[10;10];
u_min=[-10;-10];
feasible.Ainput=[eye(size(B1,2));-eye(size(B1,2))];
feasible.Binput=[u_max;-u_min];

Uset=Polyhedron('A',feasible.Ainput,'B',feasible.Binput);


Xorig=Xset*Uset; %the big Z set at the start


InputSet=Uset; % variables for the terminal set constraints
LiftStateSet=Xorig;

%Lifted representation of system
A_lift=[A B1;zeros(size(B1,2),size(B1,2)+size(A,2))];
B_lift=[B2;eye(size(B2,2))];
F=[eye(size(A,2));zeros(size(B1,2),size(A,2))];

%lqr
[K]=-dlqr(A_lift,B_lift,1*eye(size(A_lift,1)),1*eye(size(B_lift,2)),zeros(size(A_lift,1),size(B_lift,2))); %A+BK is stable in DT sense

%place
% [K,~,tol]=place(A_lift,B_lift,[0 0.1 0.3 .15 .2 1]')
% K=-K;

Acl=(A_lift+B_lift*K); %same as phi

Kx=K(:,1:size(A,1));

% Acl=Acl(1:size(A,1),1:size(A,2));

%note: Disturbance, feasibility only on original states, not lifted system,
%so check constraints accordingly

%initial states
x0=[10;0;10;0];
u0=zeros(size(B2,2),1);
uminus1=zeros(size(B2,2),1);
xLo=[x0;u0];
c0=zeros(size(B2,2),1);
L=eye(size(A,2)+size(B2,2));
L0=L;
xtrue=xLo;
%begin MPC

clear Xset;

%get robust control inv set
GetTerminalSet;
for t=1:Tsim %all time
   clc; 
   %inside horizon
   
   cvx_begin quiet
  
   variable x_lift(size(A_lift,1),Horizon+1);
   variable u(size(B1,2),Horizon);
%    variable c(size(B1,2),Horizon); %u=Kx+c
   
   minimise sum(sum(abs(x_lift)))+sum(sum(abs(u))) %1-norm min
   
   for i=1:Horizon+1
       clc;
       if(i==1)
          x_lift(:,i) == (A_lift)*xLo + B_lift*u0; %dynamics
          
          zero_set = Polyhedron(zeros(1,size(B2,2)));
          Y_i = Dset*zero_set;
          %Y_i=F*Dset_prev;
          
          Xset=minus(Xorig,Y_i);%tigten set
          Xorig=Xset; %new Xorig for next MPC horizon
          
          Q=computeHRep(Xset);
          Q.A*x_lift(:,i)<=Q.b; %tightened state constraints
          
       elseif(i<=Horizon)
          x_lift(:,i) == (A_lift)*x_lift(:,i-1) + B_lift*u(:,i-1);  
          %u(:,i-1) == K*x_lift(:,i-1) + c(:,i-1); 
          %W = -Dset +(A)*Dset_prev; %dist set W
          %Wlift=F*W;
          
          % compute Yj, Yi here
          temp=zeros(size(x_lift,1),1); %to initialize temp, how do I get empty set here instead of zeros?
          Y_i=(Acl^(i-1-1))*F*A*Dset_prev;
          for ii=2:i-1
              Y_i = Y_i + plus(((-Acl)^(i-1-ii))*B_lift*Kx*Dset_prev,temp);
          end
          
%           Y_i=(Acl^(i-1-1))*F*A*Dset_prev + temp;
          
          Xset=minus(Xset,Y_i);
          
          Q=computeHRep(Xset);
          Q.A*x_lift(:,i)<=Q.b; %tightened state constraints
          
       elseif(i==Horizon+1) %terminal constraint
           %put terminal set here
           x_lift(:,i) == (A_lift)*x_lift(:,i-1) + B_lift*u(:,i-1); 
           Zn=Cdelta-Ln*F*(-Dset+A*Dset_prev);
           Qterm=computeHRep(Zn);
           Qterm.A*x_lift(:,i)<=Qterm.b;
           
       end
       
       
       
   end
   cvx_end 
   %apply and store/update
   xtrue=(A_lift+B_lift*K)*xtrue + B_lift*u(:,1); %true dynamaics
   
   %update
   %xLo=x_lift(:,1);
   xLo=xtrue + ([1-2*rand(size(A,1),1);zeros(size(B1,2),1)])*norm_e_inf; %corrupt estimate (only original states)
   u0=u(:,1);
   
   %store
   x_trajectory(:,t)=xLo(1:size(A,1)); %estimates used
   x_trajectory_actual(:,t)=xtrue(1:size(A,1),1); %actual pos/vel
   u_applied(:,t)=u(:,1); %applied input
    
    
    
    
    
    
end



%cost
cost=0;
for i=1:Tsim
   
    cost=cost + norm(x_trajectory(:,i)) + norm(u_applied(:,i));
    
    
    
end








