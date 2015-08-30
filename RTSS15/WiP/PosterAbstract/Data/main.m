
%% load all
 temp_names = getcondvects(3); %truth tabel for all names possible
 for i = 1:size(temp_names,1)
    shit = num2str(temp_names(i,:));
    Schedule(i,:) = strcat(shit(1),shit(4),shit(7));
 end
 temp1 = dir('CSV'); %all CSV here
 temp = temp1(3:end);
 
 ct = 0;
 for i = 1:length(temp) % first two are . and ..
    for j = 1:size(Schedule,1)
        if(sum(temp(i).name(1:3)==Schedule(j,:))==3) %if matching file for schedule
            %Schedule(j,:)
            %temp(i).name
            %''
            ct = ct+1;
            CPU_GPU(ct,:) = temp_names(j,:);
            [CPU_freq(:,ct),GPU_freq(:,ct),Throughput(:,:,ct),MeanPower(:,:,ct)] = getData(temp(i).name);
        end
    end
 end
 
 %% viz
 figure;
 legendmatrix =cell(ct,1);
 for i = 1:ct
    C = ones(6,6)*i*100; 
    surf(CPU_freq(:,i),GPU_freq(:,i),Throughput(:,:,i),C);
    legendmatrix{i} = strcat(num2str(CPU_GPU(i,:)));
    hold all;
     
 end
 legend(legendmatrix);
 xlabel('CPU freq (GHz)');
 ylabel('GPU freq (GHz)');
 zlabel('VP rate (Hz)');
 
 
 legendmatrix =cell(ct,1);
  figure;
 for i = 1:ct
    C = ones(6,6)*i*100; 
    surf(CPU_freq(:,i),GPU_freq(:,i),MeanPower(:,:,i)*12.001,C);
    hold all;
    legendmatrix{i} = strcat(num2str(CPU_GPU(i,:))); 
 end
  legend(legendmatrix);
  xlabel('CPU freq (GHz)');
 ylabel('GPU freq (GHz)');
 zlabel('Mean Power (W)');
 
 %% more plots
 figure;
 x = 20*1:20:20*ct;
 legendmatrix1 = cell(3,1);
 temp = 0;
 for j = [1 3 6]
    temp = temp+1; 
    legendmatrix1{temp} = strcat('CPU (GHz) =',num2str(CPU_freq(j,1)),'; GPU (GHz) =',num2str(GPU_freq(j,1)));
 end
 for i = 1:ct
     
    bar(x(i),Throughput(1,1,i));hold on;
    bar(x(i)+2,Throughput(3,3,i),'g');hold on; 
    bar(x(i)+4,Throughput(6,6,i),'y');hold on; 
    
 end
 grid on;
 ax = gca;
 ax.XTick = x;
 ax.XTickLabel = legendmatrix;
legend(legendmatrix1);

%% power

 figure;
 x = 20*1:20:20*ct;
 legendmatrix1 = cell(3,1);
 temp = 0;
 for j = [1 3 6]
    temp = temp+1; 
    legendmatrix1{temp} = strcat('CPU (GHz) =',num2str(CPU_freq(j,1)),'; GPU (GHz) =',num2str(GPU_freq(j,1)));
 end
 for i = 1:ct
     
    bar(x(i),MeanPower(1,1,i));hold on;
    bar(x(i)+2,MeanPower(3,3,i),'g');hold on; 
    bar(x(i)+4,MeanPower(6,6,i),'y');hold on; 
    
 end
 grid on;
 ax = gca;
 ax.XTick = x;
 ax.XTickLabel = legendmatrix;
legend(legendmatrix1);
 

%% normalized stuff
cost_analysis = 0;

if(cost_analysis)

Througput_norm = Throughput/(max(Throughput(:)));
MeanPower_norm = MeanPower/max(MeanPower(:));


for alpha1 = 0.1:.1:0.9
    
alpha2 = 1-alpha1;

[alpha1 alpha2]

Cost = alpha1*Througput_norm + alpha2*(1./MeanPower_norm);

 figure;
 legendmatrix =cell(ct,1);
 for i = 1:ct
    C = ones(6,6)*i*100; 
    surf(CPU_freq(:,i),GPU_freq(:,i),Cost(:,:,i),C);
    legendmatrix{i} = strcat(num2str(CPU_GPU(i,:)));
    hold all;
     
 end
 legend(legendmatrix);
 xlabel('CPU freq (GHz)');
 ylabel('GPU freq (GHz)');
 zlabel('Cost');
 title(strcat('\alpha_1 = ',num2str(alpha1)));  
end


end