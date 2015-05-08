folder = '../../Data/Barrel';
images = dir([folder,'/*.png']);
testimages = [2,6,7:10,12:50];
mats = dir('trained*.mat');
maskfolder = '../../OpenCV/ObjDetector/Images/Train/Masks';
masks = dir([maskfolder, '/*.png']);

for i=1:length(mats)
    GMs = load(mats(i).name);
    disp(mats(i).name);
    s=regexp(mats(i).name,'_NF\d_', 'match');
    s = s{1};
    nbfeatures = str2double(s(4));
    trainingimages = GMs.trainingimages;
    shape_classifier = 'GMM';%GMs.shape_classifier;
    
    time_error = zeros(1,2);
    nbemptyframes  = 0;
    for m=testimages
        sprintf('Processing test image %d\n',m)
        [I,M]= read_img_and_mask(images(m).name, masks,maskfolder, folder);
        if isempty(M)
            sprintf('Skipping image %s because it has no matching mask\n',images(m).name);
            continue
        end
        
        [elapsedtime,esterror, fie] = run_perception_module([folder, '/',images(m).name], GMs,M, nbfeatures, shape_classifier);
        if ~fie
            time_error(m,1) = elapsedtime;
            time_error(m,2) = esterror;
        end
        nbemptyframes = nbemptyframes + fie;
    end
    tecurve{i,1} = mats(i).name;
    tecurve{i,2} = mean(time_error);
    tecurve{i,3} = nbemptyframes;
    
    time_error = zeros(length(trainingimages),2);
    nbemptyframes  = 0;
    for m=trainingimages
        sprintf('Processing training image %d\n',m)
        [I,M]= read_img_and_mask(images(m).name, masks,maskfolder);
        if isempty(M)
            sprintf('Skipping image %s because it has no matching mask\n',images(m).name);
            continue
        end
        [elapsedtime,esterror, fie] = run_perception_module([folder, '/',images(m).name], GMs, M, nbfeatures, shape_classifier);
        if ~fie
            time_error(m,1) = elapsedtime;
            time_error(m,2) = esterror;
        end
        nbemptyframes = nbemptyframes + fie;
    end
    tecurve{i,4} = mean(time_error);
    tecurve{i,5} = nbemptyframes;
end
save('tecurve.mat','tecurve');
