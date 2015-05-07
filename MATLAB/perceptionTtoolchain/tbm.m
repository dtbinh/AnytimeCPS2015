folder = '../../Data/Barrel';
images = dir([folder,'/*.png']);
load([folder,'/BarrelMasks.mat'])
testimages = [2,6,7,8,9,10,12,13,14];
mats = dir('trained*.mat');

for i=1:length(mats)
    GMs = load(mats(i).name);
	disp(mats(i).name);
    s=regexp(mats(i).name,'_NF\d_', 'match');
    s = s{1};
    nbfeatures = str2double(s(4));
    trainingimages = GMs.trainingimages;

    time_error = zeros(1,2);
    nbemptyframes  = 0;
    for m=testimages
        sprintf('Processing test image %d\n',m)
        imageName = [folder, '/',images(m).name];
        [elapsedtime,esterror, fie] = run_perception_module(imageName, GMs,bw(:,:,m), nbfeatures);
        if ~fie
            time_error(m,1) = elapsedtime;
            time_error(m,2) = esterror;
        end
	nbemptyframes = nbemptyframes + fie;
    end
    tecurve{i,1} = mats(i).name;
    tecurve{i,2}=mean(time_error);
    tecurve{i,3} = nbemptyframes;

    time_error = zeros(length(trainingimages),2);
    nbemptyframes  = 0;
    for m=trainingimages
        sprintf('Processing training image %d\n',m)
        imageName = [folder, '/',images(m).name];
        [elapsedtime,esterror, fie] = run_perception_module(imageName, GMs,bw(:,:,m), nbfeatures);
        if ~isinf(elapsedtime) && ~isinf(esterror)
            time_error(m,1) = elapsedtime;
            time_error(m,2) = esterror;
        end
	nbemptyframes = nbemptyframes + fie;
    end
    tecurve{i,4} = mean(time_error);
    tecurve{i,5} = nbemptyframes;
end
save('tecurve.mat','tecurve');
