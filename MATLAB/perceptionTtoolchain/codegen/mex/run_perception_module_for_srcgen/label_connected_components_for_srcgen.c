/*
 * label_connected_components_for_srcgen.c
 *
 * Code generation for function 'label_connected_components_for_srcgen'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "label_connected_components_for_srcgen.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRTEInfo n_emlrtRTEI = { 1, 14,
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m"
};

static emlrtRTEInfo q_emlrtRTEI = { 7, 1,
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m"
};

static emlrtRTEInfo r_emlrtRTEI = { 28, 13,
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m"
};

static emlrtBCInfo u_emlrtBCI = { -1, -1, 18, 23, "q",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo v_emlrtBCI = { -1, -1, 24, 38, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo w_emlrtBCI = { 1, 1200, 22, 27, "BW",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo x_emlrtBCI = { -1, -1, 22, 33, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo y_emlrtBCI = { -1, -1, 22, 44, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo ab_emlrtBCI = { 1, 1200, 22, 59, "L",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo bb_emlrtBCI = { -1, -1, 22, 65, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo cb_emlrtBCI = { -1, -1, 22, 76, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo db_emlrtBCI = { 1, 1200, 23, 27, "L",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo eb_emlrtBCI = { -1, -1, 23, 33, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

static emlrtBCInfo fb_emlrtBCI = { -1, -1, 23, 45, "nhbrs",
  "label_connected_components_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\label_connected_components_for_srcgen.m",
  0 };

/* Function Definitions */
void c_label_connected_components_fo(const emlrtStack *sp, const boolean_T BW
  [1920000], real_T L[1920000])
{
  emxArray_real_T *q;
  int32_T i8;
  real_T curlabel;
  emxArray_real_T *ff;
  emxArray_int32_T *ii;
  emxArray_real_T *b_q;
  emxArray_real_T *c_q;
  emxArray_real_T *d_q;
  int32_T i;
  int32_T j;
  int32_T loop_ub;
  int32_T i9;
  int16_T p[2];
  int32_T b_ii;
  int32_T idx;
  int16_T b_p[2];
  real_T nhbrs_data[8];
  real_T b_nhbrs_data[8];
  int32_T exitg2;
  boolean_T exitg1;
  boolean_T guard1 = false;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /*  n = 4 or 8 */
  /*  BW = black and white image */
  /*  minimumSize: ignore all components of less than a minimumSize pixels */
  memset(&L[0], 0, 1920000U * sizeof(real_T));
  b_emxInit_real_T(sp, &q, 2, &q_emlrtRTEI, true);
  i8 = q->size[0] * q->size[1];
  q->size[0] = 0;
  q->size[1] = 2;
  emxEnsureCapacity(sp, (emxArray__common *)q, i8, (int32_T)sizeof(real_T),
                    &n_emlrtRTEI);
  curlabel = 1.0;
  emxInit_real_T(sp, &ff, 1, &r_emlrtRTEI, true);
  emxInit_int32_T(sp, &ii, 1, &s_emlrtRTEI, true);
  b_emxInit_real_T(sp, &b_q, 2, &n_emlrtRTEI, true);
  b_emxInit_real_T(sp, &c_q, 2, &n_emlrtRTEI, true);
  b_emxInit_real_T(sp, &d_q, 2, &n_emlrtRTEI, true);
  for (i = 0; i < 1200; i++) {
    for (j = 0; j < 1600; j++) {
      if ((BW[i + 1200 * j] == 1) && (!(L[i + 1200 * j] != 0.0))) {
        L[i + 1200 * j] = curlabel;
        i8 = b_q->size[0] * b_q->size[1];
        b_q->size[0] = q->size[0] + 1;
        b_q->size[1] = 2;
        emxEnsureCapacity(sp, (emxArray__common *)b_q, i8, (int32_T)sizeof
                          (real_T), &n_emlrtRTEI);
        for (i8 = 0; i8 < 2; i8++) {
          loop_ub = q->size[0];
          for (i9 = 0; i9 < loop_ub; i9++) {
            b_q->data[i9 + b_q->size[0] * i8] = q->data[i9 + q->size[0] * i8];
          }
        }

        b_q->data[q->size[0]] = 1.0 + (real_T)i;
        b_q->data[q->size[0] + b_q->size[0]] = 1.0 + (real_T)j;
        i8 = q->size[0] * q->size[1];
        q->size[0] = b_q->size[0];
        q->size[1] = 2;
        emxEnsureCapacity(sp, (emxArray__common *)q, i8, (int32_T)sizeof(real_T),
                          &n_emlrtRTEI);
        for (i8 = 0; i8 < 2; i8++) {
          loop_ub = b_q->size[0];
          for (i9 = 0; i9 < loop_ub; i9++) {
            q->data[i9 + q->size[0] * i8] = b_q->data[i9 + b_q->size[0] * i8];
          }
        }

        /*  pop */
        while (!(q->size[0] == 0)) {
          for (i8 = 0; i8 < 2; i8++) {
            p[i8] = (int16_T)q->data[q->size[0] * i8];
          }

          if (2 > q->size[0]) {
            i8 = 0;
            i9 = 0;
          } else {
            i8 = 1;
            i9 = q->size[0];
            b_ii = q->size[0];
            i9 = emlrtDynamicBoundsCheckFastR2012b(b_ii, 1, i9, &u_emlrtBCI, sp);
          }

          b_ii = c_q->size[0] * c_q->size[1];
          c_q->size[0] = i9 - i8;
          c_q->size[1] = 2;
          emxEnsureCapacity(sp, (emxArray__common *)c_q, b_ii, (int32_T)sizeof
                            (real_T), &n_emlrtRTEI);
          for (b_ii = 0; b_ii < 2; b_ii++) {
            loop_ub = i9 - i8;
            for (idx = 0; idx < loop_ub; idx++) {
              c_q->data[idx + c_q->size[0] * b_ii] = q->data[(i8 + idx) +
                q->size[0] * b_ii];
            }
          }

          i8 = q->size[0] * q->size[1];
          q->size[0] = c_q->size[0];
          q->size[1] = 2;
          emxEnsureCapacity(sp, (emxArray__common *)q, i8, (int32_T)sizeof
                            (real_T), &n_emlrtRTEI);
          for (i8 = 0; i8 < 2; i8++) {
            loop_ub = c_q->size[0];
            for (i9 = 0; i9 < loop_ub; i9++) {
              q->data[i9 + q->size[0] * i8] = c_q->data[i9 + c_q->size[0] * i8];
            }
          }

          /*  get neighbors */
          /*  Get n neighbours of pixel(i,j) in an image sized r-by-c */
          idx = 0;
          if (p[1] > 1) {
            b_p[0] = p[0];
            b_p[1] = (int16_T)(p[1] - 1);
            idx = 1;
            for (i8 = 0; i8 < 2; i8++) {
              nhbrs_data[i8] = b_p[i8];
            }
          }

          if (p[1] < 1600) {
            b_ii = idx + 1;
            for (i8 = 0; i8 < 2; i8++) {
              i9 = 0;
              while (i9 <= idx - 1) {
                b_nhbrs_data[(idx + 1) * i8] = nhbrs_data[idx * i8];
                i9 = 1;
              }
            }

            b_nhbrs_data[idx] = p[0];
            b_nhbrs_data[(idx + idx) + 1] = (real_T)p[1] + 1.0;
            idx++;
            for (i8 = 0; i8 < 2; i8++) {
              for (i9 = 0; i9 < b_ii; i9++) {
                nhbrs_data[i9 + idx * i8] = b_nhbrs_data[i9 + b_ii * i8];
              }
            }
          }

          if (p[0] > 1) {
            b_ii = idx + 1;
            for (i8 = 0; i8 < 2; i8++) {
              for (i9 = 0; i9 < idx; i9++) {
                b_nhbrs_data[i9 + (idx + 1) * i8] = nhbrs_data[i9 + idx * i8];
              }
            }

            b_nhbrs_data[idx] = (real_T)p[0] - 1.0;
            b_nhbrs_data[(idx + idx) + 1] = p[1];
            idx++;
            for (i8 = 0; i8 < 2; i8++) {
              for (i9 = 0; i9 < b_ii; i9++) {
                nhbrs_data[i9 + idx * i8] = b_nhbrs_data[i9 + b_ii * i8];
              }
            }
          }

          if (p[0] < 1200) {
            b_ii = idx + 1;
            for (i8 = 0; i8 < 2; i8++) {
              for (i9 = 0; i9 < idx; i9++) {
                b_nhbrs_data[i9 + (idx + 1) * i8] = nhbrs_data[i9 + idx * i8];
              }
            }

            b_nhbrs_data[idx] = (real_T)p[0] + 1.0;
            b_nhbrs_data[(idx + idx) + 1] = p[1];
            idx++;
            for (i8 = 0; i8 < 2; i8++) {
              for (i9 = 0; i9 < b_ii; i9++) {
                nhbrs_data[i9 + idx * i8] = b_nhbrs_data[i9 + b_ii * i8];
              }
            }
          }

          b_ii = 1;
          do {
            exitg2 = 0;
            emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
            if (b_ii - 1 <= idx - 1) {
              i8 = (int32_T)nhbrs_data[emlrtDynamicBoundsCheckFastR2012b(b_ii, 1,
                idx, &x_emlrtBCI, sp) - 1];
              if (BW[(emlrtDynamicBoundsCheckFastR2012b(i8, 1, 1200, &w_emlrtBCI,
                    sp) + 1200 * ((int32_T)nhbrs_data
                                  [(emlrtDynamicBoundsCheckFastR2012b(b_ii, 1,
                      idx, &y_emlrtBCI, sp) + idx) - 1] - 1)) - 1] == 1) {
                i8 = (int32_T)nhbrs_data[emlrtDynamicBoundsCheckFastR2012b(b_ii,
                  1, idx, &bb_emlrtBCI, sp) - 1];
                if (!(L[(emlrtDynamicBoundsCheckFastR2012b(i8, 1, 1200,
                       &ab_emlrtBCI, sp) + 1200 * ((int32_T)nhbrs_data
                       [(emlrtDynamicBoundsCheckFastR2012b(b_ii, 1, idx,
                         &cb_emlrtBCI, sp) + idx) - 1] - 1)) - 1] != 0.0)) {
                  i8 = (int32_T)nhbrs_data[emlrtDynamicBoundsCheckFastR2012b
                    (b_ii, 1, idx, &eb_emlrtBCI, sp) - 1];
                  L[(emlrtDynamicBoundsCheckFastR2012b(i8, 1, 1200, &db_emlrtBCI,
                      sp) + 1200 * ((int32_T)nhbrs_data
                                    [(emlrtDynamicBoundsCheckFastR2012b(b_ii, 1,
                        idx, &fb_emlrtBCI, sp) + idx) - 1] - 1)) - 1] = curlabel;
                  emlrtDynamicBoundsCheckFastR2012b(b_ii, 1, idx, &v_emlrtBCI,
                    sp);
                  i8 = d_q->size[0] * d_q->size[1];
                  d_q->size[0] = q->size[0] + 1;
                  d_q->size[1] = 2;
                  emxEnsureCapacity(sp, (emxArray__common *)d_q, i8, (int32_T)
                                    sizeof(real_T), &n_emlrtRTEI);
                  for (i8 = 0; i8 < 2; i8++) {
                    loop_ub = q->size[0];
                    for (i9 = 0; i9 < loop_ub; i9++) {
                      d_q->data[i9 + d_q->size[0] * i8] = q->data[i9 + q->size[0]
                        * i8];
                    }
                  }

                  for (i8 = 0; i8 < 2; i8++) {
                    d_q->data[q->size[0] + d_q->size[0] * i8] = nhbrs_data[(b_ii
                      + idx * i8) - 1];
                  }

                  i8 = q->size[0] * q->size[1];
                  q->size[0] = d_q->size[0];
                  q->size[1] = 2;
                  emxEnsureCapacity(sp, (emxArray__common *)q, i8, (int32_T)
                                    sizeof(real_T), &n_emlrtRTEI);
                  for (i8 = 0; i8 < 2; i8++) {
                    loop_ub = d_q->size[0];
                    for (i9 = 0; i9 < loop_ub; i9++) {
                      q->data[i9 + q->size[0] * i8] = d_q->data[i9 + d_q->size[0]
                        * i8];
                    }
                  }
                }
              }

              b_ii++;
              emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);
        }

        idx = 0;
        i8 = ii->size[0];
        ii->size[0] = 1920000;
        emxEnsureCapacity(sp, (emxArray__common *)ii, i8, (int32_T)sizeof
                          (int32_T), &o_emlrtRTEI);
        b_ii = 1;
        exitg1 = false;
        while ((!exitg1) && (b_ii < 1920001)) {
          guard1 = false;
          if (L[b_ii - 1] == curlabel) {
            idx++;
            ii->data[idx - 1] = b_ii;
            if (idx >= 1920000) {
              exitg1 = true;
            } else {
              guard1 = true;
            }
          } else {
            guard1 = true;
          }

          if (guard1) {
            b_ii++;
          }
        }

        i8 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity(sp, (emxArray__common *)ii, i8, (int32_T)sizeof
                          (int32_T), &p_emlrtRTEI);
        i8 = ff->size[0];
        ff->size[0] = ii->size[0];
        emxEnsureCapacity(sp, (emxArray__common *)ff, i8, (int32_T)sizeof(real_T),
                          &n_emlrtRTEI);
        loop_ub = ii->size[0];
        for (i8 = 0; i8 < loop_ub; i8++) {
          ff->data[i8] = ii->data[i8];
        }

        if (ff->size[0] <= 8) {
          i8 = ii->size[0];
          ii->size[0] = ff->size[0];
          emxEnsureCapacity(sp, (emxArray__common *)ii, i8, (int32_T)sizeof
                            (int32_T), &n_emlrtRTEI);
          loop_ub = ff->size[0];
          for (i8 = 0; i8 < loop_ub; i8++) {
            ii->data[i8] = (int32_T)ff->data[i8];
          }

          loop_ub = ii->size[0];
          for (i8 = 0; i8 < loop_ub; i8++) {
            L[ii->data[i8] - 1] = 0.0;
          }
        } else {
          curlabel++;
        }
      } else {
        /*  do nothing */
      }

      emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
    }

    emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
  }

  emxFree_real_T(&d_q);
  emxFree_real_T(&c_q);
  emxFree_real_T(&b_q);
  emxFree_int32_T(&ii);
  emxFree_real_T(&ff);
  emxFree_real_T(&q);
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (label_connected_components_for_srcgen.c) */
