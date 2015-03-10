/*
 * run_perception_module_for_srcgen_data.c
 *
 * Code generation for function 'run_perception_module_for_srcgen_data'
 *
 */

/* Include files */
#include "rt_nonfinite.h"
#include "run_perception_module_for_srcgen.h"
#include "run_perception_module_for_srcgen_data.h"
#include "libmwmorphop_binary_tbb.h"
#include "libmwordfilt2.h"
#include "tmwtypes.h"

/* Variable Definitions */
const volatile char_T *emlrtBreakCheckR2012bFlagVar;
emlrtRSInfo p_emlrtRSI = { 20, "eml_int_forloop_overflow_check",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_int_forloop_overflow_check.m"
};

emlrtRSInfo hb_emlrtRSI = { 14, "sqrt",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elfun\\sqrt.m"
};

emlrtRSInfo rb_emlrtRSI = { 19, "ind2sub",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\ind2sub.m"
};

emlrtRSInfo fc_emlrtRSI = { 16, "max",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\datafun\\max.m"
};

emlrtRSInfo gc_emlrtRSI = { 18, "eml_min_or_max",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_min_or_max.m"
};

emlrtRSInfo hc_emlrtRSI = { 108, "eml_min_or_max",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_min_or_max.m"
};

emlrtRSInfo ic_emlrtRSI = { 229, "eml_min_or_max",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_min_or_max.m"
};

emlrtRSInfo jc_emlrtRSI = { 202, "eml_min_or_max",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\eml_min_or_max.m"
};

emlrtRSInfo qc_emlrtRSI = { 45, "repmat",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\repmat.m"
};

emlrtRSInfo bd_emlrtRSI = { 39, "eml_matlab_zggev",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggev.m"
};

emlrtRSInfo cd_emlrtRSI = { 84, "eml_matlab_zggev",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggev.m"
};

emlrtRSInfo fd_emlrtRSI = { 40, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo gd_emlrtRSI = { 36, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo hd_emlrtRSI = { 27, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo id_emlrtRSI = { 23, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo jd_emlrtRSI = { 140, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo kd_emlrtRSI = { 77, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo ld_emlrtRSI = { 102, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtRSInfo md_emlrtRSI = { 106, "eml_matlab_zggbal",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\eml\\lapack\\matlab\\eml_matlab_zggbal.m"
};

emlrtMCInfo i_emlrtMCI = { 28, 19, "assert",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\assert.m"
};

emlrtMCInfo l_emlrtMCI = { 405, 5, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

emlrtMCInfo m_emlrtMCI = { 404, 15, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

emlrtRTEInfo o_emlrtRTEI = { 127, 5, "find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

emlrtRTEInfo p_emlrtRTEI = { 249, 13, "find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

emlrtRTEInfo s_emlrtRTEI = { 33, 6, "find",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\elmat\\find.m"
};

c_run_perception_module_for_src *d_run_perception_module_for_src;
emlrtRSInfo ne_emlrtRSI = { 28, "assert",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\assert.m"
};

emlrtRSInfo te_emlrtRSI = { 404, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

emlrtRSInfo cf_emlrtRSI = { 405, "colon",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\eml\\lib\\matlab\\ops\\colon.m" };

emlrtRSInfo ff_emlrtRSI = { 18, "indexDivide",
  "C:\\Program Files\\MATLAB\\R2014b\\toolbox\\shared\\coder\\coder\\+coder\\+internal\\indexDivide.m"
};

/* End of code generation (run_perception_module_for_srcgen_data.c) */
