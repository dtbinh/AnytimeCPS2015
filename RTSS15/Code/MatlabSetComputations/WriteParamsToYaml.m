load('/home/mlab-retro/Documents/AnytimeCPS2015/RTSS15/Code/MatlabSetComputations/Data/Sets.mat');
X = struct();
rZfA = cell(numel(deltas),numel(deltas));
cZfA = cell(numel(deltas),numel(deltas));
valsZfA = cell(numel(deltas),numel(deltas));

rAlift = cell(numel(deltas),numel(deltas));
cAlift = cell(numel(deltas),numel(deltas));
valsAlift = cell(numel(deltas),numel(deltas));

rA0lift = cell(numel(deltas),numel(deltas));
cA0lift = cell(numel(deltas),numel(deltas));
valsA0lift = cell(numel(deltas),numel(deltas));

% rZA = cell(numel(deltas),numel(deltas));
% cZA = cell(numel(deltas),numel(deltas));
% valsZA = cell(numel(deltas),numel(deltas));
% 


for i=1:numel(deltas)
    for j=1:numel(deltas)
        for k = 0:H   %constraints for all time steps     
            [rZA(i,j,k+1,:),cZA(i,j,k+1,:),valsZA(i,j,k+1,:)] = find(Zj(i,j,k+1).A); %only A has sparsity, not B
            X.(sprintf(strcat('ZA_',num2str(i),num2str(j),num2str(k)))) = reshape(valsZA(i,j,k+1,:),...
                1,numel(valsZA(i,j,k+1,:)));
            X.(sprintf(strcat('Zb_',num2str(i),num2str(j),num2str(k)))) = Zj(i,j,k+1).b';
        end
        % write terminal set
        [rZfA{i,j},cZfA{i,j},valsZfA{i,j}] = find(Zf(i,j).A);
        temp = reshape(valsZfA{i,j},1,numel(valsZfA{i,j}));
        X.(sprintf(strcat('ZfA_',num2str(i),num2str(j)))) = temp;
        X.(sprintf(strcat('Zfb_',num2str(i),num2str(j)))) = Zf(i,j).b';
        
        [rAlift{i,j},cAlift{i,j},valsAlift{i,j}] = find(A_lift(:,:,j)); %this is A_lift for all non-zero
        temp = reshape(valsAlift{i,j},1,numel(valsAlift{i,j}));
        X.(sprintf(strcat('A_lift_',num2str(i),num2str(j)))) = temp;
        %add B_lift
        
         [rA0lift{i,j},cA0lift{i,j},valsA0lift{i,j}] = find(A_lift(:,:,i)); %this is A_lift for j = 0
        temp = reshape(valsA0lift{i,j},1,numel(valsA0lift{i,j}));
        X.(sprintf(strcat('A_lift_0_',num2str(i),num2str(j)))) = temp;
        %add B_lift_0
        
    end
    
end

WriteYaml('test.yaml',X)