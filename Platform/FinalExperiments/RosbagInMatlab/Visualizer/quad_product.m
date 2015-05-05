function qp = quad_product(x)
Q = diag([10 10 10 .1 .1 .1]);

qp = x'*Q*x;

