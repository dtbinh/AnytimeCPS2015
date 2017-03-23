function ProblemParams = RecFeasProb(S,Acl,A_lift,Fhat,N,alpha_is,dist_params)

%% get some info

Sigmas_k = cell(N+1,1);
HL_jF = cell(N+1,1);
% sigma_i_j = zeros(N+2,1);
H = S.A;

numModes = size(Acl,3);
numConstrs = size(H,1);

covar_what = cell(1,numModes);
Sigmas_kpj_k = cell(N+1,numModes);
betas_i = cell(numConstrs,numModes);
rec_probs = cell(1,numModes);
rec_probs_mode = cell(1,numModes);

for mode = 1:numModes
    Lhat = reshape(Acl(:,:,mode),size(Acl,1),size(Acl,2));
    Ahat =  reshape(A_lift(:,:,mode),size(Acl,1),size(Acl,2));
    n_x = size(Fhat,2);
    A = Ahat(1:n_x,1:n_x);
    
    cov_w = dist_params(mode).cov_w;
    cov_e = dist_params(mode).cov_e; %edit for all modes
    cov_what = (A)*cov_e*(A)' + cov_e + cov_w;
    covar_what{mode} = cov_what;
    
    temp_j_k = zeros(size(Lhat,1),size(Lhat,2));
    
    for j = 1:N+1 %j=1 means 0, ..., N+1 means N
        Lhat_j = Lhat^(j-1);
        temp_j_k = temp_j_k + (Lhat_j*Fhat)*cov_what*(Lhat_j*Fhat)';
        cov_j_k = temp_j_k + Fhat*cov_e*Fhat';
        Sigmas_k{j}= cov_j_k;
        Sigmas_kpj_k{j,mode} = Sigmas_k{j};
        
        HL_jF{j} = H*Lhat_j*Fhat;
        if(j>1 && j<=N+1) %for rec feas computations, only upto N on the next step, ...
            %N+1 is via feedback
            for i = 1:numConstrs
                beta(i) = sqrt(2)*erfinv(1-2*alpha_is(i));
                betas_i{i,mode} = beta(i);
                
                temp_H = HL_jF{j-1};
                sigma_i(i) =  temp_H(i,:)*cov_what*temp_H(i,:)';
                gamma_i(i) = beta(i)*(norm(sqrtm(Sigmas_k{j-1})*H(i,:)') - ...
                    norm(sqrtm(Sigmas_k{j})*H(i,:)'));
                if(gamma_i(i)>=0)
                   keyboard 
                end
                recf(i,j-1) = normcdf(-gamma_i(i),0,(sigma_i(i)));%
                
            end
        end
    end
    rec_probs{mode} = recf;
    temp_matrix = rec_probs{mode};
    rec_probs_mode{mode} = min(temp_matrix(:));
end

ProblemParams.rec_probs = rec_probs;
ProblemParams.rec_probs_mode = rec_probs_mode;
ProblemParams.betas_i = betas_i;
ProblemParams.Sigmas_kpj_k = Sigmas_kpj_k;
ProblemParams.covar_what = covar_what;