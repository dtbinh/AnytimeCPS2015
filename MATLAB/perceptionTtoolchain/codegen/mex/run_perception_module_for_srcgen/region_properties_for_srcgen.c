/*
 * region_properties_for_srcgen.c
 *
 * Code generation for function 'region_properties_for_srcgen'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "region_properties_for_srcgen.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "eml_warning.h"
#include "eml_int_forloop_overflow_check.h"
#include "sqrt.h"
#include "rdivide.h"
#include "sum.h"
#include "eig.h"
#include "repmat.h"
#include "mean.h"
#include "ind2sub.h"
#include "run_perception_module_for_srcgen_mexutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo kc_emlrtRSI = { 30, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo lc_emlrtRSI = { 34, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo mc_emlrtRSI = { 37, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo nc_emlrtRSI = { 38, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo oc_emlrtRSI = { 39, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo pc_emlrtRSI = { 46, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo sc_emlrtRSI = { 68, "eml_mtimes_helper",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtRSInfo tc_emlrtRSI = { 21, "eml_mtimes_helper",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtRSInfo uc_emlrtRSI = { 54, "eml_xgemm",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\blas\\eml_xgemm.m"
};

static emlrtRSInfo vc_emlrtRSI = { 1, "xgemm",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\coder\\coder\\+coder\\+internal\\+blas\\xgemm.p"
};

static emlrtMCInfo n_emlrtMCI = { 42, 5, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtMCInfo o_emlrtMCI = { 43, 5, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtMCInfo t_emlrtMCI = { 104, 13, "eml_mtimes_helper",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtMCInfo u_emlrtMCI = { 103, 23, "eml_mtimes_helper",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtRTEInfo t_emlrtRTEI = { 1, 18, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRTEInfo u_emlrtRTEI = { 33, 5, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRTEInfo v_emlrtRTEI = { 35, 5, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRTEInfo w_emlrtRTEI = { 37, 5, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRTEInfo db_emlrtRTEI = { 32, 1, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtECInfo c_emlrtECI = { 1, 35, 9, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtECInfo d_emlrtECI = { 2, 37, 18, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtBCInfo gb_emlrtBCI = { -1, -1, 51, 11, "stats",
  "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m",
  0 };

static emlrtBCInfo hb_emlrtBCI = { -1, -1, 47, 11, "stats",
  "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m",
  0 };

static emlrtBCInfo ib_emlrtBCI = { -1, -1, 48, 11, "stats",
  "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m",
  0 };

static emlrtBCInfo jb_emlrtBCI = { -1, -1, 49, 11, "stats",
  "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m",
  0 };

static emlrtBCInfo kb_emlrtBCI = { -1, -1, 50, 11, "stats",
  "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m",
  0 };

static emlrtRSInfo qe_emlrtRSI = { 43, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo re_emlrtRSI = { 42, "region_properties_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\region_properties_for_srcgen.m"
};

static emlrtRSInfo se_emlrtRSI = { 103, "eml_mtimes_helper",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

static emlrtRSInfo bf_emlrtRSI = { 104, "eml_mtimes_helper",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\eml_mtimes_helper.m"
};

/* Function Declarations */
static boolean_T b_eml_relop(const creal_T a, const creal_T b);
static boolean_T eml_relop(const creal_T a, const creal_T b);

