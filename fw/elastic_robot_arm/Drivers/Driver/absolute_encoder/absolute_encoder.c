/******************************************************************************
 * Elastic actuator controller
 *****************************************************************************/
/******************************************************************************
 * Brief description:
 * Module		: absolute_encoder.c
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
#include "main.h"
#include "absolute_encoder.h"

/******************************************************************************
 * LOCAL DEFINITION
 *****************************************************************************/
typedef enum
{
	ABS_ENC_SEND_STATUS_OK,
	ABS_ENC_SEND_STATUS_FAILED,
} ABS_ENC_SEND_STATUS_t;
/* AMT-20 encoder command, sent from MCU */
#define NOP_A5			0x00
#define RD_POS			0x10
#define SET_ZERO_POS	0x70

/* Encoder configuration */
#define ENC_PULSE_PER_ROUND	4096
#define ENC_RAD_PER_PULSE	0.0015339807878856   // (2*M_PI/ENC_PULSE_PER_ROUND)

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/
#define AbsoluteEncoderNSSPinSet()	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_SET)
#define AbsoluteEncoderNSSPinClear()	HAL_GPIO_WritePin(NSS_GPIO_Port, NSS_Pin, GPIO_PIN_RESET)

SPI_HandleTypeDef hspi2;

static bool receiveDone = false;

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
static inline void MX_SPI2_Init(void);
static ABS_ENC_SEND_STATUS_t AbsoluteEncoderSendCommand(uint8_t sendCommand, uint8_t *receivedData);

/******************************************************************************
 * PUBLIC FUNCTION DEFINITION
 *****************************************************************************/
/**
 * @brief :
 * @param :
 * @return:
 */
void InitAbsoluteEncoder()
{
	MX_SPI2_Init();
}

/**
 * @brief :
 * @param :
 * @return:
 */
ABS_ENC_READ_STATUS_t AbsoluteEncoderReadEncoder(double *position)
{
	ABS_ENC_READ_STATUS_t ret = ABS_ENC_READ_STATUS_OK;
	uint16_t failToleranceTimer = 100;
	uint8_t spiRXBuffer;
	uint16_t receivedData;

	/* Start reading the position by sending the rd_pos command (0x10) */
	AbsoluteEncoderNSSPinSet();
	HAL_Delay(20);
	if(AbsoluteEncoderSendCommand(RD_POS, &spiRXBuffer) != ABS_ENC_SEND_STATUS_OK)
	{
		ret = ABS_ENC_READ_STATUS_FAILED;
		goto stop;
	}

	/* Wait for receiving the original rd_pos command back */
	do {
		if(AbsoluteEncoderSendCommand(NOP_A5, &spiRXBuffer) != ABS_ENC_SEND_STATUS_OK)
		{
			ret = ABS_ENC_READ_STATUS_FAILED;
			goto stop;
		}
		failToleranceTimer--;
		if(failToleranceTimer <= 0)
		{
			ret = ABS_ENC_READ_STATUS_FAILED;
			goto stop;
		}
	} while( spiRXBuffer != RD_POS );

	/* Receive MSB */
	if(AbsoluteEncoderSendCommand(NOP_A5, &spiRXBuffer) != ABS_ENC_SEND_STATUS_OK)
	{
		ret = ABS_ENC_READ_STATUS_FAILED;
		goto stop;
	}

	spiRXBuffer &= 0x0F;
	receivedData = spiRXBuffer << 8;

	/* Receive LSB */
	if(AbsoluteEncoderSendCommand(NOP_A5, &spiRXBuffer) != ABS_ENC_SEND_STATUS_OK)
	{
		ret = ABS_ENC_READ_STATUS_FAILED;
		goto stop;
	}

	receivedData += spiRXBuffer;

	/* Calculate current position and return */
stop:
	if(ret == ABS_ENC_READ_STATUS_OK)
	{
		*position = (double)(receivedData*ENC_RAD_PER_PULSE);
	}

	return ret;
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
static inline void MX_SPI2_Init(void)
{
	/* SPI2 parameter configuration*/
	  hspi2.Instance = SPI2;
	  hspi2.Init.Mode = SPI_MODE_MASTER;
	  hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	  hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	  hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	  hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	  hspi2.Init.NSS = SPI_NSS_SOFT;
	  hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_64;
	  hspi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	  hspi2.Init.TIMode = SPI_TIMODE_DISABLE;
	  hspi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	  hspi2.Init.CRCPolynomial = 10;
	  if (HAL_SPI_Init(&hspi2) != HAL_OK)
	  {
	    Error_Handler();
	  }
}

void HAL_SPI_TxRxCpltCallback(SPI_HandleTypeDef *hspi)
{
	receiveDone = true;
}

static ABS_ENC_SEND_STATUS_t AbsoluteEncoderSendCommand(uint8_t sendCommand, uint8_t *receivedData)
{
	ABS_ENC_SEND_STATUS_t ret = ABS_ENC_SEND_STATUS_OK;
	uint16_t failToleranceTimer = 100;
	uint8_t txDataBuffer = sendCommand;

	receiveDone = false;
	AbsoluteEncoderNSSPinClear(); // Start the communication by pulling CSB pin low

	// Send command out and receive data back
	if(HAL_SPI_TransmitReceive_IT(&hspi2, &txDataBuffer, receivedData, 1) != HAL_OK)
	{
		ret = ABS_ENC_SEND_STATUS_FAILED;
	}
	else
	{
		while(!receiveDone) // Wait for current transmission to be done
		{
			failToleranceTimer--;
			if(failToleranceTimer<=0)
			{
				ret = ABS_ENC_SEND_STATUS_FAILED;
				break;
			}

		}
		receiveDone = false;
	}

	AbsoluteEncoderNSSPinSet(); // Stop the communication by pulling CSB pin high
	HAL_Delay(10);
	return ret;
}

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
