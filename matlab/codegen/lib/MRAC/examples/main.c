/*
 * File: main.c
 *
 * MATLAB Coder version            : 4.1
 * C/C++ source code generated on  : 14-Apr-2020 15:46:37
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/
/* Include Files */
#include "MRAC.h"
#include "main.h"
#include "MRAC_terminate.h"
#include "MRAC_initialize.h"

/* Function Declarations */
static void argInit_2x1_real_T(double result[2]);
static void argInit_5x1_real_T(double result[5]);
static double argInit_real_T(void);
static void main_MRAC(void);

/* Function Definitions */

/*
 * Arguments    : double result[2]
 * Return Type  : void
 */
static void argInit_2x1_real_T(double result[2])
{
  double result_tmp;

  /* Loop over the array to initialize each element. */
  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result_tmp = argInit_real_T();
  result[0] = result_tmp;

  /* Set the value of the array element.
     Change this value to the value that the application requires. */
  result[1] = result_tmp;
}

/*
 * Arguments    : double result[5]
 * Return Type  : void
 */
static void argInit_5x1_real_T(double result[5])
{
  int idx0;

  /* Loop over the array to initialize each element. */
  for (idx0 = 0; idx0 < 5; idx0++) {
    /* Set the value of the array element.
       Change this value to the value that the application requires. */
    result[idx0] = argInit_real_T();
  }
}

/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
static void main_MRAC(void)
{
  double theta_l_tmp;
  double dv0[5];
  double dv1[2];
  double V_control;
  double phi_k[5];
  double theta_r[2];

  /* Initialize function 'MRAC' input arguments. */
  theta_l_tmp = argInit_real_T();

  /* Initialize function input argument 'phi_k_1'. */
  /* Initialize function input argument 'theta_r_k_1'. */
  /* Call the entry-point 'MRAC'. */
  argInit_5x1_real_T(dv0);
  argInit_2x1_real_T(dv1);
  MRAC(theta_l_tmp, theta_l_tmp, argInit_real_T(), argInit_real_T(),
       argInit_real_T(), dv0, dv1, argInit_real_T(), argInit_real_T(),
       argInit_real_T(), argInit_real_T(), &V_control, phi_k, theta_r);
}

/*
 * Arguments    : int argc
 *                const char * const argv[]
 * Return Type  : int
 */
int main(int argc, const char * const argv[])
{
  (void)argc;
  (void)argv;

  /* Initialize the application.
     You do not need to do this more than one time. */
  MRAC_initialize();

  /* Invoke the entry-point functions.
     You can call entry-point functions multiple times. */
  main_MRAC();

  /* Terminate the application.
     You do not need to do this more than one time. */
  MRAC_terminate();
  return 0;
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
