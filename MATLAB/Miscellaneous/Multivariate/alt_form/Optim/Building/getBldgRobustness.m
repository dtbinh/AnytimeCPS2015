%bldg get shizzle

%%
I1 = 10:19;
%I2 if needed
room_temp_occu = room_temp(I1);

signed_dists1 = zeros(numel(I1),1);

for i = 1:numel(I1)
    x = room_temp_occu(i)/10; %scale here
    x=2.65;
signed_dists1(i) = getWavApprox_mex(x,wavparams.C,wavparams.D, ...
    wavparams.k_min,wavparams.k_max,wavparams.j_min,wavparams.j_max);

end

bl_r = SoftMin(10*signed_dists1);