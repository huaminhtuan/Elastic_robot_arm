/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: motor_controller.c
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
#include "motor_controller.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
#define TIM_PWM_CCR_COUNTER 400
#define TIM_PWM_PRESCALER	18

#define prevPulse			32767
#define ENC_PULSE_PER_ROUND	44
#define ENC_RAD_PER_PULSE	0.1427996660722633 // (2*M_PI/ENC_PULSE_PER_ROUND)
#define MOTOR_GEAR_REDUCTION_RATIO 217

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/
static TIM_HandleTypeDef htim1;
static TIM_HandleTypeDef htim3;
static int64_t motorPosition = 0;

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
static inline void MX_TIM1_Init(void);
static inline void MX_TIM3_Init(void);

/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief : Configure motor controller's essential peripherals:
 * 			- PWM for H-bridge controlling
 * 			- ENC for encoder reading
 * @param : None
 * @return: None
 */
void InitMotorController()
{
	/* Configure PWM for H-bridge controlling */
	MX_TIM1_Init();
	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	/* Configure ENC for encoder reading */
	MX_TIM3_Init();
	HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
}

void MotorSetDutyCycle(float dutyCycle)
{
	if(dutyCycle > 1)
		dutyCycle = 1;
	else if (dutyCycle < 0)
		dutyCycle = 0;

	uint16_t counterValue = 0;
	counterValue = (uint16_t)(dutyCycle*TIM_PWM_CCR_COUNTER-1);
	TIM1->CCR1 = counterValue;

//	TIM_OC_InitTypeDef sConfigOC;
//	sConfigOC.OCMode = TIM_OCMODE_PWM1;
//	sConfigOC.Pulse = counterValue;
//	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
//	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
//	HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1);
//	HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
}

/**
 * @brief : Calculate current position and velocity
 * @param position    : Current position (unit: radian)
 * @param velocity    : Current velocity (unit: radian/second)
 * @param samplingTime: Sampling time (unit: second)
 * @return: None
 */
void MotorReadEncoder(double *position, double *velocity, double samplingTime)
{
	int64_t currPulse;
	int64_t encoderIncrement;

	currPulse = TIM3->CNT;
	encoderIncrement = (int64_t)(currPulse - prevPulse);

	motorPosition += (encoderIncrement);
	*position = (double)(motorPosition*ENC_RAD_PER_PULSE/MOTOR_GEAR_REDUCTION_RATIO);
	*velocity = (double)((encoderIncrement*ENC_RAD_PER_PULSE/MOTOR_GEAR_REDUCTION_RATIO)/samplingTime);

	/* Reset counter */
	TIM3->CNT = prevPulse;
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief : TIM1 Initialization Function
 * @param : None
 * @return: None
 */
static inline void MX_TIM1_Init(void)
{
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	TIM_OC_InitTypeDef sConfigOC = {0};
	TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = TIM_PWM_PRESCALER-1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = TIM_PWM_CCR_COUNTER-1;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.RepetitionCounter = 0;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = TIM_PWM_CCR_COUNTER*0.5-1;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
	{
		Error_Handler();
	}
	sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
	sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
	sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
	sBreakDeadTimeConfig.DeadTime = 0;
	sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
	sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
	sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
	if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
	{
		Error_Handler();
	}
	HAL_TIM_MspPostInit(&htim1);

}

/**
 * @brief : TIM3 Initialization Function
 * @param : None
 * @return: None
 */
static inline void MX_TIM3_Init(void)
{
	TIM_Encoder_InitTypeDef sConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim3.Instance = TIM3;
	htim3.Init.Prescaler = 0;
	htim3.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim3.Init.Period = 65535;
	htim3.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim3.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	sConfig.EncoderMode = TIM_ENCODERMODE_TI12;
	sConfig.IC1Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC1Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC1Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC1Filter = 0;
	sConfig.IC2Polarity = TIM_ICPOLARITY_RISING;
	sConfig.IC2Selection = TIM_ICSELECTION_DIRECTTI;
	sConfig.IC2Prescaler = TIM_ICPSC_DIV1;
	sConfig.IC2Filter = 0;
	if (HAL_TIM_Encoder_Init(&htim3, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim3, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}

	/* Reset Counter */
	TIM3->CNT = 32767;
}


/******************************************************************************
 * END OF FILE
 *****************************************************************************/
