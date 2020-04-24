/*
 * File: MRAC.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Apr-2020 15:46:37
 */

/* Include Files */
#include "MRAC.h"

/* Function Definitions */

/*
 * Arguments    : double theta_l
 *                double theta_l_dot
 *                double theta_m
 *                double theta_m_dot
 *                double theta_m_d
 *                const double phi_k_1[5]
 *                const double theta_r_k_1[2]
 *                double b_gamma
 *                double Kv
 *                double N
 *                double T
 *                double *V_control
 *                double phi_k[5]
 *                double theta_r[2]
 * Return Type  : void
 */
void MRAC(double theta_l, double theta_l_dot, double theta_m, double theta_m_dot,
          double theta_m_d, const double phi_k_1[5], const double theta_r_k_1[2],
          double b_gamma, double Kv, double N, double T, double *V_control,
          double phi_k[5], double theta_r[2])
{
  double theta_idx_1;
  double theta[5];
  int i0;
  double c_gamma[10];
  double theta_idx_0;
  double d_gamma[10];
  double d0;

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  MRAC */
  /*  Input theta_l     : Load angular position */
  /*  Input theta_l_dot : Load angular velocity */
  /*  Input theta_m     : Motor angular position */
  /*  Input theta_m_dot : Motor angular velocity */
  /*  Input theta_m_d   : Motor desired angular position */
  /*  Input phi_k_1     : Prior system estimated parameters [L^T M Ks_hat Ds_hat] */
  /*  Input theta_r_k_1 : Prior reference model state variables */
  /*  Output tau_m   : Control torque */
  /*  Output phi_k   : Current estimated system parameters */
  /*  Output theta_r : Current reference model state variables */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /*  function [V_control, phi_k, theta_r]  = MRAC(theta_l, theta_l_dot, theta_m, theta_m_dot,...  */
  /*                        theta_m_d, phi_k_1, theta_r_k_1) */
  /* %%%%%%%% Local variable %%%%%%%%% */
  /*      gamma = 1; % Learning rate coefficient */
  /*      Kv = 12; */
  /*      N = 10; % Gear ratio */
  /*      T = 0.001; % Sampling period */
  /*  Damping ratio */
  /*  Natural frequency */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Reference Model %%%%%%%%% */
  /*  -T*(w_n^2) */
  /*  1-2*T*xi*w_n */
  /*  T*(w_n^2) */
  /*  Reference model */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Adaption Law %%%%%%%%% */
  /*  State variable */
  /*  Error between System respond and reference model respond */
  /*  Regressor */
  /*  Derivative of parameters calculated from parameter */
  /*  adaption law */
  theta_idx_1 = 1.9599999999999997 / phi_k_1[2];
  theta_r[0] = (theta_r_k_1[0] + T * theta_r_k_1[1]) + 0.0 * theta_m_d;
  theta[0] = -theta_m;
  theta_r[1] = (-0.00196 * theta_r_k_1[0] + 0.9972 * theta_r_k_1[1]) + 0.00196 *
    theta_m_d;
  theta[1] = -theta_m_dot;
  theta[2] = theta_m_d;
  theta[3] = -1.0 / N * theta_l;
  theta[4] = -1.0 / N * theta_l_dot;
  for (i0 = 0; i0 < 5; i0++) {
    c_gamma[i0] = 0.0 * theta[i0];
    c_gamma[i0 + 5] = theta_idx_1 * theta[i0];
  }

  for (i0 = 0; i0 < 10; i0++) {
    c_gamma[i0] *= -b_gamma;
  }

  for (i0 = 0; i0 < 5; i0++) {
    d_gamma[i0] = 0.0;
    d0 = c_gamma[i0 + 5];
    d_gamma[i0] = c_gamma[i0] * 1.26 + d0 * 0.26;
    d_gamma[i0 + 5] = 0.0;
    d_gamma[i0 + 5] = c_gamma[i0] * 0.26 + d0 * 0.27;
  }

  theta_idx_0 = theta_m - theta_r[0];
  theta_idx_1 = theta_m_dot - theta_r[1];
  for (i0 = 0; i0 < 5; i0++) {
    phi_k[i0] = 0.0;
    d0 = d_gamma[i0] * theta_idx_0 + d_gamma[i0 + 5] * theta_idx_1;
    phi_k[i0] = d0;
    phi_k[i0] = phi_k_1[i0] + T * d0;
  }

  /*  Appoximated parameters calculated from its derivative */
  /*  [L^T M Ks_hat Ds_hat] */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Control Signal %%%%%%%%% */
  *V_control = Kv * ((((-phi_k[0] * theta_m + -phi_k[1] * theta_m_dot) + phi_k[2]
                       * theta_m_d) - phi_k[3] * (1.0 / N) * theta_l) - phi_k[4]
                     * (1.0 / N) * theta_l_dot);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
}

/*
 * File trailer for MRAC.c
 *
 * [EOF]
 */
