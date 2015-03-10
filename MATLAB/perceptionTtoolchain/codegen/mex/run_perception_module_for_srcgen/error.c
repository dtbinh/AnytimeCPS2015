/*
 * error.c
 *
 * Code generation for function 'error'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "error.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtMCInfo d_emlrtMCI = { 16, 1, "error",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\lang\\error.m"
};

static emlrtRSInfo ue_emlrtRSI = { 16, "error",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\lang\\error.m"
};

/* Function Definitions */
void error(const emlrtStack *sp)
{
  const mxArray *y;
  static const int32_T iv2[2] = { 1, 72 };

  const mxArray *m3;
  char_T cv4[72];
  static const char_T cv5[72] = { 'I', 'm', 'a', 'g', 'e', ' ', 'J', ' ', 's',
    't', 'i', 'l', 'l', ' ', 'h', 'a', 's', ' ', 'N', 'a', 'N', 's', ' ', 'i',
    'n', ' ', 't', 'h', 'e', ' ', 'n', 'o', 'r', 'm', 'a', 'l', 'i', 'z', 'e',
    'd', ' ', 'i', 'm', 'a', 'g', 'e', ' ', '-', ' ', 't', 'h', 'i', 's', ' ',
    's', 'h', 'o', 'u', 'l', 'd', ' ', 'n', 'o', 't', ' ', 'h', 'a', 'p', 'p',
    'e', 'n', '.' };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  y = NULL;
  m3 = emlrtCreateCharArray(2, iv2);
  memcpy(&cv4[0], &cv5[0], 72U * sizeof(char_T));
  emlrtInitCharArrayR2013a(sp, 72, m3, cv4);
  emlrtAssign(&y, m3);
  st.site = &ue_emlrtRSI;
  b_error(&st, y, &d_emlrtMCI);
}

/* End of code generation (error.c) */
