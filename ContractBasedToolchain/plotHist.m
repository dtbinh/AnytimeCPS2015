fileID = fopen('results/vehDetector_1.txt');
C = textscan(fileID,'%s %f %f %f %f');
fclose(fileID);

% plot histogram of quality
quality = C{2};
hist(quality, 20);

% plot histogram of time
time = C{5};
hist(time, 20);