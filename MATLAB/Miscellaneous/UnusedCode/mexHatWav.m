function psi = mexHatWav(x,sigma)

%x in R^2
%sigma is sigma as in the gaussiam for the log
if(nargin==1)
    sigma = 1; %default
end

psi = (1/(pi*sigma^4))*(1-(norm(x)^2)/(2*sigma^2))* ...
       exp(-(norm(x)^2)/(2*sigma^2));

