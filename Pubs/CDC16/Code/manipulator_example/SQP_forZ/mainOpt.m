% Find Z outer
shrink_factor = 1.2;
shrinking_count = 0;
Z_overbar;
Z_overbar_orig = Z_set_overbar;
save('SetsAndParams_Z.mat','Z_set_overbar','-append');
notflag = 1;
while(notflag)
% see if we can find a violator
findViolator;
if(flag~=1) %couldn't find that sob
   Zset = Z_set_overbar; 
   notflag =0;
else
    'found violation'%shrink to smaller than largest value that violated and redo
    'shrinking'
    shrinking_count = shrinking_count+1;
    ZA = Z_set_overbar.A;
    ZB = Z_set_overbar.b/shrink_factor;
    Z_set_overbar = Polyhedron('A',ZA,'b',ZB);
    save('SetsAndParams_Z.mat','Z_set_overbar','-append');
end



end
%Find ROA for x