/* Function Definitions */
static boolean_T b_eml_relop(const creal_T a, const creal_T b)
{
  boolean_T p;
  real_T absbi;
  real_T y;
  real_T absxk;
  int32_T exponent;
  real_T absar;
  real_T absbr;
  real_T Ma;
  int32_T b_exponent;
  int32_T c_exponent;
  int32_T d_exponent;
  if ((muDoubleScalarAbs(a.re) > 8.9884656743115785E+307) || (muDoubleScalarAbs
       (a.im) > 8.9884656743115785E+307) || (muDoubleScalarAbs(b.re) >
       8.9884656743115785E+307) || (muDoubleScalarAbs(b.im) >
       8.9884656743115785E+307)) {
    absbi = muDoubleScalarHypot(a.re / 2.0, a.im / 2.0);
    y = muDoubleScalarHypot(b.re / 2.0, b.im / 2.0);
  } else {
    absbi = muDoubleScalarHypot(a.re, a.im);
    y = muDoubleScalarHypot(b.re, b.im);
  }

  absxk = y / 2.0;
  if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      absxk = ldexp(1.0, exponent - 53);
    }
  } else {
    absxk = rtNaN;
  }

  if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi) &&
       muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
    p = true;
  } else {
    p = false;
  }

  if (p) {
    absar = muDoubleScalarAbs(a.re);
    absxk = muDoubleScalarAbs(a.im);
    absbr = muDoubleScalarAbs(b.re);
    absbi = muDoubleScalarAbs(b.im);
    if (absar > absxk) {
      Ma = absar;
      absar = absxk;
    } else {
      Ma = absxk;
    }

    if (absbr > absbi) {
      absxk = absbr;
      absbr = absbi;
    } else {
      absxk = absbi;
    }

    if (Ma > absxk) {
      if (absar < absbr) {
        absbi = Ma - absxk;
        y = (absar / 2.0 + absbr / 2.0) / (Ma / 2.0 + absxk / 2.0) * (absbr -
          absar);
      } else {
        absbi = Ma;
        y = absxk;
      }
    } else if (Ma < absxk) {
      if (absar > absbr) {
        y = absxk - Ma;
        absbi = (absar / 2.0 + absbr / 2.0) / (Ma / 2.0 + absxk / 2.0) * (absar
          - absbr);
      } else {
        absbi = Ma;
        y = absxk;
      }
    } else {
      absbi = absar;
      y = absbr;
    }

    absxk = muDoubleScalarAbs(y / 2.0);
    if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &b_exponent);
        absxk = ldexp(1.0, b_exponent - 53);
      }
    } else {
      absxk = rtNaN;
    }

    if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi) &&
         muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      absbi = muDoubleScalarAtan2(a.im, a.re);
      y = muDoubleScalarAtan2(b.im, b.re);
      absxk = muDoubleScalarAbs(y / 2.0);
      if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
        if (absxk <= 2.2250738585072014E-308) {
          absxk = 4.94065645841247E-324;
        } else {
          frexp(absxk, &c_exponent);
          absxk = ldexp(1.0, c_exponent - 53);
        }
      } else {
        absxk = rtNaN;
      }

      if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi) &&
           muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
        p = true;
      } else {
        p = false;
      }

      if (p) {
        if (absbi > 0.78539816339744828) {
          if (absbi > 2.3561944901923448) {
            absbi = -a.im;
            y = -b.im;
          } else {
            absbi = -a.re;
            y = -b.re;
          }
        } else if (absbi > -0.78539816339744828) {
          absbi = a.im;
          y = b.im;
        } else if (absbi > -2.3561944901923448) {
          absbi = a.re;
          y = b.re;
        } else {
          absbi = -a.im;
          y = -b.im;
        }

        absxk = muDoubleScalarAbs(y / 2.0);
        if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
          if (absxk <= 2.2250738585072014E-308) {
            absxk = 4.94065645841247E-324;
          } else {
            frexp(absxk, &d_exponent);
            absxk = ldexp(1.0, d_exponent - 53);
          }
        } else {
          absxk = rtNaN;
        }

        if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi)
             && muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          absbi = 0.0;
          y = 0.0;
        }
      }
    }
  }

  return absbi < y;
}

