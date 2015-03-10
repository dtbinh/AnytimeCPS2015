/*
 * File: eig.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "eig.h"
#include "sqrt.h"
#include "run_perception_module_for_srcgen_rtwutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Declarations */
static void eml_matlab_zhgeqz(const creal_T A[4], int ilo, int ihi, int *info,
  creal_T alpha1[2], creal_T beta1[2]);
static double eml_matlab_zlangeM(const creal_T x[4]);
static void eml_matlab_zlartg(const creal_T f, const creal_T g, double *cs,
  creal_T *sn);

/* Function Definitions */

/*
 * Arguments    : const creal_T A[4]
 *                int ilo
 *                int ihi
 *                int *info
 *                creal_T alpha1[2]
 *                creal_T beta1[2]
 * Return Type  : void
 */
static void eml_matlab_zhgeqz(const creal_T A[4], int ilo, int ihi, int *info,
  creal_T alpha1[2], creal_T beta1[2])
{
  creal_T b_A[4];
  int i;
  double eshift_re;
  double eshift_im;
  creal_T ctemp;
  double rho_re;
  double rho_im;
  double anorm;
  double sumsq;
  boolean_T firstNonZero;
  int j;
  int ifirst;
  double reAij;
  double imAij;
  double temp1;
  double temp2;
  double b_atol;
  boolean_T failed;
  boolean_T guard1 = false;
  boolean_T guard2 = false;
  int istart;
  int ilast;
  int ilastm1;
  int ifrstm;
  int ilastm;
  int iiter;
  boolean_T goto60;
  boolean_T goto70;
  boolean_T goto90;
  int jiter;
  int32_T exitg1;
  boolean_T exitg3;
  boolean_T b_guard1 = false;
  creal_T t1;
  creal_T d;
  boolean_T exitg2;
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
  anorm = 0.0;
  if (ilo > ihi) {
  } else {
    anorm = 0.0;
    sumsq = 0.0;
    firstNonZero = true;
    for (j = ilo; j <= ihi; j++) {
      ifirst = j + 1;
      if (ihi < j + 1) {
        ifirst = ihi;
      }

      for (i = ilo; i <= ifirst; i++) {
        reAij = A[(i + ((j - 1) << 1)) - 1].re;
        imAij = A[(i + ((j - 1) << 1)) - 1].im;
        if (reAij != 0.0) {
          temp1 = fabs(reAij);
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
          temp1 = fabs(imAij);
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

    anorm *= sqrt(sumsq);
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
    goto60 = false;
    goto70 = false;
    goto90 = false;
    jiter = 1;
    do {
      exitg1 = 0;
      if (jiter <= 30 * ((ihi - ilo) + 1)) {
        if (ilast + 1 == ilo) {
          goto60 = true;
        } else if (fabs(b_A[ilast + (ilastm1 << 1)].re) + fabs(b_A[ilast +
                    (ilastm1 << 1)].im) <= b_atol) {
          b_A[ilast + (ilastm1 << 1)].re = 0.0;
          b_A[ilast + (ilastm1 << 1)].im = 0.0;
          goto60 = true;
        } else {
          j = ilastm1;
          exitg3 = false;
          while ((!exitg3) && (j + 1 >= ilo)) {
            if (j + 1 == ilo) {
              firstNonZero = true;
            } else if (fabs(b_A[j].re) + fabs(b_A[j].im) <= b_atol) {
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
              if (iiter - iiter / 10 * 10 != 0) {
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
                if (rt_hypotd_snf(rho_re - b_A[ilast + (ilast << 1)].re, rho_im
                                  - b_A[ilast + (ilast << 1)].im) <=
                    rt_hypotd_snf(anorm - b_A[ilast + (ilast << 1)].re, reAij -
                                  b_A[ilast + (ilast << 1)].im)) {
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
              exitg2 = false;
              while ((!exitg2) && (j + 1 > ifirst)) {
                istart = 2;
                ctemp.re = b_A[3].re - anorm;
                ctemp.im = b_A[3].im - reAij;
                temp1 = imAij * (fabs(ctemp.re) + fabs(ctemp.im));
                temp2 = imAij * (fabs(b_A[3].re) + fabs(b_A[3].im));
                sumsq = temp1;
                if (temp2 > temp1) {
                  sumsq = temp2;
                }

                if ((sumsq < 1.0) && (sumsq != 0.0)) {
                  temp1 /= sumsq;
                  temp2 /= sumsq;
                }

                if ((fabs(b_A[1].re) + fabs(b_A[1].im)) * temp2 <= temp1 *
                    b_atol) {
                  goto90 = true;
                  exitg2 = true;
                } else {
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
              eml_matlab_zlartg(ctemp, b_A[1 + ((istart - 1) << 1)], &anorm, &t1);
              j = istart;
              while (j < ilast + 1) {
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
      for (ifirst = 0; ifirst + 1 <= ilast + 1; ifirst++) {
        alpha1[ifirst].re = rtNaN;
        alpha1[ifirst].im = 0.0;
        beta1[ifirst].re = rtNaN;
        beta1[ifirst].im = 0.0;
      }
    } else {
      guard1 = true;
    }
  }

  if (guard1) {
    for (j = 0; j + 1 < ilo; j++) {
      alpha1[j] = b_A[j + (j << 1)];
    }
  }
}

/*
 * Arguments    : const creal_T x[4]
 * Return Type  : double
 */
static double eml_matlab_zlangeM(const creal_T x[4])
{
  double y;
  int k;
  boolean_T exitg1;
  double absxk;
  y = 0.0;
  k = 0;
  exitg1 = false;
  while ((!exitg1) && (k < 4)) {
    absxk = rt_hypotd_snf(x[k].re, x[k].im);
    if (rtIsNaN(absxk)) {
      y = rtNaN;
      exitg1 = true;
    } else {
      if (absxk > y) {
        y = absxk;
      }

      k++;
    }
  }

  return y;
}

/*
 * Arguments    : const creal_T f
 *                const creal_T g
 *                double *cs
 *                creal_T *sn
 * Return Type  : void
 */
static void eml_matlab_zlartg(const creal_T f, const creal_T g, double *cs,
  creal_T *sn)
{
  double scale;
  double f2s;
  double g2;
  double fs_re;
  double fs_im;
  double gs_re;
  double gs_im;
  boolean_T guard1 = false;
  double g2s;
  scale = fabs(f.re);
  f2s = fabs(f.im);
  if (f2s > scale) {
    scale = f2s;
  }

  f2s = fabs(g.re);
  g2 = fabs(g.im);
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
  guard1 = false;
  if (scale >= 7.4428285367870146E+137) {
    do {
      fs_re *= 1.3435752215134178E-138;
      fs_im *= 1.3435752215134178E-138;
      gs_re *= 1.3435752215134178E-138;
      gs_im *= 1.3435752215134178E-138;
      scale *= 1.3435752215134178E-138;
    } while (!(scale < 7.4428285367870146E+137));

    guard1 = true;
  } else if (scale <= 1.3435752215134178E-138) {
    if ((g.re == 0.0) && (g.im == 0.0)) {
      *cs = 1.0;
      sn->re = 0.0;
      sn->im = 0.0;
    } else {
      do {
        fs_re *= 7.4428285367870146E+137;
        fs_im *= 7.4428285367870146E+137;
        gs_re *= 7.4428285367870146E+137;
        gs_im *= 7.4428285367870146E+137;
        scale *= 7.4428285367870146E+137;
      } while (!(scale > 1.3435752215134178E-138));

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
        scale = rt_hypotd_snf(gs_re, gs_im);
        sn->re = gs_re / scale;
        sn->im = -gs_im / scale;
      } else {
        g2s = sqrt(g2);
        *cs = rt_hypotd_snf(fs_re, fs_im) / g2s;
        f2s = fabs(f.re);
        g2 = fabs(f.im);
        if (g2 > f2s) {
          f2s = g2;
        }

        if (f2s > 1.0) {
          scale = rt_hypotd_snf(f.re, f.im);
          fs_re = f.re / scale;
          fs_im = f.im / scale;
        } else {
          f2s = 7.4428285367870146E+137 * f.re;
          g2 = 7.4428285367870146E+137 * f.im;
          scale = rt_hypotd_snf(f2s, g2);
          fs_re = f2s / scale;
          fs_im = g2 / scale;
        }

        gs_re /= g2s;
        gs_im = -gs_im / g2s;
        sn->re = fs_re * gs_re - fs_im * gs_im;
        sn->im = fs_re * gs_im + fs_im * gs_re;
      }
    } else {
      f2s = sqrt(1.0 + g2 / scale);
      *cs = 1.0 / f2s;
      scale += g2;
      fs_re = f2s * fs_re / scale;
      fs_im = f2s * fs_im / scale;
      sn->re = fs_re * gs_re - fs_im * -gs_im;
      sn->im = fs_re * -gs_im + fs_im * gs_re;
    }
  }
}

/*
 * Arguments    : const double A[4]
 *                creal_T V[2]
 * Return Type  : void
 */
void eig(const double A[4], creal_T V[2])
{
  creal_T b_A[4];
  int ii;
  double anrm;
  creal_T beta1[2];
  int i;
  boolean_T ilascl;
  double anrmto;
  double cfromc;
  double ctoc;
  boolean_T notdone;
  double cfrom1;
  double cto1;
  double mul;
  int ilo;
  int ihi;
  int j;
  boolean_T exitg3;
  int nzcount;
  int jj;
  boolean_T exitg4;
  boolean_T guard2 = false;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T guard1 = false;
  for (ii = 0; ii < 4; ii++) {
    b_A[ii].re = A[ii];
    b_A[ii].im = 0.0;
  }

  anrm = eml_matlab_zlangeM(b_A);
  if (!((!rtIsInf(anrm)) && (!rtIsNaN(anrm)))) {
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
      cfromc = anrm;
      ctoc = anrmto;
      notdone = true;
      while (notdone) {
        cfrom1 = cfromc * 2.0041683600089728E-292;
        cto1 = ctoc / 4.9896007738368E+291;
        if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
          mul = 2.0041683600089728E-292;
          cfromc = cfrom1;
        } else if (fabs(cto1) > fabs(cfromc)) {
          mul = 4.9896007738368E+291;
          ctoc = cto1;
        } else {
          mul = ctoc / cfromc;
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
            cfromc = b_A[(i + (ii << 1)) - 1].re;
            ctoc = b_A[(i + (ii << 1)) - 1].im;
            b_A[(i + (ii << 1)) - 1] = b_A[ii << 1];
            b_A[ii << 1].re = cfromc;
            b_A[ii << 1].im = ctoc;
          }
        }

        if (j != 1) {
          for (ii = 0; ii < 2; ii++) {
            cfromc = b_A[ii + ((j - 1) << 1)].re;
            ctoc = b_A[ii + ((j - 1) << 1)].im;
            b_A[ii + ((j - 1) << 1)] = b_A[ii];
            b_A[ii].re = cfromc;
            b_A[ii].im = ctoc;
          }
        }

        ilo = 2;
      }
    } else {
      if (i != 2) {
        for (ii = 0; ii < 2; ii++) {
          cfromc = b_A[ii << 1].re;
          ctoc = b_A[ii << 1].im;
          b_A[ii << 1] = b_A[1 + (ii << 1)];
          b_A[1 + (ii << 1)].re = cfromc;
          b_A[1 + (ii << 1)].im = ctoc;
        }
      }

      if (j != 2) {
        for (ii = 0; ii < 2; ii++) {
          cfromc = b_A[ii].re;
          ctoc = b_A[ii].im;
          b_A[ii] = b_A[2 + ii];
          b_A[2 + ii].re = cfromc;
          b_A[2 + ii].im = ctoc;
        }
      }

      ihi = 1;
    }

    eml_matlab_zhgeqz(b_A, ilo, ihi, &ii, V, beta1);
    if ((ii != 0) || (!ilascl)) {
    } else {
      notdone = true;
      while (notdone) {
        cfrom1 = anrmto * 2.0041683600089728E-292;
        cto1 = anrm / 4.9896007738368E+291;
        if ((fabs(cfrom1) > fabs(anrm)) && (anrm != 0.0)) {
          mul = 2.0041683600089728E-292;
          anrmto = cfrom1;
        } else if (fabs(cto1) > fabs(anrmto)) {
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
      cfrom1 = fabs(beta1[ii].re);
      cfromc = fabs(beta1[ii].im);
      if (cfrom1 > cfromc) {
        cfromc = beta1[ii].im / beta1[ii].re;
        ctoc = beta1[ii].re + cfromc * beta1[ii].im;
        V[ii].re = (V[ii].re + cfromc * V[ii].im) / ctoc;
        V[ii].im = (mul - cfromc * cto1) / ctoc;
      } else if (cfromc == cfrom1) {
        if (beta1[ii].re > 0.0) {
          cfromc = 0.5;
        } else {
          cfromc = -0.5;
        }

        if (beta1[ii].im > 0.0) {
          ctoc = 0.5;
        } else {
          ctoc = -0.5;
        }

        V[ii].re = (V[ii].re * cfromc + V[ii].im * ctoc) / cfrom1;
        V[ii].im = (mul * cfromc - cto1 * ctoc) / cfrom1;
      } else {
        cfromc = beta1[ii].re / beta1[ii].im;
        ctoc = beta1[ii].im + cfromc * beta1[ii].re;
        V[ii].re = (cfromc * V[ii].re + V[ii].im) / ctoc;
        V[ii].im = (cfromc * mul - cto1) / ctoc;
      }
    }
  }
}

/*
 * File trailer for eig.c
 *
 * [EOF]
 */
