
optParams.x0 = sym('x0qq%drr',[optParams.dim 1]);
u = sym('uqq%drr',[(optParams.len-1)*optParams.dim_u 1]);
cost_fn_formax = -alternate_objfun2_u_toy_linear(u,optParams)

