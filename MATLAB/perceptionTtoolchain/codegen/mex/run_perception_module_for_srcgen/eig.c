/*
 * eig.c
 *
 * Code generation for function 'eig'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "eig.h"
#include "eml_warning.h"
#include "mod.h"
#include "eml_error.h"
#include "eml_int_forloop_overflow_check.h"
#include "sqrt.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo wc_emlrtRSI = { 62, "eig",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m"
};

static emlrtRSInfo xc_emlrtRSI = { 71, "eig",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\matfun\\eig.m"
};

static emlrtRSInfo yc_emlrtRSI = { 11, "eml_xgeev",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\eml_xgeev.m"
};

static emlrtRSInfo ad_emlrtRSI = { 24, "eml_lapack_xgeev",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\internal\\eml_lapack_xgeev.m"
};

static emlrtRSInfo dd_emlrtRSI = { 124, "eml_matlab_zggev",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggev.m"
};

static emlrtRSInfo ed_emlrtRSI = { 125, "eml_matlab_zggev",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggev.m"
};

static emlrtRSInfo nd_emlrtRSI = { 62, "eml_matlab_zgghrd",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zgghrd.m"
};

static emlrtRSInfo od_emlrtRSI = { 64, "eml_matlab_zgghrd",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zgghrd.m"
};

static emlrtRSInfo pd_emlrtRSI = { 77, "eml_matlab_zgghrd",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zgghrd.m"
};

static emlrtRSInfo qd_emlrtRSI = { 67, "eml_matlab_zlartg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlartg.m"
};

static emlrtRSInfo rd_emlrtRSI = { 93, "eml_matlab_zlartg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlartg.m"
};

static emlrtRSInfo sd_emlrtRSI = { 102, "eml_matlab_zlartg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlartg.m"
};

static emlrtRSInfo td_emlrtRSI = { 106, "eml_matlab_zlartg",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlartg.m"
};

static emlrtRSInfo ud_emlrtRSI = { 10, "eml_zrot_rows",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_zrot_rows.m"
};

static emlrtRSInfo vd_emlrtRSI = { 10, "eml_zrot_cols",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_zrot_cols.m"
};

static emlrtRSInfo wd_emlrtRSI = { 447, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo xd_emlrtRSI = { 435, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo yd_emlrtRSI = { 421, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo ae_emlrtRSI = { 412, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo be_emlrtRSI = { 402, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo ce_emlrtRSI = { 110, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo de_emlrtRSI = { 37, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

static emlrtRSInfo ee_emlrtRSI = { 20, "eml_matlab_zlanhs",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlanhs.m"
};

static emlrtRSInfo fe_emlrtRSI = { 21, "eml_matlab_zlanhs",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlanhs.m"
};

static emlrtRSInfo ge_emlrtRSI = { 57, "eml_matlab_zlanhs",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zlanhs.m"
};

static emlrtRSInfo gf_emlrtRSI = { 332, "eml_matlab_zhgeqz",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zhgeqz.m"
};

/* Function Declarations */
static void eml_matlab_zgghrd(const emlrtStack *sp, int32_T ilo, int32_T ihi,
  creal_T A[4]);
static void eml_matlab_zhgeqz(const emlrtStack *sp, const creal_T A[4], int32_T
  ilo, int32_T ihi, int32_T *info, creal_T alpha1[2], creal_T beta1[2]);
static void eml_matlab_zlartg(const emlrtStack *sp, const creal_T f, const
  creal_T g, real_T *cs, creal_T *sn);

