/*
 * rdivide.c
 *
 * Code generation for function 'rdivide'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "rdivide.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */
void b_rdivide(const real_T x[7680000], const real_T y[7680000], real_T z
               [7680000])
{
  int32_T i4;
  for (i4 = 0; i4 < 7680000; i4++) {
    z[i4] = x[i4] / y[i4];
  }
}

void c_rdivide(const real_T x[2], real_T y, real_T z[2])
{
  int32_T i5;
  for (i5 = 0; i5 < 2; i5++) {
    z[i5] = x[i5] / y;
  }
}

void rdivide(const real_T x[5760000], const real_T y[5760000], real_T z[5760000])
{
  int32_T i2;
  for (i2 = 0; i2 < 5760000; i2++) {
    z[i2] = x[i2] / y[i2];
  }
}

/* End of code generation (rdivide.c) */
