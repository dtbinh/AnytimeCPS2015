function Ks = dlqrft( A, B, N, Q, R, Qf )
%DLQRFT Finite-horizon discrete LQR for a linear system.
%   Ks = dlqrft( A, B, Q, R, Qf )
%
%Returns the sequence of feedback matrices Kj for LQR of discrete-time
%system: x[k+1] = A*x[k] + B*u[k], with cost function
%   J = sum_{k=0}^{N-1} (x[k]'*Q*x[k] + u[k]'*R*u[k]) + x[N]'*Qf*x[N]
%The feedback control is given by u[k] = K[k]*x[k], for k = 0,...,N-1.
%
%Q and Qf must be positive semi-definite, while R must be positive
%definite, although the function does NOT check these (you must make sure
%that they satisfy the conditions).
%
%Ks is a cell array of the matrices K's, where Ks{j+1} is K[j].
%
%Reference: <a
%href="http://www.stanford.edu/class/ee363/lectures/dlqr.pdf">Lecture on LQR by Prof. Stefen Boyd</a>.
%
% (C) 2014 by Truong X. Nghiem (nghiem@seas.upenn.edu)

Q = (Q + Q')/2;
R = (R + R')/2;
Qf = (Qf + Qf')/2;

Ks = cell(1, N);

% Some temporary values
BT = B';
AT = A';

% This is P[j]
P = Qf;  % P[N] = Qf

for j = N:-1:1  % t = N-1 down to 0
    % Compute K[t] = -(R+B'*P[t+1]*B)^{-1}*B'*P[t+1]*A
    BP = BT*P;  % B'*P[t+1]
    Ks{j} = -(R + BP*B) \ (BP*A);
    
    % Update P[t]
    % P[t] = Q + A'*P[t+1]*A - A'*P[t+1]*B*(R+B'*P[t+1]*B)^{-1}*B'*P[t+1]*A
    %      = Q + A'*P[t+1]*A + A'*P[t+1]*B*K[t]
    AP = AT*P;  % A'*P[t+1]
    P = Q + AP*A + AP*B*Ks{j};
end


end

