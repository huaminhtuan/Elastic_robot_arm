/*
 * File: mrac.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Feb-2021 12:24:36
 */

/* Include Files */
#include "mrac.h"

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
 *                double xi
 *                double w_n
 *                double q1
 *                double q2
 *                double *V_control
 *                double phi_k[5]
 *                double theta_r[2]
 * Return Type  : void
 */
void mrac(double theta_l, double theta_l_dot, double theta_m, double theta_m_dot,
          double theta_m_d, const double phi_k_1[5], const double theta_r_k_1[2],
          double b_gamma, double Kv, double N, double T, double xi, double w_n,
          double q1, double q2, double *V_control, double phi_k[5], double
          theta_r[2])
{
  double p2_tmp;
  double p2;
  double p3;
  double theta_idx_1;
  double theta[5];
  int i0;
  double c_gamma[10];
  double dv0[4];
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
  /*  Output theta_r : Current reference model  state variables */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%%% Local variable %%%%%%%%%% */
  /*      gamma = 0.995; % Learning rate coefficient */
  /*      % lon --> cham thich nghi, it gai */
  /*      % nho --> tn nhanh, co the nhieu */
  /*      Kv = 20; */
  /*      N = 10; % Gear ratio */
  /*      T = 0.001; % Sampling period */
  /*      xi = 1; % Damping ratio */
  /*      w_n = 5; % Natural frequency */
  /*      q1 = 3; */
  /*      q2 = 5; */
  p2_tmp = w_n * w_n;
  p2 = q1 / (2.0 * p2_tmp);
  p3 = (2.0 * p2 + q2) / (4.0 * xi * w_n);

  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Reference Model %%%%%%%%% */
  /*  -T*(w_n^2) */
  /*  1-2*T*xi*w_n */
  /*  T*(w_n^2) */
  theta_r[0] = (theta_r_k_1[0] + T * theta_r_k_1[1]) + 0.0 * theta_m_d;
  theta_r[1] = (-T * p2_tmp * theta_r_k_1[0] + (1.0 - 2.0 * T * xi * w_n) *
                theta_r_k_1[1]) + T * p2_tmp * theta_m_d;

  /*  Reference model */
  /* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
  /* %%%%%%%% Adaption Law %%%%%%%%% */
  /*  State variable */
  /*  Error between System respond and reference model respond */
  /*  Regressor */
  /*  Derivative of parameters calculated from parameter */
  /*  adaption law */
  theta_idx_1 = p2_tmp / phi_k_1[2];
  theta[0] = -theta_m;
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

  dv0[0] = 2.0 * xi * w_n * p2 + p2_tmp * p3;
  for (i0 = 0; i0 < 5; i0++) {
    d_gamma[i0] = 0.0;
    d0 = c_gamma[i0 + 5];
    d_gamma[i0] = c_gamma[i0] * dv0[0] + d0 * p2;
    d_gamma[i0 + 5] = 0.0;
    d_gamma[i0 + 5] = c_gamma[i0] * p2 + d0 * p3;
  }

  p2_tmp = theta_m - theta_r[0];
  theta_idx_1 = theta_m_dot - theta_r[1];
  for (i0 = 0; i0 < 5; i0++) {
    phi_k[i0] = 0.0;
    d0 = d_gamma[i0] * p2_tmp + d_gamma[i0 + 5] * theta_idx_1;
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
 * File trailer for mrac.c
 *
 * [EOF]
 */
