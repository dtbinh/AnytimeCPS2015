function bl_r = getBldgRobustness(room_temp,optParams,I1)
%bldg get shizzle in interval I1
wavparams = optParams.wavparams;
%%

%I2 if needed
room_temp_occu = room_temp(I1);

signed_dists1 = zeros(numel(I1),1);

for i = 1:numel(I1)    
    x = room_temp_occu(i)/10; %scale here
    signed_dists1(i) = getWavApprox(x,wavparams.C,wavparams.D, ...
    wavparams.k_min,wavparams.k_max,wavparams.j_min,wavparams.j_max); 
end

bl_r = SoftMin(10*signed_dists1);