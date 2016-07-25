function fhat = Beta_fhat_x(x,theta_jk,dist_array_xy,dx,dy,J,K)
%% evaluate c_0 = integral_-inf^inf f(t)dt
if(dx==dy)
    c_0 = dx*dy*sum(dist_array_xy(:));
else
    sum_x = dx*sum(dist_array_xy,2);
    c_0 = dy*sum(sum_x);
end

%% evaluate f_hat
if(x(1)==0 && x(2)==0)
    fhat = c_0;
else
    fhat = c_0;
end

for j_ix = 1:numel(J)
    for k1_ix = 1:numel(K)
        for k2_ix = 1:numel(K)
            j = J(j_ix);
            k1 = K(k1_ix);
            k2 = K(k2_ix);
            
            arg_x = ((2^j)*x)-[k1;k2];
            psi_jk = (2^(1*j/2))*mexHatWav(arg_x);
            fhat = fhat + theta_jk(j_ix,k1_ix,k2_ix)*psi_jk;
        end
    end
end