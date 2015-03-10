function[control,cost,Zf] = RMPC_compute(A,A_lift,B_lift,A_lift_prev,B_lift_prev,B1,B2,K,Kx,Acl,F,xLo,u0,Dset,Dset_prev,Xorig,Cdelta,eps,eps_k,Horizon)

%MPC
N=Horizon;
Ln=(A_lift+B_lift*K)^(Horizon);

   cvx_begin quiet
  
   variable x_lift(size(A_lift,1),Horizon+1+1);
   variable u(size(B1,2),Horizon+1+1);
   variable state(size(A,1),(Horizon+1+1));
   
%     minimise sum(sum(abs(x_lift))) %1-norm min
% minimise norm(state(:)) + 0.001 * norm(u(:))
  minimise quad_over_lin(state(:),1)+0.1*quad_over_lin(u(:),1) 
   for j=0:Horizon+1
       
       if(j==0)
          x_lift(:,j+1) == (A_lift_prev)*xLo + B_lift_prev*u0; %dynamics
          state(:,j+1)==x_lift(1:size(A,1),j+1);         
%           zero_set = Polyhedron(zeros(1,size(B2,2)));
%           Y_j = Dset_prev*zero_set;
%                     
%           Xset1=minus(Xorig,Y_j);%tigten set
          [Q.A Q.b]=getZj(A,Acl,B_lift,Kx,F,Xorig,N,j,eps_k,eps);
%           Q=computeHRep(Xset1);
          Test=Polyhedron('A',Q.A,'b',Q.b);
          %test if empty, if yes, screwed 
            if(Test.isEmptySet==1)
             exception = MException('Zj:empty', ...
            'Zj empty at j= %d',j);
            throw(exception);
            end
          
          Q.A*x_lift(:,j+1)<=Q.b; %tightened state constraints
          
       elseif(j<=Horizon)
          x_lift(:,j+1) == (A_lift)*x_lift(:,j) + B_lift*u(:,j);  
          state(:,j+1)==x_lift(1:size(A,1),j+1);
          
%           temp=zeros(size(x_lift,1),1); %to initialize temp, how do I get empty set here instead of zeros?
%          Y_j=(Acl^(j-1))*F*A*Dset_prev;
%           for i=2:j
%               Y_j = plus(-(Acl)^(j-i)*B_lift*Kx*Dset,Y_j);
%           end
          


%           Xset=minus(Xorig,Y_j);
%           Xset=getZj(A,Acl,B_lift,Kx,F,Xorig,N,j,eps_k,eps);
          [Q.A Q.b]=getZj(A,Acl,B_lift,Kx,F,Xorig,N,j,eps_k,eps);
%           Q=computeHRep(Xset);
           Test=Polyhedron('A',Q.A,'b',Q.b);
          %test if empty, if yes, screwed 
            if(Test.isEmptySet==1)
             exception = MException('Zj:empty', ...
            'Zj empty at j= %d',j);
            throw(exception);
            end 



          Q.A*x_lift(:,j+1)<=Q.b; %tightened state constraints
          
       elseif(j==Horizon+1) %terminal constraint
           %put terminal set here
           x_lift(:,j+1) == (A_lift)*x_lift(:,j) + B_lift*u(:,j); 
           state(:,j+1)==x_lift(1:size(A,1),j+1);
           
           
           Zf=Cdelta-Ln*F*(-Dset+A*Dset_prev);
           
           if(Zf.isEmptySet==1)
             exception = MException('Zf:empty', ...
            'Zf empty at %d',j);
            throw(exception);
           end 
           
           
           
           Qterm=computeHRep(Zf);
           Qterm.minHRep;
           Qterm.A*x_lift(:,j+1)<=Qterm.b;

       end
       
       
       
   end
   
   cvx_end

   control=u(:,1);
%    cost=norm((state(:))) + 0.001 * norm(u(:));
cost=quad_over_lin(state(:),1)+0.1*quad_over_lin(u(:),1) ;