static boolean_T eml_relop(const creal_T a, const creal_T b)
{
  boolean_T p;
  real_T absbi;
  real_T y;
  real_T absxk;
  int32_T exponent;
  real_T absar;
  real_T absbr;
  real_T Ma;
  int32_T b_exponent;
  int32_T c_exponent;
  int32_T d_exponent;
  if ((muDoubleScalarAbs(a.re) > 8.9884656743115785E+307) || (muDoubleScalarAbs
       (a.im) > 8.9884656743115785E+307) || (muDoubleScalarAbs(b.re) >
       8.9884656743115785E+307) || (muDoubleScalarAbs(b.im) >
       8.9884656743115785E+307)) {
    absbi = muDoubleScalarHypot(a.re / 2.0, a.im / 2.0);
    y = muDoubleScalarHypot(b.re / 2.0, b.im / 2.0);
  } else {
    absbi = muDoubleScalarHypot(a.re, a.im);
    y = muDoubleScalarHypot(b.re, b.im);
  }

  absxk = y / 2.0;
  if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      absxk = ldexp(1.0, exponent - 53);
    }
  } else {
    absxk = rtNaN;
  }

  if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi) &&
       muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
    p = true;
  } else {
    p = false;
  }

  if (p) {
    absar = muDoubleScalarAbs(a.re);
    absxk = muDoubleScalarAbs(a.im);
    absbr = muDoubleScalarAbs(b.re);
    absbi = muDoubleScalarAbs(b.im);
    if (absar > absxk) {
      Ma = absar;
      absar = absxk;
    } else {
      Ma = absxk;
    }

    if (absbr > absbi) {
      absxk = absbr;
      absbr = absbi;
    } else {
      absxk = absbi;
    }

    if (Ma > absxk) {
      if (absar < absbr) {
        absbi = Ma - absxk;
        y = (absar / 2.0 + absbr / 2.0) / (Ma / 2.0 + absxk / 2.0) * (absbr -
          absar);
      } else {
        absbi = Ma;
        y = absxk;
      }
    } else if (Ma < absxk) {
      if (absar > absbr) {
        y = absxk - Ma;
        absbi = (absar / 2.0 + absbr / 2.0) / (Ma / 2.0 + absxk / 2.0) * (absar
          - absbr);
      } else {
        absbi = Ma;
        y = absxk;
      }
    } else {
      absbi = absar;
      y = absbr;
    }

    absxk = muDoubleScalarAbs(y / 2.0);
    if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &b_exponent);
        absxk = ldexp(1.0, b_exponent - 53);
      }
    } else {
      absxk = rtNaN;
    }

    if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi) &&
         muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      absbi = muDoubleScalarAtan2(a.im, a.re);
      y = muDoubleScalarAtan2(b.im, b.re);
      absxk = muDoubleScalarAbs(y / 2.0);
      if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
        if (absxk <= 2.2250738585072014E-308) {
          absxk = 4.94065645841247E-324;
        } else {
          frexp(absxk, &c_exponent);
          absxk = ldexp(1.0, c_exponent - 53);
        }
      } else {
        absxk = rtNaN;
      }

      if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi) &&
           muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
        p = true;
      } else {
        p = false;
      }

      if (p) {
        if (absbi > 0.78539816339744828) {
          if (absbi > 2.3561944901923448) {
            absbi = -a.im;
            y = -b.im;
          } else {
            absbi = -a.re;
            y = -b.re;
          }
        } else if (absbi > -0.78539816339744828) {
          absbi = a.im;
          y = b.im;
        } else if (absbi > -2.3561944901923448) {
          absbi = a.re;
          y = b.re;
        } else {
          absbi = -a.im;
          y = -b.im;
        }

        absxk = muDoubleScalarAbs(y / 2.0);
        if ((!muDoubleScalarIsInf(absxk)) && (!muDoubleScalarIsNaN(absxk))) {
          if (absxk <= 2.2250738585072014E-308) {
            absxk = 4.94065645841247E-324;
          } else {
            frexp(absxk, &d_exponent);
            absxk = ldexp(1.0, d_exponent - 53);
          }
        } else {
          absxk = rtNaN;
        }

        if ((muDoubleScalarAbs(y - absbi) < absxk) || (muDoubleScalarIsInf(absbi)
             && muDoubleScalarIsInf(y) && ((absbi > 0.0) == (y > 0.0)))) {
          p = true;
        } else {
          p = false;
        }

        if (p) {
          absbi = 0.0;
          y = 0.0;
        }
      }
    }
  }

  return absbi > y;
}

