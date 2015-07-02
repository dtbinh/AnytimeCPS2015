function bbox = limitBbox(bbox,r,c)

% limit the bounding box to the image
% limit width
if (bbox(1)+bbox(3) >= c)
    bbox(3) = c - bbox(1) - 1;
end

% limit height 
if (bbox(2)+bbox(4) >= r)
    bbox(4) = r - bbox(2) - 1;
end

if (bbox(3) < 0 || bbox(4) < 0)
    bbox = [];
end

