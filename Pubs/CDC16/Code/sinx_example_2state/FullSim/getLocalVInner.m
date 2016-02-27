function V_inner_local = getLocalVInner(x_k,X_k,Z_k,Z,X,U,V_inner_global,a)
if(~isempty(Z_k))
   Z_k = intersect(Z_k,Z); 
end

if(isempty(X_k))
    X_k = T_inv_diffeo(Z_k,a);
    X_k = intersect(X_k,X);
    X_k.minHRep;
end

[~,maxs,mins] = getRect(X_k);
[~,u_max,u_min] = getRect(U);

V_inner_local = Polyhedron('lb',(u_min+tan(maxs(2)))*a*cos(max(abs(mins(2)),abs(maxs(2)))), ...
    'ub',(u_max+tan(mins(2)))*a*cos(max(abs(mins(2)),abs(maxs(2)))));
temp = V_inner_global\V_inner_local;
if(temp.isEmptySet~=1)
   'damn son'
    pause
end
% [~,maxv,minv] = getRect(V_inner_local);
% [~,maxloc,minloc] = getRect(V_inner_global);
% 
% if(maxv<maxloc) %if tighter than needed
%    [maxv maxloc]
%    maxv = maxloc;
%    'too tight up'
% end
% 
% if(minv>minloc+eps*10)
%     [minv minloc]
%     minv-minloc
%     minv = minloc;
%     'too tight down'
%     
% end
% V_inner_local = Polyhedron('lb',minv,'ub',maxv);
% 
% 

