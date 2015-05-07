folder = '../../Data/Barrel';
images = dir([folder,'/*.png']);
load([folder,'/BarrelMasks.mat'])
trainingimages = [1,3,4,5,11];
testimages = [2,6,7,8,9,10,12,13,14];
mats = dir('trained*.mat');

for i=1:length(mats)
    GMs = load(mats(i).name);
	disp(mats(i).name);
    s=regexp(mats(i).name,'_NF\d_', 'match');
    s = s{1};
    nbfeatures = str2double(s(4));

    time_error = zeros(1,2);
    for m=testimages
        sprintf('Processing test image %d\n',m)
        imageName = [folder, '/',images(m).name];
        [elapsedtime,esterror] = run_perception_module(imageName, GMs,bw(:,:,m), nbfeatures);
        if ~isinf(elapsedtime) && ~isinf(esterror)
            time_error(m,1) = elapsedtime;
            time_error(m,2) = esterror;
        end
    end
    tecurve{i,1} = mats(i).name;
    tecurve{i,2}=mean(time_error);

    time_error = zeros(length(trainingimages),2);
    for m=trainingimages
        sprintf('Processing training image %d\n',m)
        imageName = [folder, '/',images(m).name];
        [elapsedtime,esterror] = run_perception_module(imageName, GMs,bw(:,:,m), nbfeatures);
        if ~isinf(elapsedtime) && ~isinf(esterror)
            time_error(m,1) = elapsedtime;
            time_error(m,2) = esterror;
        end
    end
    tecurve{i,3}=mean(time_error);
end
save('tecurve.mat','tecurve');
