function y = test_code_style(x) 
%#codegen

if (x == 1)
    y = 1;
elseif (x == 2)
    y = 2;
elseif (x == 3)    
    y = 3;
else
    y = 4;
end