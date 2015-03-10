/*
 * File: run_perception_module_for_srcgen.c
 *
 * MATLAB Coder version            : 2.7
 * C/C++ source code generated on  : 10-Mar-2015 11:47:01
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "run_perception_module_for_srcgen_emxutil.h"
#include "region_properties_for_srcgen.h"
#include "label_connected_components_for_srcgen.h"
#include "medfilt2.h"
#include "sum.h"
#include "repmat.h"
#include "posteriors_for_srcgen.h"
#include "preprocess_img.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Function Definitions */

/*
 * Arguments    : const unsigned char Im[5760000]
 *                const unsigned char colors[3]
 *                double minAcceptanceProbScalingFactor
 *                double minSignificanceProb
 *                double minAcceptanceProb
 *                const double muPOI[12]
 *                const double SigmaPOI[36]
 *                const double ComponentProportionPOI[4]
 *                const double muNON[12]
 *                const double SigmaNON[36]
 *                const double ComponentProportionNON[4]
 *                const emxArray_real_T *Alpha
 *                const emxArray_real_T *SupportVectorLabels
 *                double KernelScale
 *                const emxArray_real_T *SupportVectors
 *                double Bias
 * Return Type  : void
 */
void run_perception_module_for_srcgen(const unsigned char Im[5760000], const
  unsigned char colors[3], double minAcceptanceProbScalingFactor, double
  minSignificanceProb, double minAcceptanceProb, const double muPOI[12], const
  double SigmaPOI[36], const double ComponentProportionPOI[4], const double
  muNON[12], const double SigmaNON[36], const double ComponentProportionNON[4],
  const emxArray_real_T *Alpha, const emxArray_real_T *SupportVectorLabels,
  double KernelScale, const emxArray_real_T *SupportVectors, double Bias)
{
  static double I[5760000];
  static double b_I[5760000];
  int n;
  int k;
  static double candidate[5760000];
  static double posteriorspoi[7680000];
  static double posteriorsnon[7680000];
  static double dv0[7680000];
  static double b_posteriorspoi[7680000];
  static double d1[1920000];
  static double d2[1920000];
  static boolean_T clusterObjOfInterest[1920000];
  int32_T exitg1;
  double b_d2;
  static boolean_T M[1920000];
  static boolean_T B[1920000];
  boolean_T nhood;
  double asize[2];
  double nsize[2];
  emxArray_creal_T *L;
  (void)Alpha;
  (void)SupportVectorLabels;
  (void)KernelScale;
  (void)SupportVectors;
  (void)Bias;

  /*  Detect pix of interest */
  minAcceptanceProb /= minAcceptanceProbScalingFactor;

  /*  allow for 1st iteration of while loop */
  preprocess_img(Im, I);
  for (n = 0; n < 3; n++) {
    for (k = 0; k < 1600; k++) {
      memcpy(&b_I[1200 * k + 1920000 * n], &I[1200 * k + 1920000 * (colors[n] -
              1)], 1200U * sizeof(double));
    }
  }

  for (n = 0; n < 3; n++) {
    for (k = 0; k < 1600; k++) {
      memcpy(&I[1200 * k + 1920000 * n], &b_I[1200 * k + 1920000 * n], 1200U *
             sizeof(double));
    }
  }

  memcpy(&candidate[0], &I[0], 5760000U * sizeof(double));
  posteriors_for_srcgen(muPOI, SigmaPOI, ComponentProportionPOI, candidate,
                        posteriorspoi);
  posteriors_for_srcgen(muNON, SigmaNON, ComponentProportionNON, candidate,
                        posteriorsnon);

  /*  For each pix, decide if it's best described by poi or non */
  c_repmat(ComponentProportionPOI, dv0);
  for (n = 0; n < 7680000; n++) {
    b_posteriorspoi[n] = posteriorspoi[n] * dv0[n];
  }

  b_sum(b_posteriorspoi, d1);
  c_repmat(ComponentProportionNON, dv0);
  for (n = 0; n < 7680000; n++) {
    posteriorspoi[n] = posteriorsnon[n] * dv0[n];
  }

  b_sum(posteriorspoi, d2);
  memset(&clusterObjOfInterest[0], 0, 1920000U * sizeof(boolean_T));

  /* initialize while */
  do {
    exitg1 = 0;
    n = 0;
    for (k = 0; k < 1920000; k++) {
      if (clusterObjOfInterest[k]) {
        n++;
      }
    }

    if ((n == 0) && (minAcceptanceProb >= minSignificanceProb)) {
      minAcceptanceProb *= minAcceptanceProbScalingFactor;
      for (k = 0; k < 1920000; k++) {
        if ((d2[k] >= minAcceptanceProb) || rtIsNaN(minAcceptanceProb)) {
          b_d2 = d2[k];
        } else {
          b_d2 = minAcceptanceProb;
        }

        clusterObjOfInterest[k] = (d1[k] > b_d2);
      }
    } else {
      exitg1 = 1;
    }
  } while (exitg1 == 0);

  /*  Filter out the smaller things */
  memcpy(&M[0], &clusterObjOfInterest[0], 1920000U * sizeof(boolean_T));
  nhood = true;
  for (n = 0; n < 2; n++) {
    asize[n] = 1200.0 + 400.0 * (double)n;
    nsize[n] = 1.0;
  }

  emxInit_creal_T(&L, 2);
  erode_binary_twod_tbb(M, asize, 2.0, &nhood, nsize, 2.0, B);
  medfilt2(B, M);

  /*  Connect components and extract features for the positive class, i.e. of barrel objects. */
  /*  */
  /*  stats = regionprops(M, 'MajorAxisLength', 'MinorAxisLength', 'Eccentricity', 'Solidity', 'Centroid'); */
  /*  statsPosClass = zeros(length(stats),6); */
  /*  for i=1:length(stats) */
  /*      statsPosClass(i,:) = [stats(i).MajorAxisLength, stats(i).MinorAxisLength, stats(i).Eccentricity, stats(i).Solidity, stats(i).Centroid]; */
  /*  end     */
  /*  M = [1 1 1 0 0 0;1 0 0 1 1 1;1 1 0 0 0 0 ; 1 1 0 0 0 0;1 1 0 0 0 1;0 0 0 0 0 1]; */
  c_label_connected_components_fo(M, d1);

  /*  Keep it simple - properties are hard-coded in function */
  region_properties_for_srcgen(d1, L);

  /*  Detect shapes */
  emxFree_creal_T(&L);
}

/*
 * File trailer for run_perception_module_for_srcgen.c
 *
 * [EOF]
 */
