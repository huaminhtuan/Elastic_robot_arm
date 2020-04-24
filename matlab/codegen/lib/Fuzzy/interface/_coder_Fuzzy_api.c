/*
 * File: _coder_Fuzzy_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Apr-2020 16:27:39
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_Fuzzy_api.h"
#include "_coder_Fuzzy_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "Fuzzy",                             /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *e_l_k, const
  char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u);

/* Function Definitions */

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T
 */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId)
{
  real_T y;
  y = c_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
static real_T c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId)
{
  real_T ret;
  static const int32_T dims = 0;
  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 0U, &dims);
  ret = *(real_T *)emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *e_l_k
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *e_l_k, const
  char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(e_l_k), &thisId);
  emlrtDestroyArray(&e_l_k);
  return y;
}

/*
 * Arguments    : const real_T u
 * Return Type  : const mxArray *
 */
static const mxArray *emlrt_marshallOut(const real_T u)
{
  const mxArray *y;
  const mxArray *m0;
  y = NULL;
  m0 = emlrtCreateDoubleScalar(u);
  emlrtAssign(&y, m0);
  return y;
}

/*
 * Arguments    : const mxArray * const prhs[9]
 *                int32_T nlhs
 *                const mxArray *plhs[1]
 * Return Type  : void
 */
void Fuzzy_api(const mxArray * const prhs[9], int32_T nlhs, const mxArray *plhs
               [1])
{
  real_T e_l_k;
  real_T e_l_k_1;
  real_T theta_m_d_k_1;
  real_T Kp;
  real_T Kd;
  real_T Ku;
  real_T T;
  real_T theta_m_d_upper_limit;
  real_T theta_m_d_lower_limit;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  (void)nlhs;
  st.tls = emlrtRootTLSGlobal;

  /* Marshall function inputs */
  e_l_k = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "e_l_k");
  e_l_k_1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "e_l_k_1");
  theta_m_d_k_1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "theta_m_d_k_1");
  Kp = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "Kp");
  Kd = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "Kd");
  Ku = emlrt_marshallIn(&st, emlrtAliasP(prhs[5]), "Ku");
  T = emlrt_marshallIn(&st, emlrtAliasP(prhs[6]), "T");
  theta_m_d_upper_limit = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]),
    "theta_m_d_upper_limit");
  theta_m_d_lower_limit = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]),
    "theta_m_d_lower_limit");

  /* Invoke the target function */
  e_l_k = Fuzzy(e_l_k, e_l_k_1, theta_m_d_k_1, Kp, Kd, Ku, T,
                theta_m_d_upper_limit, theta_m_d_lower_limit);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(e_l_k);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Fuzzy_atexit(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtEnterRtStackR2012b(&st);
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
  Fuzzy_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Fuzzy_initialize(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  mexFunctionCreateRootTLS();
  st.tls = emlrtRootTLSGlobal;
  emlrtClearAllocCountR2012b(&st, false, 0U, 0);
  emlrtEnterRtStackR2012b(&st);
  emlrtFirstTimeR2012b(emlrtRootTLSGlobal);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void Fuzzy_terminate(void)
{
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  emlrtLeaveRtStackR2012b(&st);
  emlrtDestroyRootTLS(&emlrtRootTLSGlobal);
}

/*
 * File trailer for _coder_Fuzzy_api.c
 *
 * [EOF]
 */
