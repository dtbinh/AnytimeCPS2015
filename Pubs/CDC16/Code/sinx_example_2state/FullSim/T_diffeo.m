function z = T_diffeo(x,a)
z = zeros(2,1);
if(numel(x)==2)
z(1) = x(1);
z(2) = a*sin(x(2));
else
    'Fuck no, wrong size state'
    
end
