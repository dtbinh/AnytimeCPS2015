function [A,B1,B2] = plant_model(Acont,Bcont,Te,Tc,h)

%integration for matrices B1,B2
syms T;

M1=int(expm(Acont*(h-T))*Bcont,T,0,Te+Tc);
B1=double(M1);

M2=int(expm(Acont*(h-T))*Bcont,T,Te+Tc,h);
B2=double(M2);

%A matrix using expm
A=expm(Acont*h);
