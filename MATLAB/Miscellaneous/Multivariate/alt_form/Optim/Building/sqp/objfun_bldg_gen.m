function f = objfun_bldg_gen(u,optParams,I1)
% maximize robustness, or min neg of robustness, bitch
z = SimBldg(u,optParams);
room_temp = z(4,:);
f =  -getBldgRobustness(room_temp,optParams,I1);
