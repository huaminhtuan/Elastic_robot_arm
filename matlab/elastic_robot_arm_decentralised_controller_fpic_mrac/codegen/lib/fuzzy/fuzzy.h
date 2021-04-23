/*
 * File: fuzzy.h
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Feb-2021 15:10:56
 */

#ifndef FUZZY_H
#define FUZZY_H

/* Include Files */
#include <stddef.h>
#include <stdlib.h>
#include "rtwtypes.h"
#include "fuzzy_types.h"

/* Function Declarations */
extern double fuzzy(double e_l_k, double e_l_k_1, double theta_d_k_1, double Kp,
                    double Kd, double Ku, double T, double theta_d_upper_limit,
                    double theta_d_lower_limit);

#endif

/*
 * File trailer for fuzzy.h
 *
 * [EOF]
 */
