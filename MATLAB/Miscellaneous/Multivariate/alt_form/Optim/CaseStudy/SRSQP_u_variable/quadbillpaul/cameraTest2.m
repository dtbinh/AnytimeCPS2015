%% Simulate Follower Model
clc;
close all;
clear all;

%% Define Variables
fiducialHeight = 0.1; % m
xBound = 12;
yBound = 12;
zBound = 12;
scrsz = get(0, 'ScreenSize');
totalTime = 5; % seconds
dT = 0.1; % seconds
figHeight = 400;
figWidth = 400;
fig1 = figure('Position',[100,200,figWidth,figHeight]);
fig2 = figure('Position',[700,200,figWidth,figHeight]);

%% Initialize Quadrotor Units
% quad 1 [X,Y,Z,ROLL,PITCH,YAW,ARMLENGTH]
quad1 = Quad(8,5,5.5,0,-10,0,(9/12));
quad1 = quad1.setXVel(1,1);
quad1 = quad1.setZVel(0.2,0.2);
% quad 2
quad2 = Quad(2,5,5,10,0,0,(9/12));

%% MAIN LOOP
for t = 0:dT:totalTime

    % -- PERSPECTIVE VIEW --
    figure(fig1);
    clf;
    hold on;
    % plot quad1
    quad1.drawArms();
    quad1.drawBody();
    quad1.drawFiducial();
    % plot quad2
    quad2.drawArms();
    quad2.drawBody();
    quad2.drawFiducial();
    quad2.drawCamera();
    
    set(gca, 'CameraPosition', [10 10 10], 'CameraTarget', [0 0 0]);
    axis([0 xBound 0 yBound 0 zBound]);
    xlabel('X');ylabel('Y');zlabel('Z');
    title('Perspective View');
    grid on;
    colormap gray
    
    % -- CAMERA VIEW --
    figure(fig2);
    clf;
    hold on;
    % plot quad1
    quad1.drawArms();
    quad1.drawBody();
    quad1.drawFiducial();
    
    camva(quad2.FOV);
    campos('manual');
    campos([quad2.x quad2.y quad2.z]);
    camtarget(quad2.cameraVector());
    camup(quad2.cameraUpVector());
    title('Camera View');
    xlabel('X');ylabel('Y');zlabel('Z');
    axis([0 xBound 0 yBound 0 zBound]);
    colormap gray
    

    % -- VISION PROCESSING FOR FOLLOWER --
    print(fig2, '-r80', '-dtiff', 'tempImage.tif');
    im = imread('tempImage.tif');
    redImage = imred(im);
    figure(3);
    RLL = bwlabel(redImage,8);
    imshow(RLL);
    % Use regionprops to compute the properties of the blobs.
    stats = regionprops(RLL,'Area','Centroid','MajorAxisLength','MinorAxisLength','Perimeter');
    % calculate circle height in pixels
    height_pix = stats.MinorAxisLength;
    %calculate distance from camera to the image plane
    distance = (fiducialHeight*figHeight)/ (2*height_pix*tan(quad2.FOV*pi/180));
    disp(distance);

    % -- UPDATE ALL PARAMETERS --
    quad1 = quad1.update(dT);
    quad2 = quad2.update(dT);
end

