/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: system.c
 * Description	:
 * Tool		    :
 * Chip		    :
 * Version      :
 * History		: 25 Mar, 2020
 *
 * Author		: Hua Minh Tuan
 * Notes		:
 *****************************************************************************/

/******************************************************************************
 * INCLUDE
 *****************************************************************************/
#include <stdbool.h>
#include "main.h"
#include "motor_controller.h"
#include "log.h"
#include "controller.h"
#include "encoder.h"
#include "eeprom.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
#define CONTROLLER_SAMPLING_TIME_MSEC	10 /* Millisecond */
#define CONTROLLER_SAMPLING_TIME_SEC	0.01 /* Second */

#define MAX_MOTOR_CONTROL_VOLTAGE	12 /* Volt */

typedef struct
{
	bool System_Flags_runAlgorithm:1;
	bool System_Flags_storeParamters:1;
}System_Flags_t;

typedef enum
{
	SYSTEM_STATE_INIT,
	SYSTEM_STATE_RUN,
}SYSTEM_STATE_t;

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/
TIM_HandleTypeDef htim2;

System_Flags_t systemFlags = {0};
SYSTEM_STATE_t systemState = SYSTEM_STATE_INIT;

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
static inline void InitSystemTimer();
static inline void InitSystemDMA();
static inline void InitSystemGPIO();
static inline void SystemClockConfig();
static inline void SystemStartTimer();

static inline void MX_DMA_Init();
static inline void MX_TIM2_Init();
static inline void MX_GPIO_Init(void);

/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief : Configure essential peripherals
 * @param :
 * @return:
 */
void InitSystem()
{
	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* Configure the system clock */
	SystemClockConfig();

	/* Configure GPIO */
	InitSystemGPIO();

	/* Configure DMA */
	InitSystemDMA();

	/* Configure logger for outputting data */
	InitLog();
	LogPrint(LOG_INFO, "Configuring!\n");

	/* Configure system timer */
	InitSystemTimer();

	/* Configure the motor controller's essential peripherals */
	InitMotorController();
	MotorSetDirection(MOTOR_DIR_POSITIVE);
	MotorSetDutyCycle(0); // min: 0.16

	/* Configure controller */
	InitController();

	/* Configure encoder */
	InitEncoder();

	/* Configure EEPROM module */
//	InitEEPROM();

	/* Start system timer */
	SystemStartTimer();

	LogPrint(LOG_INFO, "Done, ready to run.....\n");
	systemState = SYSTEM_STATE_RUN;
}

