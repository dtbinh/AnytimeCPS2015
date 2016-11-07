function data = recreate_profilingData(Data_rec)
data.err_x = Data_rec(:,1);
data.err_y = Data_rec(:,2);
data.err_z = Data_rec(:,3);
data.err_yaw = Data_rec(:,4);
data.err_pitch = Data_rec(:,5);
data.err_roll = Data_rec(:,6);