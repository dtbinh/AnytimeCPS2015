/*
 * colon.c
 *
 * Code generation for function 'colon'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "colon.h"
#include "eml_warning.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */
void assert_pmaxsize(const emlrtStack *sp, boolean_T p)
{
  const mxArray *y;
  static const int32_T iv14[2] = { 1, 21 };

  const mxArray *m10;
  char_T cv25[21];
  int32_T i;
  static const char_T cv26[21] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'p', 'm', 'a', 'x', 's', 'i', 'z', 'e' };

  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = sp;
  b_st.tls = sp->tls;
  if (p) {
  } else {
    y = NULL;
    m10 = emlrtCreateCharArray(2, iv14);
    for (i = 0; i < 21; i++) {
      cv25[i] = cv26[i];
    }

    emlrtInitCharArrayR2013a(sp, 21, m10, cv25);
    emlrtAssign(&y, m10);
    st.site = &te_emlrtRSI;
    b_st.site = &cf_emlrtRSI;
    b_error(&st, b_message(&b_st, y, &l_emlrtMCI), &m_emlrtMCI);
  }
}

void b_float_colon_length(real_T a, int32_T *n, real_T *anew, real_T *bnew,
  boolean_T *n_too_large)
{
  real_T ndbl;
  real_T absa;
  if (muDoubleScalarIsNaN(a)) {
    *n = 1;
    *anew = rtNaN;
    *bnew = 1.0;
    *n_too_large = false;
  } else {
    *anew = a;
    ndbl = muDoubleScalarFloor(-(1.0 - a) + 0.5);
    *bnew = a + -ndbl;
    absa = muDoubleScalarAbs(a);
    if (muDoubleScalarAbs(1.0 - *bnew) < 4.4408920985006262E-16 *
        muDoubleScalarMax(absa, 1.0)) {
      ndbl++;
      *bnew = 1.0;
    } else if (1.0 - *bnew > 0.0) {
      *bnew = a + -(ndbl - 1.0);
    } else {
      ndbl++;
    }

    *n_too_large = false;
    *n = (int32_T)ndbl;
  }
}

void float_colon_length(real_T b, int32_T *n, real_T *anew, real_T *bnew,
  boolean_T *n_too_large)
{
  real_T ndbl;
  real_T cdiff;
  real_T absb;
  if (muDoubleScalarIsNaN(b)) {
    *n = 1;
    *anew = rtNaN;
    *bnew = b;
    *n_too_large = false;
  } else {
    *anew = 1.0;
    ndbl = muDoubleScalarFloor((b - 1.0) + 0.5);
    *bnew = 1.0 + ndbl;
    cdiff = (1.0 + ndbl) - b;
    absb = muDoubleScalarAbs(b);
    if (muDoubleScalarAbs(cdiff) < 4.4408920985006262E-16 * muDoubleScalarMax
        (1.0, absb)) {
      ndbl++;
      *bnew = b;
    } else if (cdiff > 0.0) {
      *bnew = 1.0 + (ndbl - 1.0);
    } else {
      ndbl++;
    }

    *n_too_large = false;
    *n = (int32_T)ndbl;
  }
}

/* End of code generation (colon.c) */
