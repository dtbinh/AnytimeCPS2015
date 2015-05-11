% Produced by CVXGEN, 2015-05-09 18:33:44 -0400.
% CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com.
% The code in this file is Copyright (C) 2006-2012 Jacob Mattingley.
% CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial
% applications without prior written permission from Jacob Mattingley.

% Filename: cvxsolve.m.
% Description: Solution file, via cvx, for use with sample.m.
function [vars, status] = cvxsolve(params, settings)
A = params.A;
A_0 = params.A_0;
B = params.B;
B_0 = params.B_0;
H_0 = params.H_0;
H_1 = params.H_1;
H_2 = params.H_2;
H_3 = params.H_3;
H_4 = params.H_4;
H_5 = params.H_5;
H_6 = params.H_6;
H_7 = params.H_7;
H_8 = params.H_8;
H_9 = params.H_9;
H_10 = params.H_10;
Hf = params.Hf;
Q = params.Q;
Q_final = params.Q_final;
g_0 = params.g_0;
if isfield(params, 'g_1')
  g_1 = params.g_1;
elseif isfield(params, 'g')
  g_1 = params.g{1};
else
  error 'could not find g_1'
end
if isfield(params, 'g_2')
  g_2 = params.g_2;
elseif isfield(params, 'g')
  g_2 = params.g{2};
else
  error 'could not find g_2'
end
if isfield(params, 'g_3')
  g_3 = params.g_3;
elseif isfield(params, 'g')
  g_3 = params.g{3};
else
  error 'could not find g_3'
end
if isfield(params, 'g_4')
  g_4 = params.g_4;
elseif isfield(params, 'g')
  g_4 = params.g{4};
else
  error 'could not find g_4'
end
if isfield(params, 'g_5')
  g_5 = params.g_5;
elseif isfield(params, 'g')
  g_5 = params.g{5};
else
  error 'could not find g_5'
end
if isfield(params, 'g_6')
  g_6 = params.g_6;
elseif isfield(params, 'g')
  g_6 = params.g{6};
else
  error 'could not find g_6'
end
if isfield(params, 'g_7')
  g_7 = params.g_7;
elseif isfield(params, 'g')
  g_7 = params.g{7};
else
  error 'could not find g_7'
end
if isfield(params, 'g_8')
  g_8 = params.g_8;
elseif isfield(params, 'g')
  g_8 = params.g{8};
else
  error 'could not find g_8'
end
if isfield(params, 'g_9')
  g_9 = params.g_9;
elseif isfield(params, 'g')
  g_9 = params.g{9};
else
  error 'could not find g_9'
end
if isfield(params, 'g_10')
  g_10 = params.g_10;
elseif isfield(params, 'g')
  g_10 = params.g{10};
else
  error 'could not find g_10'
