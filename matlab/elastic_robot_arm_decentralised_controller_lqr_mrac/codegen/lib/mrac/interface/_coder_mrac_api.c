/*
 * File: _coder_mrac_api.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Feb-2021 12:24:36
 */

/* Include Files */
#include "tmwtypes.h"
#include "_coder_mrac_api.h"
#include "_coder_mrac_mex.h"

/* Variable Definitions */
emlrtCTX emlrtRootTLSGlobal = NULL;
emlrtContext emlrtContextGlobal = { true,/* bFirstTime */
  false,                               /* bInitialized */
  131467U,                             /* fVersionInfo */
  NULL,                                /* fErrorFunction */
  "mrac",                              /* fFunctionName */
  NULL,                                /* fRTCallStack */
  false,                               /* bDebugMode */
  { 2045744189U, 2170104910U, 2743257031U, 4284093946U },/* fSigWrd */
  NULL                                 /* fSigMem */
};

/* Function Declarations */
static real_T b_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId);
static const mxArray *b_emlrt_marshallOut(const real_T u[5]);
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *phi_k_1,
  const char_T *identifier))[5];
static const mxArray *c_emlrt_marshallOut(const real_T u[2]);
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[5];
static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *theta_r_k_1, const char_T *identifier))[2];
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *theta_l,
  const char_T *identifier);
static const mxArray *emlrt_marshallOut(const real_T u);
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[2];
static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src, const
  emlrtMsgIdentifier *msgId);
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[5];
static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[2];

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
  y = g_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}

/*
 * Arguments    : const real_T u[5]
 * Return Type  : const mxArray *
 */
