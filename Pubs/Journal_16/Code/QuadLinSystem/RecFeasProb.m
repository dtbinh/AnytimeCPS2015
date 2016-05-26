function Pr_rec_feas = RecFeasProb(S,Acl,A_lift,Fhat,N,alpha_is,dist_params)


%% get some info
numModes = size(Acl,3);
Sigmas_k = cell(N+1,1);
H = S.A;

for mode = 1:numModes
    Lhat = reshape(Acl(:,:,mode),size(Acl,1),size(Acl,2));
    Ahat =  reshape(A_lift(:,:,mode),size(Acl,1),size(Acl,2));
    cov_w = dist_params.cov_w;
    cov_e = dist_params.cov_e; %edit for all modes
    cov_what = (Ahat*Fhat)*cov_e*(Ahat*Fhat)' + Fhat*cov_e*Fhat' + ...
        Fhat*cov_w*Fhat';
    
    temp_j_k = zeros(size(Lhat,1),size(Lhat,2));
    for j = 1:N+1 %j=1 means 0, ..., N+1 means N
        Lhat_j = L^(j-1);
        temp_j_k = temp_j_k + Lhat_j*cov_what*Lhat_j';
        cov_j_k = temp_j_k + Fhat*cov_e*Fhat';
        Sigmas_k{j}= cov_j_k;
        
    end
end