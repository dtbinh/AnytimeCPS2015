function plot_path(map, path)
% PLOT_PATH Visualize a path through an environment
%   PLOT_PATH(map, path) creates a figure showing a path through the
%   environment.  path is an N-by-3 matrix where each row corresponds to the
%   (x, y, z) coordinates of one point along the path.
vx = zeros(4,6*map.nblocks); vy = zeros(4,6*map.nblocks); vz = zeros(4,6*map.nblocks);
%     faceMat = [1 2 3 1 1 5; 2 3 6 8 2 8; 3 6 5 4 7 6; 4 7 4 5 3 7];
 
C = zeros(4, 3);
C(1,:) = [1 0 0];
C(2,:) = [0 0 1];
C(3,:) = [1 0 1];
C(4,:) = [1 1 0];
for i = 1:map.nblocks
    lwrLimit = map.blocks(i,1:3);
    uprLimit = map.blocks(i,4:6);
        v    = [lwrLimit(1:3); ...
        uprLimit(1) lwrLimit(2) lwrLimit(3);...
        uprLimit(1) lwrLimit(2) uprLimit(3);...
        lwrLimit(1) lwrLimit(2) uprLimit(3);...
        lwrLimit(1) uprLimit(2) uprLimit(3);...
        uprLimit(1) uprLimit(2) uprLimit(3);...
        uprLimit(1) uprLimit(2) lwrLimit(3);...
        lwrLimit(1) uprLimit(2) lwrLimit(3)];
 
    startx = (i-4)*4+1;
    starty = (i-1)*6+1;
    vx(:,starty:starty+5) = [v(1,1) v(2,1) v(3,1) v(1,1) v(1,1) v(5,1); ...
                            v(2,1) v(3,1) v(6,1) v(8,1) v(2,1) v(8,1);...
                            v(3,1) v(6,1) v(5,1) v(5,1) v(7,1) v(7,1);...
                            v(4,1) v(7,1) v(4,1) v(4,1) v(8,1) v(6,1)];
    vy(:,starty:starty+5) = [v(1,2) v(2,2) v(3,2) v(1,2) v(1,2) v(5,2); ...
                            v(2,2) v(3,2) v(6,2) v(8,2) v(2,2) v(8,2);...
                            v(3,2) v(6,2) v(5,2) v(5,2) v(7,2) v(7,2);...
                            v(4,2) v(7,2) v(4,2) v(4,2) v(8,2) v(6,2)];
    vz(:,starty:starty+5) = [v(1,3) v(2,3) v(3,3) v(1,3) v(1,3) v(5,3); ...
                            v(2,3) v(3,3) v(6,3) v(8,3) v(2,3) v(8,3);...
                            v(3,3) v(6,3) v(5,3) v(5,3) v(7,3) v(7,3);...
                            v(4,3) v(7,3) v(4,3) v(4,3) v(8,3) v(6,3)];
end
% figure();
grid on; grid minor;
xlabel('x');
ylabel('y');
zlabel('z');
hold on;
data = map.boundary;
axis ([data(1) data(4) data(2) data(5) data(3) data(6)]);
axis equal
fill3(vx,vy,vz,[1 1 1]);
alpha(.24);
if (size(path))
    for i = 1:size(path,1)
    plot3(path(i,1), path(i,2),path(i,3), '*k', 'linewidth', 3);
    pause(0.05);
    hold on;
    end
end
end

