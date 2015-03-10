Acont=[ 0 1 0 0; 0 0 0 0; 0 0 0 1; 0 0 0 0];

%Diagonalization data
%M=SJS^-1; M=Acont here
%S=[0 0 1 0;0 0 0 1;1 0 0 0;0 1 0 0];
%J=[0 1 0 0;0 0 0 0;0 0 0 1;0 0 0 0];

% sampling time
h=0.02;

%fixed est and control times for now
Te=0.005; %0.044 is max fop h=0.25; 0.009 (tc=0.0001) is max with h=0.01
Tc=0.0001;


%integration for matrices B1,B2
syms T
Bcont=[0 0;1 0;0 0;0 1 ];

M1=int(expm(Acont*(h-T))*Bcont,T,0,Te+Tc);
B1=double(M1);

M2=int(expm(Acont*(h-T))*Bcont,T,Te+Tc,h);
B2=double(M2);

%A matrix using expm
A=expm(Acont*h);

%o/p matrix, only positions
C=[1 0 0 0;0 0 1 0];

