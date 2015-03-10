/*
 * File: region_properties_for_srcgen.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "region_properties_for_srcgen.h"
#include "sqrt.h"
#include "rdivide.h"
#include "sum.h"
#include "eig.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "repmat.h"
#include "mean.h"
#include "run_perception_module_for_srcgen_rtwutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Declarations */
static boolean_T b_eml_relop(const creal_T a, const creal_T b);
static boolean_T eml_relop(const creal_T a, const creal_T b);
static double rt_atan2d_snf(double u0, double u1);

/* Function Definitions */

/*
 * Arguments    : const creal_T a
 *                const creal_T b
 * Return Type  : boolean_T
 */
static boolean_T b_eml_relop(const creal_T a, const creal_T b)
{
  boolean_T p;
  double absbi;
  double y;
  double absxk;
  int exponent;
  double absar;
  double absbr;
  double Ma;
  int b_exponent;
  int c_exponent;
  int d_exponent;
  if ((fabs(a.re) > 8.9884656743115785E+307) || (fabs(a.im) >
       8.9884656743115785E+307) || (fabs(b.re) > 8.9884656743115785E+307) ||
      (fabs(b.im) > 8.9884656743115785E+307)) {
    absbi = rt_hypotd_snf(a.re / 2.0, a.im / 2.0);
    y = rt_hypotd_snf(b.re / 2.0, b.im / 2.0);
  } else {
    absbi = rt_hypotd_snf(a.re, a.im);
    y = rt_hypotd_snf(b.re, b.im);
  }

  absxk = y / 2.0;
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      absxk = ldexp(1.0, exponent - 53);
    }
  } else {
    absxk = rtNaN;
  }

  if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) && ((absbi >
         0.0) == (y > 0.0)))) {
    p = true;
  } else {
    p = false;
  }

  if (p) {
    absar = fabs(a.re);
    absxk = fabs(a.im);
    absbr = fabs(b.re);
    absbi = fabs(b.im);
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

    absxk = fabs(y / 2.0);
    if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &b_exponent);
        absxk = ldexp(1.0, b_exponent - 53);
      }
    } else {
      absxk = rtNaN;
    }

    if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) && ((absbi >
           0.0) == (y > 0.0)))) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      absbi = rt_atan2d_snf(a.im, a.re);
      y = rt_atan2d_snf(b.im, b.re);
      absxk = fabs(y / 2.0);
      if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
        if (absxk <= 2.2250738585072014E-308) {
          absxk = 4.94065645841247E-324;
        } else {
          frexp(absxk, &c_exponent);
          absxk = ldexp(1.0, c_exponent - 53);
        }
      } else {
        absxk = rtNaN;
      }

      if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) && ((absbi >
             0.0) == (y > 0.0)))) {
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

        absxk = fabs(y / 2.0);
        if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
          if (absxk <= 2.2250738585072014E-308) {
            absxk = 4.94065645841247E-324;
          } else {
            frexp(absxk, &d_exponent);
            absxk = ldexp(1.0, d_exponent - 53);
          }
        } else {
          absxk = rtNaN;
        }

        if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) &&
             ((absbi > 0.0) == (y > 0.0)))) {
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

/*
 * Arguments    : const creal_T a
 *                const creal_T b
 * Return Type  : boolean_T
 */
static boolean_T eml_relop(const creal_T a, const creal_T b)
{
  boolean_T p;
  double absbi;
  double y;
  double absxk;
  int exponent;
  double absar;
  double absbr;
  double Ma;
  int b_exponent;
  int c_exponent;
  int d_exponent;
  if ((fabs(a.re) > 8.9884656743115785E+307) || (fabs(a.im) >
       8.9884656743115785E+307) || (fabs(b.re) > 8.9884656743115785E+307) ||
      (fabs(b.im) > 8.9884656743115785E+307)) {
    absbi = rt_hypotd_snf(a.re / 2.0, a.im / 2.0);
    y = rt_hypotd_snf(b.re / 2.0, b.im / 2.0);
  } else {
    absbi = rt_hypotd_snf(a.re, a.im);
    y = rt_hypotd_snf(b.re, b.im);
  }

  absxk = y / 2.0;
  if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
    if (absxk <= 2.2250738585072014E-308) {
      absxk = 4.94065645841247E-324;
    } else {
      frexp(absxk, &exponent);
      absxk = ldexp(1.0, exponent - 53);
    }
  } else {
    absxk = rtNaN;
  }

  if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) && ((absbi >
         0.0) == (y > 0.0)))) {
    p = true;
  } else {
    p = false;
  }

  if (p) {
    absar = fabs(a.re);
    absxk = fabs(a.im);
    absbr = fabs(b.re);
    absbi = fabs(b.im);
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

    absxk = fabs(y / 2.0);
    if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
      if (absxk <= 2.2250738585072014E-308) {
        absxk = 4.94065645841247E-324;
      } else {
        frexp(absxk, &b_exponent);
        absxk = ldexp(1.0, b_exponent - 53);
      }
    } else {
      absxk = rtNaN;
    }

    if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) && ((absbi >
           0.0) == (y > 0.0)))) {
      p = true;
    } else {
      p = false;
    }

    if (p) {
      absbi = rt_atan2d_snf(a.im, a.re);
      y = rt_atan2d_snf(b.im, b.re);
      absxk = fabs(y / 2.0);
      if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
        if (absxk <= 2.2250738585072014E-308) {
          absxk = 4.94065645841247E-324;
        } else {
          frexp(absxk, &c_exponent);
          absxk = ldexp(1.0, c_exponent - 53);
        }
      } else {
        absxk = rtNaN;
      }

      if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) && ((absbi >
             0.0) == (y > 0.0)))) {
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

        absxk = fabs(y / 2.0);
        if ((!rtIsInf(absxk)) && (!rtIsNaN(absxk))) {
          if (absxk <= 2.2250738585072014E-308) {
            absxk = 4.94065645841247E-324;
          } else {
            frexp(absxk, &d_exponent);
            absxk = ldexp(1.0, d_exponent - 53);
          }
        } else {
          absxk = rtNaN;
        }

        if ((fabs(y - absbi) < absxk) || (rtIsInf(absbi) && rtIsInf(y) &&
             ((absbi > 0.0) == (y > 0.0)))) {
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

/*
 * Arguments    : double u0
 *                double u1
 * Return Type  : double
 */
static double rt_atan2d_snf(double u0, double u1)
{
  double y;
  int b_u0;
  int b_u1;
  if (rtIsNaN(u0) || rtIsNaN(u1)) {
    y = rtNaN;
  } else if (rtIsInf(u0) && rtIsInf(u1)) {
    if (u0 > 0.0) {
      b_u0 = 1;
    } else {
      b_u0 = -1;
    }

    if (u1 > 0.0) {
      b_u1 = 1;
    } else {
      b_u1 = -1;
    }

    y = atan2(b_u0, b_u1);
  } else if (u1 == 0.0) {
    if (u0 > 0.0) {
      y = RT_PI / 2.0;
    } else if (u0 < 0.0) {
      y = -(double)(RT_PI / 2.0);
    } else {
      y = 0.0;
    }
  } else {
    y = atan2(u0, u1);
  }

  return y;
}

/*
 * stats: n-by-6, each row contains 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid',
 *  of the kth component in labeled image L. Centroid is 2D
 * Arguments    : const double L[1920000]
 *                emxArray_creal_T *stats
 * Return Type  : void
 */
void region_properties_for_srcgen(const double L[1920000], emxArray_creal_T
  *stats)
{
  double maxval[1600];
  int ix;
  int iy;
  int idx;
  int ixstart;
  double mtmp;
  int br;
  boolean_T exitg5;
  boolean_T exitg4;
  int i9;
  int n;
  emxArray_real_T *ff;
  emxArray_real_T *X;
  emxArray_real_T *X_minus_mu;
  emxArray_real_T *I;
  emxArray_real_T *J;
  emxArray_real_T *a;
  emxArray_int32_T *ii;
  emxArray_int32_T *vk;
  static boolean_T x[1920000];
  boolean_T exitg3;
  boolean_T guard1 = false;
  double mu[2];
  double y[4];
  int ic;
  int ia;
  double b_y[4];
  creal_T D[2];
  creal_T b_mtmp;
  boolean_T exitg2;
  creal_T c_mtmp;
  boolean_T exitg1;
  double y_re;
  double bim;
  double brm;
  double d;
  double Centroid[2];

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
  ix = 0;
  iy = -1;
  for (idx = 0; idx < 1600; idx++) {
    ix += 1200;
    ixstart = ix - 1199;
    mtmp = L[ix - 1200];
    if (rtIsNaN(L[ix - 1200])) {
      br = ix - 1198;
      exitg5 = false;
      while ((!exitg5) && (br <= ix)) {
        ixstart = br;
        if (!rtIsNaN(L[br - 1])) {
          mtmp = L[br - 1];
          exitg5 = true;
        } else {
          br++;
        }
      }
    }

    if (ixstart < ix) {
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
  if (rtIsNaN(maxval[0])) {
    ix = 2;
    exitg4 = false;
    while ((!exitg4) && (ix < 1601)) {
      ixstart = ix;
      if (!rtIsNaN(maxval[ix - 1])) {
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

  i9 = stats->size[0] * stats->size[1];
  stats->size[0] = (int)mtmp;
  stats->size[1] = 6;
  emxEnsureCapacity((emxArray__common *)stats, i9, (int)sizeof(creal_T));
  idx = (int)mtmp * 6;
  for (i9 = 0; i9 < idx; i9++) {
    stats->data[i9].re = 0.0;
    stats->data[i9].im = 0.0;
  }

  n = 0;
  b_emxInit_real_T(&ff, 1);
  emxInit_real_T(&X, 2);
  emxInit_real_T(&X_minus_mu, 2);
  b_emxInit_real_T(&I, 1);
  b_emxInit_real_T(&J, 1);
  emxInit_real_T(&a, 2);
  emxInit_int32_T(&ii, 1);
  emxInit_int32_T(&vk, 1);
  while (n <= (int)mtmp - 1) {
    for (i9 = 0; i9 < 1920000; i9++) {
      x[i9] = (L[i9] == 1.0 + (double)n);
    }

    idx = 0;
    i9 = ii->size[0];
    ii->size[0] = 1920000;
    emxEnsureCapacity((emxArray__common *)ii, i9, (int)sizeof(int));
    iy = 1;
    exitg3 = false;
    while ((!exitg3) && (iy < 1920001)) {
      guard1 = false;
      if (x[iy - 1]) {
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

    i9 = ii->size[0];
    if (1 > idx) {
      ii->size[0] = 0;
    } else {
      ii->size[0] = idx;
    }

    emxEnsureCapacity((emxArray__common *)ii, i9, (int)sizeof(int));
    i9 = ff->size[0];
    ff->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)ff, i9, (int)sizeof(double));
    idx = ii->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      ff->data[i9] = ii->data[i9];
    }

    i9 = ii->size[0];
    ii->size[0] = ff->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i9, (int)sizeof(int));
    idx = ff->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      ii->data[i9] = (int)ff->data[i9];
    }

    i9 = ii->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i9, (int)sizeof(int));
    idx = ii->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      ii->data[i9]--;
    }

    i9 = vk->size[0];
    vk->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)vk, i9, (int)sizeof(int));
    idx = ii->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      iy = ii->data[i9];
      vk->data[i9] = iy / 1200;
    }

    i9 = ii->size[0];
    emxEnsureCapacity((emxArray__common *)ii, i9, (int)sizeof(int));
    idx = ii->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      ii->data[i9] -= vk->data[i9] * 1200;
    }

    i9 = I->size[0];
    I->size[0] = ii->size[0];
    emxEnsureCapacity((emxArray__common *)I, i9, (int)sizeof(double));
    idx = ii->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      I->data[i9] = ii->data[i9] + 1;
    }

    i9 = J->size[0];
    J->size[0] = vk->size[0];
    emxEnsureCapacity((emxArray__common *)J, i9, (int)sizeof(double));
    idx = vk->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      J->data[i9] = vk->data[i9] + 1;
    }

    iy = I->size[0];
    idx = J->size[0];
    i9 = X->size[0] * X->size[1];
    X->size[0] = iy;
    X->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)X, i9, (int)sizeof(double));
    for (i9 = 0; i9 < iy; i9++) {
      X->data[i9] = I->data[i9];
    }

    for (i9 = 0; i9 < idx; i9++) {
      X->data[i9 + X->size[0]] = J->data[i9];
    }

    mean(X, mu);
    e_repmat(mu, X->size[0], X_minus_mu);
    i9 = X_minus_mu->size[0] * X_minus_mu->size[1];
    X_minus_mu->size[0] = X->size[0];
    X_minus_mu->size[1] = 2;
    emxEnsureCapacity((emxArray__common *)X_minus_mu, i9, (int)sizeof(double));
    idx = X->size[0] * X->size[1];
    for (i9 = 0; i9 < idx; i9++) {
      X_minus_mu->data[i9] = X->data[i9] - X_minus_mu->data[i9];
    }

    i9 = a->size[0] * a->size[1];
    a->size[0] = 2;
    a->size[1] = X_minus_mu->size[0];
    emxEnsureCapacity((emxArray__common *)a, i9, (int)sizeof(double));
    idx = X_minus_mu->size[0];
    for (i9 = 0; i9 < idx; i9++) {
      for (iy = 0; iy < 2; iy++) {
        a->data[iy + a->size[0] * i9] = X_minus_mu->data[i9 + X_minus_mu->size[0]
          * iy];
      }
    }

    if ((a->size[1] == 1) || (X_minus_mu->size[0] == 1)) {
      for (i9 = 0; i9 < 2; i9++) {
        for (iy = 0; iy < 2; iy++) {
          y[i9 + (iy << 1)] = 0.0;
          idx = a->size[1];
          for (br = 0; br < idx; br++) {
            y[i9 + (iy << 1)] += a->data[i9 + a->size[0] * br] *
              X_minus_mu->data[br + X_minus_mu->size[0] * iy];
          }
        }
      }
    } else {
      idx = a->size[1];
      for (i9 = 0; i9 < 4; i9++) {
        y[i9] = 0.0;
      }

      for (iy = 0; iy < 4; iy += 2) {
        for (ic = iy; ic + 1 <= iy + 2; ic++) {
          y[ic] = 0.0;
        }
      }

      br = 0;
      for (iy = 0; iy < 4; iy += 2) {
        ix = 0;
        i9 = br + idx;
        for (ixstart = br; ixstart + 1 <= i9; ixstart++) {
          if (X_minus_mu->data[ixstart] != 0.0) {
            ia = ix;
            for (ic = iy; ic + 1 <= iy + 2; ic++) {
              ia++;
              y[ic] += X_minus_mu->data[ixstart] * a->data[ia - 1];
            }
          }

          ix += 2;
        }

        br += idx;
      }
    }

    iy = X->size[0];
    for (i9 = 0; i9 < 4; i9++) {
      b_y[i9] = y[i9] / (double)iy;
    }

    eig(b_y, D);
    ixstart = 1;
    b_mtmp = D[0];
    if (rtIsNaN(D[0].re) || rtIsNaN(D[0].im)) {
      ix = 2;
      exitg2 = false;
      while ((!exitg2) && (ix < 3)) {
        ixstart = 2;
        if (!(rtIsNaN(D[1].re) || rtIsNaN(D[1].im))) {
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
    if (rtIsNaN(D[0].re) || rtIsNaN(D[0].im)) {
      ix = 2;
      exitg1 = false;
      while ((!exitg1) && (ix < 3)) {
        ixstart = 2;
        if (!(rtIsNaN(D[1].re) || rtIsNaN(D[1].im))) {
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

    if (b_mtmp.im == 0.0) {
      if (c_mtmp.im == 0.0) {
        y_re = c_mtmp.re / b_mtmp.re;
        bim = 0.0;
      } else if (c_mtmp.re == 0.0) {
        y_re = 0.0;
        bim = c_mtmp.im / b_mtmp.re;
      } else {
        y_re = c_mtmp.re / b_mtmp.re;
        bim = c_mtmp.im / b_mtmp.re;
      }
    } else if (b_mtmp.re == 0.0) {
      if (c_mtmp.re == 0.0) {
        y_re = c_mtmp.im / b_mtmp.im;
        bim = 0.0;
      } else if (c_mtmp.im == 0.0) {
        y_re = 0.0;
        bim = -(c_mtmp.re / b_mtmp.im);
      } else {
        y_re = c_mtmp.im / b_mtmp.im;
        bim = -(c_mtmp.re / b_mtmp.im);
      }
    } else {
      brm = fabs(b_mtmp.re);
      bim = fabs(b_mtmp.im);
      if (brm > bim) {
        bim = b_mtmp.im / b_mtmp.re;
        d = b_mtmp.re + bim * b_mtmp.im;
        y_re = (c_mtmp.re + bim * c_mtmp.im) / d;
        bim = (c_mtmp.im - bim * c_mtmp.re) / d;
      } else if (bim == brm) {
        if (b_mtmp.re > 0.0) {
          bim = 0.5;
        } else {
          bim = -0.5;
        }

        if (b_mtmp.im > 0.0) {
          d = 0.5;
        } else {
          d = -0.5;
        }

        y_re = (c_mtmp.re * bim + c_mtmp.im * d) / brm;
        bim = (c_mtmp.im * bim - c_mtmp.re * d) / brm;
      } else {
        bim = b_mtmp.re / b_mtmp.im;
        d = b_mtmp.im + bim * b_mtmp.re;
        y_re = (bim * c_mtmp.re + c_mtmp.im) / d;
        bim = (bim * c_mtmp.im - c_mtmp.re) / d;
      }
    }

    c_sum(X, mu);
    c_rdivide(mu, ff->size[0], Centroid);
    stats->data[n] = b_mtmp;
    stats->data[n + stats->size[0]] = c_mtmp;
    stats->data[n + (stats->size[0] << 1)].re = 1.0 - (y_re * y_re - bim * bim);
    stats->data[n + (stats->size[0] << 1)].im = 0.0 - (y_re * bim + bim * y_re);
    b_sqrt(&stats->data[n + (stats->size[0] << 1)]);
    stats->data[n + stats->size[0] * 3].re = 1.0;
    stats->data[n + stats->size[0] * 3].im = 0.0;
    for (i9 = 0; i9 < 2; i9++) {
      stats->data[n + stats->size[0] * (4 + i9)].re = Centroid[i9];
      stats->data[n + stats->size[0] * (4 + i9)].im = 0.0;
    }

    n++;
  }

  emxFree_int32_T(&vk);
  emxFree_int32_T(&ii);
  emxFree_real_T(&a);
  emxFree_real_T(&J);
  emxFree_real_T(&I);
  emxFree_real_T(&X_minus_mu);
  emxFree_real_T(&X);
  emxFree_real_T(&ff);
}

/*
 * File trailer for region_properties_for_srcgen.c
 *
 * [EOF]
 */
