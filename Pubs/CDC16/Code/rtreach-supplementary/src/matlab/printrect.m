function printrect(rect, varargin)
if isempty(varargin)
    rect %#ok<NOPRT>
elseif strcmp(varargin{1}, 'p')
    P = Polyhedron('lb', rect(1:2,1), 'ub', rect(1:2,2));
    if nargin > 2
        P.plot('ShowIndex', 1, varargin{2:end});
    else
        P.plot('ShowIndex', 1);
    end
end