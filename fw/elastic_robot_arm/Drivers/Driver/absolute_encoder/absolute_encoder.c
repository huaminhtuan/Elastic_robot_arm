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
/*
 * AMT-20 encoder command, sent from MCU
 */
#define NOP_A5			0x00
#define RD_POS			0x10
#define SET_ZERO_POS	0x70

/******************************************************************************
 * LOCAL VARIABLE DECLARATION
 *****************************************************************************/
static SPI_HandleTypeDef hspi2;
DMA_HandleTypeDef hdma_spi2_rx;
DMA_HandleTypeDef hdma_spi2_tx;

static uint8_t spiTXBuffer;
static uint8_t spiRXBuffer;

static READ_CURRENT_POS_SEQUENCE readState = RD_POS_READY_FOR_READING;
static uint16_t receiveDataBuffer;

/******************************************************************************
 * LOCAL FUNCTION PROTOTYPE
 *****************************************************************************/
static void AbsoluteEncoderReadSequence();
static inline void MX_SPI2_Init(void);

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
bool AbsoluteEncoderTriggerReadEncoder()
{
	if(readState == RD_POS_READY_FOR_READING)
	{
		AbsoluteEncoderReadSequence();
		return true;
	}

	return false;
}

/**
 * @brief :
 * @param :
 * @return:
 */
bool AbsoluteEncoderReadDataBuffer(uint16_t *buf)
{
	if(readState == RD_POS_DATA_BUFFER_READY)
	{
		*buf = receiveDataBuffer;
		readState = RD_POS_READY_FOR_READING;
		return true;
	}
	return false;
}

/**
 * @brief :
 * @param :
 * @return:
 */
READ_CURRENT_POS_SEQUENCE AbsoluteEncoderGetReadStatus()
{
	return readState;
}

/******************************************************************************
 * LOCAL FUNCTION DEFINITION
 *****************************************************************************/
static void AbsoluteEncoderReadSequence()
{
	switch (readState)
	{
		case RD_POS_READY_FOR_READING:
		case RD_POS_SEND_READ_COMMAND:
			spiTXBuffer = RD_POS;
			HAL_SPI_TransmitReceive_DMA(&hspi2, &spiTXBuffer, &spiRXBuffer, 1);
			readState = RD_POS_WAIT_FOR_RESPONSE;
			break;
		case RD_POS_WAIT_FOR_RESPONSE:
			if(spiRXBuffer == RD_POS)
				readState = RD_POS_RECEIVE_MSB;
			receiveDataBuffer = 0x00;
			spiTXBuffer = NOP_A5;
			HAL_SPI_TransmitReceive_DMA(&hspi2, &spiTXBuffer, &spiRXBuffer, 1);
			break;
		case RD_POS_RECEIVE_MSB:
			spiTXBuffer = NOP_A5;
			HAL_SPI_TransmitReceive_DMA(&hspi2, &spiTXBuffer, &spiRXBuffer, 1);
			receiveDataBuffer = spiRXBuffer << 8;
			readState = RD_POS_RECEIVE_LSB;
			break;
		case RD_POS_RECEIVE_LSB:
			receiveDataBuffer |= spiRXBuffer;
			readState = RD_POS_DATA_BUFFER_READY;
			break;
		default:
			break;
	}
}

static inline void MX_SPI2_Init(void)
{
	/* SPI2 parameter configuration*/
	hspi2.Instance = SPI2;
	hspi2.Init.Mode = SPI_MODE_MASTER;
	hspi2.Init.Direction = SPI_DIRECTION_2LINES;
	hspi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi2.Init.NSS = SPI_NSS_HARD_OUTPUT;
	hspi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_32;
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
	AbsoluteEncoderReadSequence();
}

/******************************************************************************
 * END OF FILE
 *****************************************************************************/
