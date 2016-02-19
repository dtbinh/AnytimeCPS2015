function [ safe ] = checkSimulation( state, simTime )

P = [
    1.0520    1.2082    0.2580    0.1988 ;
    1.2082   33.9334    4.6631    4.0269 ;
    0.2580    4.6631    2.2108    1.0090 ;
    0.1988    4.0269    1.0090    0.8424 ];

time = [0 simTime];

[~, y] = ode45('safety_controller_dynamics', time, state);

safe = true;

len = size(y(:,1));

% check if we violated the constraints
for i = 1:len
   x = y(i,1); 
   vel = y(i,2);
   theta = y(i,3);
   
   if (x < -1 || x > 1 ...
       || vel < -1 || vel > 1 ...
       || theta < degtorad(-15) || theta > degtorad(15))
    safe = false;
    break;
   end
end

% check if the final state is safe
if (safe)
    lastState = y(end,:);

    state_swapped = [lastState(1) ; lastState(3) ; lastState(2) ; lastState(4)]; 

    potential = state_swapped.' * P * state_swapped;

    if (potential > 1)
        safe = false;
    end
end

end

