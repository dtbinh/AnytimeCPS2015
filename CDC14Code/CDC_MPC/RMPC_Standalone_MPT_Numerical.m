%straightforward robust MPC with fixed delay/error;



PlantModelNumerical;

%
Tsim=100;
Horizon=7; %3 works for h=0.25

%variables for state/input
x_trajectory=zeros(size(A,1),Tsim);
u_applied=zeros(size(B1,2),Tsim);
x_trajectory_actual=zeros(size(A,1),Tsim);

%disturbance set (inf norm bound)
norm_e_inf=1; %bound
disturbance.A=[eye(size(A,1));-eye(size(A,1))];
disturbance.b=norm_e_inf*[ones(size(A,1),1);ones(size(A,1),1)];

Dset=Polyhedron('A',disturbance.A,'B',disturbance.b);
Dset_prev=Dset; %hardwire for now, we are dealing with only one mode

%Feasible set (initial) of states and inputs
x_max=100*ones(size(A,1),1);
x_min=-100*ones(size(A,1),1);

feasible.A=[eye(size(A,1));-eye(size(A,1))];
feasible.b=[x_max;-x_min];

Xset=Polyhedron('A',feasible.A,'B',feasible.b); 


u_max=[100]*ones(size(B2,2),1);
u_min=[-100]*ones(size(B2,2),1);
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
  [K]=-1*dlqr(A_lift,B_lift,1*eye(size(A_lift,1)),1*eye(size(B_lift,2)),zeros(size(A_lift,1),size(B_lift,2))); %A+BK is stable in DT sense

%place
% [K,~,tol]=place(A_lift,B_lift,[0 0.1 0.3 .15 .2 1]')
% K=-K;
%[K,~,tol]=place(A_lift,B_lift,[0.01 0.1 0 0]');
 %[K,~,tol]=place(A_lift,B_lift,[0.75 .92]');
 % K=-K;


Acl=(A_lift+B_lift*K); %same as phi

Kx=K(:,1:size(A,1));


%initial states
x0=[10]*ones(size(A,1),1);
u0=0*ones(size(B2,2),1);
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
    
   %inside horizon
   
   cvx_begin quiet
  
   variable x_lift(size(A_lift,1),Horizon+1);
   variable u(size(B1,2),Horizon+1);
   variable state(size(A,1),(Horizon+1));
   
%     minimise sum(sum(abs(x_lift))) %1-norm min
minimise norm((state(:))) + .001 * norm(u(:))
   
   for i=1:Horizon+1
       
       if(i==1)
          x_lift(:,i) == (A_lift)*xLo + B_lift*u0; %dynamics
          state(:,i)==x_lift(1:size(A,1),i);         
          zero_set = Polyhedron(zeros(1,size(B2,2)));
          Y_i = Dset*zero_set;
                    
          Xset1=minus(Xorig,Y_i);%tigten set
          
          Q=computeHRep(Xset1);
          Q.A*x_lift(:,i)<=Q.b; %tightened state constraints
          
       elseif(i<=Horizon)
          x_lift(:,i) == (A_lift)*x_lift(:,i-1) + B_lift*u(:,i-1);  
          state(:,i)==x_lift(1:size(A,1),i);
          
          temp=zeros(size(x_lift,1),1); %to initialize temp, how do I get empty set here instead of zeros?
         
          for ii=2:i-1
              temp = plus(-(Acl)^(i-1-ii)*B_lift*Kx*Dset,temp);
          end
          
          Y_i=(Acl^(i-1-1))*F*A*Dset_prev + temp;

          Xset=minus(Xorig,Y_i);
          
          Q=computeHRep(Xset);
          Q.A*x_lift(:,i)<=Q.b; %tightened state constraints
          
       elseif(i==Horizon+1) %terminal constraint
           %put terminal set here
           x_lift(:,i) == (A_lift)*x_lift(:,i-1) + B_lift*u(:,i-1); 
           state(:,i)==x_lift(1:size(A,1),i);
           Zn=Cdelta-Ln*F*(-Dset+A*Dset_prev);
           Qterm=computeHRep(Zn);
           Qterm.A*x_lift(:,i)<=Qterm.b;

       end
       
       
       
   end
   cvx_end 
   %apply and store/update
   xtrue=(A_lift)*xtrue + B_lift*u(:,1); %true dynamics
   
   %update
   
   xLo=xtrue + ([1-2*rand(size(A,1),1);zeros(size(B1,2),1)])*norm_e_inf; %corrupt estimate (only original states)
   u0=u(:,1);
   
   [[xtrue;u0] [xLo;u0]]
   
   %store
   x_trajectory(:,t)=xLo(1:size(A,1)); %estimates used
   x_trajectory_actual(:,t)=xtrue(1:size(A,1),1); %actual pos/vel
   u_applied(:,t)=u(:,1); %applied input
    
     
    
end
x_trajectory=[x0 x_trajectory]; %append initial state
x_trajectory_actual=[x0 x_trajectory];


%cost
cost=0;
for i=1:Tsim
   
    cost=cost + norm(x_trajectory(:,i)) + norm(u_applied(:,i));
    
    
    
end








