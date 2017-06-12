%% Visualize Map
clc;
clear all;
close all;

% map = load_map('sample_maps/map1.txt',.1,.1,.3);
map = load_map('sample_maps/map2.txt', .5, .5, 0);
boundary = map.boundary;
valid = [0.0  -1.0 2.0; 
         3.0  17.0 4.0; 
         0.0  -5.0 0.5;
         8.0  18.0 6.0];
collision = [0.0 2.0 1.0; 
             3.0 18.5 4.5];
% prod(size(map))
%%
start = [0 2 0];
stop  = [9 9 7];

% start = [0.0  -4.9 0.2];
% stop  = [8.0  18.0 3.0];
% start = [0.0  0 0.2];
% stop  = [8.0  8.0 8.0];
% start = [0  3 6];
% stop  = [20  5 6];

path_d = dijkstra(map, start, stop);
path_a = dijkstra(map, start, stop, true);

%%

plot_path(map, path_d);
axis([boundary(1) boundary(4) boundary(2) boundary(5) boundary(3) boundary(6)])
xlabel('x');
ylabel('y');
zlabel('z');

plot_path(map, path_a);
axis([boundary(1) boundary(4) boundary(2) boundary(5) boundary(3) boundary(6)])
xlabel('x');
ylabel('y');
zlabel('z');
