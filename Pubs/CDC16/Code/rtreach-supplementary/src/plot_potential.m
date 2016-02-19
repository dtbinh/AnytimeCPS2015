% Stanley Bak
% 4-28-2014
% Plot where the potential is < 1

% step size in the plot
step = 0.025;

% potential matrix, we will plot when x^t * P * x  < 1
P = [
    1.0520    1.2082    0.2580    0.1988 ;
    1.2082   33.9334    4.6631    4.0269 ;
    0.2580    4.6631    2.2108    1.0090 ;
    0.1988    4.0269    1.0090    0.8424 ];

%figure
clf
hold on

for y=-1:step:1
  for x=-1.25:step:1.25
    state = [x ; 0 ; y ; 0]; % notice swapping of column 2 and 3
    
    potential = state.' * P * state;
    
    color = 'r*';
    
    if (potential < 1)
        color = 'b*';
    end
        
    plot(x, y, color)
        
  end
end

hold off

%title('Potential < 1')
%xlabel('Position')
%ylabel('Velocity')

