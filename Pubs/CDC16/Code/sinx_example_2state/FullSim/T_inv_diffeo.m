function x = T_inv_diffeo(z,a)
 x = zeros(2,1);
if(numel(z)==2)
x(1) = z(1);
x(2) = asin(z(2)/a);
else
    'Fuck no, wrong size state'
   
end
