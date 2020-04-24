/*
 * File: _coder_Fuzzy_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Apr-2020 16:27:39
 */

#ifndef _CODER_FUZZY_API_H
#define _CODER_FUZZY_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_Fuzzy_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern real_T Fuzzy(real_T e_l_k, real_T e_l_k_1, real_T theta_m_d_k_1, real_T
                    Kp, real_T Kd, real_T Ku, real_T T, real_T
                    theta_m_d_upper_limit, real_T theta_m_d_lower_limit);
extern void Fuzzy_api(const mxArray * const prhs[9], int32_T nlhs, const mxArray
                      *plhs[1]);
extern void Fuzzy_atexit(void);
extern void Fuzzy_initialize(void);
extern void Fuzzy_terminate(void);
extern void Fuzzy_xil_terminate(void);

#endif

/*
 * File trailer for _coder_Fuzzy_api.h
 *
 * [EOF]
 */
