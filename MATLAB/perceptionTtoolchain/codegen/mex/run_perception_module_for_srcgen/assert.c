/*
 * assert.c
 *
 * Code generation for function 'assert'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "assert.h"
#include "eml_warning.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */
void b_assert(const emlrtStack *sp, boolean_T cond)
{
  const mxArray *y;
  static const int32_T iv7[2] = { 1, 36 };

  const mxArray *m7;
  char_T cv13[36];
  int32_T i;
  static const char_T cv14[36] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'i', 'n', 'd', '2', 's', 'u', 'b', '_', 'I', 'n', 'd',
    'e', 'x', 'O', 'u', 't', 'O', 'f', 'R', 'a', 'n', 'g', 'e' };

  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;
  if (cond) {
  } else {
    y = NULL;
    m7 = emlrtCreateCharArray(2, iv7);
    for (i = 0; i < 36; i++) {
      cv13[i] = cv14[i];
    }

    emlrtInitCharArrayR2013a(sp, 36, m7, cv13);
    emlrtAssign(&y, m7);
    st.site = &ne_emlrtRSI;
    b_error(&st, b_message(&st, y, &i_emlrtMCI), &i_emlrtMCI);
  }
}

/* End of code generation (assert.c) */
