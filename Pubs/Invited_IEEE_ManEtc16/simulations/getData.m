function [CPU_freq,GPU_freq,Throughput,MeanPower,Delta_90th] = getData(filename)

M = importfile(strcat('CSV/',filename));

x = unique(M(:,1));
y = unique(M(:,2));

 for k = 1:length(x)*length(y)
    for i = 1:length(x)
        for j = 1:length(y)
           
            if(x(i)==M(k,1) && y(j)==M(k,2))
               Throughput(i,j) = M(k,3); 
               MeanPower(i,j) = 12.001*M(k,9);
               Delta_90th(i,j) = M(k,4);
            end
            
        end
    end
 end
 
 CPU_freq = x/(10^6); %in GHz
 GPU_freq = y/(10^9);
 
 