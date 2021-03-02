/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: log.c
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
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <stdbool.h>
#include "main.h"
#include "log.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
#define LOG_TX_BUFFER_SIZE		100
#define LOG_RX_BUFFER_SIZE		100
#define LOG_RECEIVED_FRAME_LEN	5

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/
UART_HandleTypeDef huart2;
DMA_HandleTypeDef hdma_usart2_tx;
DMA_HandleTypeDef hdma_usart2_rx;
static bool transmitInProgress = false;
static bool receiveDone = false;

static char LogTxBuffer[LOG_TX_BUFFER_SIZE];
static char LogRxBuffer[LOG_RX_BUFFER_SIZE];

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
static inline void MX_USART2_UART_Init(void);
/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief :
 * @param :
 * @return:
 */
void InitLog()
{
	MX_USART2_UART_Init();
	HAL_UART_Receive_DMA(&huart2, (uint8_t *)(LogRxBuffer), LOG_RECEIVED_FRAME_LEN);
}

/**
 * @brief :
 * @param :
 * @return:
 */
void LogPrint(LOG_MESSAGE_TYPE_t messageType, const char *string,...)
{
	while(transmitInProgress);

	uint8_t userStringStartPosition = 0;
	memset((void *) LogTxBuffer, 0, sizeof(LogTxBuffer));

	switch (messageType)
	{
	case LOG_INFO:
		strncpy(LogTxBuffer, "INFO: ", 6);
		userStringStartPosition = 6;
		break;
	case LOG_DEBUG:
		strncpy(LogTxBuffer, "DEBUG: ", 7);
		userStringStartPosition = 7;
		break;
	case LOG_WARNING:
		strncpy(LogTxBuffer, "WARNING: ", 9);
		userStringStartPosition = 9;
		break;
	case LOG_ERROR:
		strncpy(LogTxBuffer, "ERROR: ", 7);
		userStringStartPosition = 7;
		break;
	default:
		break;
	}

	va_list arg;

	va_start(arg, string);
	vsprintf((char *) (LogTxBuffer+userStringStartPosition), string, arg);
	va_end(arg);

	uint16_t len = strlen(LogTxBuffer);
	HAL_UART_Transmit_DMA(&huart2, (uint8_t*)(LogTxBuffer), len);

	transmitInProgress = true;
}

LOG_RECEIVE_PROGRESS_t LogCheckReceiveDone()
{
	if(receiveDone)
	{
		receiveDone = false;
		HAL_UART_Receive_DMA(&huart2, (uint8_t *)(LogRxBuffer), LOG_RECEIVED_FRAME_LEN);
		return LOG_RECEIVE_PROGRESS_DONE;
	}
	else
	{
		return LOG_RECEIVE_PROGRESS_WAITING;
	}
}

void LogGetReceivedData(char *data)
{
	int i = 0;
	for(i=0; i<LOG_RECEIVED_FRAME_LEN; i++)
	{
		*data = LogRxBuffer[i];
		data++;
	}
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static inline void MX_USART2_UART_Init(void)
{
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 115200;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
}

void HAL_UART_TxCpltCallback(UART_HandleTypeDef *huart)
{
	UNUSED(huart);
	transmitInProgress = false;
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	receiveDone = true;
}

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
