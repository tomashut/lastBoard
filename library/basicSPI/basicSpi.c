#include "basicSpi.h"

SPI_ERR basicSpi_ParamsInstall(st_spiPhy* this, st_spiConfig* config)
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	switch(config->spiNum)
	{
		case spi_1:
			this->handlerSpi.Instance = SPI1;
		break;
		case spi_2:
			this->handlerSpi.Instance = SPI2;
		break;
		case spi_3:
			this->handlerSpi.Instance = SPI3;
		break;
		case spi_4:
			this->handlerSpi.Instance = SPI4;
		break;
		case spi_5:
			this->handlerSpi.Instance = SPI5;
		break;
		default :
		break;
	}
	switch(config->mode)
	{
		case slave:
			this->handlerSpi.Init.Mode	= SPI_MODE_SLAVE ;
		break;
		case master:
			this->handlerSpi.Init.Mode	= SPI_MODE_MASTER;
		break;
	}
	switch(config->direction)
	{
		case simplex:
			this->handlerSpi.Init.Direction	= SPI_DIRECTION_1LINE		 ;
		break;
		case halfDuplex:
			this->handlerSpi.Init.Direction	= SPI_DIRECTION_2LINES_RXONLY;
		break;
		case fullDuplex:
			this->handlerSpi.Init.Direction	= SPI_DIRECTION_2LINES		 ;
		break;
	}
	switch(config->firstBit)
	{
		case 0:
			this->handlerSpi.Init.FirstBit	= SPI_FIRSTBIT_MSB;
		break;

		case 1:
			this->handlerSpi.Init.FirstBit	= SPI_FIRSTBIT_LSB;
		break;
	}
	switch(config->baudrate)
	{
		case baudrateprescaler_2:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_2  ;
		break;
		case baudrateprescaler_4:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_4  ;
		break;
		case baudrateprescaler_8:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_8  ;
		break;
		case baudrateprescaler_16:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_16 ;
		break;
		case baudrateprescaler_32:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_32 ;
		break;
		case baudrateprescaler_64:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_64 ;
		break;
		case baudrateprescaler_128:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_128;
		break;
		case baudrateprescaler_256:
			this->handlerSpi.Init.BaudRatePrescaler	= SPI_BAUDRATEPRESCALER_256;
		break;
	}
	this->handlerSpi.Init.DataSize 				= SPI_DATASIZE_8BIT			;
	this->handlerSpi.Init.CLKPolarity 			= config->cpol				;
	this->handlerSpi.Init.CLKPhase 				= config->cpha				;
	this->handlerSpi.Init.NSS 					= SPI_NSS_SOFT				;
	this->handlerSpi.Init.TIMode 				= SPI_TIMODE_DISABLE		;
	this->handlerSpi.Init.CRCCalculation 		= SPI_CRCCALCULATION_DISABLE;
	this->handlerSpi.Init.CRCPolynomial 		= 10						;

	//#elif defined(OTHER)
#else

#endif

	return SPI_ERROR_NONE;

}
SPI_ERR basicSpi_Init(st_spiPhy* this, st_spiConfig* config)
{

	basicSpi_ParamsInstall(this, config);

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

	if(HAL_SPI_Init(&this->handlerSpi) != HAL_OK)
		return SPI_INIT_ERROR;

#else
	//#elif defined(OTHER)
#endif
	return SPI_ERROR_NONE;
}

SPI_ERR basicSpi_transmit(st_spiPhy* this) 
{

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	if (HAL_SPI_Transmit(&this->handlerSpi, this->pTxData, this->sizeTxData, this->timeout)!= HAL_OK)
		return SPI_ERROR;
//#elif defined(OTHER)
#else

#endif

	return SPI_ERROR_NONE;
}

SPI_ERR	basicSpi_receive(st_spiPhy* this)
{

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	if (HAL_SPI_Receive(&this->handlerSpi, this->pRxData, this->sizeRxData, this->timeout)!= HAL_OK)
		return SPI_ERROR;

#else
	//#elif defined(OTHER)
#endif

	return SPI_ERROR_NONE;
}

SPI_ERR basicSpi_transmitReceive(st_spiPhy *this)
{

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	if (HAL_SPI_TransmitReceive(&this->handlerSpi, this->pTxData, this->pRxData,this->sizeData, this->timeout)!= HAL_OK)
	{
		return SPI_ERROR;
	}

#else
	//#elif defined(OTHER)
#endif

	return SPI_ERROR_NONE;
}

SPI_ERR basicSpi_InstallFunctions(st_basicSpi *this)
{
	this->spi_func.init 			 = basicSpi_Init			;
	this->spi_func.transmit 		 = basicSpi_transmit		;
	this->spi_func.receive 			 = basicSpi_receive			;
	this->spi_func.transmitReceive	 = basicSpi_transmitReceive	;
	this->spi_func.pin_init			 = &basicPin_Init			;
	return SPI_ERROR_NONE;
}