static const mxArray *b_emlrt_marshallOut(const real_T u[5])
{
  const mxArray *y;
  const mxArray *m1;
  static const int32_T iv0[1] = { 0 };

  static const int32_T iv1[1] = { 5 };

  y = NULL;
  m1 = emlrtCreateNumericArray(1, iv0, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m1, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m1, iv1, 1);
  emlrtAssign(&y, m1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *phi_k_1
 *                const char_T *identifier
 * Return Type  : real_T (*)[5]
 */
static real_T (*c_emlrt_marshallIn(const emlrtStack *sp, const mxArray *phi_k_1,
  const char_T *identifier))[5]
{
  real_T (*y)[5];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = d_emlrt_marshallIn(sp, emlrtAlias(phi_k_1), &thisId);
  emlrtDestroyArray(&phi_k_1);
  return y;
}
/*
 * Arguments    : const real_T u[2]
 * Return Type  : const mxArray *
 */
  static const mxArray *c_emlrt_marshallOut(const real_T u[2])
{
  const mxArray *y;
  const mxArray *m2;
  static const int32_T iv2[1] = { 0 };

  static const int32_T iv3[1] = { 2 };

  y = NULL;
  m2 = emlrtCreateNumericArray(1, iv2, mxDOUBLE_CLASS, mxREAL);
  emlrtMxSetData((mxArray *)m2, (void *)&u[0]);
  emlrtSetDimensions((mxArray *)m2, iv3, 1);
  emlrtAssign(&y, m2);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[5]
 */
static real_T (*d_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[5]
{
  real_T (*y)[5];
  y = h_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *theta_r_k_1
 *                const char_T *identifier
 * Return Type  : real_T (*)[2]
 */
  static real_T (*e_emlrt_marshallIn(const emlrtStack *sp, const mxArray
  *theta_r_k_1, const char_T *identifier))[2]
{
  real_T (*y)[2];
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = f_emlrt_marshallIn(sp, emlrtAlias(theta_r_k_1), &thisId);
  emlrtDestroyArray(&theta_r_k_1);
  return y;
}

/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *theta_l
 *                const char_T *identifier
 * Return Type  : real_T
 */
static real_T emlrt_marshallIn(const emlrtStack *sp, const mxArray *theta_l,
  const char_T *identifier)
{
  real_T y;
  emlrtMsgIdentifier thisId;
  thisId.fIdentifier = (const char *)identifier;
  thisId.fParent = NULL;
  thisId.bParentIsCell = false;
  y = b_emlrt_marshallIn(sp, emlrtAlias(theta_l), &thisId);
  emlrtDestroyArray(&theta_l);
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
 * Arguments    : const emlrtStack *sp
 *                const mxArray *u
 *                const emlrtMsgIdentifier *parentId
 * Return Type  : real_T (*)[2]
 */
static real_T (*f_emlrt_marshallIn(const emlrtStack *sp, const mxArray *u, const
  emlrtMsgIdentifier *parentId))[2]
{
  real_T (*y)[2];
  y = i_emlrt_marshallIn(sp, emlrtAlias(u), parentId);
  emlrtDestroyArray(&u);
  return y;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T
 */
  static real_T g_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId)
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
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[5]
 */
static real_T (*h_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[5]
{
  real_T (*ret)[5];
  static const int32_T dims[1] = { 5 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[5])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}
/*
 * Arguments    : const emlrtStack *sp
 *                const mxArray *src
 *                const emlrtMsgIdentifier *msgId
 * Return Type  : real_T (*)[2]
 */
  static real_T (*i_emlrt_marshallIn(const emlrtStack *sp, const mxArray *src,
  const emlrtMsgIdentifier *msgId))[2]
{
  real_T (*ret)[2];
  static const int32_T dims[1] = { 2 };

  emlrtCheckBuiltInR2012b(sp, msgId, src, "double", false, 1U, dims);
  ret = (real_T (*)[2])emlrtMxGetData(src);
  emlrtDestroyArray(&src);
  return ret;
}

/*
 * Arguments    : const mxArray * const prhs[15]
 *                int32_T nlhs
 *                const mxArray *plhs[3]
 * Return Type  : void
 */
void mrac_api(const mxArray * const prhs[15], int32_T nlhs, const mxArray *plhs
              [3])
{
  real_T (*phi_k)[5];
  real_T (*theta_r)[2];
  real_T theta_l;
  real_T theta_l_dot;
  real_T theta_m;
  real_T theta_m_dot;
  real_T theta_m_d;
  real_T (*phi_k_1)[5];
  real_T (*theta_r_k_1)[2];
  real_T b_gamma;
  real_T Kv;
  real_T N;
  real_T T;
  real_T xi;
  real_T w_n;
  real_T q1;
  real_T q2;
  real_T V_control;
  emlrtStack st = { NULL,              /* site */
    NULL,                              /* tls */
    NULL                               /* prev */
  };

  st.tls = emlrtRootTLSGlobal;
  phi_k = (real_T (*)[5])mxMalloc(sizeof(real_T [5]));
  theta_r = (real_T (*)[2])mxMalloc(sizeof(real_T [2]));

  /* Marshall function inputs */
  theta_l = emlrt_marshallIn(&st, emlrtAliasP(prhs[0]), "theta_l");
  theta_l_dot = emlrt_marshallIn(&st, emlrtAliasP(prhs[1]), "theta_l_dot");
  theta_m = emlrt_marshallIn(&st, emlrtAliasP(prhs[2]), "theta_m");
  theta_m_dot = emlrt_marshallIn(&st, emlrtAliasP(prhs[3]), "theta_m_dot");
  theta_m_d = emlrt_marshallIn(&st, emlrtAliasP(prhs[4]), "theta_m_d");
  phi_k_1 = c_emlrt_marshallIn(&st, emlrtAlias(prhs[5]), "phi_k_1");
  theta_r_k_1 = e_emlrt_marshallIn(&st, emlrtAlias(prhs[6]), "theta_r_k_1");
  b_gamma = emlrt_marshallIn(&st, emlrtAliasP(prhs[7]), "gamma");
  Kv = emlrt_marshallIn(&st, emlrtAliasP(prhs[8]), "Kv");
  N = emlrt_marshallIn(&st, emlrtAliasP(prhs[9]), "N");
  T = emlrt_marshallIn(&st, emlrtAliasP(prhs[10]), "T");
  xi = emlrt_marshallIn(&st, emlrtAliasP(prhs[11]), "xi");
  w_n = emlrt_marshallIn(&st, emlrtAliasP(prhs[12]), "w_n");
  q1 = emlrt_marshallIn(&st, emlrtAliasP(prhs[13]), "q1");
  q2 = emlrt_marshallIn(&st, emlrtAliasP(prhs[14]), "q2");

  /* Invoke the target function */
  mrac(theta_l, theta_l_dot, theta_m, theta_m_dot, theta_m_d, *phi_k_1,
       *theta_r_k_1, b_gamma, Kv, N, T, xi, w_n, q1, q2, &V_control, *phi_k,
       *theta_r);

  /* Marshall function outputs */
  plhs[0] = emlrt_marshallOut(V_control);
  if (nlhs > 1) {
    plhs[1] = b_emlrt_marshallOut(*phi_k);
  }

  if (nlhs > 2) {
    plhs[2] = c_emlrt_marshallOut(*theta_r);
  }
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mrac_atexit(void)
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
  mrac_xil_terminate();
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void mrac_initialize(void)
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
void mrac_terminate(void)
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
 * File trailer for _coder_mrac_api.c
 *
 * [EOF]
 */
