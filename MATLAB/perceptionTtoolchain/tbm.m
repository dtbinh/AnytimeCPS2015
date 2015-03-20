folder = '../../Data/Barrel';
images = dir([folder,'/*.png']);
load([folder,'/BarrelMasks.mat'])

i=0;
mats = dir('*.mat');
for matstr = mats
    GMs = load(matstr.name);
    i=i+1;
    time_error = zeros(GMs.knobs.nbimages,2);
    for m=1:GMs.knobs.nbimages
        imageName = [folder, '/',images(m).name];
        [time_error(m,1), time_error(m,2)] = run_perception_module(imageName, GMs,bw(:,:,m));
    end
    tecurve{i,1} = matstr.name;
    tecurve{i,2}=mean(time_error);
end