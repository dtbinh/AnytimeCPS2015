function [str] = getCvxIndexes(AMatrix)
%give it a matrix, it'll spit out a string to be used for indexing for
%sparse cvxgen param for that matrix, copy paste it to cvxgen

str = [];
%if nargin==1
%   tol = eps; 
%end

Matrix = AMatrix;%.*(abs(AMatrix)>tol);
[r,c,~] = find(Matrix);

for i = 1:length(r)
   str = horzcat(str,num2str(r(i)),',',num2str(c(i)),' ');
    
    
end
'no of elements'
numel(r)
'indexing'
str=horzcat('{',str,'}')
