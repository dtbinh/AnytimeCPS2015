function Zjs = getZjs_smpc(S,ProblemParams,N)
%%
H = S.A;
b = S.b;


rec_probs = ProblemParams.rec_probs;
rec_probs_mode = ProblemParams.rec_probs_mode;
betas_i = ProblemParams.betas_i;
Sigmas_kpj_k = ProblemParams.Sigmas_kpj_k;
covar_what = ProblemParams.covar_what;
n_x = ProblemParams.n_x;

numModes = numel(rec_probs);
numConstrs = size(H,1);
temp_vector = zeros(numConstrs,1);
beta_vector = cell(N+1,numModes);
b_new = cell(N+1,numModes);

for mode = 1:numModes
    for j = 1:N+1 %not N+2, N+2 is term set mate
        for i = 1:numConstrs-n_x %for the states
        temp_vector(i) = betas_i{i,mode}*norm(sqrtm(Sigmas_kpj_k{j,mode}) ...
            *H(i,:)');
        end
        beta_vector{j,mode} = temp_vector;
        b_new{j,mode} = b - beta_vector{j,mode};
        Zjs{j,mode} = Polyhedron('A',H,'b',b_new{j,mode});
        if(Zjs{j,mode}.isEmptySet)
            'Empty Zj, entering debug'
           keyboard; 
        end
    end
end



