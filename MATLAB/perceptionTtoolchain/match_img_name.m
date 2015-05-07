function maskname = match_img_name(masks,imgname)
maskname = [];
s=regexp(imgname,'(.*)\.png$', 'tokens');
imgnb = s{1};
for m=1:length(masks)
    s=regexp(masks(m).name,imgnb{1}, 'match');
    if ~isempty(s)
        maskname = masks(m).name;
        break
    end
end

