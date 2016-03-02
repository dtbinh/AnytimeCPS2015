%% Find Z outer and refine to Z inner
shrink_factor = 1.1;
shrinking_count = 0;
Z_overbar;
Z_overbar_orig = Z_set_overbar;
save('SetsAndParams_Z.mat','Z_set_overbar','X','params','-append');
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

%now grow this

%save new stuff
%% Find ROA for x
X_overbar;
X_overbar_orig = X_set_overbar;
save('SetsAndParams_Z.mat','Zset','X_set_overbar','params','-append');

notflag = 1;
while(notflag)
% see if we can find a violator
findViolator_x;
if(flag~=1) %couldn't find that sob
   Xset = X_set_overbar; 
   notflag =0;
else
    'found violation'%shrink to smaller than largest value that violated and redo
    'shrinking'
    shrinking_count = shrinking_count+1;
    XA = X_set_overbar.A;
    XB = X_set_overbar.b/shrink_factor;
    X_set_overbar = Polyhedron('A',XA,'b',XB);
    save('SetsAndParams_Z.mat','X_set_overbar','-append');
end



end

%now grow this

%save new stuff