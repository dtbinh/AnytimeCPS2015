/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * permn2.c
 *
 * Code generation for function 'permn2'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "alt_getWavApprox_vector_genable.h"
#include "permn2.h"
#include "alt_getWavApprox_vector_genable_emxutil.h"
#include "error.h"
#include "eml_int_forloop_overflow_check.h"
#include "scalexpAlloc.h"
#include "mpower.h"
#include "alt_getWavApprox_vector_genable_mexutil.h"
#include "alt_getWavApprox_vector_genable_data.h"

/* Variable Definitions */
static emlrtRSInfo r_emlrtRSI = { 137, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRSInfo s_emlrtRSI = { 140, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRSInfo t_emlrtRSI = { 142, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRSInfo u_emlrtRSI = { 152, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRSInfo v_emlrtRSI = { 154, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRSInfo w_emlrtRSI = { 39, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtRSInfo x_emlrtRSI = { 53, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtRSInfo y_emlrtRSI = { 100, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtRSInfo ab_emlrtRSI = { 58, "power",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/ops/power.m" };

static emlrtRSInfo bb_emlrtRSI = { 73, "applyScalarFunction",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/applyScalarFunction.m"
};

static emlrtRSInfo cb_emlrtRSI = { 101, "applyScalarFunction",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/applyScalarFunction.m"
};

static emlrtRSInfo db_emlrtRSI = { 10, "floor",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elfun/floor.m" };

static emlrtRSInfo eb_emlrtRSI = { 24, "applyScalarFunctionInPlace",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/applyScalarFunctionInPlace.m"
};

static emlrtRSInfo fb_emlrtRSI = { 39, "rem",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elfun/rem.m" };

static emlrtRSInfo gb_emlrtRSI = { 69, "rem",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elfun/rem.m" };

static emlrtRSInfo hb_emlrtRSI = { 146, "applyScalarFunction",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/applyScalarFunction.m"
};

static emlrtMCInfo emlrtMCI = { 20, 5, "error",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/lang/error.m" };

static emlrtRTEInfo i_emlrtRTEI = { 1, 19, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRTEInfo j_emlrtRTEI = { 16, 9, "scalexpAlloc",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/scalexpAlloc.m" };

static emlrtRTEInfo k_emlrtRTEI = { 152, 9, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m"
};

static emlrtRTEInfo l_emlrtRTEI = { 1, 10, "scalexpAlloc",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/scalexpAlloc.m" };

static emlrtRTEInfo u_emlrtRTEI = { 17, 19, "scalexpAlloc",
  "/usr/local/MATLAB/R2015b/toolbox/eml/eml/+coder/+internal/scalexpAlloc.m" };

static emlrtRTEInfo v_emlrtRTEI = { 63, 15, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtBCInfo p_emlrtBCI = { -1, -1, 155, 13, "V", "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m",
  0 };

static emlrtDCInfo e_emlrtDCI = { 155, 13, "permn2",
  "/home/mlab-retro/Documents/AnytimeCPS2015/MATLAB/STaliro_Smooth/Smooth/wavelet/permn2.m",
  1 };

static emlrtRSInfo sb_emlrtRSI = { 20, "error",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/lang/error.m" };

/* Function Declarations */
static void c_error(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    emlrtMCInfo *location);

/* Function Definitions */
static void c_error(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  pArrays[0] = b;
  pArrays[1] = c;
  emlrtCallMATLABR2012b(sp, 0, NULL, 2, pArrays, "error", true, location);
}

void permn2(const emlrtStack *sp, emxArray_real_T *V, real_T N, real_T K,
            emxArray_real_T *M)
{
  emxArray_real_T *B;
  emxArray_real_T *x;
  emxArray_real_T *z;
  int32_T i6;
  int32_T k;
  real_T b_K;
  static const char_T varargin_1[18] = { 'p', 'e', 'r', 'm', 'n', ':', 'I', 'n',
    'v', 'a', 'l', 'i', 'd', 'I', 'n', 'd', 'e', 'x' };

  char_T u[18];
  const mxArray *y;
  static const int32_T iv1[2] = { 1, 18 };

  const mxArray *m0;
  static const char_T varargin_2[48] = { 'T', 'h', 'i', 'r', 'd', ' ', 'a', 'r',
    'g', 'u', 'm', 'e', 'n', 't', ' ', 's', 'h', 'o', 'u', 'l', 'd', ' ', 'c',
    'o', 'n', 't', 'a', 'i', 'n', ' ', 'p', 'o', 's', 'i', 't', 'i', 'v', 'e',
    ' ', 'i', 'n', 't', 'e', 'g', 'e', 'r', 's', '.' };

  char_T b_u[48];
  const mxArray *b_y;
  static const int32_T iv2[2] = { 1, 48 };

  int32_T nx;
  int32_T sz_idx_1;
  uint32_T b_varargin_1[2];
  int32_T maxdimlen;
  int32_T nV;
  real_T Npos;
  real_T anew;
  real_T apnd;
  boolean_T overflow;
  real_T ndbl;
  real_T absa;
  int32_T b_k;
  int32_T c_k;
  jmp_buf * volatile emlrtJBStack;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  emlrtStack d_st;
  emlrtStack e_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
  d_st.prev = &c_st;
  d_st.tls = c_st.tls;
  e_st.prev = &d_st;
  e_st.tls = d_st.tls;
  emlrtHeapReferenceStackEnterFcnR2012b(sp);

  /*  PERMN - permutations with repetition */
  /*    Using two input variables V and N, M = PERMN(V,N) returns all */
  /*    permutations of N elements taken from the vector V, with repetitions. */
  /*    V can be any type of array (numbers, cells etc.) and M will be of the */
  /*    same type as V.  If V is empty or N is 0, M will be empty.  M has the */
  /*    size numel(V).^N-by-N.  */
  /*  */
  /*    When only a subset of these permutations is needed, you can call PERMN */
  /*    with 3 input variables: M = PERMN(V,N,K) returns only the K-ths */
  /*    permutations.  The output is the same as M = PERMN(V,N) ; M = M(K,:), */
  /*    but it avoids memory issues that may occur when there are too many */
  /*    combinations.  This is particulary useful when you only need a few */
  /*    permutations at a given time. If V or K is empty, or N is zero, M will */
  /*    be empty. M has the size numel(K)-by-N.  */
  /*  */
  /*    [M, I] = PERMN(...) also returns an index matrix I so that M = V(I). */
  /*  */
  /*    Examples: */
  /*      M = permn([1 2 3],2) % returns the 9-by-2 matrix: */
  /*               1     1 */
  /*               1     2 */
  /*               1     3 */
  /*               2     1 */
  /*               2     2 */
  /*               2     3 */
  /*               3     1 */
  /*               3     2 */
  /*               3     3 */
  /*  */
  /*      M = permn([99 7],4) % returns the 16-by-4 matrix: */
  /*               99     99    99    99 */
  /*               99     99    99     7 */
  /*               99     99     7    99 */
  /*               99     99     7     7 */
  /*               ... */
  /*                7      7     7    99 */
  /*                7      7     7     7 */
  /*  */
  /*      M = permn({'hello!' 1:3},2) % returns the 4-by-2 cell array */
  /*              'hello!'        'hello!' */
  /*              'hello!'        [1x3 double] */
  /*              [1x3 double]    'hello!' */
  /*              [1x3 double]    [1x3 double] */
  /*  */
  /*      V = 11:15, N = 3, K = [2 124 21 99] */
  /*      M = permn(V, N, K) % returns the 4-by-3 matrix: */
  /*      %        11  11  12 */
  /*      %        15  15  14 */
  /*      %        11  15  11 */
  /*      %        14  15  14 */
  /*      % which are the 2nd, 124th, 21st and 99th permutations */
  /*      % Check with PERMN using two inputs */
  /*      M2 = permn(V,N) ; isequal(M2(K,:),M) */
  /*      % Note that M2 is a 125-by-3 matrix */
  /*  */
  /*      % PERMN can be used generate a binary table, as in */
  /*      B = permn([0 1],5)   */
  /*  */
  /*    NB Matrix sizes increases exponentially at rate (n^N)*N. */
  /*  */
  /*    See also PERMS, NCHOOSEK */
  /*             ALLCOMB, PERMPOS on the File Exchange */
  /*  tested in Matlab 2016a */
  /*  version 6.1 (may 2016) */
  /*  (c) Jos van der Geest */
  /*  Matlab File Exchange Author ID: 10584 */
  /*  email: samelinoa@gmail.com */
  /*  History */
  /*  1.1 updated help text */
  /*  2.0 new faster algorithm */
  /*  3.0 (aug 2006) implemented very fast algorithm */
  /*  3.1 (may 2007) Improved algorithm Roger Stafford pointed out that for some values, the floor */
  /*    operation on floating points, according to the IEEE 754 standard, could return */
  /*    erroneous values. His excellent solution was to add (1/2) to the values */
  /*    of A. */
  /*  3.2 (may 2007) changed help and error messages slightly */
  /*  4.0 (may 2008) again a faster implementation, based on ALLCOMB, suggested on the */
  /*    newsgroup comp.soft-sys.matlab on May 7th 2008 by "Helper". It was */
  /*    pointed out that COMBN(V,N) equals ALLCOMB(V,V,V...) (V repeated N */
  /*    times), ALLCMOB being faster. Actually version 4 is an improvement */
  /*    over version 1 ... */
  /*  4.1 (jan 2010) removed call to FLIPLR, using refered indexing N:-1:1 */
  /*    (is faster, suggestion of Jan Simon, jan 2010), removed REPMAT, and */
  /*    let NDGRID handle this */
  /*  4.2 (apr 2011) corrrectly return a column vector for N = 1 (error pointed */
  /*     out by Wilson). */
  /*  4.3 (apr 2013) make a reference to COMBNSUB */
  /*  5.0 (may 2015) NAME CHANGED (COMBN -> PERMN) and updated description, */
  /*    following comment by Stephen Obeldick that this function is misnamed */
  /*    as it produces permutations with repetitions rather then combinations. */
  /*  5.1 (may 2015) always calculate M via indices */
  /*  6.0 (may 2015) merged the functionaly of permnsub (aka combnsub) and this */
  /*    function */
  /*  6.1 (may 2016) fixed spelling errors */
  /* narginchk(2,3) ; */
  /* if fix(N) ~= N || N < 0 || numel(N) ~= 1 ; */
  /*     error('permn:negativeN','Second argument should be a positive integer') ; */
  /* end */
  /* % */
  /*  %if nargin==2, % PERMN(V,N) - return all permutations */
  /*       */
  /*      if nV==0 || N == 0, */
  /*          M = zeros(nV,N) ; */
  /*          I = zeros(nV,N) ; */
  /*           */
  /*      elseif N == 1, */
  /*          % return column vectors */
  /*          M = V(:) ; */
  /*          I = (1:nV).' ; */
  /*      else */
  /*          % this is faster than the math trick used for the call with three */
  /*          % arguments. */
  /*          %YY = zeros(nV*ones(1,N+1)); */
  /*          for nn = 1:N */
  /*              */
  /*          end */
  /*          [Y{N:-1:1}] = ndgrid(1:nV) ; */
  /*          I = reshape(cat(N+1,Y{:}),[],N) ; */
  /*          M = V(I) ; */
  /*      end */
  /*  else % PERMN(V,N,K) - return a subset of all permutations */
  emxInit_real_T(sp, &B, 2, &k_emlrtRTEI, true);
  emxInit_real_T(sp, &x, 2, &i_emlrtRTEI, true);
  emxInit_real_T(sp, &z, 2, &l_emlrtRTEI, true);
  if ((V->size[1] == 0) || (N == 0.0)) {
    i6 = M->size[0] * M->size[1];
    M->size[0] = 1;
    M->size[1] = (int32_T)N;
    emxEnsureCapacity(sp, (emxArray__common *)M, i6, (int32_T)sizeof(real_T),
                      &i_emlrtRTEI);
    k = (int32_T)N;
    for (i6 = 0; i6 < k; i6++) {
      M->data[i6] = 0.0;
    }
  } else {
    if (K < 0.0) {
      b_K = muDoubleScalarCeil(K);
    } else {
      b_K = muDoubleScalarFloor(K);
    }

    if (!!(K != b_K)) {
      st.site = &r_emlrtRSI;
      for (i6 = 0; i6 < 18; i6++) {
        u[i6] = varargin_1[i6];
      }

      y = NULL;
      m0 = emlrtCreateCharArray(2, iv1);
      emlrtInitCharArrayR2013a(&st, 18, m0, &u[0]);
      emlrtAssign(&y, m0);
      for (i6 = 0; i6 < 48; i6++) {
        b_u[i6] = varargin_2[i6];
      }

      b_y = NULL;
      m0 = emlrtCreateCharArray(2, iv2);
      emlrtInitCharArrayR2013a(&st, 48, m0, &b_u[0]);
      emlrtAssign(&b_y, m0);
      b_st.site = &sb_emlrtRSI;
      c_error(&b_st, y, b_y, &emlrtMCI);
    } else {
      st.site = &s_emlrtRSI;
      i6 = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = V->size[1];
      emxEnsureCapacity(&st, (emxArray__common *)x, i6, (int32_T)sizeof(real_T),
                        &i_emlrtRTEI);
      k = V->size[0] * V->size[1];
      for (i6 = 0; i6 < k; i6++) {
        x->data[i6] = V->data[i6];
      }

      nx = V->size[1];
      b_st.site = &w_emlrtRSI;
      sz_idx_1 = V->size[1];
      for (i6 = 0; i6 < 2; i6++) {
        b_varargin_1[i6] = (uint32_T)V->size[i6];
      }

      maxdimlen = 1;
      if ((int32_T)b_varargin_1[1] > 1) {
        maxdimlen = (int32_T)b_varargin_1[1];
      }

      if (V->size[1] < maxdimlen) {
      } else {
        maxdimlen = V->size[1];
      }

      if (sz_idx_1 > maxdimlen) {
        b_st.site = &x_emlrtRSI;
        b_error(&b_st);
      }

      i6 = V->size[0] * V->size[1];
      V->size[0] = 1;
      V->size[1] = sz_idx_1;
      emxEnsureCapacity(&st, (emxArray__common *)V, i6, (int32_T)sizeof(real_T),
                        &i_emlrtRTEI);
      if (nx == V->size[1]) {
      } else {
        emlrtErrorWithMessageIdR2012b(&st, &v_emlrtRTEI,
          "Coder:MATLAB:getReshapeDims_notSameNumel", 0);
      }

      b_st.site = &y_emlrtRSI;
      if (nx > 2147483646) {
        c_st.site = &n_emlrtRSI;
        check_forloop_overflow_error(&c_st);
      }

      for (k = 0; k + 1 <= nx; k++) {
        V->data[k] = x->data[k];
      }

      /*  v1.1 make input a row vector */
      nV = V->size[1];
      st.site = &t_emlrtRSI;
      Npos = mpower(&st, V->size[1], N);
      if (!!(K > Npos)) {
        /* warning('permn:IndexOverflow', ... */
        /*     'Values of K exceeding the total number of combinations are saturated.') */
        K = muDoubleScalarMin(K, Npos);
      }

      /* The engine is based on version 3.2 with the correction */
      /* suggested by Roger Stafford. This approach uses a single matrix */
      /* multiplication. */
      st.site = &u_emlrtRSI;
      b_st.site = &j_emlrtRSI;
      c_st.site = &k_emlrtRSI;
      if (muDoubleScalarIsNaN(1.0 - N)) {
        sz_idx_1 = 1;
        anew = rtNaN;
        apnd = 0.0;
        overflow = false;
      } else if (muDoubleScalarIsInf(1.0 - N)) {
        sz_idx_1 = 1;
        anew = rtNaN;
        apnd = 0.0;
        overflow = !(1.0 - N == 0.0);
      } else {
        anew = 1.0 - N;
        ndbl = muDoubleScalarFloor((0.0 - (1.0 - N)) + 0.5);
        apnd = (1.0 - N) + ndbl;
        absa = muDoubleScalarAbs(1.0 - N);
        if (muDoubleScalarAbs(apnd) < 4.4408920985006262E-16 * muDoubleScalarMax
            (absa, 0.0)) {
          ndbl++;
          apnd = 0.0;
        } else if (apnd > 0.0) {
          apnd = (1.0 - N) + (ndbl - 1.0);
        } else {
          ndbl++;
        }

        overflow = (2.147483647E+9 < ndbl);
        sz_idx_1 = (int32_T)ndbl;
      }

      d_st.site = &l_emlrtRSI;
      if (!overflow) {
      } else {
        emlrtErrorWithMessageIdR2012b(&d_st, &n_emlrtRTEI,
          "Coder:MATLAB:pmaxsize", 0);
      }

      i6 = z->size[0] * z->size[1];
      z->size[0] = 1;
      z->size[1] = sz_idx_1;
      emxEnsureCapacity(&c_st, (emxArray__common *)z, i6, (int32_T)sizeof(real_T),
                        &i_emlrtRTEI);
      if (sz_idx_1 > 0) {
        z->data[0] = anew;
        if (sz_idx_1 > 1) {
          z->data[sz_idx_1 - 1] = apnd;
          i6 = sz_idx_1 - 1;
          maxdimlen = asr_s32(i6, 1U);
          d_st.site = &m_emlrtRSI;
          for (k = 1; k < maxdimlen; k++) {
            z->data[k] = anew + (real_T)k;
            z->data[(sz_idx_1 - k) - 1] = apnd - (real_T)k;
          }

          if (maxdimlen << 1 == sz_idx_1 - 1) {
            z->data[maxdimlen] = (anew + apnd) / 2.0;
          } else {
            z->data[maxdimlen] = anew + (real_T)maxdimlen;
            z->data[maxdimlen + 1] = apnd - (real_T)maxdimlen;
          }
        }
      }

      st.site = &u_emlrtRSI;
      b_st.site = &p_emlrtRSI;
      c_st.site = &ab_emlrtRSI;
      anew = V->size[1];
      d_st.site = &bb_emlrtRSI;
      i6 = B->size[0] * B->size[1];
      B->size[0] = 1;
      B->size[1] = z->size[1];
      emxEnsureCapacity(&d_st, (emxArray__common *)B, i6, (int32_T)sizeof(real_T),
                        &j_emlrtRTEI);
      if (dimagree(B, z)) {
      } else {
        emlrtErrorWithMessageIdR2012b(&d_st, &u_emlrtRTEI, "MATLAB:dimagree", 0);
      }

      maxdimlen = z->size[1];
      d_st.site = &cb_emlrtRSI;
      if (1 > z->size[1]) {
        overflow = false;
      } else {
        overflow = (z->size[1] > 2147483646);
      }

      if (overflow) {
        e_st.site = &n_emlrtRSI;
        check_forloop_overflow_error(&e_st);
      }

      emlrtEnterParallelRegion(&c_st, omp_in_parallel());
      emlrtPushJmpBuf(&c_st, &emlrtJBStack);

#pragma omp parallel for \
 num_threads(emlrtAllocRegionTLSs(c_st.tls, omp_in_parallel(), omp_get_max_threads(), omp_get_num_procs())) \
 private(c_k)

      for (b_k = 1; b_k <= maxdimlen; b_k++) {
        c_k = b_k;
        B->data[c_k - 1] = muDoubleScalarPower(anew, z->data[c_k - 1]);
      }

      emlrtPopJmpBuf(&c_st, &emlrtJBStack);
      emlrtExitParallelRegion(&c_st, omp_in_parallel());
      i6 = B->size[0] * B->size[1];
      B->size[0] = 1;
      emxEnsureCapacity(sp, (emxArray__common *)B, i6, (int32_T)sizeof(real_T),
                        &i_emlrtRTEI);
      maxdimlen = B->size[0];
      sz_idx_1 = B->size[1];
      k = maxdimlen * sz_idx_1;
      for (i6 = 0; i6 < k; i6++) {
        B->data[i6] *= K - 0.5;
      }

      /*  matrix multiplication */
      st.site = &v_emlrtRSI;
      b_st.site = &db_emlrtRSI;
      i6 = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = B->size[1];
      emxEnsureCapacity(&b_st, (emxArray__common *)x, i6, (int32_T)sizeof(real_T),
                        &i_emlrtRTEI);
      k = B->size[0] * B->size[1];
      for (i6 = 0; i6 < k; i6++) {
        x->data[i6] = B->data[i6];
      }

      c_st.site = &eb_emlrtRSI;
      if (1 > B->size[1]) {
        overflow = false;
      } else {
        overflow = (B->size[1] > 2147483646);
      }

      if (overflow) {
        d_st.site = &n_emlrtRSI;
        check_forloop_overflow_error(&d_st);
      }

      for (k = 0; k + 1 <= B->size[1]; k++) {
        x->data[k] = muDoubleScalarFloor(x->data[k]);
      }

      st.site = &v_emlrtRSI;
      b_st.site = &fb_emlrtRSI;
      i6 = z->size[0] * z->size[1];
      z->size[0] = 1;
      z->size[1] = x->size[1];
      emxEnsureCapacity(&b_st, (emxArray__common *)z, i6, (int32_T)sizeof(real_T),
                        &j_emlrtRTEI);
      if (b_dimagree(z, x)) {
      } else {
        emlrtErrorWithMessageIdR2012b(&b_st, &u_emlrtRTEI, "MATLAB:dimagree", 0);
      }

      b_st.site = &gb_emlrtRSI;
      c_st.site = &bb_emlrtRSI;
      i6 = z->size[0] * z->size[1];
      z->size[0] = 1;
      z->size[1] = x->size[1];
      emxEnsureCapacity(&c_st, (emxArray__common *)z, i6, (int32_T)sizeof(real_T),
                        &j_emlrtRTEI);
      if (b_dimagree(z, x)) {
      } else {
        emlrtErrorWithMessageIdR2012b(&c_st, &u_emlrtRTEI, "MATLAB:dimagree", 0);
      }

      c_st.site = &hb_emlrtRSI;
      if (1 > x->size[1]) {
        overflow = false;
      } else {
        overflow = (x->size[1] > 2147483646);
      }

      if (overflow) {
        d_st.site = &n_emlrtRSI;
        check_forloop_overflow_error(&d_st);
      }

      for (k = 0; k + 1 <= x->size[1]; k++) {
        z->data[k] = muDoubleScalarRem(x->data[k], nV);
      }

      i6 = M->size[0] * M->size[1];
      M->size[0] = 1;
      M->size[1] = z->size[1];
      emxEnsureCapacity(sp, (emxArray__common *)M, i6, (int32_T)sizeof(real_T),
                        &i_emlrtRTEI);
      maxdimlen = V->size[1];
      k = z->size[0] * z->size[1];
      for (i6 = 0; i6 < k; i6++) {
        anew = z->data[i6] + 1.0;
        if (anew != (int32_T)muDoubleScalarFloor(anew)) {
          emlrtIntegerCheckR2012b(anew, &e_emlrtDCI, sp);
        }

        sz_idx_1 = (int32_T)anew;
        if (!((sz_idx_1 >= 1) && (sz_idx_1 <= maxdimlen))) {
          emlrtDynamicBoundsCheckR2012b(sz_idx_1, 1, maxdimlen, &p_emlrtBCI, sp);
        }

        M->data[i6] = V->data[sz_idx_1 - 1];
      }
    }
  }

  emxFree_real_T(&z);
  emxFree_real_T(&x);
  emxFree_real_T(&B);

  /*  end */
  /*  Algorithm using for-loops */
  /*  which can be implemented in C or VB */
  /*  */
  /*  nv = length(V) ; */
  /*  C = zeros(nv^N,N) ; % declaration */
  /*  for ii=1:N, */
  /*      cc = 1 ; */
  /*      for jj=1:(nv^(ii-1)), */
  /*          for kk=1:nv, */
  /*              for mm=1:(nv^(N-ii)), */
  /*                  C(cc,ii) = V(kk) ; */
  /*                  cc = cc + 1 ; */
  /*              end */
  /*          end */
  /*      end */
  /*  end */
  emlrtHeapReferenceStackLeaveFcnR2012b(sp);
}

/* End of code generation (permn2.c) */
