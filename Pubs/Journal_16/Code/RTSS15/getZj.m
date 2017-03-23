function [ZA Zb] = getZj(A,Acl,B_lift,Kx,F,Xorig,N,j,eps_k,eps)
% N=Horizon;eps_k=2;eps=2;
% j=11;
ZA=Xorig.A;
bz=Xorig.b;
if(j==0)
%    supports=arrayfun(@(idx) norm([eye(size(A,1)) zeros(size(A,1),1)]*ZA(idx,:)',1), 1:size(ZA,1));
 supports=arrayfun(@(idx) norm([eye(size(A,1)) zeros(size(A,1),size(Acl,1)-size(A,1))]*ZA(idx,:)',1), 1:size(ZA,1));

   Zb=bz-eps_k*supports'; 
    
    
    
elseif(j<=N)
    supports_k = arrayfun(@(idx) norm([(Acl^(j-1)*F*A)']*ZA(idx,:)',1), 1:size(ZA,1));
    temp=0;
    for i=2:j
        temp = temp + arrayfun(@(idx) norm([-(Acl^(j-i)*B_lift*Kx)']*ZA(idx,:)',1), 1:size(ZA,1));
    end
    
    Zb=bz-(eps_k*supports_k' + eps*temp');
%     j
%     supports_k
%     temp
%     supports_k+temp;
elseif(j==N+1)
    
    'this not here'
    
end




