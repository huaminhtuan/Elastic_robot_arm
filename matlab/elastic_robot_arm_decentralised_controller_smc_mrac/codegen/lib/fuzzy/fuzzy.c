/*
 * File: fuzzy.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Feb-2021 15:10:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "fuzzy.h"
#include "trapmf1.h"
#include "trimf1.h"

/* Function Definitions */

/*
 * Arguments    : double e_l_k
 *                double e_l_k_1
 *                double theta_d_k_1
 *                double Kp
 *                double Kd
 *                double Ku
 *                double T
 *                double theta_d_upper_limit
 *                double theta_d_lower_limit
 * Return Type  : double
 */
double fuzzy(double e_l_k, double e_l_k_1, double theta_d_k_1, double Kp, double
             Kd, double Ku, double T, double theta_d_upper_limit, double
             theta_d_lower_limit)
{
  double theta_d;
  double e;
  double de;
  int idx;
  double fuzzy_e[5];
  double fuzzy_de[5];
  static const double dv0[4] = { -2.8, -1.2, -0.2, -0.1 };

  double dv1[3];
  static const double dv2[4] = { -2.8, -1.2, -0.4, -0.2 };

  static const double dv3[4] = { 0.1, 0.2, 1.2, 2.8 };

  static const double dv4[4] = { 0.2, 0.4, 1.2, 2.8 };

  int j;
  double varargin_1[6];
  double rules[25];
  boolean_T exitg1;
  double b_varargin_1[4];
  double u_PS;
  double u_ZE;
  double u_NS;
  double u_NB;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  Fuzzy */
  /*  Input e_l_k        : Current error between load angular position feedback and  */
  /*                       desired load angular position */
  /*  Input e_l_k_1      : Prior error between load angular position feedback and */
  /*                       desired load angular position */
  /*  Input theta_m_d_k_1: Prior desired motor angular position */
  /*  Output theta_m_d: Desired motor position */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%% Local variable %%%%%%%%%% */
  /*      Kp = 5; */
  /*      Kd = 0.1; */
  /*      Ku = 1; */
  /*      T = 0.001; */
  /*      theta_d_upper_limit = pi; */
  /*      theta_d_lower_limit = -pi; */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Preprocessing %%%%%%%%% */
  e = Kp * e_l_k;
  de = Kd * (e_l_k - e_l_k_1) / T;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Fuzzification %%%%%%%%% */
  /* %% */
  /*  Input e */
  /*  	Range: [-1  1] */
  /* 	Membership functions: NB, NS, ZE, PS, PB */
  /*  Input de: */
  /* 	Range: [-1  1] */
  /* 	Membership functions: NB, NS, ZE, PS, PB */
  /* %% */
  /*  */
  /*  1 to 5: NB, NS, ZE, PS, PB */
  for (idx = 0; idx < 5; idx++) {
    fuzzy_e[idx] = 0.0;
    fuzzy_de[idx] = 0.0;
  }

  /*  1 to 5: NB, NS, ZE, PS, PB */
  /*  Out of range */
  if (e < -1.0) {
    fuzzy_e[0] = 1.0;

    /*  NB */
  } else if (e > 1.0) {
    fuzzy_e[4] = 1.0;

    /*  PB */
  } else {
    fuzzy_e[0] = trapmf(e, dv0);

    /*  NB */
    dv1[0] = -0.2;
    dv1[1] = -0.1;
    dv1[2] = 0.0;
    fuzzy_e[1] = trimf(e, dv1);

    /*  NS */
    dv1[0] = -0.1;
    dv1[1] = 0.0;
    dv1[2] = 0.1;
    fuzzy_e[2] = trimf(e, dv1);

    /*  ZE */
    dv1[0] = 0.0;
    dv1[1] = 0.1;
    dv1[2] = 0.2;
    fuzzy_e[3] = trimf(e, dv1);

    /*  PS */
    fuzzy_e[4] = trapmf(e, dv3);

    /*  PB */
  }

  if (de < -1.0) {
    fuzzy_de[0] = 1.0;

    /*  NB */
  } else if (de > 1.0) {
    fuzzy_de[4] = 1.0;

    /*  PB */
  } else {
    fuzzy_de[0] = trapmf(de, dv2);

    /*  NB */
    dv1[0] = -0.4;
    dv1[1] = -0.2;
    dv1[2] = 0.0;
    fuzzy_de[1] = trimf(de, dv1);

    /*  NS */
    dv1[0] = -0.2;
    dv1[1] = 0.0;
    dv1[2] = 0.2;
    fuzzy_de[2] = trimf(de, dv1);

    /*  ZE */
    dv1[0] = 0.0;
    dv1[1] = 0.2;
    dv1[2] = 0.4;
    fuzzy_de[3] = trimf(de, dv1);

    /*  PS */
    fuzzy_de[4] = trapmf(de, dv4);

    /*  PB */
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Fuzzy Inference Rules %%%%%%%%% */
  /* %% */
  /*  ------------------------------ */
  /*  | \e|    |    |    |    |    | */
  /*  |de\| NB | NS | ZE | PS | PB | */
  /*  |----------------------------- */
  /*  |	NB| NB | NB | NB | NS | ZE | */
  /*  |----------------------------- */
  /*  | NS| NB | NB | NS | ZE | PS | */
  /*  |----------------------------- */
  /*  | ZE| NB | NS | ZE | PS | PB | */
  /*  |----------------------------- */
  /*  | PS| NS | ZE | PS | PB | PB | */
  /*  |----------------------------- */
  /*  | PB| ZE | PS | PB | PB | PB | */
  /*  ------------------------------ */
  /*  MAX-PROD aggregation rules */
  /* %% */
  /*  Firing strength */
  for (idx = 0; idx < 5; idx++) {
    for (j = 0; j < 5; j++) {
      rules[idx + 5 * j] = fuzzy_de[idx] * fuzzy_e[j];
    }
  }

  /*  Accummulation */
  varargin_1[0] = rules[22];
  varargin_1[1] = rules[18];
  varargin_1[2] = rules[23];
  varargin_1[3] = rules[14];
  varargin_1[4] = rules[19];
  varargin_1[5] = rules[24];
  if (!rtIsNaN(rules[22])) {
    idx = 1;
  } else {
    idx = 0;
    j = 2;
    exitg1 = false;
    while ((!exitg1) && (j < 7)) {
      if (!rtIsNaN(varargin_1[j - 1])) {
        idx = j;
        exitg1 = true;
      } else {
        j++;
      }
    }
  }

  if (idx == 0) {
    de = rules[22];
  } else {
    de = varargin_1[idx - 1];
    idx++;
    for (j = idx; j < 7; j++) {
      e = varargin_1[j - 1];
      if (de < e) {
        de = e;
      }
    }
  }

  b_varargin_1[0] = rules[21];
  b_varargin_1[1] = rules[17];
  b_varargin_1[2] = rules[13];
  b_varargin_1[3] = rules[9];
  if (!rtIsNaN(rules[21])) {
    idx = 1;
  } else {
    idx = 0;
    j = 2;
    exitg1 = false;
    while ((!exitg1) && (j < 5)) {
      if (!rtIsNaN(b_varargin_1[j - 1])) {
        idx = j;
        exitg1 = true;
      } else {
        j++;
      }
    }
  }

  if (idx == 0) {
    u_PS = rules[21];
  } else {
    u_PS = b_varargin_1[idx - 1];
    idx++;
    for (j = idx; j < 5; j++) {
      e = b_varargin_1[j - 1];
      if (u_PS < e) {
        u_PS = e;
      }
    }
  }

  fuzzy_e[0] = rules[20];
  fuzzy_e[1] = rules[16];
  fuzzy_e[2] = rules[12];
  fuzzy_e[3] = rules[8];
  fuzzy_e[4] = rules[4];
  if (!rtIsNaN(rules[20])) {
    idx = 1;
  } else {
    idx = 0;
    j = 2;
    exitg1 = false;
    while ((!exitg1) && (j < 6)) {
      if (!rtIsNaN(fuzzy_e[j - 1])) {
        idx = j;
        exitg1 = true;
      } else {
        j++;
      }
    }
  }

  if (idx == 0) {
    u_ZE = rules[20];
  } else {
    u_ZE = fuzzy_e[idx - 1];
    idx++;
    for (j = idx; j < 6; j++) {
      e = fuzzy_e[j - 1];
      if (u_ZE < e) {
        u_ZE = e;
      }
    }
  }

  b_varargin_1[0] = rules[15];
  b_varargin_1[1] = rules[11];
  b_varargin_1[2] = rules[7];
  b_varargin_1[3] = rules[3];
  if (!rtIsNaN(rules[15])) {
    idx = 1;
  } else {
    idx = 0;
    j = 2;
    exitg1 = false;
    while ((!exitg1) && (j < 5)) {
      if (!rtIsNaN(b_varargin_1[j - 1])) {
        idx = j;
        exitg1 = true;
      } else {
        j++;
      }
    }
  }

  if (idx == 0) {
    u_NS = rules[15];
  } else {
    u_NS = b_varargin_1[idx - 1];
    idx++;
    for (j = idx; j < 5; j++) {
      e = b_varargin_1[j - 1];
      if (u_NS < e) {
        u_NS = e;
      }
    }
  }

  varargin_1[0] = rules[0];
  varargin_1[1] = rules[5];
  varargin_1[2] = rules[10];
  varargin_1[3] = rules[1];
  varargin_1[4] = rules[6];
  varargin_1[5] = rules[2];
  if (!rtIsNaN(rules[0])) {
    idx = 1;
  } else {
    idx = 0;
    j = 2;
    exitg1 = false;
    while ((!exitg1) && (j < 7)) {
      if (!rtIsNaN(varargin_1[j - 1])) {
        idx = j;
        exitg1 = true;
      } else {
        j++;
      }
    }
  }

  if (idx == 0) {
    u_NB = rules[0];
  } else {
    u_NB = varargin_1[idx - 1];
    idx++;
    for (j = idx; j < 7; j++) {
      e = varargin_1[j - 1];
      if (u_NB < e) {
        u_NB = e;
      }
    }
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Defuzzification %%%%%%%%% */
  /* %% */
  /*  Defuzzification method: Center of gravity */
  /* %% */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Postprocessing %%%%%%%%% */
  theta_d = ((((de + u_PS * 0.3) + u_ZE * 0.0) + u_NS * -0.3) + -u_NB) / ((((de
    + u_PS) + u_ZE) + u_NS) + u_NB) * Ku * T + theta_d_k_1;

  /*  Saturation */
  if (theta_d > theta_d_upper_limit) {
    theta_d = theta_d_upper_limit;
  } else {
    if (theta_d < theta_d_lower_limit) {
      theta_d = theta_d_lower_limit;
    }
  }

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  return theta_d;
}

/*
 * File trailer for fuzzy.c
 *
 * [EOF]
 */