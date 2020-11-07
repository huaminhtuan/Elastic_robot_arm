/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: Fuzzy.c
 * Description	:
 * Tool		    : MATLAB Coder version: 4.1
 * Chip		    :
 * Version      :
 * History		: C/C++ source code generated on: 14-Apr-2020 16:27:39
 *
 * Author		: Hua Minh Tuan
 * Notes		:
 *****************************************************************************/

/******************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <math.h>
#include <stdbool.h>
#include "Fuzzy.h"
#include "rt_nonfinite.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
#define Kp						1
#define Kd						1
#define Ku						1
#define T						0.01
#define theta_m_d_upper_limit	M_PI
#define theta_m_d_lower_limit	-M_PI

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
double trapmf(double x, const double params[4]);
double trimf(double x, const double params[3]);

/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief :
 * @param :
 * @return:
 */
double Fuzzy(double e_l_k, double e_l_k_1, double theta_m_d_k_1)
{
	double theta_m_d;
	double e;
	double de;
	int idx;
	double fuzzy_e[5];
	double fuzzy_de[5];
	static const double dv0[4] = { -2.8, -1.2, -0.4, -0.2 };

	double dv1[3];
	static const double dv2[4] = { -2.8, -1.2, -0.3, -0.1 };

	static const double dv3[3] = { -0.3, -0.1, 0.0 };

	static const double dv4[3] = { 0.0, 0.1, 0.3 };

	static const double dv5[4] = { 0.1, 0.3, 1.2, 2.8 };

	static const double dv6[4] = { 0.2, 0.4, 1.2, 2.8 };

	int j;
	double varargin_1[6];
	double rules[25];
	bool exitg1;
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
	/* %%%%%%%% Local variable %%%%%%%%% */
	/*      Kp = 1; */
	/*      Kd = 1; */
	/*      Ku = 1; */
	/*      T = 0.001; */
	/*      theta_m_d_upper_limit = pi; */
	/*      theta_m_d_lower_limit = -pi; */
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
		dv1[0] = -0.4;
		dv1[1] = -0.2;
		dv1[2] = 0.0;
		fuzzy_e[1] = trimf(e, dv1);

		/*  NS */
		dv1[0] = -0.2;
		dv1[1] = 0.0;
		dv1[2] = 0.2;
		fuzzy_e[2] = trimf(e, dv1);

		/*  ZE */
		dv1[0] = 0.0;
		dv1[1] = 0.2;
		dv1[2] = 0.4;
		fuzzy_e[3] = trimf(e, dv1);

		/*  PS */
		fuzzy_e[4] = trapmf(e, dv6);

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
		fuzzy_de[1] = trimf(de, dv3);

		/*  NS */
		dv1[0] = -0.1;
		dv1[1] = 0.0;
		dv1[2] = 0.1;
		fuzzy_de[2] = trimf(de, dv1);

		/*  ZE */
		fuzzy_de[3] = trimf(de, dv4);

		/*  PS */
		fuzzy_de[4] = trapmf(de, dv5);

		/*  PB */
	}

	/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	/* %%%%%%%% Fuzzy Inference Rules %%%%%%%%% */
	/* %% */
	/*  ------------------------------ */
	/*  | \e|    |    |    |    |    | */
	/*  |de\| NB | NS | ZE | PS | PB | */
	/*  |----------------------------- */
	/*  |	NB| PB | PB | PB | PS | ZE | */
	/*  |----------------------------- */
	/*  | NS| PB | PB | PS | ZE | NS | */
	/*  |----------------------------- */
	/*  | ZE| PB | PS | ZE | NS | NB | */
	/*  |----------------------------- */
	/*  | PS| PS | ZE | NS | NB | NB | */
	/*  |----------------------------- */
	/*  | PB| ZE | NS | NB | NB | NB | */
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
	theta_m_d = (((((de + u_PS * 0.3) + u_ZE * 0.0) + u_NS * -0.3) + -u_NB) /
			((((de + u_PS) + u_ZE) + u_NS) + u_NB) * T + theta_m_d_k_1) * Ku;

	/*  Saturation */
//	if (theta_m_d > theta_m_d_upper_limit) {
//		theta_m_d = theta_m_d_upper_limit;
//	} else {
//		if (theta_m_d < theta_m_d_lower_limit) {
//			theta_m_d = theta_m_d_lower_limit;
//		}
//	}

	/* %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% */
	return theta_m_d;
}
/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief :
 * @param :
 * @return:
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

/**
 * @brief :
 * @param :
 * @return:
 */
double trimf(double x, const double params[3])
{
	double y;
	y = 0.0;
	if ((params[0] != params[1]) && (params[0] < x) && (x < params[1])) {
		y = (x - params[0]) * (1.0 / (params[1] - params[0]));
	}

	if ((params[1] != params[2]) && (params[1] < x) && (x < params[2])) {
		y = (params[2] - x) * (1.0 / (params[2] - params[1]));
	}

	if (x == params[1]) {
		y = 1.0;
	}

	return y;
}

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