end
gf = params.gf;
z_0 = params.z_0;
z_ref = params.z_ref;
cvx_begin
  % Caution: automatically generated by cvxgen. May be incorrect.
  variable z_0(9, 1);
  variable z_1(9, 1);
  variable z_2(9, 1);
  variable z_3(9, 1);
  variable z_4(9, 1);
  variable z_5(9, 1);
  variable z_6(9, 1);
  variable z_7(9, 1);
  variable z_8(9, 1);
  variable z_9(9, 1);
  variable z_10(9, 1);
  variable z_11(9, 1);
  variable z_12(9, 1);
  variable z_13(9, 1);
  variable z_14(9, 1);
  variable z_15(9, 1);
  variable z_16(9, 1);
  variable z_17(9, 1);
  variable z_18(9, 1);
  variable z_19(9, 1);
  variable z_20(9, 1);
  variable z_21(9, 1);
  variable z_22(9, 1);
  variable z_23(9, 1);
  variable z_24(9, 1);
  variable z_25(9, 1);
  variable z_26(9, 1);
  variable z_27(9, 1);
  variable z_28(9, 1);
  variable z_29(9, 1);
  variable z_30(9, 1);
  variable z_31(9, 1);
  variable u_0(3, 1);
  variable u_1(3, 1);
  variable u_2(3, 1);
  variable u_3(3, 1);
  variable u_4(3, 1);
  variable u_5(3, 1);
  variable u_6(3, 1);
  variable u_7(3, 1);
  variable u_8(3, 1);
  variable u_9(3, 1);
  variable u_10(3, 1);
  variable u_11(3, 1);
  variable u_12(3, 1);
  variable u_13(3, 1);
  variable u_14(3, 1);
  variable u_15(3, 1);
  variable u_16(3, 1);
  variable u_17(3, 1);
  variable u_18(3, 1);
  variable u_19(3, 1);
  variable u_20(3, 1);
  variable u_21(3, 1);
  variable u_22(3, 1);
  variable u_23(3, 1);
  variable u_24(3, 1);
  variable u_25(3, 1);
  variable u_26(3, 1);
  variable u_27(3, 1);
  variable u_28(3, 1);
  variable u_29(3, 1);
  variable u_30(3, 1);

  minimize(quad_form(z_0 - z_ref, Q) + quad_form(z_1 - z_ref, Q) + quad_form(z_2 - z_ref, Q) + quad_form(z_3 - z_ref, Q) + quad_form(z_4 - z_ref, Q) + quad_form(z_5 - z_ref, Q) + quad_form(z_6 - z_ref, Q) + quad_form(z_7 - z_ref, Q) + quad_form(z_8 - z_ref, Q) + quad_form(z_9 - z_ref, Q) + quad_form(z_10 - z_ref, Q) + quad_form(z_11 - z_ref, Q) + quad_form(z_12 - z_ref, Q) + quad_form(z_13 - z_ref, Q) + quad_form(z_14 - z_ref, Q) + quad_form(z_15 - z_ref, Q) + quad_form(z_16 - z_ref, Q) + quad_form(z_17 - z_ref, Q) + quad_form(z_18 - z_ref, Q) + quad_form(z_19 - z_ref, Q) + quad_form(z_20 - z_ref, Q) + quad_form(z_21 - z_ref, Q) + quad_form(z_22 - z_ref, Q) + quad_form(z_23 - z_ref, Q) + quad_form(z_24 - z_ref, Q) + quad_form(z_25 - z_ref, Q) + quad_form(z_26 - z_ref, Q) + quad_form(z_27 - z_ref, Q) + quad_form(z_28 - z_ref, Q) + quad_form(z_29 - z_ref, Q) + quad_form(z_30 - z_ref, Q) + quad_form(z_31 - z_ref, Q_final));
  subject to
    z_0 == z_0;
    z_1 == A_0*z_0 + B_0*u_0;
    z_1 == A*z_0 + B*u_0;
    z_2 == A*z_1 + B*u_1;
    z_3 == A*z_2 + B*u_2;
    z_4 == A*z_3 + B*u_3;
    z_5 == A*z_4 + B*u_4;
    z_6 == A*z_5 + B*u_5;
    z_7 == A*z_6 + B*u_6;
    z_8 == A*z_7 + B*u_7;
    z_9 == A*z_8 + B*u_8;
    z_10 == A*z_9 + B*u_9;
    z_11 == A*z_10 + B*u_10;
    z_12 == A*z_11 + B*u_11;
    z_13 == A*z_12 + B*u_12;
    z_14 == A*z_13 + B*u_13;
    z_15 == A*z_14 + B*u_14;
    z_16 == A*z_15 + B*u_15;
    z_17 == A*z_16 + B*u_16;
    z_18 == A*z_17 + B*u_17;
    z_19 == A*z_18 + B*u_18;
    z_20 == A*z_19 + B*u_19;
    z_21 == A*z_20 + B*u_20;
    z_22 == A*z_21 + B*u_21;
    z_23 == A*z_22 + B*u_22;
    z_24 == A*z_23 + B*u_23;
    z_25 == A*z_24 + B*u_24;
    z_26 == A*z_25 + B*u_25;
    z_27 == A*z_26 + B*u_26;
    z_28 == A*z_27 + B*u_27;
    z_29 == A*z_28 + B*u_28;
    z_30 == A*z_29 + B*u_29;
    z_31 == A*z_30 + B*u_30;
    H_0*z_0 <= g_0;
    H_1*z_1 <= g_1;
    H_2*z_2 <= g_2;
    H_3*z_3 <= g_3;
    H_4*z_4 <= g_4;
    H_5*z_5 <= g_5;
    H_6*z_6 <= g_6;
    H_7*z_7 <= g_7;
    H_8*z_8 <= g_8;
    H_9*z_9 <= g_9;
    H_10*z_10 <= g_10;
    Hf*z_31 <= gf;
