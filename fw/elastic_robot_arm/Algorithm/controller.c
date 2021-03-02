/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: controller.c
 * Description	:
 * Tool		    :
 * Chip		    :
 * Version      :
 * History		:
 *
 * Author		: Hua Minh Tuan
 * Notes		:
 *****************************************************************************/

/******************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <stdint.h>
#include "main.h"
#include "motor_controller.h"
#include "log.h"
#include "controller.h"
#include "incremental_encoder.h"
#include "absolute_encoder.h"

#include "MRAC.h"
#include "Fuzzy.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
#define MAX_MOTOR_CONTROL_VOLTAGE		12 /* Volt */
#define LOW_PASS_FILTER_TIME_CONSTANT	0.5
#define CONTROLLER_MAX_DEVIATION		0.523599 /* Radian. approximate 30 degrees */

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/


/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief :
 * @param :
 * @return:
 */
void InitController()
{
}

/**
 * @brief :
 * @param :
 * @return:
 */
void ControllerRun(double loadDesiredAngle)
{
	/* Local variables */
	double controlVoltage = 0;

	/* Read motor current angle */
	double motorAngle;
	double motorVelocity;
	MotorReadEncoder(&motorAngle, &motorVelocity, CONTROLLER_SAMPLING_TIME_SEC);

	/* Read load current angle */
	double loadAngle;
	double loadVelocity;
	IncrementalEncoderReadEncoder(&loadAngle, &loadVelocity, CONTROLLER_SAMPLING_TIME_SEC);

	/* Calculate the deviation between motor and load angles. If the absolute value of the deviation is
	 * larger than a specific value, it means that there is collision. Then stop the controller */
	double angleDeviation = loadAngle - motorAngle/4;
	if ((angleDeviation>CONTROLLER_MAX_DEVIATION) || (angleDeviation<-CONTROLLER_MAX_DEVIATION))
	{
		MotorSetDirection(MOTOR_DIR_POSITIVE);
		MotorSetDutyCycle(0);
		goto print;
	}

	/* Low-pass filter */
//	double loadDesiredAngleAfterFiltered;
//	static double prevLoadDesiredAngleAfterFiltered = 0;
//	loadDesiredAngleAfterFiltered = (CONTROLLER_SAMPLING_TIME_SEC*loadDesiredAngle+LOW_PASS_FILTER_TIME_CONSTANT*prevLoadDesiredAngleAfterFiltered)/
//			(CONTROLLER_SAMPLING_TIME_SEC+LOW_PASS_FILTER_TIME_CONSTANT);
//	prevLoadDesiredAngleAfterFiltered = loadDesiredAngleAfterFiltered;

	/* Fuzzy PI controller */
	double currMotorDesiredAngle;
	static double prevMotorDesiredAngle = 0;
//	double currLoadError = loadDesiredAngleAfterFiltered - loadAngle;
	double currLoadError = loadDesiredAngle - loadAngle;
	static double prevLoadError = 0;
	currMotorDesiredAngle = Fuzzy(currLoadError, prevLoadError, prevMotorDesiredAngle);
	prevLoadError = currLoadError;
	prevMotorDesiredAngle = currMotorDesiredAngle;

	/* Model reference adaptive controller */
	static double prevParameter[5] = {2.760782, 1.057416, 2.764187, 1.221422, 0.998208};
	static double prevReferenceModel[2] = {0,0};
	double currParameter[5];
	double currReferenceModel[2];
	MRAC(loadAngle, loadVelocity, motorAngle, motorVelocity, currMotorDesiredAngle, prevParameter, prevReferenceModel,
			&controlVoltage, currParameter, currReferenceModel);
	prevParameter[0] = currParameter[0];
	prevParameter[1] = currParameter[1];
	prevParameter[2] = currParameter[2];
	prevParameter[3] = currParameter[3];
	prevParameter[4] = currParameter[4];
	prevReferenceModel[0] = currReferenceModel[0];
	prevReferenceModel[1] = currReferenceModel[1];

	/* Saturate output */
	if(controlVoltage > MAX_MOTOR_CONTROL_VOLTAGE)
		controlVoltage = MAX_MOTOR_CONTROL_VOLTAGE;
	else if(controlVoltage < -MAX_MOTOR_CONTROL_VOLTAGE)
		controlVoltage = -MAX_MOTOR_CONTROL_VOLTAGE;

	static uint32_t timeStamp = 0;

	/* Set control voltage */
	if(controlVoltage < 0)
	{
		MotorSetDirection(MOTOR_DIR_NEGATIVE);
		controlVoltage = -controlVoltage;
	}
	else
	{
		MotorSetDirection(MOTOR_DIR_POSITIVE);
	}
	float dutyCycle = (float)(controlVoltage/MAX_MOTOR_CONTROL_VOLTAGE);
	MotorSetDutyCycle(dutyCycle);

print:
	LogPrint(LOG_DEBUG, "%d\t%f\t%f\t%f\t%f\n", timeStamp, loadAngle, motorAngle, controlVoltage, currMotorDesiredAngle);
	timeStamp++;
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
