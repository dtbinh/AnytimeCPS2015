% example 2
%(always not P1) AND (always not P2)
P1 = Polyhedron('A',1,'b',-2);
P2 = Polyhedron('A',-1,'b',-2);
[Params_P1] = WavSignedDistScalar(P1,xmin,xmax,dx,1);
[Params_P2] = WavSignedDistScalar(P2,xmin,xmax,dx,1);
pause;
close all;clc;
%plot(P1);hold all;plot(P2);

%% 
Ntrials = 10;

for i = 1:Ntrials

trajec(:,i) = 0.5*randn(10,1);
traj = trajec(:,i);

r_exact_P1 = -getRobustnessP(traj,P1,Params_P1,1);
r_approx_P1 = -getRobustnessP(traj,P1,Params_P1,0);

r_exact_P2 = -getRobustnessP(traj,P2,Params_P2,1);
r_approx_P2 = -getRobustnessP(traj,P2,Params_P2,0);

r_phi_exact = min(r_exact_P1,r_exact_P2);
r_phi_approx = SoftMin([r_approx_P1,r_approx_P2]);
err(i) = r_phi_exact-r_phi_approx;
end
[mean(abs(err)) std(abs(err))]