cvx_end
vars.u_0 = u_0;
vars.u_1 = u_1;
vars.u{1} = u_1;
vars.u_2 = u_2;
vars.u{2} = u_2;
vars.u_3 = u_3;
vars.u{3} = u_3;
vars.u_4 = u_4;
vars.u{4} = u_4;
vars.u_5 = u_5;
vars.u{5} = u_5;
vars.u_6 = u_6;
vars.u{6} = u_6;
vars.u_7 = u_7;
vars.u{7} = u_7;
vars.u_8 = u_8;
vars.u{8} = u_8;
vars.u_9 = u_9;
vars.u{9} = u_9;
vars.u_10 = u_10;
vars.u{10} = u_10;
vars.u_11 = u_11;
vars.u{11} = u_11;
vars.u_12 = u_12;
vars.u{12} = u_12;
vars.u_13 = u_13;
vars.u{13} = u_13;
vars.u_14 = u_14;
vars.u{14} = u_14;
vars.u_15 = u_15;
vars.u{15} = u_15;
vars.u_16 = u_16;
vars.u{16} = u_16;
vars.u_17 = u_17;
vars.u{17} = u_17;
vars.u_18 = u_18;
vars.u{18} = u_18;
vars.u_19 = u_19;
vars.u{19} = u_19;
vars.u_20 = u_20;
vars.u{20} = u_20;
vars.u_21 = u_21;
vars.u{21} = u_21;
vars.u_22 = u_22;
vars.u{22} = u_22;
vars.u_23 = u_23;
vars.u{23} = u_23;
vars.u_24 = u_24;
vars.u{24} = u_24;
vars.u_25 = u_25;
vars.u{25} = u_25;
vars.u_26 = u_26;
vars.u{26} = u_26;
vars.u_27 = u_27;
vars.u{27} = u_27;
vars.u_28 = u_28;
vars.u{28} = u_28;
vars.u_29 = u_29;
vars.u{29} = u_29;
vars.u_30 = u_30;
vars.u{30} = u_30;
vars.z_0 = z_0;
vars.z_1 = z_1;
vars.z{1} = z_1;
vars.z_2 = z_2;
vars.z{2} = z_2;
vars.z_3 = z_3;
vars.z{3} = z_3;
vars.z_4 = z_4;
vars.z{4} = z_4;
vars.z_5 = z_5;
vars.z{5} = z_5;
vars.z_6 = z_6;
vars.z{6} = z_6;
vars.z_7 = z_7;
vars.z{7} = z_7;
vars.z_8 = z_8;
vars.z{8} = z_8;
vars.z_9 = z_9;
vars.z{9} = z_9;
vars.z_10 = z_10;
vars.z{10} = z_10;
vars.z_11 = z_11;
vars.z{11} = z_11;
vars.z_12 = z_12;
vars.z{12} = z_12;
vars.z_13 = z_13;
vars.z{13} = z_13;
vars.z_14 = z_14;
vars.z{14} = z_14;
vars.z_15 = z_15;
vars.z{15} = z_15;
vars.z_16 = z_16;
vars.z{16} = z_16;
vars.z_17 = z_17;
vars.z{17} = z_17;
vars.z_18 = z_18;
vars.z{18} = z_18;
vars.z_19 = z_19;
vars.z{19} = z_19;
vars.z_20 = z_20;
vars.z{20} = z_20;
vars.z_21 = z_21;
vars.z{21} = z_21;
vars.z_22 = z_22;
vars.z{22} = z_22;
vars.z_23 = z_23;
vars.z{23} = z_23;
vars.z_24 = z_24;
vars.z{24} = z_24;
vars.z_25 = z_25;
vars.z{25} = z_25;
vars.z_26 = z_26;
vars.z{26} = z_26;
vars.z_27 = z_27;
vars.z{27} = z_27;
vars.z_28 = z_28;
vars.z{28} = z_28;
vars.z_29 = z_29;
vars.z{29} = z_29;
vars.z_30 = z_30;
vars.z{30} = z_30;
vars.z_31 = z_31;
vars.z{31} = z_31;
status.cvx_status = cvx_status;
% Provide a drop-in replacement for csolve.
status.optval = cvx_optval;
status.converged = strcmp(cvx_status, 'Solved');
