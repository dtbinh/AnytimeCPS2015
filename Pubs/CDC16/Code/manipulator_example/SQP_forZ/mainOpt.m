% Find Z outer
Z_overbar;
save('SetsAndParams_Z.mat','Z_set_overbar','-append');
% see if we can find a violator
findViolator;
if(status~=1) %couldn't find that sob
   Zset = Z_overbar; 
else
   %shrink to smaller than largest value that violated and redo
end

