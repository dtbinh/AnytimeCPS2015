function Pr_rec_feas = RecFeasProb(S,Acl,Fhat,alpha_is,dist_params)

%% get some info
numModes = size(Acl,3);

for mode = 1:numModes
   L = reshape(Acl(:,:,mode),size(Acl,1),size(Acl,2)); 
    
end