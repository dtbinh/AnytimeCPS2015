/*
 * posteriors_for_srcgen.c
 *
 * Code generation for function 'posteriors_for_srcgen'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "posteriors_for_srcgen.h"
#include "evalGaussianPrecomputedInv.h"
#include "inv.h"
#include "rdivide.h"
#include "repmat.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
static emlrtRSInfo q_emlrtRSI = { 17, "posteriors_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\posteriors_for_srcgen.m"
};

static emlrtRSInfo r_emlrtRSI = { 18, "posteriors_for_srcgen",
  "C:\\Users\\mlab\\Documents\\GitHub\\AnytimeCPS2015\\MATLAB\\sensing toolchain\\posteriors_for_srcgen.m"
};

/* Function Definitions */
void posteriors_for_srcgen(c_run_perception_module_for_src *SD, const emlrtStack
  *sp, const real_T mu[12], const real_T Sigma[36], const real_T
  ComponentProportion[4], const real_T data[5760000], real_T post[7680000])
{
  int32_T k;
  real_T invVariance[9];
  real_T b_mu[3];
  int32_T i3;
  emlrtStack st;
  st.prev = sp;
  st.tls = sp->tls;

  /*  Compute the posterior probability of each row in data (M-by-N) in */
  /*  the GMM with mean mu (K-by-N), variance Sigma (N-by-N-by-K), and */
  /*  mixing proportions ComponentProportion (1-by-K). */
  /*  N is the space dimension, K is the nb of components in the GMM, M is the */
  /*  nb of data points. */
  /*  */
  /*  There's room for improving run speed here. */
  memset(&SD->f2.den[0], 0, 1920000U * sizeof(real_T));
  for (k = 0; k < 4; k++) {
    /*      likelihood2(:,k) =  mvnpdf(data, mu(k,:),Sigma(:,:,k)); */
    /*      likelihood(:,k) = evalGaussian(data,mu(k,:), Sigma(:,:,k)); */
    st.site = &q_emlrtRSI;
    inv(&st, *(real_T (*)[9])&Sigma[9 * k], invVariance);
    memcpy(&SD->f2.data[0], &data[0], 5760000U * sizeof(real_T));
    for (i3 = 0; i3 < 3; i3++) {
      b_mu[i3] = mu[k + (i3 << 2)];
    }

    st.site = &r_emlrtRSI;
    evalGaussianPrecomputedInv(SD, &st, SD->f2.data, b_mu, invVariance, *(real_T
                                (*)[1920000])&SD->f2.likelihood[1920000 * k]);

    /*      nnz(abs(likelihood(:,k)-likelihood2(:,k))) */
    /*      max(abs(likelihood(:,k)-likelihood2(:,k))) */
    for (i3 = 0; i3 < 1920000; i3++) {
      SD->f2.den[i3] += ComponentProportion[k] * SD->f2.likelihood[i3 + 1920000 *
        k];
    }

    emlrtBreakCheckFastR2012b(emlrtBreakCheckR2012bFlagVar, sp);
  }

  c_repmat(ComponentProportion, SD->f2.dv3);
  for (i3 = 0; i3 < 7680000; i3++) {
    SD->f2.b_likelihood[i3] = SD->f2.likelihood[i3] * SD->f2.dv3[i3];
  }

  d_repmat(SD->f2.den, SD->f2.dv4);
  b_rdivide(SD->f2.b_likelihood, SD->f2.dv4, post);
}

/* End of code generation (posteriors_for_srcgen.c) */
