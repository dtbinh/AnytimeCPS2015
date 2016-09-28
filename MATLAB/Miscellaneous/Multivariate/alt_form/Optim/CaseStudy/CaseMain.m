% case study main

%% sys dynamics
g = 9.8;
m = 0.5;
h = 1/5; %5Hz

tempA = sparse(6,6);
tempA(1:3,4:6) = eye(3);
tempB = sparse(6,3);
tempB(4,1) = g;
tempB(5,2) = -g;
tempB(6,3) = 1/m;
sys_c = ss(tempA,tempB,eye(6),zeros(6,3));
sys_d = c2d(sys_c,h);
%% viz some trajectories for sanity check
x = zeros(6,1);
Tmax = 100;
X = zeros(6,Tmax);
for t = 1:Tmax
    u=[randn(2,1);1];
    x = sys_d.A*x + sys_d.B*u;
    X(:,t) = x;
    
end
plot3(X(1,:),X(2,:),X(3,:),'o');grid on
axis('square');
xlabel('x');ylabel('y');zlabel('z');

%% describe sets and their signed dist approxs
xmin = -7;
xmax = 7;
dx = 0.1;

NoFly = Polyhedron('lb',[-1 -1 0],'ub',[1 1 5]);
Terminal = Polyhedron('lb',[3 3 0],'ub',[4 4 1]);
Feasible = Polyhedron('lb',[xmin*ones(1,2) 0],'ub',xmax*ones(1,3));
Zone1 = Polyhedron('lb',[xmin*ones(1,2) 0],'ub',[0 xmax xmax]);
Zone2 = Polyhedron('lb',[0 xmin 0],'ub',xmax*ones(1,3));
wp = cell(4,1);

close all;
plot(Feasible,'Color','gray','Alpha',0.1);
hold on;
plot(Zone1,'Color','orange','Alpha',0.2);
hold on;
plot(Zone2,'Color','black','Alpha',0.2);
hold on;
plot(NoFly);
hold on;
plot(Terminal,'Color','green');
xlabel('x');ylabel('y');

%%
dim = size(Feasible.A,2);
grid_x = xmin:dx:xmax;
dist_array_xy = zeros(numel(grid_x)*ones(1,dim));

optional.k_min = -5;
optional.k_max = +5;
optional.j_min = 0;
optional.j_max = 0; %2 works well in R2
E_dash = double(getcondvects(dim));

genCode =1;
getCoeffs = 1;
if(genCode)
    cfg=coder.config('mex');
        
    %for get coeffs (grid_x,dist_array_xy,dx,j_min,j_max,k_min,k_max,E_dash,0);
    arg_ins = {coder.typeof(grid_x),coder.typeof(dist_array_xy),coder.typeof(dx),...
       coder.typeof(optional.j_min),coder.typeof(optional.j_max),...
       coder.typeof(optional.k_min), coder.typeof(optional.k_max), coder.typeof(E_dash),...
       coder.typeof(0)};
    codegen -config cfg alt_getCoefficientsVector_genable -report -args arg_ins
        
end
%%
optional.filename = [];
if(getCoeffs)
   parfor i=1:4
       if(i==1)
    %optional.savefile = 'NoFly_Params.mat'; 
   wavparams_NoFly = WavSignedDistVector_Rn(NoFly,xmin,xmax,dx,0);%,optional);
  wp{i} = wavparams_NoFly;	
       end
        if(i==2)
   %optional.savefile = 'Terminal_Params.mat';
   wavparams_Terminal = WavSignedDistVector_Rn(Terminal,xmin,xmax,dx,0);%,optional);
   wp{i} = wavparams_Terminal;	
        end
        if(i==3)
        wavparams_Zone1 = WavSignedDistVector_Rn(Zone1,xmin,xmax,dx,0);%,optional);    
	wp{i} = wavparams_Zone1;
        end
        if(i==4)
        wavparams_Zone2 = WavSignedDistVector_Rn(Zone2,xmin,xmax,dx,0);%,optional);    
	wp{i} = wavparams_Zone2;
        end
   end
end
save('ControllerData_fine.mat','wp');
%save('Controller data','wavparams_NoFly','wavparams_Terminal','wavparams_Zone1',...
%    'wavparams_Zone2');
