% Stanley Bak
% Aug 21, 2014
% Testing for a violation of the lyapunov potential found by Z3

%%% run a simulation
start = [0.125, 0.75, 0, -0.224420905];
[t, y] = ode45('safety_controller_dynamics', [0,0.5], start);

% potential matrix, we will plot when x^t * P * x  < 1
P = [
    1.0520    1.2082    0.2580    0.1988 ;
    1.2082   33.9334    4.6631    4.0269 ;
    0.2580    4.6631    2.2108    1.0090 ;
    0.1988    4.0269    1.0090    0.8424 ];


len = size(y,1);

pots = zeros(len,1);

for i = 1:len
   state = y(i,:);
   
   % column 2 and 3 swapped
   stateSwapped = [state(1) ; state(3) ; state(2) ; state(4)];
   
   pot = stateSwapped.' * P * stateSwapped;
    
   pots(i) = pot;
    
end

OH OK, so just a Z3 violation because normal vector is for circle, not ellipse!

clf
plot(t, pots, 'k-');