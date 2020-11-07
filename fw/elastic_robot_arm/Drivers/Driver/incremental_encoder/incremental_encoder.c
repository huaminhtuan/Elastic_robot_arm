/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: incremental_encoder.c
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
#include <math.h>
#include "main.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
#define prevPulse			32767
#define ENC_PULSE_PER_ROUND	4096
#define ENC_RAD_PER_PULSE	0.0015339807878856   // (2*M_PI/ENC_PULSE_PER_ROUND)

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/
static TIM_HandleTypeDef htim4;
static double motorPosition = 0;

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
static inline void MX_TIM4_Init(void);

/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief :
 * @param :
 * @return:
 */
void InitIncrementalEncoder()
{
	MX_TIM4_Init();
	HAL_TIM_Encoder_Start(&htim4, TIM_CHANNEL_ALL);
}

/**
 * @brief : Calculate current position and velocity
 * @param position    : Current position (unit: radian)
 * @param velocity    : Current velocity (unit: radian/second)
 * @param samplingTime: Sampling time (unit: second)
 * @return: None
 */
void IncrementalEncoderReadEncoder(double *position, double *velocity, double samplingTime)
{
	uint16_t currPulse;
	double encoderIncrement;

	currPulse = TIM4->CNT;
	encoderIncrement = (double)((currPulse - prevPulse)*ENC_RAD_PER_PULSE);

	motorPosition += encoderIncrement;
	*position = motorPosition;
	*velocity = encoderIncrement/samplingTime;

	/* Reset counter */
	TIM4->CNT = 32767;
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief TIM4 Initialization Function
 * @param None
 * @retval None
 */
static inline void MX_TIM4_Init(void)
{
	TIM_Encoder_InitTypeDef sConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim4.Instance = TIM4;
	htim4.Init.Prescaler = 0;
	htim4.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim4.Init.Period = 65535;
	htim4.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim4.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim4, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim4, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/* Reset Counter */
	TIM4->CNT = 32767;
}

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
