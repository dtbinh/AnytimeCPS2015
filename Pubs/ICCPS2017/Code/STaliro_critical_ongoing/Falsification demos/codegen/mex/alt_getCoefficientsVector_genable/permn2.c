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
#include "alt_getCoefficientsVector_genable.h"
#include "permn2.h"
#include "mpower.h"
#include "alt_getCoefficientsVector_genable_emxutil.h"
#include "error.h"
#include "eml_int_forloop_overflow_check.h"

/* Variable Definitions */
static emlrtRSInfo r_emlrtRSI = { 20, "eml_int_forloop_overflow_check",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/eml/eml_int_forloop_overflow_check.m"
};

static emlrtRSInfo u_emlrtRSI = { 137, "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m" };

static emlrtRSInfo v_emlrtRSI = { 140, "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m" };

static emlrtRSInfo w_emlrtRSI = { 142, "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m" };

static emlrtRSInfo x_emlrtRSI = { 39, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtRSInfo y_emlrtRSI = { 53, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtRSInfo ab_emlrtRSI = { 100, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtMCInfo emlrtMCI = { 20, 5, "error",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/lang/error.m" };

static emlrtRTEInfo d_emlrtRTEI = { 1, 19, "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m" };

static emlrtRTEInfo k_emlrtRTEI = { 63, 15, "reshape",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/elmat/reshape.m" };

static emlrtBCInfo g_emlrtBCI = { -1, -1, 155, 13, "V", "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m", 0 };

static emlrtDCInfo emlrtDCI = { 155, 13, "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m", 1 };

static emlrtBCInfo h_emlrtBCI = { 1, 81, 155, 13, "V", "permn2",
  "/home/mlab-retro/Documents/MATLAB/STaliro/Smooth/wavelet/permn2.m", 0 };

static emlrtRSInfo ib_emlrtRSI = { 20, "error",
  "/usr/local/MATLAB/R2015b/toolbox/eml/lib/matlab/lang/error.m" };

/* Function Declarations */
static void b_error(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    emlrtMCInfo *location);

/* Function Definitions */
static void b_error(const emlrtStack *sp, const mxArray *b, const mxArray *c,
                    emlrtMCInfo *location)
{
  const mxArray *pArrays[2];
  pArrays[0] = b;
  pArrays[1] = c;
  emlrtCallMATLABR2012b(sp, 0, NULL, 2, pArrays, "error", true, location);
}

void b_permn2(const emlrtStack *sp, real_T V[81], real_T K, real_T M[2])
{
  real_T b_K;
  int32_T k;
  static const char_T varargin_1[18] = { 'p', 'e', 'r', 'm', 'n', ':', 'I', 'n',
    'v', 'a', 'l', 'i', 'd', 'I', 'n', 'd', 'e', 'x' };

  char_T u[18];
  const mxArray *y;
  static const int32_T iv2[2] = { 1, 18 };

  const mxArray *m1;
  static const char_T varargin_2[48] = { 'T', 'h', 'i', 'r', 'd', ' ', 'a', 'r',
    'g', 'u', 'm', 'e', 'n', 't', ' ', 's', 'h', 'o', 'u', 'l', 'd', ' ', 'c',
    'o', 'n', 't', 'a', 'i', 'n', ' ', 'p', 'o', 's', 'i', 't', 'i', 'v', 'e',
    ' ', 'i', 'n', 't', 'e', 'g', 'e', 'r', 's', '.' };

  char_T b_u[48];
  const mxArray *b_y;
  static const int32_T iv3[2] = { 1, 48 };

  real_T x[81];
  real_T r[2];
  real_T d2;
  int32_T i2;
  emlrtStack st;
  emlrtStack b_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;

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
  if (K < 0.0) {
    b_K = muDoubleScalarCeil(K);
  } else {
    b_K = muDoubleScalarFloor(K);
  }

  if (!!(K != b_K)) {
    st.site = &u_emlrtRSI;
    for (k = 0; k < 18; k++) {
      u[k] = varargin_1[k];
    }

    y = NULL;
    m1 = emlrtCreateCharArray(2, iv2);
    emlrtInitCharArrayR2013a(&st, 18, m1, &u[0]);
    emlrtAssign(&y, m1);
    for (k = 0; k < 48; k++) {
      b_u[k] = varargin_2[k];
    }

    b_y = NULL;
    m1 = emlrtCreateCharArray(2, iv3);
    emlrtInitCharArrayR2013a(&st, 48, m1, &b_u[0]);
    emlrtAssign(&b_y, m1);
    b_st.site = &ib_emlrtRSI;
    b_error(&b_st, y, b_y, &emlrtMCI);
  } else {
    memcpy(&x[0], &V[0], 81U * sizeof(real_T));
    memcpy(&V[0], &x[0], 81U * sizeof(real_T));

    /*  v1.1 make input a row vector */
    /* The engine is based on version 3.2 with the correction */
    /* suggested by Roger Stafford. This approach uses a single matrix */
    /* multiplication. */
    /*  matrix multiplication */
    for (k = 0; k < 2; k++) {
      r[k] = muDoubleScalarRem(muDoubleScalarFloor((K - 0.5) *
        (0.012345679012345678 + 0.98765432098765427 * (real_T)k)), 81.0);
    }

    for (k = 0; k < 2; k++) {
      d2 = r[k] + 1.0;
      if (d2 != (int32_T)d2) {
        emlrtIntegerCheckR2012b(d2, &emlrtDCI, sp);
      }

      i2 = (int32_T)d2;
      if (!((i2 >= 1) && (i2 <= 81))) {
        emlrtDynamicBoundsCheckR2012b(i2, 1, 81, &h_emlrtBCI, sp);
      }

      M[k] = V[i2 - 1];
    }
  }

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
}

void permn2(const emlrtStack *sp, emxArray_real_T *V, real_T K, real_T M[2])
{
  int32_T i1;
  real_T b_K;
  static const char_T varargin_1[18] = { 'p', 'e', 'r', 'm', 'n', ':', 'I', 'n',
    'v', 'a', 'l', 'i', 'd', 'I', 'n', 'd', 'e', 'x' };

  char_T u[18];
  const mxArray *y;
  static const int32_T iv0[2] = { 1, 18 };

  const mxArray *m0;
  static const char_T varargin_2[48] = { 'T', 'h', 'i', 'r', 'd', ' ', 'a', 'r',
    'g', 'u', 'm', 'e', 'n', 't', ' ', 's', 'h', 'o', 'u', 'l', 'd', ' ', 'c',
    'o', 'n', 't', 'a', 'i', 'n', ' ', 'p', 'o', 's', 'i', 't', 'i', 'v', 'e',
    ' ', 'i', 'n', 't', 'e', 'g', 'e', 'r', 's', '.' };

  char_T b_u[48];
  const mxArray *b_y;
  static const int32_T iv1[2] = { 1, 48 };

  emxArray_real_T *x;
  int32_T maxdimlen;
  int32_T nx;
  int32_T sz_idx_1;
  int32_T B[2];
  int32_T nV;
  real_T Npos;
  real_T r[2];
  real_T d1;
  emlrtStack st;
  emlrtStack b_st;
  emlrtStack c_st;
  st.prev = sp;
  st.tls = sp->tls;
  b_st.prev = &st;
  b_st.tls = st.tls;
  c_st.prev = &b_st;
  c_st.tls = b_st.tls;
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
  if (V->size[1] == 0) {
    for (i1 = 0; i1 < 2; i1++) {
      M[i1] = 0.0;
    }
  } else {
    if (K < 0.0) {
      b_K = muDoubleScalarCeil(K);
    } else {
      b_K = muDoubleScalarFloor(K);
    }

    if (!!(K != b_K)) {
      st.site = &u_emlrtRSI;
      for (i1 = 0; i1 < 18; i1++) {
        u[i1] = varargin_1[i1];
      }

      y = NULL;
      m0 = emlrtCreateCharArray(2, iv0);
      emlrtInitCharArrayR2013a(&st, 18, m0, &u[0]);
      emlrtAssign(&y, m0);
      for (i1 = 0; i1 < 48; i1++) {
        b_u[i1] = varargin_2[i1];
      }

      b_y = NULL;
      m0 = emlrtCreateCharArray(2, iv1);
      emlrtInitCharArrayR2013a(&st, 48, m0, &b_u[0]);
      emlrtAssign(&b_y, m0);
      b_st.site = &ib_emlrtRSI;
      b_error(&b_st, y, b_y, &emlrtMCI);
    } else {
      emxInit_real_T(sp, &x, 2, &d_emlrtRTEI, true);
      st.site = &v_emlrtRSI;
      i1 = x->size[0] * x->size[1];
      x->size[0] = 1;
      x->size[1] = V->size[1];
      emxEnsureCapacity(&st, (emxArray__common *)x, i1, (int32_T)sizeof(real_T),
                        &d_emlrtRTEI);
      maxdimlen = V->size[0] * V->size[1];
      for (i1 = 0; i1 < maxdimlen; i1++) {
        x->data[i1] = V->data[i1];
      }

      nx = V->size[1];
      b_st.site = &x_emlrtRSI;
      sz_idx_1 = V->size[1];
      for (i1 = 0; i1 < 2; i1++) {
        B[i1] = V->size[i1];
      }

      maxdimlen = 1;
      if ((uint32_T)B[1] > 1U) {
        maxdimlen = B[1];
      }

      if (V->size[1] < maxdimlen) {
      } else {
        maxdimlen = V->size[1];
      }

      if (sz_idx_1 > maxdimlen) {
        b_st.site = &y_emlrtRSI;
        error(&b_st);
      }

      i1 = V->size[0] * V->size[1];
      V->size[0] = 1;
      V->size[1] = sz_idx_1;
      emxEnsureCapacity(&st, (emxArray__common *)V, i1, (int32_T)sizeof(real_T),
                        &d_emlrtRTEI);
      if (nx == V->size[1]) {
      } else {
        emlrtErrorWithMessageIdR2012b(&st, &k_emlrtRTEI,
          "Coder:MATLAB:getReshapeDims_notSameNumel", 0);
      }

      b_st.site = &ab_emlrtRSI;
      if (nx > 2147483646) {
        c_st.site = &r_emlrtRSI;
        check_forloop_overflow_error(&c_st);
      }

      for (maxdimlen = 0; maxdimlen + 1 <= nx; maxdimlen++) {
        V->data[maxdimlen] = x->data[maxdimlen];
      }

      emxFree_real_T(&x);

      /*  v1.1 make input a row vector */
      nV = V->size[1];
      st.site = &w_emlrtRSI;
      Npos = mpower(V->size[1]);
      if (!!(K > Npos)) {
        /* warning('permn:IndexOverflow', ... */
        /*     'Values of K exceeding the total number of combinations are saturated.') */
        K = muDoubleScalarMin(K, Npos);
      }

      /* The engine is based on version 3.2 with the correction */
      /* suggested by Roger Stafford. This approach uses a single matrix */
      /* multiplication. */
      /*  matrix multiplication */
      for (maxdimlen = 0; maxdimlen < 2; maxdimlen++) {
        r[maxdimlen] = muDoubleScalarRem(muDoubleScalarFloor((K - 0.5) *
          muDoubleScalarPower(nV, -1.0 + (((real_T)maxdimlen + 1.0) - 1.0))), nV);
      }

      maxdimlen = V->size[1];
      for (i1 = 0; i1 < 2; i1++) {
        d1 = r[i1] + 1.0;
        if (d1 != (int32_T)d1) {
          emlrtIntegerCheckR2012b(d1, &emlrtDCI, sp);
        }

        sz_idx_1 = (int32_T)d1;
        if (!((sz_idx_1 >= 1) && (sz_idx_1 <= maxdimlen))) {
          emlrtDynamicBoundsCheckR2012b(sz_idx_1, 1, maxdimlen, &g_emlrtBCI, sp);
        }

        M[i1] = V->data[sz_idx_1 - 1];
      }
    }
  }

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
