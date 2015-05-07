function [I, M]= read_img_and_mask(imgname, masks,maskfolder)

I = [];
M = [];
Im=imread(imgname);
I = preprocess_img(Im);
maskname = match_img_name(masks,imgname);
if ~isempty(maskname)
    M = imread([maskfolder, '/',maskname]);
end