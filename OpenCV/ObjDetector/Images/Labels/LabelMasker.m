
% read from label images to get masks on detected objects

k = 3; %no of comps
temp = 0;

for i = 1:10
    for j = 1:9
        filename = strcat('label',num2str(k),'_',num2str(i),'.',num2str(j),'.png');
        if(exist(filename,'file'))
            close all;
            temp = temp + 1;
            imshow(filename);
            bw(:,:,temp) = roipoly;
            imname{temp} = filename;
            prompt = 'was this detection crap (1/0)';
            reply = input(prompt);
            crap(temp) = reply;
        else
            close all
            
        end
        
    end
    
end

%% write

for i = 1:numel(imname)
    if(~crap(i))
        maskname = strcat('LabelMasks/','mask_',imname{i}(1:end));
        imwrite(bw(:,:,i),maskname);
    end
end