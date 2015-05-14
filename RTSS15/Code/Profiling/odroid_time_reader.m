
fid = fopen('log_time_f_550.txt');
c = fread(fid);


ct = 0;
buffer = [];
data = [];
for i = 1:numel(c)
    if(c(i)~=' ')
        buffer = strcat(buffer,char(c(i)));
    else
        ct = ct + 1;
        data(ct) = str2num(buffer);
        buffer = [];
    end
    
end

data = data*(10^-6); %to ms
hold all;grid on;
ecdf(data(100:end));
axis([0 60 0 1]);