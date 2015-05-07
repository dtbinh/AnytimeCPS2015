/* Produced by CVXGEN, 2015-04-28 17:40:57 -0400.  */
/* CVXGEN is Copyright (C) 2006-2012 Jacob Mattingley, jem@cvxgen.com. */
/* The code in this file is Copyright (C) 2006-2012 Jacob Mattingley. */
/* CVXGEN, or solvers produced by CVXGEN, cannot be used for commercial */
/* applications without prior written permission from Jacob Mattingley. */

/* Filename: solver.h. */
/* Description: Header file with relevant definitions. */
#ifndef SOLVER_H
#define SOLVER_H
/* Uncomment the next line to remove all library dependencies. */
/*#define ZERO_LIBRARY_MODE */
#ifdef MATLAB_MEX_FILE
/* Matlab functions. MATLAB_MEX_FILE will be defined by the mex compiler. */
/* If you are not using the mex compiler, this functionality will not intrude, */
/* as it will be completely disabled at compile-time. */
#include "mex.h"
#else
#ifndef ZERO_LIBRARY_MODE
#include <stdio.h>
#endif
#endif
/* Space must be allocated somewhere (testsolver.c, csolve.c or your own */
/* program) for the global variables vars, params, work and settings. */
/* At the bottom of this file, they are externed. */
#ifndef ZERO_LIBRARY_MODE
#include <math.h>
#define pm(A, m, n) printmatrix(#A, A, m, n, 1)
#endif

namespace FEAT_100 {

typedef struct Params_t {
  double z_0[9];
  double z_ref[9];
  double Q[81];
  double Q_final[81];
  double A_0[15];
  double B_0[9];
  double A[15];
  double B[9];
  double u_limit[3];
  double *z[1];
} Params;
typedef struct Vars_t {
  double *z_1; /* 9 rows. */
  double *z_2; /* 9 rows. */
  double *z_3; /* 9 rows. */
  double *z_4; /* 9 rows. */
  double *z_5; /* 9 rows. */
  double *z_6; /* 9 rows. */
  double *z_7; /* 9 rows. */
  double *z_8; /* 9 rows. */
  double *z_9; /* 9 rows. */
  double *z_10; /* 9 rows. */
  double *z_11; /* 9 rows. */
  double *t_01; /* 3 rows. */
  double *u_0; /* 3 rows. */
  double *t_02; /* 3 rows. */
  double *u_1; /* 3 rows. */
  double *t_03; /* 3 rows. */
  double *u_2; /* 3 rows. */
  double *t_04; /* 3 rows. */
  double *u_3; /* 3 rows. */
  double *t_05; /* 3 rows. */
  double *u_4; /* 3 rows. */
  double *t_06; /* 3 rows. */
  double *u_5; /* 3 rows. */
  double *t_07; /* 3 rows. */
  double *u_6; /* 3 rows. */
  double *t_08; /* 3 rows. */
  double *u_7; /* 3 rows. */
  double *t_09; /* 3 rows. */
  double *u_8; /* 3 rows. */
  double *t_10; /* 3 rows. */
  double *u_9; /* 3 rows. */
  double *t_11; /* 3 rows. */
  double *u_10; /* 3 rows. */
  double *z[12];
  double *u[11];
} Vars;
typedef struct Workspace_t {
  double h[99];
  double s_inv[99];
  double s_inv_z[99];
  double b[108];
  double q[165];
  double rhs[471];
  double x[471];
  double *s;
  double *z;
  double *y;
  double lhs_aff[471];
  double lhs_cc[471];
  double buffer[471];
  double buffer2[471];
  double KKT[1323];
  double L[1758];
  double d[471];
  double v[471];
  double d_inv[471];
  double gap;
  double optval;
  double ineq_resid_squared;
  double eq_resid_squared;
  double block_33[1];
  /* Pre-op symbols. */
  double quad_572003176448[1];
  double quad_104548143104[1];
  double quad_34000510976[1];
  int converged;
} Workspace;
typedef struct Settings_t {
  double resid_tol;
  double eps;
  int max_iters;
  int refine_steps;
  int better_start;
  /* Better start obviates the need for s_init and z_init. */
  double s_init;
  double z_init;
  int verbose;
  /* Show extra details of the iterative refinement steps. */
  int verbose_refinement;
  int debug;
  /* For regularization. Minimum value of abs(D_ii) in the kkt D factor. */
  double kkt_reg;
} Settings;
extern Vars vars;
extern Params params;
extern Workspace work;
extern Settings settings;
/* Function definitions in ldl.c: */
void ldl_solve(double *target, double *var);
void ldl_factor(void);
double check_factorization(void);
void matrix_multiply(double *result, double *source);
double check_residual(double *target, double *multiplicand);
void fill_KKT(void);

/* Function definitions in matrix_support.c: */
void multbymA(double *lhs, double *rhs);
void multbymAT(double *lhs, double *rhs);
void multbymG(double *lhs, double *rhs);
void multbymGT(double *lhs, double *rhs);
void multbyP(double *lhs, double *rhs);
void fillq(void);
void fillh(void);
void fillb(void);
void pre_ops(void);

/* Function definitions in solver.c: */
double eval_gap(void);
void set_defaults(void);
void setup_pointers(void);
void setup_indexed_params(void);
void setup_indexed_optvars(void);
void setup_indexing(void);
void set_start(void);
double eval_objv(void);
void fillrhs_aff(void);
void fillrhs_cc(void);
void refine(double *target, double *var);
double calc_ineq_resid_squared(void);
double calc_eq_resid_squared(void);
void better_start(void);
void fillrhs_start(void);
long solve(void);

/* Function definitions in testsolver.c: */
int main(int argc, char **argv);
void load_default_data(void);

/* Function definitions in util.c: */
void tic(void);
float toc(void);
float tocq(void);
void printmatrix(char *name, double *A, int m, int n, int sparse);
double unif(double lower, double upper);
float ran1(long*idum, int reset);
float randn_internal(long *idum, int reset);
double randn(void);
void reset_rand(void);

} //end namespace
#endif
