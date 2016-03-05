function zkp1 = linplant(A,B,zk,vk)
%z_{k+1} = Az_k + Bu_k
zkp1 = A*zk + B*vk;