/* Function Definitions */
static void eml_matlab_zgghrd(const emlrtStack *sp, int32_T ilo, int32_T ihi,
  creal_T A[4])
{
  int32_T jcol;
  int32_T jrow;
  real_T scale;
  real_T f2s;
  real_T g2;
  real_T fs_re;
  real_T fs_im;
  real_T gs_re;
  real_T gs_im;
  int32_T count;
  int32_T rescaledir;
  boolean_T guard1 = false;
  real_T c;
  real_T d;
  real_T g2s;
  boolean_T b7;
  boolean_T b8;
  boolean_T b9;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  if (ihi < ilo + 2) {
  } else {
    for (jcol = ilo - 1; jcol + 1 < ihi - 1; jcol++) {
      for (jrow = ihi - 2; jrow + 2 > jcol + 2; jrow--) {
        st.site = &nd_emlrtRSI;
        scale = muDoubleScalarAbs(A[jrow + (jcol << 1)].re);
        f2s = muDoubleScalarAbs(A[jrow + (jcol << 1)].im);
        if (f2s > scale) {
          scale = f2s;
        }

        f2s = muDoubleScalarAbs(A[(jrow + (jcol << 1)) + 1].re);
        g2 = muDoubleScalarAbs(A[(jrow + (jcol << 1)) + 1].im);
        if (g2 > f2s) {
          f2s = g2;
        }

        if (f2s > scale) {
          scale = f2s;
        }

        fs_re = A[jrow + (jcol << 1)].re;
        fs_im = A[jrow + (jcol << 1)].im;
        gs_re = A[(jrow + (jcol << 1)) + 1].re;
        gs_im = A[(jrow + (jcol << 1)) + 1].im;
        count = 0;
        rescaledir = 0;
        guard1 = false;
        if (scale >= 7.4428285367870146E+137) {
          do {
            count++;
            fs_re *= 1.3435752215134178E-138;
            fs_im *= 1.3435752215134178E-138;
            gs_re *= 1.3435752215134178E-138;
            gs_im *= 1.3435752215134178E-138;
            scale *= 1.3435752215134178E-138;
          } while (!(scale < 7.4428285367870146E+137));

          rescaledir = 1;
          guard1 = true;
        } else if (scale <= 1.3435752215134178E-138) {
          if ((A[(jrow + (jcol << 1)) + 1].re == 0.0) && (A[(jrow + (jcol << 1))
               + 1].im == 0.0)) {
            c = 1.0;
            gs_re = 0.0;
            gs_im = 0.0;
            fs_re = A[jrow + (jcol << 1)].re;
            fs_im = A[jrow + (jcol << 1)].im;
          } else {
            do {
              count++;
              fs_re *= 7.4428285367870146E+137;
              fs_im *= 7.4428285367870146E+137;
              gs_re *= 7.4428285367870146E+137;
              gs_im *= 7.4428285367870146E+137;
              scale *= 7.4428285367870146E+137;
            } while (!(scale > 1.3435752215134178E-138));

            rescaledir = -1;
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          scale = fs_re * fs_re + fs_im * fs_im;
          g2 = gs_re * gs_re + gs_im * gs_im;
          f2s = g2;
          if (1.0 > g2) {
            f2s = 1.0;
          }

          if (scale <= f2s * 2.0041683600089728E-292) {
            if ((A[jrow + (jcol << 1)].re == 0.0) && (A[jrow + (jcol << 1)].im ==
                 0.0)) {
              c = 0.0;
              fs_re = muDoubleScalarHypot(A[(jrow + (jcol << 1)) + 1].re, A
                [(jrow + (jcol << 1)) + 1].im);
              fs_im = 0.0;
              d = muDoubleScalarHypot(gs_re, gs_im);
              gs_re /= d;
              gs_im = -gs_im / d;
            } else {
              b_st.site = &qd_emlrtRSI;
              if (g2 < 0.0) {
                c_st.site = &hb_emlrtRSI;
                eml_error(&c_st);
              }

              g2s = muDoubleScalarSqrt(g2);
              c = muDoubleScalarHypot(fs_re, fs_im) / g2s;
              f2s = muDoubleScalarAbs(A[jrow + (jcol << 1)].re);
              g2 = muDoubleScalarAbs(A[jrow + (jcol << 1)].im);
              if (g2 > f2s) {
                f2s = g2;
              }

              if (f2s > 1.0) {
                d = muDoubleScalarHypot(A[jrow + (jcol << 1)].re, A[jrow + (jcol
                  << 1)].im);
                fs_re = A[jrow + (jcol << 1)].re / d;
                fs_im = A[jrow + (jcol << 1)].im / d;
              } else {
                g2 = 7.4428285367870146E+137 * A[jrow + (jcol << 1)].re;
                scale = 7.4428285367870146E+137 * A[jrow + (jcol << 1)].im;
                d = muDoubleScalarHypot(g2, scale);
                fs_re = g2 / d;
                fs_im = scale / d;
              }

              g2 = gs_re / g2s;
              gs_im = -gs_im / g2s;
              gs_re = fs_re * g2 - fs_im * gs_im;
              gs_im = fs_re * gs_im + fs_im * g2;
              fs_re = c * A[jrow + (jcol << 1)].re + (gs_re * A[(jrow + (jcol <<
                1)) + 1].re - gs_im * A[(jrow + (jcol << 1)) + 1].im);
              fs_im = c * A[jrow + (jcol << 1)].im + (gs_re * A[(jrow + (jcol <<
                1)) + 1].im + gs_im * A[(jrow + (jcol << 1)) + 1].re);
            }
          } else {
            b_st.site = &rd_emlrtRSI;
            f2s = 1.0 + g2 / scale;
            if (f2s < 0.0) {
              c_st.site = &hb_emlrtRSI;
              eml_error(&c_st);
            }

            f2s = muDoubleScalarSqrt(f2s);
            fs_re *= f2s;
            fs_im *= f2s;
            c = 1.0 / f2s;
            d = scale + g2;
            f2s = fs_re / d;
            scale = fs_im / d;
            g2 = gs_re;
            gs_re = f2s * gs_re - scale * -gs_im;
            gs_im = f2s * -gs_im + scale * g2;
            if (rescaledir > 0) {
              b_st.site = &sd_emlrtRSI;
              if (1 > count) {
                b7 = false;
              } else {
                b7 = (count > 2147483646);
              }

              if (b7) {
                c_st.site = &p_emlrtRSI;
                check_forloop_overflow_error(&c_st);
              }

              for (rescaledir = 1; rescaledir <= count; rescaledir++) {
                fs_re *= 7.4428285367870146E+137;
                fs_im *= 7.4428285367870146E+137;
              }
            } else {
              if (rescaledir < 0) {
                b_st.site = &td_emlrtRSI;
                if (1 > count) {
                  b8 = false;
                } else {
                  b8 = (count > 2147483646);
                }

                if (b8) {
                  c_st.site = &p_emlrtRSI;
                  check_forloop_overflow_error(&c_st);
                }

                for (rescaledir = 1; rescaledir <= count; rescaledir++) {
                  fs_re *= 1.3435752215134178E-138;
                  fs_im *= 1.3435752215134178E-138;
                }
              }
            }
          }
        }

        A[jrow + (jcol << 1)].re = fs_re;
        A[jrow + (jcol << 1)].im = fs_im;
        A[(jrow + (jcol << 1)) + 1].re = 0.0;
        A[(jrow + (jcol << 1)) + 1].im = 0.0;
        st.site = &od_emlrtRSI;
        b_st.site = &ud_emlrtRSI;
        if (1 > ihi) {
          b9 = false;
        } else {
          b9 = (ihi > 2147483646);
        }

        if (b9) {
          c_st.site = &p_emlrtRSI;
          check_forloop_overflow_error(&c_st);
        }

        for (rescaledir = 0; rescaledir + 1 <= ihi; rescaledir++) {
          fs_re = c * A[rescaledir << 1].re + (gs_re * A[1 + (rescaledir << 1)].
            re - gs_im * A[1 + (rescaledir << 1)].im);
          fs_im = c * A[rescaledir << 1].im + (gs_re * A[1 + (rescaledir << 1)].
            im + gs_im * A[1 + (rescaledir << 1)].re);
          scale = A[rescaledir << 1].im;
          f2s = A[rescaledir << 1].re;
          A[1 + (rescaledir << 1)].re = c * A[1 + (rescaledir << 1)].re - (gs_re
            * A[rescaledir << 1].re + gs_im * A[rescaledir << 1].im);
          A[1 + (rescaledir << 1)].im = c * A[1 + (rescaledir << 1)].im - (gs_re
            * scale - gs_im * f2s);
          A[rescaledir << 1].re = fs_re;
          A[rescaledir << 1].im = fs_im;
        }

        gs_re = -gs_re;
        gs_im = -gs_im;
        st.site = &pd_emlrtRSI;
        b_st.site = &vd_emlrtRSI;
        for (rescaledir = ilo - 1; rescaledir + 1 < 3; rescaledir++) {
          fs_re = c * A[2 + rescaledir].re + (gs_re * A[rescaledir].re - gs_im *
            A[rescaledir].im);
          fs_im = c * A[2 + rescaledir].im + (gs_re * A[rescaledir].im + gs_im *
            A[rescaledir].re);
          scale = A[2 + rescaledir].im;
          f2s = A[2 + rescaledir].re;
          A[rescaledir].re = c * A[rescaledir].re - (gs_re * A[2 + rescaledir].
            re + gs_im * A[2 + rescaledir].im);
          A[rescaledir].im = c * A[rescaledir].im - (gs_re * scale - gs_im * f2s);
          A[2 + rescaledir].re = fs_re;
          A[2 + rescaledir].im = fs_im;
        }
      }
    }
  }
}

static void eml_matlab_zhgeqz(const emlrtStack *sp, const creal_T A[4], int32_T
  ilo, int32_T ihi, int32_T *info, creal_T alpha1[2], creal_T beta1[2])
{
  creal_T b_A[4];
  int32_T i;
  real_T eshift_re;
  real_T eshift_im;
  creal_T ctemp;
  real_T rho_re;
  real_T rho_im;
  real_T anorm;
  real_T sumsq;
  boolean_T firstNonZero;
  boolean_T b_ilo;
  int32_T j;
  int32_T jp1;
  boolean_T c_ilo;
  real_T reAij;
  real_T imAij;
  real_T temp1;
  real_T temp2;
  real_T b_atol;
  boolean_T failed;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  int32_T ifirst;
  int32_T istart;
  int32_T ilast;
  int32_T ilastm1;
  int32_T ifrstm;
  int32_T ilastm;
  int32_T iiter;
  int32_T maxit;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  boolean_T b1;
  int32_T jiter;
  int32_T exitg1;
  boolean_T exitg3;
  boolean_T b_guard1 = false;
  creal_T t1;
  creal_T d;
  boolean_T exitg2;
  boolean_T b2;
  boolean_T b3;
  boolean_T b4;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  memcpy(&b_A[0], &A[0], sizeof(creal_T) << 2);
  *info = 0;
  for (i = 0; i < 2; i++) {
    alpha1[i].re = 0.0;
    alpha1[i].im = 0.0;
    beta1[i].re = 1.0;
    beta1[i].im = 0.0;
  }

  eshift_re = 0.0;
  eshift_im = 0.0;
  ctemp.re = 0.0;
  ctemp.im = 0.0;
  rho_re = 0.0;
  rho_im = 0.0;
  st.site = &de_emlrtRSI;
  anorm = 0.0;
  if (ilo > ihi) {
  } else {
    anorm = 0.0;
    sumsq = 0.0;
    firstNonZero = true;
    b_st.site = &ee_emlrtRSI;
    if (ilo > ihi) {
      b_ilo = false;
    } else {
      b_ilo = (ihi > 2147483646);
    }

    if (b_ilo) {
      c_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&c_st);
    }

    for (j = ilo; j <= ihi; j++) {
      jp1 = j + 1;
      if (ihi < j + 1) {
        jp1 = ihi;
      }

      b_st.site = &fe_emlrtRSI;
      if (ilo > jp1) {
        c_ilo = false;
      } else {
        c_ilo = (jp1 > 2147483646);
      }

      if (c_ilo) {
        c_st.site = &p_emlrtRSI;
        check_forloop_overflow_error(&c_st);
      }

      for (i = ilo; i <= jp1; i++) {
        reAij = A[(i + ((j - 1) << 1)) - 1].re;
        imAij = A[(i + ((j - 1) << 1)) - 1].im;
        if (reAij != 0.0) {
          temp1 = muDoubleScalarAbs(reAij);
          if (firstNonZero) {
            sumsq = 1.0;
            anorm = temp1;
            firstNonZero = false;
          } else if (anorm < temp1) {
            temp2 = anorm / temp1;
            sumsq = 1.0 + sumsq * temp2 * temp2;
            anorm = temp1;
          } else {
            temp2 = temp1 / anorm;
            sumsq += temp2 * temp2;
          }
        }

        if (imAij != 0.0) {
          temp1 = muDoubleScalarAbs(imAij);
          if (firstNonZero) {
            sumsq = 1.0;
            anorm = temp1;
            firstNonZero = false;
          } else if (anorm < temp1) {
            temp2 = anorm / temp1;
            sumsq = 1.0 + sumsq * temp2 * temp2;
            anorm = temp1;
          } else {
            temp2 = temp1 / anorm;
            sumsq += temp2 * temp2;
          }
        }
      }
    }

    b_st.site = &ge_emlrtRSI;
    if (sumsq < 0.0) {
      c_st.site = &hb_emlrtRSI;
      eml_error(&c_st);
    }

    anorm *= muDoubleScalarSqrt(sumsq);
  }

  reAij = 2.2204460492503131E-16 * anorm;
  b_atol = 2.2250738585072014E-308;
  if (reAij > 2.2250738585072014E-308) {
    b_atol = reAij;
  }

  temp1 = 2.2250738585072014E-308;
  if (anorm > 2.2250738585072014E-308) {
    temp1 = anorm;
  }

  imAij = 1.0 / temp1;
  failed = true;
  j = ihi + 1;
  while (j < 3) {
    alpha1[1] = A[3];
    j = 3;
  }

  guard1 = false;
  guard2 = false;
  if (ihi >= ilo) {
    ifirst = ilo;
    istart = ilo;
    ilast = ihi - 1;
    ilastm1 = ihi - 2;
    ifrstm = ilo;
    ilastm = ihi;
    iiter = 0;
    maxit = 30 * ((ihi - ilo) + 1);
    goto60 = false;
    goto70 = false;
    goto90 = false;
    st.site = &ce_emlrtRSI;
    if (1 > maxit) {
      b1 = false;
    } else {
      b1 = (maxit > 2147483646);
    }

    if (b1) {
      b_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    jiter = 1;
    do {
      exitg1 = 0;
      if (jiter <= maxit) {
        if (ilast + 1 == ilo) {
          goto60 = true;
        } else if (muDoubleScalarAbs(b_A[ilast + (ilastm1 << 1)].re) +
                   muDoubleScalarAbs(b_A[ilast + (ilastm1 << 1)].im) <= b_atol)
        {
          b_A[ilast + (ilastm1 << 1)].re = 0.0;
          b_A[ilast + (ilastm1 << 1)].im = 0.0;
          goto60 = true;
        } else {
          j = ilastm1;
          exitg3 = false;
          while ((!exitg3) && (j + 1 >= ilo)) {
            if (j + 1 == ilo) {
              firstNonZero = true;
            } else if (muDoubleScalarAbs(b_A[j].re) + muDoubleScalarAbs(b_A[j].
                        im) <= b_atol) {
              b_A[j].re = 0.0;
              b_A[j].im = 0.0;
              firstNonZero = true;
            } else {
              firstNonZero = false;
            }

            if (firstNonZero) {
              ifirst = j + 1;
              goto70 = true;
              exitg3 = true;
            } else {
              j--;
            }
          }
        }

        if (goto60 || goto70) {
          firstNonZero = true;
        } else {
          firstNonZero = false;
        }

        if (!firstNonZero) {
          for (i = 0; i < 2; i++) {
            alpha1[i].re = rtNaN;
            alpha1[i].im = 0.0;
            beta1[i].re = rtNaN;
            beta1[i].im = 0.0;
          }

          *info = 1;
          exitg1 = 1;
        } else {
          b_guard1 = false;
          if (goto60) {
            goto60 = false;
            alpha1[ilast] = b_A[ilast + (ilast << 1)];
            ilast = ilastm1;
            ilastm1--;
            if (ilast + 1 < ilo) {
              failed = false;
              guard2 = true;
              exitg1 = 1;
            } else {
              iiter = 0;
              eshift_re = 0.0;
              eshift_im = 0.0;
              ilastm = ilast + 1;
              if (ifrstm > ilast + 1) {
                ifrstm = ilo;
              }

              b_guard1 = true;
            }
          } else {
            if (goto70) {
              goto70 = false;
              iiter++;
              ifrstm = ifirst;
              st.site = &gf_emlrtRSI;
              if (c_mod(&st, iiter) != 0) {
                reAij = -(b_A[ilast + (ilast << 1)].re - b_A[ilastm1 + (ilastm1 <<
                           1)].re);
                temp1 = -(b_A[ilast + (ilast << 1)].im - b_A[ilastm1 + (ilastm1 <<
                           1)].im);
                if (temp1 == 0.0) {
                  t1.re = reAij / 2.0;
                  t1.im = 0.0;
                } else if (reAij == 0.0) {
                  t1.re = 0.0;
                  t1.im = temp1 / 2.0;
                } else {
                  t1.re = reAij / 2.0;
                  t1.im = temp1 / 2.0;
                }

                d.re = (t1.re * t1.re - t1.im * t1.im) + (b_A[ilastm1 + (ilast <<
                  1)].re * b_A[ilast + (ilastm1 << 1)].re - b_A[ilastm1 + (ilast
                  << 1)].im * b_A[ilast + (ilastm1 << 1)].im);
                d.im = (t1.re * t1.im + t1.im * t1.re) + (b_A[ilastm1 + (ilast <<
                  1)].re * b_A[ilast + (ilastm1 << 1)].im + b_A[ilastm1 + (ilast
                  << 1)].im * b_A[ilast + (ilastm1 << 1)].re);
                b_sqrt(&d);
                rho_re = b_A[ilastm1 + (ilastm1 << 1)].re - (t1.re - d.re);
                rho_im = b_A[ilastm1 + (ilastm1 << 1)].im - (t1.im - d.im);
                anorm = b_A[ilastm1 + (ilastm1 << 1)].re - (t1.re + d.re);
                reAij = b_A[ilastm1 + (ilastm1 << 1)].im - (t1.im + d.im);
                if (muDoubleScalarHypot(rho_re - b_A[ilast + (ilast << 1)].re,
                                        rho_im - b_A[ilast + (ilast << 1)].im) <=
                    muDoubleScalarHypot(anorm - b_A[ilast + (ilast << 1)].re,
                                        reAij - b_A[ilast + (ilast << 1)].im)) {
                  anorm = rho_re;
                  reAij = rho_im;
                  rho_re = t1.re - d.re;
                  rho_im = t1.im - d.im;
                } else {
                  rho_re = t1.re + d.re;
                  rho_im = t1.im + d.im;
                }
              } else {
                eshift_re += b_A[ilast + (ilastm1 << 1)].re;
                eshift_im += b_A[ilast + (ilastm1 << 1)].im;
                anorm = eshift_re;
                reAij = eshift_im;
              }

              j = ilastm1;
              jp1 = ilastm1 + 1;
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = 2;
                ctemp.re = b_A[3].re - anorm;
                ctemp.im = b_A[3].im - reAij;
                temp1 = imAij * (muDoubleScalarAbs(ctemp.re) + muDoubleScalarAbs
                                 (ctemp.im));
                temp2 = imAij * (muDoubleScalarAbs(b_A[2 + jp1].re) +
                                 muDoubleScalarAbs(b_A[2 + jp1].im));
                sumsq = temp1;
                if (temp2 > temp1) {
                  sumsq = temp2;
                }

                if ((sumsq < 1.0) && (sumsq != 0.0)) {
                  temp1 /= sumsq;
                  temp2 /= sumsq;
                }

                if ((muDoubleScalarAbs(b_A[1].re) + muDoubleScalarAbs(b_A[1].im))
                    * temp2 <= temp1 * b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
                  jp1 = 1;
                  j = 0;
                }
              }

              if (!goto90) {
                istart = ifirst;
                if (ifirst == ilastm1 + 1) {
                  ctemp.re = rho_re;
                  ctemp.im = rho_im;
                } else {
                  ctemp.re = b_A[(ifirst + ((ifirst - 1) << 1)) - 1].re - anorm;
                  ctemp.im = b_A[(ifirst + ((ifirst - 1) << 1)) - 1].im - reAij;
                }

                goto90 = true;
              }
            }

            if (goto90) {
              goto90 = false;
              st.site = &be_emlrtRSI;
              eml_matlab_zlartg(&st, ctemp, b_A[1 + ((istart - 1) << 1)], &anorm,
                                &t1);
              j = istart;
              while (j < ilast + 1) {
                st.site = &ae_emlrtRSI;
                b_st.site = &ud_emlrtRSI;
                if (1 > ilastm) {
                  b2 = false;
                } else {
                  b2 = (ilastm > 2147483646);
                }

                if (b2) {
                  c_st.site = &p_emlrtRSI;
                  check_forloop_overflow_error(&c_st);
                }

                for (j = 0; j + 1 <= ilastm; j++) {
                  d.re = anorm * b_A[j << 1].re + (t1.re * b_A[1 + (j << 1)].re
                    - t1.im * b_A[1 + (j << 1)].im);
                  d.im = anorm * b_A[j << 1].im + (t1.re * b_A[1 + (j << 1)].im
                    + t1.im * b_A[1 + (j << 1)].re);
                  reAij = b_A[j << 1].im;
                  temp1 = b_A[j << 1].re;
                  b_A[1 + (j << 1)].re = anorm * b_A[1 + (j << 1)].re - (t1.re *
                    b_A[j << 1].re + t1.im * b_A[j << 1].im);
                  b_A[1 + (j << 1)].im = anorm * b_A[1 + (j << 1)].im - (t1.re *
                    reAij - t1.im * temp1);
                  b_A[j << 1] = d;
                }

                t1.re = -t1.re;
                t1.im = -t1.im;
                st.site = &yd_emlrtRSI;
                b_st.site = &vd_emlrtRSI;
                for (i = ifrstm - 1; i + 1 < 3; i++) {
                  d.re = anorm * b_A[2 + i].re + (t1.re * b_A[i].re - t1.im *
                    b_A[i].im);
                  d.im = anorm * b_A[2 + i].im + (t1.re * b_A[i].im + t1.im *
                    b_A[i].re);
                  reAij = b_A[2 + i].im;
                  temp1 = b_A[2 + i].re;
                  b_A[i].re = anorm * b_A[i].re - (t1.re * b_A[2 + i].re + t1.im
                    * b_A[2 + i].im);
                  b_A[i].im = anorm * b_A[i].im - (t1.re * reAij - t1.im * temp1);
                  b_A[2 + i] = d;
                }

                j = 2;
              }
            }

            b_guard1 = true;
          }

          if (b_guard1) {
            jiter++;
          }
        }
      } else {
        guard2 = true;
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  } else {
    guard1 = true;
  }

  if (guard2) {
    if (failed) {
      *info = ilast + 1;
      st.site = &xd_emlrtRSI;
      if (1 > ilast + 1) {
        b3 = false;
      } else {
        b3 = (ilast + 1 > 2147483646);
      }

      if (b3) {
        b_st.site = &p_emlrtRSI;
        check_forloop_overflow_error(&b_st);
      }

      for (jp1 = 0; jp1 + 1 <= ilast + 1; jp1++) {
        alpha1[jp1].re = rtNaN;
        alpha1[jp1].im = 0.0;
        beta1[jp1].re = rtNaN;
        beta1[jp1].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    st.site = &wd_emlrtRSI;
    if (1 > ilo - 1) {
      b4 = false;
    } else {
      b4 = (ilo - 1 > 2147483646);
    }

    if (b4) {
      b_st.site = &p_emlrtRSI;
      check_forloop_overflow_error(&b_st);
    }

    for (j = 0; j + 1 < ilo; j++) {
      alpha1[j] = b_A[j + (j << 1)];
    }
  }
}

static void eml_matlab_zlartg(const emlrtStack *sp, const creal_T f, const
  creal_T g, real_T *cs, creal_T *sn)
{
  real_T scale;
  real_T f2s;
  real_T g2;
  real_T fs_re;
  real_T fs_im;
  real_T gs_re;
  real_T gs_im;
  int32_T count;
  int32_T rescaledir;
  boolean_T guard1 = false;
  real_T g2s;
  boolean_T b5;
  boolean_T b6;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  scale = muDoubleScalarAbs(f.re);
  f2s = muDoubleScalarAbs(f.im);
  if (f2s > scale) {
    scale = f2s;
  }

  f2s = muDoubleScalarAbs(g.re);
  g2 = muDoubleScalarAbs(g.im);
  if (g2 > f2s) {
    f2s = g2;
  }

  if (f2s > scale) {
    scale = f2s;
  }

  fs_re = f.re;
  fs_im = f.im;
  gs_re = g.re;
  gs_im = g.im;
  count = 0;
  rescaledir = 0;
  guard1 = false;
  if (scale >= 7.4428285367870146E+137) {
    do {
      count++;
      fs_re *= 1.3435752215134178E-138;
      fs_im *= 1.3435752215134178E-138;
      gs_re *= 1.3435752215134178E-138;
      gs_im *= 1.3435752215134178E-138;
      scale *= 1.3435752215134178E-138;
    } while (!(scale < 7.4428285367870146E+137));

    rescaledir = 1;
    guard1 = true;
  } else if (scale <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
    } else {
      do {
        count++;
        fs_re *= 7.4428285367870146E+137;
        fs_im *= 7.4428285367870146E+137;
        gs_re *= 7.4428285367870146E+137;
        gs_im *= 7.4428285367870146E+137;
        scale *= 7.4428285367870146E+137;
      } while (!(scale > 1.3435752215134178E-138));

      rescaledir = -1;
      guard1 = true;
    }
  } else {
    guard1 = true;
  }

  if (guard1) {
    scale = fs_re * fs_re + fs_im * fs_im;
    g2 = gs_re * gs_re + gs_im * gs_im;
    f2s = g2;
    if (1.0 > g2) {
      f2s = 1.0;
    }

    if (scale <= f2s * 2.0041683600089728E-292) {
      if ((f.re == 0.0) && (f.im == 0.0)) {
        *cs = 0.0;
        scale = muDoubleScalarHypot(gs_re, gs_im);
        sn->re = gs_re / scale;
        sn->im = -gs_im / scale;
      } else {
        st.site = &qd_emlrtRSI;
        if (g2 < 0.0) {
          b_st.site = &hb_emlrtRSI;
          eml_error(&b_st);
        }

        g2s = muDoubleScalarSqrt(g2);
        *cs = muDoubleScalarHypot(fs_re, fs_im) / g2s;
        f2s = muDoubleScalarAbs(f.re);
        g2 = muDoubleScalarAbs(f.im);
        if (g2 > f2s) {
          f2s = g2;
        }

        if (f2s > 1.0) {
          scale = muDoubleScalarHypot(f.re, f.im);
          fs_re = f.re / scale;
          fs_im = f.im / scale;
        } else {
          f2s = 7.4428285367870146E+137 * f.re;
          g2 = 7.4428285367870146E+137 * f.im;
          scale = muDoubleScalarHypot(f2s, g2);
          fs_re = f2s / scale;
          fs_im = g2 / scale;
        }

        gs_re /= g2s;
        gs_im = -gs_im / g2s;
        sn->re = fs_re * gs_re - fs_im * gs_im;
        sn->im = fs_re * gs_im + fs_im * gs_re;
      }
    } else {
      st.site = &rd_emlrtRSI;
      f2s = 1.0 + g2 / scale;
      if (f2s < 0.0) {
        b_st.site = &hb_emlrtRSI;
        eml_error(&b_st);
      }

      f2s = muDoubleScalarSqrt(f2s);
      *cs = 1.0 / f2s;
      scale += g2;
      fs_re = f2s * fs_re / scale;
      fs_im = f2s * fs_im / scale;
      sn->re = fs_re * gs_re - fs_im * -gs_im;
      sn->im = fs_re * -gs_im + fs_im * gs_re;
      if (rescaledir > 0) {
        st.site = &sd_emlrtRSI;
        if (1 > count) {
          b5 = false;
        } else {
          b5 = (count > 2147483646);
        }

        if (b5) {
          b_st.site = &p_emlrtRSI;
          check_forloop_overflow_error(&b_st);
        }
      } else {
        if (rescaledir < 0) {
          st.site = &td_emlrtRSI;
          if (1 > count) {
            b6 = false;
          } else {
            b6 = (count > 2147483646);
          }

          if (b6) {
            b_st.site = &p_emlrtRSI;
            check_forloop_overflow_error(&b_st);
          }
        }
      }
    }
  }
}

void eig(const emlrtStack *sp, const real_T A[4], creal_T V[2])
{
  creal_T b_A[4];
  int32_T ii;
  int32_T nzcount;
  real_T anrm;
  boolean_T exitg5;
  real_T absxk;
  creal_T beta1[2];
  int32_T i;
  boolean_T ilascl;
  real_T anrmto;
  real_T ctoc;
  boolean_T notdone;
  real_T cfrom1;
  real_T cto1;
  real_T mul;
  int32_T ilo;
  int32_T ihi;
  int32_T j;
  boolean_T exitg3;
  int32_T jj;
  boolean_T exitg4;
  boolean_T guard2 = false;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1 = false;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  st.prev = sp;
  st.tls = sp->tls;
  st.site = &wc_emlrtRSI;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  for (ii = 0; ii < 4; ii++) {
    b_A[ii].re = A[ii];
    b_A[ii].im = 0.0;
  }

  b_st.site = &yc_emlrtRSI;
  c_st.site = &ad_emlrtRSI;
  nzcount = 0;
  anrm = 0.0;
  ii = 0;
  exitg5 = false;
  while ((!exitg5) && (ii < 4)) {
    absxk = muDoubleScalarHypot(b_A[ii].re, 0.0);
    if (muDoubleScalarIsNaN(absxk)) {
      anrm = rtNaN;
      exitg5 = true;
    } else {
      if (absxk > anrm) {
        anrm = absxk;
      }

      ii++;
    }
  }

  if (!((!muDoubleScalarIsInf(anrm)) && (!muDoubleScalarIsNaN(anrm)))) {
    for (i = 0; i < 2; i++) {
      V[i].re = rtNaN;
      V[i].im = 0.0;
      beta1[i].re = rtNaN;
      beta1[i].im = 0.0;
    }
  } else {
    ilascl = false;
    anrmto = anrm;
    if ((anrm > 0.0) && (anrm < 6.7178761075670888E-139)) {
      anrmto = 6.7178761075670888E-139;
      ilascl = true;
    } else {
      if (anrm > 1.4885657073574029E+138) {
        anrmto = 1.4885657073574029E+138;
        ilascl = true;
      }
    }

    if (ilascl) {
      absxk = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        cfrom1 = absxk * 2.0041683600089728E-292;
        cto1 = ctoc / 4.9896007738368E+291;
        if ((cfrom1 > ctoc) && (ctoc != 0.0)) {
          mul = 2.0041683600089728E-292;
          absxk = cfrom1;
        } else if (cto1 > absxk) {
          mul = 4.9896007738368E+291;
          ctoc = cto1;
        } else {
          mul = ctoc / absxk;
          notdone = false;
        }

        for (ii = 0; ii < 4; ii++) {
          b_A[ii].re *= mul;
          b_A[ii].im *= mul;
        }
      }
    }

    ilo = 1;
    ihi = 2;
    i = 0;
    j = 0;
    notdone = false;
    ii = 2;
    exitg3 = false;
    while ((!exitg3) && (ii > 0)) {
      nzcount = 0;
      i = ii;
      j = 2;
      jj = 1;
      exitg4 = false;
      while ((!exitg4) && (jj <= 2)) {
        guard2 = false;
        if ((b_A[(ii + ((jj - 1) << 1)) - 1].re != 0.0) || (b_A[(ii + ((jj - 1) <<
               1)) - 1].im != 0.0) || (ii == jj)) {
          if (nzcount == 0) {
            j = jj;
            nzcount = 1;
            guard2 = true;
          } else {
            nzcount = 2;
            exitg4 = true;
          }
        } else {
          guard2 = true;
        }

        if (guard2) {
          jj++;
        }
      }

      if (nzcount < 2) {
        notdone = true;
        exitg3 = true;
      } else {
        ii--;
      }
    }

    if (!notdone) {
      i = 0;
      j = 0;
      notdone = false;
      jj = 1;
      exitg1 = false;
      while ((!exitg1) && (jj <= 2)) {
        nzcount = 0;
        i = 2;
        j = jj;
        ii = 1;
        exitg2 = false;
        while ((!exitg2) && (ii <= 2)) {
          guard1 = false;
          if ((b_A[(ii + ((jj - 1) << 1)) - 1].re != 0.0) || (b_A[(ii + ((jj - 1)
                 << 1)) - 1].im != 0.0) || (ii == jj)) {
            if (nzcount == 0) {
              i = ii;
              nzcount = 1;
              guard1 = true;
            } else {
              nzcount = 2;
              exitg2 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            ii++;
          }
        }

        if (nzcount < 2) {
          notdone = true;
          exitg1 = true;
        } else {
          jj++;
        }
      }

      if (!notdone) {
      } else {
        if (i != 1) {
          for (ii = 0; ii + 1 < 3; ii++) {
            absxk = b_A[(i + (ii << 1)) - 1].re;
            ctoc = b_A[(i + (ii << 1)) - 1].im;
            b_A[(i + (ii << 1)) - 1] = b_A[ii << 1];
            b_A[ii << 1].re = absxk;
            b_A[ii << 1].im = ctoc;
          }
        }

        if (j != 1) {
          for (ii = 0; ii < 2; ii++) {
            absxk = b_A[ii + ((j - 1) << 1)].re;
            ctoc = b_A[ii + ((j - 1) << 1)].im;
            b_A[ii + ((j - 1) << 1)] = b_A[ii];
            b_A[ii].re = absxk;
            b_A[ii].im = ctoc;
          }
        }

        ilo = 2;
      }
    } else {
      if (i != 2) {
        for (ii = 0; ii < 2; ii++) {
          absxk = b_A[(i + (ii << 1)) - 1].re;
          ctoc = b_A[(i + (ii << 1)) - 1].im;
          b_A[(i + (ii << 1)) - 1] = b_A[1 + (ii << 1)];
          b_A[1 + (ii << 1)].re = absxk;
          b_A[1 + (ii << 1)].im = ctoc;
        }
      }

      if (j != 2) {
        for (ii = 0; ii < 2; ii++) {
          absxk = b_A[ii + ((j - 1) << 1)].re;
          ctoc = b_A[ii + ((j - 1) << 1)].im;
          b_A[ii + ((j - 1) << 1)] = b_A[2 + ii];
          b_A[2 + ii].re = absxk;
          b_A[2 + ii].im = ctoc;
        }
      }

      ihi = 1;
    }

    d_st.site = &dd_emlrtRSI;
    eml_matlab_zgghrd(&d_st, ilo, ihi, b_A);
    d_st.site = &ed_emlrtRSI;
    eml_matlab_zhgeqz(&d_st, b_A, ilo, ihi, &nzcount, V, beta1);
    if ((nzcount != 0) || (!ilascl)) {
    } else {
      notdone = true;
      while (notdone) {
        cfrom1 = anrmto * 2.0041683600089728E-292;
        cto1 = anrm / 4.9896007738368E+291;
        if ((cfrom1 > anrm) && (anrm != 0.0)) {
          mul = 2.0041683600089728E-292;
          anrmto = cfrom1;
        } else if (cto1 > anrmto) {
          mul = 4.9896007738368E+291;
          anrm = cto1;
        } else {
          mul = anrm / anrmto;
          notdone = false;
        }

        for (ii = 0; ii < 2; ii++) {
          V[ii].re *= mul;
          V[ii].im *= mul;
        }
      }
    }
  }

  for (ii = 0; ii < 2; ii++) {
    cto1 = V[ii].re;
    mul = V[ii].im;
    if (beta1[ii].im == 0.0) {
      if (V[ii].im == 0.0) {
        V[ii].re /= beta1[ii].re;
        V[ii].im = 0.0;
      } else if (V[ii].re == 0.0) {
        V[ii].re = 0.0;
        V[ii].im = mul / beta1[ii].re;
      } else {
        V[ii].re /= beta1[ii].re;
        V[ii].im = mul / beta1[ii].re;
      }
    } else if (beta1[ii].re == 0.0) {
      if (V[ii].re == 0.0) {
        V[ii].re = V[ii].im / beta1[ii].im;
        V[ii].im = 0.0;
      } else if (V[ii].im == 0.0) {
        V[ii].re = 0.0;
        V[ii].im = -(cto1 / beta1[ii].im);
      } else {
        V[ii].re = V[ii].im / beta1[ii].im;
        V[ii].im = -(cto1 / beta1[ii].im);
      }
    } else {
      cfrom1 = muDoubleScalarAbs(beta1[ii].re);
      absxk = muDoubleScalarAbs(beta1[ii].im);
      if (cfrom1 > absxk) {
        absxk = beta1[ii].im / beta1[ii].re;
        ctoc = beta1[ii].re + absxk * beta1[ii].im;
        V[ii].re = (V[ii].re + absxk * V[ii].im) / ctoc;
        V[ii].im = (mul - absxk * cto1) / ctoc;
      } else if (absxk == cfrom1) {
        if (beta1[ii].re > 0.0) {
          absxk = 0.5;
        } else {
          absxk = -0.5;
        }

        if (beta1[ii].im > 0.0) {
          ctoc = 0.5;
        } else {
          ctoc = -0.5;
        }

        V[ii].re = (V[ii].re * absxk + V[ii].im * ctoc) / cfrom1;
        V[ii].im = (mul * absxk - cto1 * ctoc) / cfrom1;
      } else {
        absxk = beta1[ii].re / beta1[ii].im;
        ctoc = beta1[ii].im + absxk * beta1[ii].re;
        V[ii].re = (absxk * V[ii].re + V[ii].im) / ctoc;
        V[ii].im = (absxk * mul - cto1) / ctoc;
      }
    }
  }

  if (nzcount != 0) {
    st.site = &xc_emlrtRSI;
    c_eml_warning(&st);
  }
}

/* End of code generation (eig.c) */
