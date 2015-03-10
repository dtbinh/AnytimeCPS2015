/*
 * File: repmat.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "repmat.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const double a[1920000]
 *                double b[5760000]
 * Return Type  : void
 */
void b_repmat(const double a[1920000], double b[5760000])
{
  int jtilecol;
  int ibtile;
  int jcol;
  int iacol;
  int ibmat;
  for (jtilecol = 0; jtilecol < 3; jtilecol++) {
    ibtile = jtilecol * 1920000;
    for (jcol = 0; jcol < 1600; jcol++) {
      iacol = jcol * 1200;
      ibmat = ibtile + jcol * 1200;
      memcpy(&b[ibmat], &a[iacol], 1200U * sizeof(double));
    }
  }
}

/*
 * Arguments    : const double a[4]
 *                double b[7680000]
 * Return Type  : void
 */
void c_repmat(const double a[4], double b[7680000])
{
  int jcol;
  int ibmat;
  int itilerow;
  for (jcol = 0; jcol < 4; jcol++) {
    ibmat = jcol * 1920000;
    for (itilerow = 0; itilerow < 1920000; itilerow++) {
      b[ibmat + itilerow] = a[jcol];
    }
  }
}

/*
 * Arguments    : const double a[1920000]
 *                double b[7680000]
 * Return Type  : void
 */
void d_repmat(const double a[1920000], double b[7680000])
{
  int jtilecol;
  int ibtile;
  for (jtilecol = 0; jtilecol < 4; jtilecol++) {
    ibtile = jtilecol * 1920000;
    memcpy(&b[ibtile], &a[0], 1920000U * sizeof(double));
  }
}

/*
 * Arguments    : const double a[2]
 *                double varargin_1
 *                emxArray_real_T *b
 * Return Type  : void
 */
void e_repmat(const double a[2], double varargin_1, emxArray_real_T *b)
{
  int jcol;
  int ibmat;
  int itilerow;
  jcol = b->size[0] * b->size[1];
  b->size[0] = (int)varargin_1;
  b->size[1] = 2;
  emxEnsureCapacity((emxArray__common *)b, jcol, (int)sizeof(double));
  if ((int)varargin_1 == 0) {
  } else {
    for (jcol = 0; jcol < 2; jcol++) {
      ibmat = jcol * (int)varargin_1;
      for (itilerow = 1; itilerow <= (int)varargin_1; itilerow++) {
        b->data[(ibmat + itilerow) - 1] = a[jcol];
      }
    }
  }
}

/*
 * Arguments    : const boolean_T a[1920000]
 *                boolean_T b[5760000]
 * Return Type  : void
 */
void repmat(const boolean_T a[1920000], boolean_T b[5760000])
{
  int jtilecol;
  int ibtile;
  int jcol;
  int iacol;
  int ibmat;
  for (jtilecol = 0; jtilecol < 3; jtilecol++) {
    ibtile = jtilecol * 1920000;
    for (jcol = 0; jcol < 1600; jcol++) {
      iacol = jcol * 1200;
      ibmat = ibtile + jcol * 1200;
      memcpy(&b[ibmat], &a[iacol], 1200U * sizeof(boolean_T));
    }
  }
}

/*
 * File trailer for repmat.c
 *
 * [EOF]
 */
