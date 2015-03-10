function[control,cost,Zn] = RMPC(A,A_lift,B_lift,A_lift_prev,B_lift_prev,B1,B2,K,Kx,Acl,F,xLo,u0,Dset,Dset_prev,Xorig,Cdelta,Horizon)

%MPC

Ln=(A_lift+B_lift*K)^(Horizon);

   cvx_begin quiet
  
   variable x_lift(size(A_lift,1),Horizon+1+1);
   variable u(size(B1,2),Horizon+1+1);
   variable state(size(A,1),(Horizon+1+1));
   
%     minimise sum(sum(abs(x_lift))) %1-norm min
minimise norm((state(:))) + .001 * norm(u(:))
   
   for j=0:Horizon+1
       
       if(j==0)
          x_lift(:,j+1) == (A_lift_prev)*xLo + B_lift_prev*u0; %dynamics
          state(:,j+1)==x_lift(1:size(A,1),j+1);         
          zero_set = Polyhedron(zeros(1,size(B2,2)));
          Y_j = Dset_prev*zero_set;
                    
          Xset1=minus(Xorig,Y_j);%tigten set
          
          Q=computeHRep(Xset1);
          Q.A*x_lift(:,j+1)<=Q.b; %tightened state constraints
          
       elseif(j<=Horizon)
          x_lift(:,j+1) == (A_lift)*x_lift(:,j) + B_lift*u(:,j);  
          state(:,j+1)==x_lift(1:size(A,1),j+1);
          
%           temp=zeros(size(x_lift,1),1); %to initialize temp, how do I get empty set here instead of zeros?
         Y_j=(Acl^(j-1))*F*A*Dset_prev;
          for i=2:j
              Y_j = plus(-(Acl)^(j-i)*B_lift*Kx*Dset,Y_j);
          end
          
%           Y_j=(Acl^(j-1))*F*A*Dset_prev + temp;

          Xset=minus(Xorig,Y_j);
          
          Q=computeHRep(Xset);
          Q.A*x_lift(:,j+1)<=Q.b; %tightened state constraints
          
       elseif(j==Horizon+1) %terminal constraint
           %put terminal set here
           x_lift(:,j+1) == (A_lift)*x_lift(:,j) + B_lift*u(:,j); 
           state(:,j+1)==x_lift(1:size(A,1),j+1);
           Zn=Cdelta-Ln*F*(-Dset+A*Dset_prev);
           Qterm=computeHRep(Zn);
           Qterm.A*x_lift(:,j+1)<=Qterm.b;

       end
       
       
       
   end
   
   cvx_end

   control=u(:,1);
   cost=norm((state(:))) + .001 * norm(u(:));