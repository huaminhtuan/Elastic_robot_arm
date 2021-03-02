/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: main.h
 * Description	:
 * Tool		    :
 * Chip		    :
 * Version      :
 * History		:
 *
 * Author		: Hua Minh Tuan
 * Notes		:
 *****************************************************************************/

#ifndef _MAIN_H
#define _MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 * INCLUDE
 *****************************************************************************/
#include "stm32f4xx_hal.h"
#include "log.h"

/******************************************************************************
 * PUBLIC DEFINITION
 *****************************************************************************/
#define B1_Pin GPIO_PIN_13
#define B1_GPIO_Port GPIOC
#define B1_EXTI_IRQn EXTI15_10_IRQn
#define USART_TX_Pin GPIO_PIN_2
#define USART_TX_GPIO_Port GPIOA
#define USART_RX_Pin GPIO_PIN_3
#define USART_RX_GPIO_Port GPIOA
#define NSS_Pin GPIO_PIN_12
#define NSS_GPIO_Port GPIOB
#define DIR_Pin GPIO_PIN_9
#define DIR_GPIO_Port GPIOA
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA
#define SWO_Pin GPIO_PIN_3
#define SWO_GPIO_Port GPIOB

/******************************************************************************
 * PUBLIC VARIABLE
 *****************************************************************************/

/******************************************************************************
 * PUBLIC FUNCTION PROTOTYPE
 *****************************************************************************/
void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);
void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif
/******************************************************************************
 * END OF FILE
 *****************************************************************************/
