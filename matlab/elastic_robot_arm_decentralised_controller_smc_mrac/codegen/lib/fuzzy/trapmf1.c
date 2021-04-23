/*
 * File: trapmf1.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 15-Feb-2021 15:10:56
 */

/* Include Files */
#include "rt_nonfinite.h"
#include "fuzzy.h"
#include "trapmf1.h"

/* Function Definitions */

/*
 * Arguments    : double x
 *                const double params[4]
 * Return Type  : double
 */
double trapmf(double x, const double params[4])
{
  double y;
  double u0;
  double u1;
  u0 = 0.0;
  u1 = 0.0;
  if (x >= params[1]) {
    u0 = 1.0;
  }

  if (x < params[0]) {
    u0 = 0.0;
  }

  if ((params[0] <= x) && (x < params[1]) && (params[0] != params[1])) {
    u0 = (x - params[0]) * (1.0 / (params[1] - params[0]));
  }

  if (x <= params[2]) {
    u1 = 1.0;
  }

  if (x > params[3]) {
    u1 = 0.0;
  }

  if ((params[2] < x) && (x <= params[3]) && (params[2] != params[3])) {
    u1 = (params[3] - x) * (1.0 / (params[3] - params[2]));
  }

  if ((u0 < u1) || rtIsNaN(u1)) {
    y = u0;
  } else {
    y = u1;
  }

  return y;
}

/*
 * File trailer for trapmf1.c
 *
 * [EOF]
 */
