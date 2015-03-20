folder = '../../Data/Barrel';
images = dir([folder,'/*.png']);
load([folder,'/BarrelMasks.mat'])

mats = dir('*.mat');
for i=1:length(mats)
    GMs = load(mats(i).name);
    s=regexp(mats(i).name,'_NF\d_', 'match');
    nbfeatures = str2double(s(4));
    time_error = zeros(GMs.knobs.nbimages,2);
    for m=1:3%GMs.knobs.nbimages
        imageName = [folder, '/',images(m).name];
        [time_error(m,1), time_error(m,2)] = run_perception_module(imageName, GMs,bw(:,:,m));
    end
    tecurve{i,1} = matstr.name;
    tecurve{i,2}=mean(time_error);
	if i>=1
	break;
	end
end
save('tecurve.mat','tecurve');
