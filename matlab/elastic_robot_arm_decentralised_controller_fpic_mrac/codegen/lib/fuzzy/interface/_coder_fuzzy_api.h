/*
 * File: _coder_fuzzy_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Feb-2021 15:10:56
 */

#ifndef _CODER_FUZZY_API_H
#define _CODER_FUZZY_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_fuzzy_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T fuzzy(real_T e_l_k, real_T e_l_k_1, real_T theta_d_k_1, real_T Kp,
                    real_T Kd, real_T Ku, real_T T, real_T theta_d_upper_limit,
                    real_T theta_d_lower_limit);
extern void fuzzy_api(const mxArray * const prhs[9], int32_T nlhs, const mxArray
                      *plhs[1]);
extern void fuzzy_atexit(void);
extern void fuzzy_initialize(void);
extern void fuzzy_terminate(void);
extern void fuzzy_xil_terminate(void);

#endif

/*
 * File trailer for _coder_fuzzy_api.h
 *
 * [EOF]
 */