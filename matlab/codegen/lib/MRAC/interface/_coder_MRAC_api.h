/*
 * File: _coder_MRAC_api.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Apr-2020 15:46:37
 */

#ifndef _CODER_MRAC_API_H
#define _CODER_MRAC_API_H

/* Include Files */
#include "tmwtypes.h"
#include "mex.h"
#include "emlrt.h"
#include <stddef.h>
#include <stdlib.h>
#include "_coder_MRAC_api.h"

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

/* Function Declarations */
extern void MRAC(real_T theta_l, real_T theta_l_dot, real_T theta_m, real_T
                 theta_m_dot, real_T theta_m_d, real_T phi_k_1[5], real_T
                 theta_r_k_1[2], real_T b_gamma, real_T Kv, real_T N, real_T T,
                 real_T *V_control, real_T phi_k[5], real_T theta_r[2]);
extern void MRAC_api(const mxArray * const prhs[11], int32_T nlhs, const mxArray
                     *plhs[3]);
extern void MRAC_atexit(void);
extern void MRAC_initialize(void);
extern void MRAC_terminate(void);
extern void MRAC_xil_terminate(void);

#endif

/*
 * File trailer for _coder_MRAC_api.h
 *
 * [EOF]
 */
