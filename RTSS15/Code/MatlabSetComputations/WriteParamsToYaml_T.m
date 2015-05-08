load('/home/mlab-retro/Documents/AnytimeCPS2015/RTSS15/Code/MatlabSetComputations/Data/SetsT.mat');
X = struct();
rZfA = cell(numel(deltas),numel(deltas));
cZfA = cell(numel(deltas),numel(deltas));
valsZfA = cell(numel(deltas),numel(deltas));

rAlift = cell(numel(deltas),numel(deltas));
cAlift = cell(numel(deltas),numel(deltas));
valsAlift = cell(numel(deltas),numel(deltas));

rBlift = cell(numel(deltas),numel(deltas));
cBlift = cell(numel(deltas),numel(deltas));
valsBAlift = cell(numel(deltas),numel(deltas));

rA0lift = cell(numel(deltas),numel(deltas));
cA0lift = cell(numel(deltas),numel(deltas));
valsA0lift = cell(numel(deltas),numel(deltas));

rB0lift = cell(numel(deltas),numel(deltas));
cB0lift = cell(numel(deltas),numel(deltas));
valsB0lift = cell(numel(deltas),numel(deltas));


for i=1:numel(deltas)
    %for j=1:numel(deltas)
    j = i;
        for k = 0:H   %constraints for all time steps     
            [rZA(i,j,k+1,:),cZA(i,j,k+1,:),valsZA(i,j,k+1,:)] = find(Zj{i}(k+1).A); %only A has sparsity, not B
            X.(sprintf(strcat('ZA_',num2str(i),num2str(j),num2str(k)))) = reshape(valsZA(i,j,k+1,:),...
                1,numel(valsZA(i,j,k+1,:)));
            X.(sprintf(strcat('Zb_',num2str(i),num2str(j),num2str(k)))) = Zj{i}(k+1).b';
        end
        % write terminal set
        [rZfA{i,j},cZfA{i,j},valsZfA{i,j}] = find(Zf_box{i}.A);
        temp = reshape(valsZfA{i,j},1,numel(valsZfA{i,j}));
        X.(sprintf(strcat('ZfA_',num2str(i),num2str(j)))) = temp;
        X.(sprintf(strcat('Zfb_',num2str(i),num2str(j)))) = Zf_box{i}.b';
        clear temp;
        
%         [rAlift{i,j},cAlift{i,j},valsAlift{i,j}] = find(A_lift(:,:,j)); %this is A_lift for all non-zero
%         temp = reshape(valsAlift{i,j},1,numel(valsAlift{i,j}));
%         X.(sprintf(strcat('A_lift_',num2str(i),num2str(j)))) = temp;
%         clear temp;
%         %add B_lift
%         [rBlift{i,j},cBlift{i,j},valsBlift{i,j}] = find(B_lift(:,:,j)); %this is A_lift for all non-zero
%         temp = reshape(valsBlift{i,j},1,numel(valsBlift{i,j}));
%         X.(sprintf(strcat('B_lift_',num2str(i),num2str(j)))) = temp;
%         clear temp;
%         
%         
%         [rA0lift{i,j},cA0lift{i,j},valsA0lift{i,j}] = find(A_lift(:,:,i)); %this is A_lift for j = 0
%         temp = reshape(valsA0lift{i,j},1,numel(valsA0lift{i,j}));
%         X.(sprintf(strcat('A_lift_0_',num2str(i),num2str(j)))) = temp;
%         clear temp;
%         %add B_lift_0
%         [rB0lift{i,j},cB0lift{i,j},valsB0lift{i,j}] = find(B_lift(:,:,i)); %this is A_lift for j = 0
%         temp = reshape(valsB0lift{i,j},1,numel(valsB0lift{i,j}));
%         X.(sprintf(strcat('B_lift_0_',num2str(i),num2str(j)))) = temp;
%         clear temp;
%         
    %end
    
end

% if(exist('sys_d','var')) %write the discrete normal dynamics too
%     Q = diag([10;10;10;1;1;1]);
%     Qf = eye(6);
%     R = diag([1;1;1]);
%     x_limit = 100*ones(6,1);
%     u_limit = [deg2rad(30);deg2rad(30);10];
%     
%     [rA,cA,vA] = find(sys_d.a);
%     temp = reshape(vA,1,numel(vA));
%     X.(sprintf('A')) = temp;
%     clear temp;
%     [rB,cB,vB] = find(sys_d.b);
%     temp = reshape(vB,1,numel(vB));
%     X.(sprintf('B')) = temp;
%     [rQ,cQ,vQ] = find(Q);
%     temp = reshape(vQ,1,numel(vQ));
%     X.(sprintf('Q')) = temp;
%     [rQf,cQf,vQf] = find(Qf);
%     temp = reshape(vQf,1,numel(vQf));
%     X.(sprintf('Qf')) = temp;
%     [rR,cR,vR] = find(R);
%     temp = reshape(vR,1,numel(vR));
%     X.(sprintf('R')) = temp;
%     X.(sprintf('x_limit')) = x_limit';
%     X.(sprintf('u_limit')) = u_limit';
%     
% end    
WriteYaml('/home/mlab-retro/Documents/AnytimeCPS2015/RTSS15/Code/MatlabSetComputations/Data/gains_T.yaml',X)