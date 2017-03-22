function [Box] = FitBoxZf(ZfOrig,S)


setBig = ZfOrig;
setInsc = S.minHRep;


%dim = size(setBig.A,2);

% for what?
%posstep=[.1;.1;.1];
%velstep=[.1;.1;.1];
%inpstep=[deg2rad(1);deg2rad(1);.1];


%for cube 10
posstep = [.5;.5;.5];
velstep = [.5;.5;.5];
inpstep = [deg2rad(1);deg2rad(1);.5];


step=[posstep;velstep;posstep;velstep;inpstep;inpstep];
%setBig.A = [eye(dim);-eye(dim)];
%setBig.b = [ones(dim,1);ones(dim,1)];

%setInsc.A = [eye(dim);-eye(dim)];
%setInsc.b = *[ones(dim,1);ones(dim,1)];

%% M1
% 
% cvx_begin
% %cvx_solver gurobi
% variables x(dim)
% minimise 0
% 
% subject to
% setBig.A*x<=setBig.b;
% setInsc.A*x>=setInsc.b;
% 
% cvx_end

%% M2
%step = [.1 .1 .05]';
Orig = Polyhedron('A',setBig.A,'B',setBig.b);
Box = Polyhedron('A',setInsc.A,'B',setInsc.b);
%Sleft = Box-Orig;
btemp = Box.b;
 while(Orig<=Box || ~(Box<=Orig))
 btemp = btemp - [step];
 
 Box = Polyhedron('A',setInsc.A,'B',btemp);

 end