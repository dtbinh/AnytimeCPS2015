load('/home/mlab-retro/Documents/AnytimeCPS2015/RTSS15/Code/MatlabSetComputations/Data/Sets.mat');
X = struct();
for i=1:numel(deltas)
    for j=1:numel(deltas)
        for k = 0:H        
            [rZA(i,j,k+1,:),cZA(i,j,k+1,:),valsZA(i,j,k+1,:)] = find(Zj(i,j,k+1).A); %only A has sparsity, not B
            X.(sprintf(strcat('ZfA',num2str(i),num2str(j),num2str(k)))) = reshape(valsZA(i,j,k+1,:),...
                1,numel(valsZA(i,j,k+1,:)));
            
        end
    end
end