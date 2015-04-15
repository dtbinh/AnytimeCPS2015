% csolve  Solves a custom quadratic program very rapidly.
%
% [vars, status] = csolve(params, settings)
%
% solves the convex optimization problem
%
%   minimize(quad_form(x_0 - x_ref, Q) + quad_form(u_0, R) + quad_form(x_1 - x_ref, Q) + quad_form(u_1, R) + quad_form(x_2 - x_ref, Q) + quad_form(u_2, R) + quad_form(x_3 - x_ref, Q) + quad_form(u_3, R) + quad_form(x_4 - x_ref, Q) + quad_form(u_4, R) + quad_form(x_5 - x_ref, Q) + quad_form(u_5, R) + quad_form(x_6 - x_ref, Q) + quad_form(u_6, R) + quad_form(x_7 - x_ref, Q) + quad_form(u_7, R) + quad_form(x_8 - x_ref, Q) + quad_form(u_8, R) + quad_form(x_9 - x_ref, Q) + quad_form(u_9, R) + quad_form(x_10 - x_ref, Q) + quad_form(u_10, R) + quad_form(x_11 - x_ref, Q_final))
%   subject to
%     x_1 == A*x_0 + B*u_0
%     x_2 == A*x_1 + B*u_1
%     x_3 == A*x_2 + B*u_2
%     x_4 == A*x_3 + B*u_3
%     x_5 == A*x_4 + B*u_4
%     x_6 == A*x_5 + B*u_5
%     x_7 == A*x_6 + B*u_6
%     x_8 == A*x_7 + B*u_7
%     x_9 == A*x_8 + B*u_8
%     x_10 == A*x_9 + B*u_9
%     x_11 == A*x_10 + B*u_10
%     abs(u_0) <= u_limit
%     abs(u_1) <= u_limit
%     abs(u_2) <= u_limit
%     abs(u_3) <= u_limit
%     abs(u_4) <= u_limit
%     abs(u_5) <= u_limit
%     abs(u_6) <= u_limit
%     abs(u_7) <= u_limit
%     abs(u_8) <= u_limit
%     abs(u_9) <= u_limit
%     abs(u_10) <= u_limit
%     abs(x_1(1)) <= x_limit(1)
%     abs(x_2(1)) <= x_limit(1)
%     abs(x_3(1)) <= x_limit(1)
%     abs(x_4(1)) <= x_limit(1)
%     abs(x_5(1)) <= x_limit(1)
%     abs(x_6(1)) <= x_limit(1)
%     abs(x_7(1)) <= x_limit(1)
%     abs(x_8(1)) <= x_limit(1)
%     abs(x_9(1)) <= x_limit(1)
%     abs(x_10(1)) <= x_limit(1)
%     abs(x_1(2)) <= x_limit(2)
%     abs(x_2(2)) <= x_limit(2)
%     abs(x_3(2)) <= x_limit(2)
%     abs(x_4(2)) <= x_limit(2)
%     abs(x_5(2)) <= x_limit(2)
%     abs(x_6(2)) <= x_limit(2)
%     abs(x_7(2)) <= x_limit(2)
%     abs(x_8(2)) <= x_limit(2)
%     abs(x_9(2)) <= x_limit(2)
%     abs(x_10(2)) <= x_limit(2)
%     abs(x_1(3)) <= x_limit(3)
%     abs(x_2(3)) <= x_limit(3)
%     abs(x_3(3)) <= x_limit(3)
%     abs(x_4(3)) <= x_limit(3)
%     abs(x_5(3)) <= x_limit(3)
%     abs(x_6(3)) <= x_limit(3)
%     abs(x_7(3)) <= x_limit(3)
%     abs(x_8(3)) <= x_limit(3)
%     abs(x_9(3)) <= x_limit(3)
%     abs(x_10(3)) <= x_limit(3)
%     abs(x_1(4)) <= x_limit(4)
%     abs(x_2(4)) <= x_limit(4)
%     abs(x_3(4)) <= x_limit(4)
%     abs(x_4(4)) <= x_limit(4)
%     abs(x_5(4)) <= x_limit(4)
%     abs(x_6(4)) <= x_limit(4)
%     abs(x_7(4)) <= x_limit(4)
%     abs(x_8(4)) <= x_limit(4)
%     abs(x_9(4)) <= x_limit(4)
%     abs(x_10(4)) <= x_limit(4)
%     abs(x_1(5)) <= x_limit(5)
%     abs(x_2(5)) <= x_limit(5)
%     abs(x_3(5)) <= x_limit(5)
%     abs(x_4(5)) <= x_limit(5)
%     abs(x_5(5)) <= x_limit(5)
%     abs(x_6(5)) <= x_limit(5)
%     abs(x_7(5)) <= x_limit(5)
%     abs(x_8(5)) <= x_limit(5)
%     abs(x_9(5)) <= x_limit(5)
%     abs(x_10(5)) <= x_limit(5)
%     abs(x_1(6)) <= x_limit(6)
%     abs(x_2(6)) <= x_limit(6)
%     abs(x_3(6)) <= x_limit(6)
%     abs(x_4(6)) <= x_limit(6)
%     abs(x_5(6)) <= x_limit(6)
%     abs(x_6(6)) <= x_limit(6)
%     abs(x_7(6)) <= x_limit(6)
%     abs(x_8(6)) <= x_limit(6)
%     abs(x_9(6)) <= x_limit(6)
%     abs(x_10(6)) <= x_limit(6)
%
% with variables
%      u_0   3 x 1
%      u_1   3 x 1
%      u_2   3 x 1
%      u_3   3 x 1
%      u_4   3 x 1
%      u_5   3 x 1
%      u_6   3 x 1
%      u_7   3 x 1
%      u_8   3 x 1
%      u_9   3 x 1
%     u_10   3 x 1
%      x_1   6 x 1
%      x_2   6 x 1
%      x_3   6 x 1
%      x_4   6 x 1
%      x_5   6 x 1
%      x_6   6 x 1
%      x_7   6 x 1
%      x_8   6 x 1
%      x_9   6 x 1
%     x_10   6 x 1
%     x_11   6 x 1
%
% and parameters
%        A   6 x 6
%        B   6 x 3
%        Q   6 x 6    PSD
%  Q_final   6 x 6    PSD
%        R   3 x 3    PSD
%  u_limit   3 x 1    positive
%      x_0   6 x 1
%  x_limit   6 x 1    positive
%    x_ref   6 x 1
%
% Note:
%   - Check status.converged, which will be 1 if optimization succeeded.
%   - You don't have to specify settings if you don't want to.
%   - To hide output, use settings.verbose = 0.
%   - To change iterations, use settings.max_iters = 20.
%   - You may wish to compare with cvxsolve to check the solver is correct.
%
% Specify params.A, ..., params.x_ref, then run
%   [vars, status] = csolve(params, settings)
% Produced by CVXGEN, 2015-04-10 21:15:44 -0400.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: csolve.m.
% Description: Help file for the Matlab solver interface.