void region_properties_for_srcgen(c_run_perception_module_for_src *SD, const
  emlrtStack *sp, const real_T L[1920000], emxArray_creal_T *stats)
{
  real_T maxval[1600];
  int32_T ix;
  int32_T iy;
  int32_T i;
  int32_T ixstart;
  real_T mtmp;
  boolean_T b_ix;
  int32_T idx;
  boolean_T exitg5;
  boolean_T b_ixstart;
  boolean_T exitg4;
  int32_T n;
  emxArray_real_T *ff;
  emxArray_real_T *X;
  emxArray_real_T *X_minus_mu;
  emxArray_real_T *I;
  emxArray_real_T *J;
  emxArray_real_T *a;
  emxArray_int32_T *ii;
  emxArray_int32_T *varargout_4;
  boolean_T exitg3;
  boolean_T guard1 = false;
  real_T dv5[2];
  int32_T b_X[2];
  int32_T b_X_minus_mu[2];
  const mxArray *y;
  static const int32_T iv15[2] = { 1, 21 };

  const mxArray *m11;
  char_T cv27[21];
  static const char_T cv28[21] = { 'C', 'o', 'd', 'e', 'r', ':', 'M', 'A', 'T',
    'L', 'A', 'B', ':', 'i', 'n', 'n', 'e', 'r', 'd', 'i', 'm' };

  real_T b_y[4];
  real_T alpha1;
  real_T beta1;
  char_T TRANSB;
  char_T TRANSA;
  ptrdiff_t m_t;
  ptrdiff_t n_t;
  ptrdiff_t k_t;
  ptrdiff_t lda_t;
  ptrdiff_t ldb_t;
  ptrdiff_t ldc_t;
  double * alpha1_t;
  double * Aia0_t;
  double * Bib0_t;
  double * beta1_t;
  double * Cic0_t;
  real_T c_y[4];
  creal_T D[2];
  creal_T b_mtmp;
  boolean_T exitg2;
  creal_T c_mtmp;
  boolean_T exitg1;
  const mxArray *d_y;
  const mxArray *e_y;
  real_T y_re;
  real_T brm;
  real_T Centroid[2];
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  emlrtStack f_st;
  emlrtStack g_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &b_st;
  d_st.tls = b_st.tls;
  e_st.prev = &c_st;
  e_st.tls = c_st.tls;
  f_st.prev = &e_st;
  f_st.tls = e_st.tls;
  g_st.prev = &f_st;
  g_st.tls = f_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /*  stats: n-by-6, each row contains 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid', */
  /*  of the kth component in labeled image L. Centroid is 2D */
  /*  By "second moments", the documentation means the second central moment. */
  /*   */
  /*  In the case of one-dimensional data, this would be the variance (or square of the standard deviation). */
  /*   */
  /*  In your case, where you have two-dimensional data, the second central moment is the covariance matrix. */
  /*   */
  /*  If X is an n-by-2 matrix of the points in your region, you can compute the covariance matrix Sigma in MATLAB like this (untested): */
  /*   */
  /*  mu=mean(X,1); */
  /*  X_minus_mu=X-repmat(mu, size(X,1), 1); */
  /*  Sigma=(X_minus_mu'*X_minus_mu)/size(X,1); */
  /*  Now, what does this have to do with ellipses? Well, what you're doing here is, in effect, fitting a multivariate normal distribution to your data. The covariance matrix determines the shape of that distribution,  */
  /*  and the contour lines of a multivariate normal distribution -- wait for it -- are ellipses! */
  /*   */
  /*  The directions and lengths of the ellipse's axes are given by the eigenvectors and eigenvalues of the covariance matrix: */
  /*   */
  /*  [V, D]=eig(Sigma); */
  /*  The columns of V are now the eigenvectors (i.e. the directions of the axes), and values on the diagonal of D are the eigenvalues (i.e. the lengths of the axes). So you already have the 'MajorAxisLength' and 'MinorAxisLength'.  */
  /*  The orientation is probably just the angle between the major axis and the horizontal (hint: use atan2 to compute this from the vector pointing along the major axis).  */
  /*  */
  /* Finally, the eccentricity is */
  /*   */
  /*  sqrt(1-(b/a)^2) */
  /*  where a is the length of the major axis and b is the length of the minor axis. */
  st.site = &kc_emlrtRSI;
  b_st.site = &fc_emlrtRSI;
  c_st.site = &gc_emlrtRSI;
  ix = 0;
  iy = -1;
  for (i = 0; i < 1600; i++) {
    ix += 1200;
    e_st.site = &hc_emlrtRSI;
    ixstart = ix - 1199;
    mtmp = L[ix - 1200];
    if (muDoubleScalarIsNaN(L[ix - 1200])) {
      f_st.site = &jc_emlrtRSI;
      if (ix - 1198 > ix) {
        b_ix = false;
      } else {
        b_ix = (ix > 2147483646);
      }

      if (b_ix) {
        g_st.site = &p_emlrtRSI;
        check_forloop_overflow_error(&g_st);
      }

      idx = ix - 1198;
      exitg5 = false;
      while ((!exitg5) && (idx <= ix)) {
        ixstart = idx;
        if (!muDoubleScalarIsNaN(L[idx - 1])) {
          mtmp = L[idx - 1];
          exitg5 = true;
        } else {
          idx++;
        }
      }
    }

    if (ixstart < ix) {
      f_st.site = &ic_emlrtRSI;
      if (ixstart + 1 > ix) {
        b_ixstart = false;
      } else {
        b_ixstart = (ix > 2147483646);
      }

      if (b_ixstart) {
        g_st.site = &p_emlrtRSI;
        check_forloop_overflow_error(&g_st);
      }

      while (ixstart + 1 <= ix) {
        if (L[ixstart] > mtmp) {
          mtmp = L[ixstart];
        }

        ixstart++;
      }
    }

    iy++;
    maxval[iy] = mtmp;
  }

  ixstart = 1;
  mtmp = maxval[0];
  if (muDoubleScalarIsNaN(maxval[0])) {
    ix = 2;
    exitg4 = false;
    while ((!exitg4) && (ix < 1601)) {
      ixstart = ix;
      if (!muDoubleScalarIsNaN(maxval[ix - 1])) {
        mtmp = maxval[ix - 1];
        exitg4 = true;
      } else {
        ix++;
      }
    }
  }

  if (ixstart < 1600) {
    while (ixstart + 1 < 1601) {
      if (maxval[ixstart] > mtmp) {
        mtmp = maxval[ixstart];
      }

      ixstart++;
    }
  }

  i = stats->size[0] * stats->size[1];
  stats->size[0] = (int32_T)mtmp;
  stats->size[1] = 6;
  emxEnsureCapacity(sp, (emxArray__common *)stats, i, (int32_T)sizeof(creal_T),
                    &t_emlrtRTEI);
  idx = (int32_T)mtmp * 6;
  for (i = 0; i < idx; i++) {
    stats->data[i].re = 0.0;
    stats->data[i].im = 0.0;
  }

  emlrtForLoopVectorCheckR2012b(1.0, 1.0, mtmp, mxDOUBLE_CLASS, (int32_T)mtmp,
    &db_emlrtRTEI, sp);
  n = 1;
  emxInit_real_T(sp, &ff, 1, &u_emlrtRTEI, true);
  b_emxInit_real_T(sp, &X, 2, &v_emlrtRTEI, true);
  b_emxInit_real_T(sp, &X_minus_mu, 2, &w_emlrtRTEI, true);
  emxInit_real_T(sp, &I, 1, &t_emlrtRTEI, true);
  emxInit_real_T(sp, &J, 1, &t_emlrtRTEI, true);
  b_emxInit_real_T(sp, &a, 2, &t_emlrtRTEI, true);
  emxInit_int32_T(sp, &ii, 1, &s_emlrtRTEI, true);
  emxInit_int32_T(sp, &varargout_4, 1, &t_emlrtRTEI, true);
  while (n - 1 <= (int32_T)mtmp - 1) {
    for (i = 0; i < 1920000; i++) {
      SD->u1.f0.x[i] = (L[i] == 1.0 + (real_T)(n - 1));
    }

    idx = 0;
    i = ii->size[0];
    ii->size[0] = 1920000;
    emxEnsureCapacity(sp, (emxArray__common *)ii, i, (int32_T)sizeof(int32_T),
                      &o_emlrtRTEI);
    iy = 1;
    exitg3 = false;
    while ((!exitg3) && (iy < 1920001)) {
      guard1 = false;
      if (SD->u1.f0.x[iy - 1]) {
        idx++;
        ii->data[idx - 1] = iy;
        if (idx >= 1920000) {
          exitg3 = true;
        } else {
          guard1 = true;
        }
      } else {
        guard1 = true;
      }

      if (guard1) {
        iy++;
      }
    }

    i = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity(sp, (emxArray__common *)ii, i, (int32_T)sizeof(int32_T),
                      &p_emlrtRTEI);
    i = ff->size[0];
    ff->size[0] = ii->size[0];
    emxEnsureCapacity(sp, (emxArray__common *)ff, i, (int32_T)sizeof(real_T),
                      &t_emlrtRTEI);
    idx = ii->size[0];
    for (i = 0; i < idx; i++) {
      ff->data[i] = ii->data[i];
    }

    st.site = &lc_emlrtRSI;
    b_st.site = &rb_emlrtRSI;
    ind2sub_indexClass(&b_st, ff, ii, varargout_4);
    i = I->size[0];
    I->size[0] = ii->size[0];
    emxEnsureCapacity(&st, (emxArray__common *)I, i, (int32_T)sizeof(real_T),
                      &t_emlrtRTEI);
    idx = ii->size[0];
    for (i = 0; i < idx; i++) {
      I->data[i] = ii->data[i];
    }

    i = J->size[0];
    J->size[0] = varargout_4->size[0];
    emxEnsureCapacity(&st, (emxArray__common *)J, i, (int32_T)sizeof(real_T),
                      &t_emlrtRTEI);
    idx = varargout_4->size[0];
    for (i = 0; i < idx; i++) {
      J->data[i] = varargout_4->data[i];
    }

    iy = I->size[0];
    idx = J->size[0];
    emlrtDimSizeEqCheckFastR2012b(iy, idx, &c_emlrtECI, sp);
    iy = I->size[0];
    idx = J->size[0];
    i = X->size[0] * X->size[1];
    X->size[0] = iy;
    X->size[1] = 2;
    emxEnsureCapacity(sp, (emxArray__common *)X, i, (int32_T)sizeof(real_T),
                      &t_emlrtRTEI);
    for (i = 0; i < iy; i++) {
      X->data[i] = I->data[i];
    }

    for (i = 0; i < idx; i++) {
      X->data[i + X->size[0]] = J->data[i];
    }

    mean(X, dv5);
    st.site = &mc_emlrtRSI;
    e_repmat(&st, dv5, X->size[0], X_minus_mu);
    for (i = 0; i < 2; i++) {
      b_X[i] = X->size[i];
    }

    for (i = 0; i < 2; i++) {
      b_X_minus_mu[i] = X_minus_mu->size[i];
    }

    emlrtSizeEqCheck2DFastR2012b(b_X, b_X_minus_mu, &d_emlrtECI, sp);
    i = X_minus_mu->size[0] * X_minus_mu->size[1];
    X_minus_mu->size[0] = X->size[0];
    X_minus_mu->size[1] = 2;
    emxEnsureCapacity(sp, (emxArray__common *)X_minus_mu, i, (int32_T)sizeof
                      (real_T), &t_emlrtRTEI);
    idx = X->size[0] * X->size[1];
    for (i = 0; i < idx; i++) {
      X_minus_mu->data[i] = X->data[i] - X_minus_mu->data[i];
    }

    st.site = &nc_emlrtRSI;
    i = a->size[0] * a->size[1];
    a->size[0] = 2;
    a->size[1] = X_minus_mu->size[0];
    emxEnsureCapacity(&st, (emxArray__common *)a, i, (int32_T)sizeof(real_T),
                      &t_emlrtRTEI);
    idx = X_minus_mu->size[0];
    for (i = 0; i < idx; i++) {
      for (iy = 0; iy < 2; iy++) {
        a->data[iy + a->size[0] * i] = X_minus_mu->data[i + X_minus_mu->size[0] *
          iy];
      }
    }

    b_st.site = &tc_emlrtRSI;
    if (!(a->size[1] == X_minus_mu->size[0])) {
      y = NULL;
      m11 = emlrtCreateCharArray(2, iv15);
      for (i = 0; i < 21; i++) {
        cv27[i] = cv28[i];
      }

      emlrtInitCharArrayR2013a(&b_st, 21, m11, cv27);
      emlrtAssign(&y, m11);
      c_st.site = &se_emlrtRSI;
      d_st.site = &bf_emlrtRSI;
      b_error(&c_st, b_message(&d_st, y, &t_emlrtMCI), &u_emlrtMCI);
    }

    if ((a->size[1] == 1) || (X_minus_mu->size[0] == 1)) {
      for (i = 0; i < 2; i++) {
        for (iy = 0; iy < 2; iy++) {
          b_y[i + (iy << 1)] = 0.0;
          idx = a->size[1];
          for (ix = 0; ix < idx; ix++) {
            b_y[i + (iy << 1)] += a->data[i + a->size[0] * ix] *
              X_minus_mu->data[ix + X_minus_mu->size[0] * iy];
          }
        }
      }
    } else {
      b_st.site = &sc_emlrtRSI;
      c_st.site = &uc_emlrtRSI;
      for (i = 0; i < 4; i++) {
        b_y[i] = 0.0;
      }

      if (a->size[1] < 1) {
      } else {
        e_st.site = &vc_emlrtRSI;
        alpha1 = 1.0;
        beta1 = 0.0;
        TRANSB = 'N';
        TRANSA = 'N';
        f_st.site = &vc_emlrtRSI;
        m_t = (ptrdiff_t)(2);
        f_st.site = &vc_emlrtRSI;
        n_t = (ptrdiff_t)(2);
        f_st.site = &vc_emlrtRSI;
        k_t = (ptrdiff_t)(a->size[1]);
        f_st.site = &vc_emlrtRSI;
        lda_t = (ptrdiff_t)(2);
        f_st.site = &vc_emlrtRSI;
        ldb_t = (ptrdiff_t)(a->size[1]);
        f_st.site = &vc_emlrtRSI;
        ldc_t = (ptrdiff_t)(2);
        alpha1_t = (double *)(&alpha1);
        Aia0_t = (double *)(&a->data[0]);
        Bib0_t = (double *)(&X_minus_mu->data[0]);
        beta1_t = (double *)(&beta1);
        Cic0_t = (double *)(&b_y[0]);
        dgemm(&TRANSA, &TRANSB, &m_t, &n_t, &k_t, alpha1_t, Aia0_t, &lda_t,
              Bib0_t, &ldb_t, beta1_t, Cic0_t, &ldc_t);
      }
    }

    iy = X->size[0];
    for (i = 0; i < 4; i++) {
      c_y[i] = b_y[i] / (real_T)iy;
    }

    st.site = &oc_emlrtRSI;
    eig(&st, c_y, D);
    ixstart = 1;
    b_mtmp = D[0];
    if (muDoubleScalarIsNaN(D[0].re) || muDoubleScalarIsNaN(D[0].im)) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix < 3)) {
        ixstart = 2;
        if (!(muDoubleScalarIsNaN(D[1].re) || muDoubleScalarIsNaN(D[1].im))) {
          b_mtmp = D[1];
          exitg2 = true;
        } else {
          ix = 3;
        }
      }
    }

    if ((ixstart < 2) && eml_relop(D[1], b_mtmp)) {
      b_mtmp = D[1];
    }

    ixstart = 1;
    c_mtmp = D[0];
    if (muDoubleScalarIsNaN(D[0].re) || muDoubleScalarIsNaN(D[0].im)) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 3)) {
        ixstart = 2;
        if (!(muDoubleScalarIsNaN(D[1].re) || muDoubleScalarIsNaN(D[1].im))) {
          c_mtmp = D[1];
          exitg1 = true;
        } else {
          ix = 3;
        }
      }
    }

    if ((ixstart < 2) && b_eml_relop(D[1], c_mtmp)) {
      c_mtmp = D[1];
    }

    if (b_mtmp.re > 0.0) {
    } else {
      d_y = NULL;
      m11 = emlrtCreateString("Assertion failed.");
      emlrtAssign(&d_y, m11);
      st.site = &re_emlrtRSI;
      b_error(&st, d_y, &n_emlrtMCI);
    }

    if (c_mtmp.re >= 0.0) {
    } else {
      e_y = NULL;
      m11 = emlrtCreateString("Assertion failed.");
      emlrtAssign(&e_y, m11);
      st.site = &qe_emlrtRSI;
      b_error(&st, e_y, &o_emlrtMCI);
    }

    if (b_mtmp.im == 0.0) {
      if (c_mtmp.im == 0.0) {
        y_re = c_mtmp.re / b_mtmp.re;
        alpha1 = 0.0;
      } else if (c_mtmp.re == 0.0) {
        y_re = 0.0;
        alpha1 = c_mtmp.im / b_mtmp.re;
      } else {
        y_re = c_mtmp.re / b_mtmp.re;
        alpha1 = c_mtmp.im / b_mtmp.re;
      }
    } else if (b_mtmp.re == 0.0) {
      if (c_mtmp.re == 0.0) {
        y_re = c_mtmp.im / b_mtmp.im;
        alpha1 = 0.0;
      } else if (c_mtmp.im == 0.0) {
        y_re = 0.0;
        alpha1 = -(c_mtmp.re / b_mtmp.im);
      } else {
        y_re = c_mtmp.im / b_mtmp.im;
        alpha1 = -(c_mtmp.re / b_mtmp.im);
      }
    } else {
      brm = muDoubleScalarAbs(b_mtmp.re);
      alpha1 = muDoubleScalarAbs(b_mtmp.im);
      if (brm > alpha1) {
        alpha1 = b_mtmp.im / b_mtmp.re;
        beta1 = b_mtmp.re + alpha1 * b_mtmp.im;
        y_re = (c_mtmp.re + alpha1 * c_mtmp.im) / beta1;
        alpha1 = (c_mtmp.im - alpha1 * c_mtmp.re) / beta1;
      } else if (alpha1 == brm) {
        if (b_mtmp.re > 0.0) {
          alpha1 = 0.5;
        } else {
          alpha1 = -0.5;
        }

        if (b_mtmp.im > 0.0) {
          beta1 = 0.5;
        } else {
          beta1 = -0.5;
        }

        y_re = (c_mtmp.re * alpha1 + c_mtmp.im * beta1) / brm;
        alpha1 = (c_mtmp.im * alpha1 - c_mtmp.re * beta1) / brm;
      } else {
        alpha1 = b_mtmp.re / b_mtmp.im;
        beta1 = b_mtmp.im + alpha1 * b_mtmp.re;
        y_re = (alpha1 * c_mtmp.re + c_mtmp.im) / beta1;
        alpha1 = (alpha1 * c_mtmp.im - c_mtmp.re) / beta1;
      }
    }

    st.site = &pc_emlrtRSI;
    c_sum(&st, X, dv5);
    c_rdivide(dv5, ff->size[0], Centroid);
    i = stats->size[0];
    stats->data[emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &hb_emlrtBCI, sp) - 1]
      .re = b_mtmp.re;
    i = stats->size[0];
    stats->data[emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &hb_emlrtBCI, sp) - 1]
      .im = b_mtmp.im;
    i = stats->size[0];
    stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &ib_emlrtBCI, sp) +
                 stats->size[0]) - 1].re = c_mtmp.re;
    i = stats->size[0];
    stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &ib_emlrtBCI, sp) +
                 stats->size[0]) - 1].im = c_mtmp.im;
    i = stats->size[0];
    stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &jb_emlrtBCI, sp) +
                 (stats->size[0] << 1)) - 1].re = 1.0 - (y_re * y_re - alpha1 *
      alpha1);
    i = stats->size[0];
    stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &jb_emlrtBCI, sp) +
                 (stats->size[0] << 1)) - 1].im = 0.0 - (y_re * alpha1 + alpha1 *
      y_re);
    i = stats->size[0];
    b_sqrt(&stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &jb_emlrtBCI,
             sp) + (stats->size[0] << 1)) - 1]);
    i = stats->size[0];
    stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &kb_emlrtBCI, sp) +
                 stats->size[0] * 3) - 1].re = 1.0;
    i = stats->size[0];
    stats->data[(emlrtDynamicBoundsCheckFastR2012b(n, 1, i, &kb_emlrtBCI, sp) +
                 stats->size[0] * 3) - 1].im = 0.0;
    iy = stats->size[0];
    emlrtDynamicBoundsCheckFastR2012b(n, 1, iy, &gb_emlrtBCI, sp);
    for (i = 0; i < 2; i++) {
      stats->data[(n + stats->size[0] * (4 + i)) - 1].re = Centroid[i];
      stats->data[(n + stats->size[0] * (4 + i)) - 1].im = 0.0;
    }

    n++;
    emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
  }

  emxFree_int32_T(&varargout_4);
  emxFree_int32_T(&ii);
  emxFree_real_T(&a);
  emxFree_real_T(&J);
  emxFree_real_T(&I);
  emxFree_real_T(&X_minus_mu);
  emxFree_real_T(&X);
  emxFree_real_T(&ff);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (region_properties_for_srcgen.c) */
