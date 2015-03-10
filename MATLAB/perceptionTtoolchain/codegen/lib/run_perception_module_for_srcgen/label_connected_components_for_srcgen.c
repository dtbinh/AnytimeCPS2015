/*
 * File: label_connected_components_for_srcgen.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "label_connected_components_for_srcgen.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * n = 4 or 8
 *  BW = black and white image
 *  minimumSize: ignore all components of less than a minimumSize pixels
 * Arguments    : const boolean_T BW[1920000]
 *                double L[1920000]
 * Return Type  : void
 */
void c_label_connected_components_fo(const boolean_T BW[1920000], double L
  [1920000])
{
  emxArray_real_T *q;
  int i7;
  double curlabel;
  emxArray_real_T *ff;
  emxArray_int32_T *ii;
  emxArray_real_T *b_q;
  emxArray_real_T *c_q;
  emxArray_real_T *d_q;
  int i;
  int j;
  int loop_ub;
  int i8;
  short p[2];
  int b_ii;
  int idx;
  short b_p[2];
  double nhbrs_data[8];
  double b_nhbrs_data[8];
  boolean_T exitg1;
  boolean_T guard1 = false;
  memset(&L[0], 0, 1920000U * sizeof(double));
  emxInit_real_T(&q, 2);
  i7 = q->size[0] * q->size[1];
  q->size[0] = 0;
  q->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)q, i7, (int)sizeof(double));
  curlabel = 1.0;
  b_emxInit_real_T(&ff, 1);
  emxInit_int32_T(&ii, 1);
  emxInit_real_T(&b_q, 2);
  emxInit_real_T(&c_q, 2);
  emxInit_real_T(&d_q, 2);
  for (i = 0; i < 1200; i++) {
    for (j = 0; j < 1600; j++) {
      if ((BW[i + 1200 * j] == 1) && (!(L[i + 1200 * j] != 0.0))) {
        L[i + 1200 * j] = curlabel;
        i7 = b_q->size[0] * b_q->size[1];
        b_q->size[0] = q->size[0] + 1;
        b_q->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)b_q, i7, (int)sizeof(double));
        for (i7 = 0; i7 < 2; i7++) {
          loop_ub = q->size[0];
          for (i8 = 0; i8 < loop_ub; i8++) {
            b_q->data[i8 + b_q->size[0] * i7] = q->data[i8 + q->size[0] * i7];
          }
        }

        b_q->data[q->size[0]] = 1.0 + (double)i;
        b_q->data[q->size[0] + b_q->size[0]] = 1.0 + (double)j;
        i7 = q->size[0] * q->size[1];
        q->size[0] = b_q->size[0];
        q->size[1] = 2;
        emxEnsureCapacity((emxArray__common *)q, i7, (int)sizeof(double));
        for (i7 = 0; i7 < 2; i7++) {
          loop_ub = b_q->size[0];
          for (i8 = 0; i8 < loop_ub; i8++) {
            q->data[i8 + q->size[0] * i7] = b_q->data[i8 + b_q->size[0] * i7];
          }
        }

        /*  pop */
        while (!(q->size[0] == 0)) {
          for (i7 = 0; i7 < 2; i7++) {
            p[i7] = (short)q->data[q->size[0] * i7];
          }

          if (2 > q->size[0]) {
            i7 = 0;
            i8 = 0;
          } else {
            i7 = 1;
            i8 = q->size[0];
          }

          b_ii = c_q->size[0] * c_q->size[1];
          c_q->size[0] = i8 - i7;
          c_q->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)c_q, b_ii, (int)sizeof(double));
          for (b_ii = 0; b_ii < 2; b_ii++) {
            loop_ub = i8 - i7;
            for (idx = 0; idx < loop_ub; idx++) {
              c_q->data[idx + c_q->size[0] * b_ii] = q->data[(i7 + idx) +
                q->size[0] * b_ii];
            }
          }

          i7 = q->size[0] * q->size[1];
          q->size[0] = c_q->size[0];
          q->size[1] = 2;
          emxEnsureCapacity((emxArray__common *)q, i7, (int)sizeof(double));
          for (i7 = 0; i7 < 2; i7++) {
            loop_ub = c_q->size[0];
            for (i8 = 0; i8 < loop_ub; i8++) {
              q->data[i8 + q->size[0] * i7] = c_q->data[i8 + c_q->size[0] * i7];
            }
          }

          /*  get neighbors */
          /*  Get n neighbours of pixel(i,j) in an image sized r-by-c */
          idx = 0;
          if (p[1] > 1) {
            b_p[0] = p[0];
            b_p[1] = (short)(p[1] - 1);
            idx = 1;
            for (i7 = 0; i7 < 2; i7++) {
              nhbrs_data[i7] = b_p[i7];
            }
          }

          if (p[1] < 1600) {
            b_ii = idx + 1;
            for (i7 = 0; i7 < 2; i7++) {
              i8 = 0;
              while (i8 <= idx - 1) {
                b_nhbrs_data[(idx + 1) * i7] = nhbrs_data[idx * i7];
                i8 = 1;
              }
            }

            b_nhbrs_data[idx] = p[0];
            b_nhbrs_data[(idx + idx) + 1] = (double)p[1] + 1.0;
            idx++;
            for (i7 = 0; i7 < 2; i7++) {
              for (i8 = 0; i8 < b_ii; i8++) {
                nhbrs_data[i8 + idx * i7] = b_nhbrs_data[i8 + b_ii * i7];
              }
            }
          }

          if (p[0] > 1) {
            b_ii = idx + 1;
            for (i7 = 0; i7 < 2; i7++) {
              for (i8 = 0; i8 < idx; i8++) {
                b_nhbrs_data[i8 + (idx + 1) * i7] = nhbrs_data[i8 + idx * i7];
              }
            }

            b_nhbrs_data[idx] = (double)p[0] - 1.0;
            b_nhbrs_data[(idx + idx) + 1] = p[1];
            idx++;
            for (i7 = 0; i7 < 2; i7++) {
              for (i8 = 0; i8 < b_ii; i8++) {
                nhbrs_data[i8 + idx * i7] = b_nhbrs_data[i8 + b_ii * i7];
              }
            }
          }

          if (p[0] < 1200) {
            b_ii = idx + 1;
            for (i7 = 0; i7 < 2; i7++) {
              for (i8 = 0; i8 < idx; i8++) {
                b_nhbrs_data[i8 + (idx + 1) * i7] = nhbrs_data[i8 + idx * i7];
              }
            }

            b_nhbrs_data[idx] = (double)p[0] + 1.0;
            b_nhbrs_data[(idx + idx) + 1] = p[1];
            idx++;
            for (i7 = 0; i7 < 2; i7++) {
              for (i8 = 0; i8 < b_ii; i8++) {
                nhbrs_data[i8 + idx * i7] = b_nhbrs_data[i8 + b_ii * i7];
              }
            }
          }

          for (b_ii = 0; b_ii < idx; b_ii++) {
            if ((BW[((int)nhbrs_data[b_ii] + 1200 * ((int)nhbrs_data[b_ii + idx]
                   - 1)) - 1] == 1) && (!(L[((int)nhbrs_data[b_ii] + 1200 *
                   ((int)nhbrs_data[b_ii + idx] - 1)) - 1] != 0.0))) {
              L[((int)nhbrs_data[b_ii] + 1200 * ((int)nhbrs_data[b_ii + idx] - 1))
                - 1] = curlabel;
              i7 = d_q->size[0] * d_q->size[1];
              d_q->size[0] = q->size[0] + 1;
              d_q->size[1] = 2;
              emxEnsureCapacity((emxArray__common *)d_q, i7, (int)sizeof(double));
              for (i7 = 0; i7 < 2; i7++) {
                loop_ub = q->size[0];
                for (i8 = 0; i8 < loop_ub; i8++) {
                  d_q->data[i8 + d_q->size[0] * i7] = q->data[i8 + q->size[0] *
                    i7];
                }
              }

              for (i7 = 0; i7 < 2; i7++) {
                d_q->data[q->size[0] + d_q->size[0] * i7] = nhbrs_data[b_ii +
                  idx * i7];
              }

              i7 = q->size[0] * q->size[1];
              q->size[0] = d_q->size[0];
              q->size[1] = 2;
              emxEnsureCapacity((emxArray__common *)q, i7, (int)sizeof(double));
              for (i7 = 0; i7 < 2; i7++) {
                loop_ub = d_q->size[0];
                for (i8 = 0; i8 < loop_ub; i8++) {
                  q->data[i8 + q->size[0] * i7] = d_q->data[i8 + d_q->size[0] *
                    i7];
                }
              }
            }
          }
        }

        idx = 0;
        i7 = ii->size[0];
        ii->size[0] = 1920000;
        emxEnsureCapacity((emxArray__common *)ii, i7, (int)sizeof(int));
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

        i7 = ii->size[0];
        if (1 > idx) {
          ii->size[0] = 0;
        } else {
          ii->size[0] = idx;
        }

        emxEnsureCapacity((emxArray__common *)ii, i7, (int)sizeof(int));
        i7 = ff->size[0];
        ff->size[0] = ii->size[0];
        emxEnsureCapacity((emxArray__common *)ff, i7, (int)sizeof(double));
        loop_ub = ii->size[0];
        for (i7 = 0; i7 < loop_ub; i7++) {
          ff->data[i7] = ii->data[i7];
        }

        if (ff->size[0] <= 8) {
          i7 = ii->size[0];
          ii->size[0] = ff->size[0];
          emxEnsureCapacity((emxArray__common *)ii, i7, (int)sizeof(int));
          loop_ub = ff->size[0];
          for (i7 = 0; i7 < loop_ub; i7++) {
            ii->data[i7] = (int)ff->data[i7];
          }

          loop_ub = ii->size[0];
          for (i7 = 0; i7 < loop_ub; i7++) {
            L[ii->data[i7] - 1] = 0.0;
          }
        } else {
          curlabel++;
        }
      } else {
        /*  do nothing */
      }
    }
  }

  emxFree_real_T(&d_q);
  emxFree_real_T(&c_q);
  emxFree_real_T(&b_q);
  emxFree_int32_T(&ii);
  emxFree_real_T(&ff);
  emxFree_real_T(&q);
}

/*
 * File trailer for label_connected_components_for_srcgen.c
 *
 * [EOF]
 */
