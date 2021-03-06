/* Produced by CVXGEN, 2015-05-06 16:38:44 -0400.  */
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


namespace FEAT_150 {



typedef struct Params_t {
  double z_ref[9];
  double Q[81];
  double Q_final[81];
  double z_0[9];
  double A_0[15];
  double B_0[9];
  double A[15];
  double B[9];
  double H_0[18];
  double g_0[18];
  double H_1[18];
  double g_1[18];
  double H_2[18];
  double g_2[18];
  double H_3[18];
  double g_3[18];
  double H_4[18];
  double g_4[18];
  double H_5[18];
  double g_5[18];
  double H_6[18];
  double g_6[18];
  double H_7[18];
  double g_7[18];
  double H_8[18];
  double g_8[18];
  double H_9[18];
  double g_9[18];
  double H_10[18];
  double g_10[18];
  double Hf[55];
  double gf[31];
  double *g[11];
} Params;
typedef struct Vars_t {
  double *z_0; /* 9 rows. */
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
  double *u_0; /* 3 rows. */
  double *u_1; /* 3 rows. */
  double *u_2; /* 3 rows. */
  double *u_3; /* 3 rows. */
  double *u_4; /* 3 rows. */
  double *u_5; /* 3 rows. */
  double *u_6; /* 3 rows. */
  double *u_7; /* 3 rows. */
  double *u_8; /* 3 rows. */
  double *u_9; /* 3 rows. */
  double *u_10; /* 3 rows. */
  double *z[12];
  double *u[11];
} Vars;
typedef struct Workspace_t {
  double h[229];
  double s_inv[229];
  double s_inv_z[229];
  double b[117];
  double q[141];
  double rhs[716];
  double x[716];
  double *s;
  double *z;
  double *y;
  double lhs_aff[716];
  double lhs_cc[716];
  double buffer[716];
  double buffer2[716];
  double KKT[1870];
  double L[2066];
  double d[716];
  double v[716];
  double d_inv[716];
  double gap;
  double optval;
  double ineq_resid_squared;
  double eq_resid_squared;
  double block_33[1];
  /* Pre-op symbols. */
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
} //end namesp
#endif
