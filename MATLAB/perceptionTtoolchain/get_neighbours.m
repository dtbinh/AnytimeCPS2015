function nhbrs = get_neighbours(n,i,j,r,c)
% Get n neighbours of pixel(i,j) in an image sized r-by-c
nhbrs = zeros(0,2);
if n==4
    if j>1
        nhbrs = [i, j-1];
    end
    if j<c
        nhbrs = [nhbrs; i, j+1];
    end
    if i > 1
        nhbrs = [nhbrs; i-1, j];
    end
    if i < r
        nhbrs = [nhbrs; i+1, j];
    end
elseif n== 8
    if j==1 && i==1
        nhbrs = [i,j+1; i+1,j; i+1, j+1];
    elseif j==1 && i==r
        nhbrs = [nhbrs; i, j+1;i-1,j; i-1,j+1];
    elseif j==1
        nhbrs = [nhbrs; i-1,j; i-1, j+1; i, j+1; i+1,j+1; i+1,j];
    elseif j==c && i==1
        nhbrs = [nhbrs; i, j-1; i+1,j-1; i+1,j];
    elseif j==c && i==r
        nhbrs = [nhbrs; i-1,j; i-1,j-1; i,j-1];
    elseif j==c
        nhbrs = [nhbrs; i-1,j; i-1,j-1; i,j-1; i+1, j-1; i+1,j];
    elseif j<c && i==1
        nhbrs = [nhbrs; i,j-1; i,j+1;i+1,j-1; i+1,j; i+1,j+1];
    elseif j<c && i==r
        nhbrs = [nhbrs; i,j-1; i,j+1; i-1,j-1; i-1,j; i-1,j+1];
    elseif j<c
        nhbrs = [nhbrs; i-1,j-1; i-1,j; i-1,j+1; i,j-1; i,j+1; i+1,j-1; i+1,j;i+1,j+1];
    end
else
    error('Only 4 and 8 neighbours supported')
end