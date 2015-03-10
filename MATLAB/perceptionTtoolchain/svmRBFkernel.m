function g = svmRBFkernel(x,z,scale)
g = exp(-norm((x-z)/scale)^2);
end