% Stanley Bak
% 4-28-2014
% Plot where the potential is < 1

% step size in the plot
step = 0.05;

% potential matrix, we will plot when x^t * P * x  < 1
P = [
    1.0520    1.2082    0.2580    0.1988 ;
    1.2082   33.9334    4.6631    4.0269 ;
    0.2580    4.6631    2.2108    1.0090 ;
    0.1988    4.0269    1.0090    0.8424 ];

%figure
clf
hold on

for y=-2:step:2
  for x=-0.4:step:0.4
    fixed_position = 0.125;
    fixed_vel = 0.75;
      
    state = [0 ; x ; 0 ; y]; % notice swapping of column 2 and 3
    
    potential = state.' * P * state;
    
    color = 'r*';
    
    if (potential < 1)
        color = 'b*';
    end
    
    %xrad = x * 180 / pi;
    %yrad = y * 180 / pi;
        
    plot(x, y, color)
        
  end
end

hold off

%title('Potential < 1')
%xlabel('Position')
%ylabel('Velocity')

