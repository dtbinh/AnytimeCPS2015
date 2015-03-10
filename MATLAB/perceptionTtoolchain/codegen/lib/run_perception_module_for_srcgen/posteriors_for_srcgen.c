/*
 * File: posteriors_for_srcgen.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "posteriors_for_srcgen.h"
#include "evalGaussianPrecomputedInv.h"
#include "inv.h"
#include "rdivide.h"
#include "repmat.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Compute the posterior probability of each row in data (M-by-N) in
 *  the GMM with mean mu (K-by-N), variance Sigma (N-by-N-by-K), and
 *  mixing proportions ComponentProportion (1-by-K).
 *  N is the space dimension, K is the nb of components in the GMM, M is the
 *  nb of data points.
 *
 *  There's room for improving run speed here.
 * Arguments    : const double mu[12]
 *                const double Sigma[36]
 *                const double ComponentProportion[4]
 *                const double data[5760000]
 *                double post[7680000]
 * Return Type  : void
 */
void posteriors_for_srcgen(const double mu[12], const double Sigma[36], const
  double ComponentProportion[4], const double data[5760000], double post[7680000])
{
  static double den[1920000];
  static double likelihood[7680000];
  int k;
  double invVariance[9];
  static double b_data[5760000];
  double b_mu[3];
  int i2;
  static double dv3[7680000];
  static double b_likelihood[7680000];
  static double dv4[7680000];
  memset(&den[0], 0, 1920000U * sizeof(double));
  for (k = 0; k < 4; k++) {
    /*      likelihood2(:,k) =  mvnpdf(data, mu(k,:),Sigma(:,:,k)); */
    /*      likelihood(:,k) = evalGaussian(data,mu(k,:), Sigma(:,:,k)); */
    inv(*(double (*)[9])&Sigma[9 * k], invVariance);
    memcpy(&b_data[0], &data[0], 5760000U * sizeof(double));
    for (i2 = 0; i2 < 3; i2++) {
      b_mu[i2] = mu[k + (i2 << 2)];
    }

    evalGaussianPrecomputedInv(b_data, b_mu, invVariance, *(double (*)[1920000])
      &likelihood[1920000 * k]);

    /*      nnz(abs(likelihood(:,k)-likelihood2(:,k))) */
    /*      max(abs(likelihood(:,k)-likelihood2(:,k))) */
    for (i2 = 0; i2 < 1920000; i2++) {
      den[i2] += ComponentProportion[k] * likelihood[i2 + 1920000 * k];
    }
  }

  c_repmat(ComponentProportion, dv3);
  for (i2 = 0; i2 < 7680000; i2++) {
    b_likelihood[i2] = likelihood[i2] * dv3[i2];
  }

  d_repmat(den, dv4);
  b_rdivide(b_likelihood, dv4, post);
}

/*
 * File trailer for posteriors_for_srcgen.c
 *
 * [EOF]
 */
