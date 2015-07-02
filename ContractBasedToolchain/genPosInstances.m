% generate positive instances
clear;

trainLabel = 'trainLabel';
trainImg = 'trainImg';
root_dir = pwd;
label_dir = fullfile(root_dir,['/',trainLabel]);
image_dir = fullfile(root_dir,['/',trainImg]);

% create positiveInstances struct
positiveInstances = struct('imageFilename', {}, 'objectBoundingBoxes', []);

% positive instances labels for vehicle
posLabels = {'Car', 'Van', 'Truck', 'Tram'};
% dimensions of input images
r = 375; c = 1242;

fileNames = dir([trainLabel,'/*.txt']);
%%
index=1;
for i = 1:size(fileNames,1)
%     fprintf('%s \n',fileNames(i,1).name);
    % get objects of image
    objects = myReadLabels(strcat([trainLabel,'/'],fileNames(i,1).name));
    % extract pos bboxes
    bboxes = []; % type_label = cell(0); 
    for j = 1:numel(objects)
        % add only fully visible bboxes for now
        if (sum(strcmp(objects(j).type,posLabels)) == 1 && objects(j).occlusion==0)
            % type_label{j} = objects(j).type;
            bbox = [objects(j).x1+1,objects(j).y1+1,objects(j).x2-objects(j).x1+1,objects(j).y2-objects(j).y1+1];
            bbox = round(bbox);
            bbox = limitBbox(bbox,r,c);
            bboxes = [bboxes; bbox];
        end
    end
    % ignore if bboxes empty
    if (isempty(bboxes))
        continue
    end
%     positiveInstances(i).imageFilename = sprintf('%s/%06d.png',image_dir,img_idx);
    positiveInstances(index).imageFilename = strcat([trainImg,'/'],fileNames(i,1).name(1:end-3),'png');
    positiveInstances(index).objectBoundingBoxes = bboxes;
    index = index + 1;
end

save('posMat.mat','positiveInstances');



