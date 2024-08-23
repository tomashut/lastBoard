#ifndef BASICSPI_H_
#define BASICSPI_H_

#include "hardwareConfig.h"
#include "typdef_basicLib.h"
#include "basicPin.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "stm32f4xx_hal_spi.h"
//#elif defined(OTHER)
#else

#endif

//Definition of SPI Error. Used for all architectures :
typedef enum SPI_ERR_T
{
	SPI_ERROR_NONE=0,
	SPI_INIT_ERROR,
	SPI_ERROR,
	SPI_BUSY,
	SPI_WRITE_ERROR,
	SPI_READ_ERROR,
	SPI_WRITE_AND_READ_ERROR

}SPI_ERR;

/****************************************************************************/
/****************************************************************************/
/* SPI PHYSICAL STRUCTURE */
typedef struct spi_phy
{
	#if ARCHITECTURE == ESP32_BOARD
	#elif ARCHITECTURE == KINTEIS
	#elif ARCHITECTURE == STM32F4xx
		SPI_HandleTypeDef 	handlerSpi  ;      	// Pointer to SPI controller.
		uint8_t 			*pTxData	;		// pTxData pointer to transmission data buffer.
		uint16_t 			sizeTxData	;		// Size amount of data to be sent
		uint8_t 			*pRxData	;		// pRxData pointer to reception data buffer.
		int16_t 			sizeData	;		// Size amount of data to be sent and received.
		uint16_t 			sizeRxData	;		// Size amount of data to be received
		uint32_t 			timeout		;		// timeout Timeout duration.

		st_pin				sclkPin		;
		st_pin				misoPin		;
		st_pin				mosiPin		;

	//#elif defined(OTHER)
	#else


	#endif
}st_spiPhy;

/****************************************************************************/
/****************************************************************************/
/* BASIC CONFIGURATION STRUCTURE */
typedef struct spi_config
{

	#if ARCHITECTURE == ESP32_BOARD
	#elif ARCHITECTURE == KINTEIS
	#elif ARCHITECTURE == STM32F4xx
		enum_spi				spiNum	 ;		// Selection of the SPI to use.
		enum_prescaler 			baudrate ;     	// Baud rate in bps. The peripheral clock frequency (PCLK) designated as APB1 or APB2 in STM32 by the prescaler is used to determine the spi clock frequency.
    	enum_mode 				mode	 ;     	// SPI mode (SPI_MODE_MASTER, SPI_MODE_SLAVE).
		enum_typeCommunication	direction;    	// Transfer direction (SPI_DIRECTION_1LINE, SPI_DIRECTION_2LINES).
    	uint32_t 				cpol	 ;   	// Clock Polarity  (SPI_POLARITY_LOW, SPI_POLARITY_HIGH).
    	uint32_t 				cpha	 ;     	// Clock Phase  (SPI_PHASE_1EDGE, SPI_PHASE_2EDGE).
    	uint32_t 				firstBit ;		// Specifies whether data transfers start from MSB or LSB bit, 1 and 0 respectively.
    	uint32_t 				nss		 ;    	// NSS (SPI_NSS_SOFT, SPI_NSS_HARD_INPUT, SPI_NSS_HARD_OUTPUT).

    	st_pin_config			sclkPin	 ;
    	st_pin_config			misoPin	 ;
    	st_pin_config			mosiPin	 ;
    //#elif defined(OTHER)
    #else

	#endif
}st_spiConfig;

/****************************************************************************/
/****************************************************************************/
/* SPI FUNCTION STRUCTURE */
typedef struct spi_functions
{
	SPI_ERR (*init)				(st_spiPhy*, st_spiConfig*);
	SPI_ERR (*receive)			(st_spiPhy*);
	SPI_ERR (*transmit)			(st_spiPhy*);
	SPI_ERR (*transmitReceive)	(st_spiPhy*);
	state	(*pin_init)			(st_pin_phy *, st_pin_config *); 	//funcion de inicializacion

}st_spiFunctions;

/****************************************************************************/
/****************************************************************************/
/* SPI STRUCTURE */
typedef struct basicSPI
{
	st_spiConfig* 	spi_config;		//Pointer to a basic configuration.
	st_spiPhy 		spi_phy;		//Physical structure of the SPI bus.
	st_spiFunctions spi_func;		//Function structure for the SPI bus.
}st_basicSpi;
/****************************************************************************/
/****************************************************************************/

// Fuctions used for all architectures :

SPI_ERR basicSpi_InstallFunctions(st_basicSpi *);

#endif  /*BASICSPI_H_ */
