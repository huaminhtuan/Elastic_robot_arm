/*
 * File: MRAC.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Apr-2020 15:46:37
 */

#ifndef MRAC_H
#define MRAC_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "MRAC_types.h"

/* Function Declarations */
extern void MRAC(double theta_l, double theta_l_dot, double theta_m, double
                 theta_m_dot, double theta_m_d, const double phi_k_1[5], const
                 double theta_r_k_1[2], double b_gamma, double Kv, double N,
                 double T, double *V_control, double phi_k[5], double theta_r[2]);

#endif

/*
 * File trailer for MRAC.h
 *
 * [EOF]
 */
