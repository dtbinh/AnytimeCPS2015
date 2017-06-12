% generate txt file for objective function
uu = sym('upp%dqq',[(optParams.len-1)*optParams.dim 1],'real');
fid = fopen('newout.txt','w');
%fprintf(fid,'%s',char(getRobustness_u_Baron(uu, obs,goal,optParams)));

fprintf(fid,'%s',regexprep(char(getRobustness_u_Baron(uu, obs,goal,optParams)),'pp','('));
fclose(fid);