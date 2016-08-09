function fhat_x = getWavApprox_vector(x,C_ejk,k_min,k_max,j_min,j_max,E)

%%
dim = log2(size(E,1)+0);
K = permn(k_min:k_max,dim);
k_sz = size(K,1);
summation = 0;
for e = 1:size(E,1)
    j_ix = 0;
    for j=j_min:1:j_max
        j_ix = j_ix + 1;
        for k_dims = 1:k_sz
            arg_x = (2^j)*x - K(k_dims,:)';
            [phis,psis] = arrayfun(@(t) MeyerWavelet(t),arg_x); %for all elements in vector x
            phi_e = (1-E(e,:)).*phis';
            psi_e = E(e,:).*psis';
            bigPsi_temp = phi_e+psi_e;
            bigPsi_ejk_x = prod(bigPsi_temp);
            summation = summation + C_ejk(e,j_ix,k_dims)*bigPsi_ejk_x;
            
        end
    end
end
fhat_x = summation;