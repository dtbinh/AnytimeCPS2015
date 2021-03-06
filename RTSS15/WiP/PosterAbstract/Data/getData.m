function [CPU_freq,GPU_freq,Throughput,MeanPower] = getData(filename)

M = importfile(strcat('CSV/',filename));

x = unique(M(:,1));
y = unique(M(:,2));

 for k = 1:length(x)*length(y)
    for i = 1:length(x)
        for j = 1:length(y)
           
            if(x(i)==M(k,1) && y(j)==M(k,2))
               Throughput(i,j) = M(k,3); 
               MeanPower(i,j) = M(k,9);
            end
            
        end
    end
 end
 
 CPU_freq = x/(10^6); %in GHz
 GPU_freq = y/(10^9);
 
 