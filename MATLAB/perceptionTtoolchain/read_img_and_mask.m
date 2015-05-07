function [I, M]= read_img_and_mask(imgname, masks,maskfolder, imgfolder)

I = [];
M = [];
Im=imread([imgfolder, '/', imgname]);
I = preprocess_img(Im);
maskname = match_img_name(masks,imgname);
if ~isempty(maskname)
    M = imread([maskfolder, '/',maskname]);
end
