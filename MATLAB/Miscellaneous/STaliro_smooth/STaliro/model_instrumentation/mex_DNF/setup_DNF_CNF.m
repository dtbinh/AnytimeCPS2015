function setup_DNF_CNF(varargin)

path_var=pwd;
addpath(path_var);

skip_mex = 0;
if nargin == 1
    skip_mex = varargin{1};
end

if ~skip_mex
    mex CFLAGS="\$CFLAGS -std=c99" DNF_CNF.c DNF_functions.c str2tree.c 
end


disp('***************************************************************************')
disp('You are all set to use DNF_CNF!')
disp('The function translates propositional formulas into Disjunctive Normal Form.')
disp('***************************************************************************')

