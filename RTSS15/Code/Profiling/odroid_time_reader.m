
fid = fopen('p50.txt');
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