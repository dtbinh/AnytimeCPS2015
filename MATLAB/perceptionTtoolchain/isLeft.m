function d = isLeft(P0, P1, P2 )
% // isLeft(): test if a point is Left|On|Right of an infinite 2D line.
% //    Input:  three points P0, P1, and P2
% //    Return: >0 for P2 left of the line through P0 to P1
% //          =0 for P2 on the line
% //          <0 for P2 right of the line

d = ( (P1(1) - P0(1)) * (P2(2) - P0(2)) - (P2(1) - P0(1)) * (P1(2) - P0(2)) );
 
