%% Find Z outer and refine to Z inner
info = 'init';
save('SetsAndParams_Z.mat','X','params','info');
shrink_factor = 1.1;
grow_factor = 1.05;
shrinking_count = 0;
Z_overbar;
Z_overbar_orig = Z_set_overbar;
save('SetsAndParams_Z.mat','Z_set_overbar','params','-append');
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
Zset_orig = Z_set_overbar;
clc;
%% now grow this
violator = 0;
iters = 0;

while(~violator)
    iters = iters+1;
    ZB = Z_set_overbar.b*grow_factor;
    ZA = Z_set_overbar.A;
    Z_set_overbar = Polyhedron('A',ZA,'b',ZB);
    save('SetsAndParams_Z','Z_set_overbar','-append');
    findViolator;
    violator = (flag~=-2); %flag=1 means found a violation, that means time to stop growing man
end

if(iters==1)
   Z_set_final = Zset_orig;
else
   Z_set_final = Polyhedron('A',ZA,'b',ZB/grow_factor); 
end
   
Z_set_overbar = Z_set_final;
Zset = Z_set_overbar;
%save new stuff
save('SetsAndParams_Z.mat','Zset','Z_set_overbar','-append');
%% Find ROA for x
X_overbar;
X_overbar_orig = X_set_overbar;
save('SetsAndParams_Z.mat','Zset','Z_set_overbar','X_set_overbar','params','-append');

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

%reset this var
X_set_overbar = Xset;
Xset_orig = Xset;
%% now grow this
violator = 0;
iters = 0;

while(~violator)
    iters = iters+1;
    XB = X_set_overbar.b*grow_factor;
    XA = X_set_overbar.A;
    X_set_overbar = Polyhedron('A',ZA,'b',ZB);
    save('SetsAndParams_Z','X_set_overbar','-append');
    findViolator_x;
    violator = (flag~=-2); %flag=1 means found a violation, that means time to stop growing man
end

if(iters==1)
   X_set_final = Xset_orig;
else
   X_set_final = Polyhedron('A',XA,'b',XB/grow_factor); 
end
%save new stuff