void SystemStateMachineProcessing()
{
	switch (systemState) {
		case SYSTEM_STATE_INIT:
			break;
		case SYSTEM_STATE_RUN:
			if(systemFlags.System_Flags_runAlgorithm)
			{
				/* Clear flag */
				systemFlags.System_Flags_runAlgorithm = false;

				/* Read motor current angle */
				double motorAngle;
				double motorVelocity;
				MotorReadEncoder(&motorAngle, &motorVelocity, CONTROLLER_SAMPLING_TIME_SEC);

				double loadAngle;
				double loadVelocity;
				EncoderReadEncoder(&loadAngle, &loadVelocity, CONTROLLER_SAMPLING_TIME_SEC);
				LogPrint(LOG_DEBUG, "motor: %f\tload: %f\n", motorAngle, loadAngle);

//				static double prevLoadError = 0;
//				double currLoadError;
//				static double prevMotorDesiredAngle = 0;
				double currMotorDesiredAngle;
//				currMotorDesiredAngle = Fuzzy(currLoadError, prevLoadError, prevMotorDesiredAngle);

				currMotorDesiredAngle = 2*3.14;
				double controlVoltage;
				static double prevParameter[5] = {1,1,1,1,1};
				static double prevReferenceModel[2] = {0,0};
				double currParameter[5];
				double currReferenceModel[2];
				MRAC(loadAngle, loadVelocity, motorAngle, motorVelocity, currMotorDesiredAngle, prevParameter, prevReferenceModel,
						&controlVoltage, currParameter, currReferenceModel);

//				/* Saturate output */
//				if(controlVoltage > MAX_MOTOR_CONTROL_VOLTAGE)
//					controlVoltage = MAX_MOTOR_CONTROL_VOLTAGE;
//				else if(controlVoltage < -MAX_MOTOR_CONTROL_VOLTAGE)
//					controlVoltage = -MAX_MOTOR_CONTROL_VOLTAGE;
//
//				/* Set control voltage */
//				if(controlVoltage < 0)
//				{
//					MotorSetDirection(MOTOR_DIR_NEGATIVE);
//				}
//				else
//				{
//					MotorSetDirection(MOTOR_DIR_POSITIVE);
//				}
//				MotorSetDutyCycle((float)(controlVoltage/MAX_MOTOR_CONTROL_VOLTAGE));
			}

			if(systemFlags.System_Flags_storeParamters)
			{
				/* Clear flag */
				systemFlags.System_Flags_storeParamters = false;
			}
			break;
		default:
			break;
	}
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief : System timer configuration
 * @param : None
 * @return: None
 */
static inline void InitSystemTimer()
{
	MX_TIM2_Init();
}

static inline void InitSystemDMA()
{
	MX_DMA_Init();
}

static inline void InitSystemGPIO()
{
	MX_GPIO_Init();
}

/**
 * @brief : System Clock Configuration
 * @param : None
 * @return: None
 */
void SystemClockConfig()
{
	RCC_OscInitTypeDef RCC_OscInitStruct = {0};
	RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

	/** Configure the main internal regulator output voltage
	 */
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLM = 8;
	RCC_OscInitStruct.PLL.PLLN = 180;
	RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
	RCC_OscInitStruct.PLL.PLLQ = 2;
	RCC_OscInitStruct.PLL.PLLR = 2;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
	{
		Error_Handler();
	}
	/** Activate the Over-Drive mode
	 */
	if (HAL_PWREx_EnableOverDrive() != HAL_OK)
	{
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB busses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
			|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
	RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief : Enable DMA controller clock
 * @param : None
 * @return: None
 */
static inline void MX_DMA_Init()
{
	/* DMA controller clock enable */
	__HAL_RCC_DMA1_CLK_ENABLE();

	/* DMA interrupt init */
	/* DMA1_Stream6_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);
	/* DMA1_Stream7_IRQn interrupt configuration */
	HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
}

/**
 * @brief : Start system 1ms timer
 * @param : None
 * @return: None
 */
static inline void SystemStartTimer()
{
	HAL_TIM_Base_Start_IT(&htim2);
}

/**
 * @brief TIM2 Initialization Function
 * @param None
 * @retval None
 */
static inline void MX_TIM2_Init()
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};

	htim2.Instance = TIM2;
	htim2.Init.Prescaler = 9000-1;
	htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim2.Init.Period = 10-1;
	htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
	{
		Error_Handler();
	}
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
	{
		Error_Handler();
	}
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

/**
 * @brief : GPIO Initialization Function
 * @param : None
 * @return: None
 */
static inline void MX_GPIO_Init(void)
{
	  GPIO_InitTypeDef GPIO_InitStruct = {0};

	  /* GPIO Ports Clock Enable */
	  __HAL_RCC_GPIOC_CLK_ENABLE();
	  __HAL_RCC_GPIOH_CLK_ENABLE();
	  __HAL_RCC_GPIOA_CLK_ENABLE();
	  __HAL_RCC_GPIOB_CLK_ENABLE();

	  /*Configure GPIO pin Output Level */
	  HAL_GPIO_WritePin(DIR_GPIO_Port, DIR_Pin, GPIO_PIN_RESET);

	  /*Configure GPIO pin : B1_Pin */
	  GPIO_InitStruct.Pin = B1_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	  /*Configure GPIO pin : DIR_Pin */
	  GPIO_InitStruct.Pin = DIR_Pin;
	  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	  GPIO_InitStruct.Pull = GPIO_NOPULL;
	  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	  HAL_GPIO_Init(DIR_GPIO_Port, &GPIO_InitStruct);
}

/**
  * @brief : Period elapsed callback in non blocking mode
  * @param htim: TIM handle
  * @return: None
  */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	static uint32_t timerCount = 0;
    if (htim->Instance == htim2.Instance)
    {
    	timerCount++;
    	/* 10ms */
    	if(timerCount%CONTROLLER_SAMPLING_TIME_MSEC == 0)
    	{
    		systemFlags.System_Flags_runAlgorithm = true;
    	}

    	/* 60s */
    	if(timerCount >= 60000)
    	{
    		timerCount = 0;
    		systemFlags.System_Flags_storeParamters = true;
    	}
    }
}

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
