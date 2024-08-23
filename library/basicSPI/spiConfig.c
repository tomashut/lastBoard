#include "spiConfig.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
st_spiConfig spi_Config[spi_inSystem_total]={
#if BOARD == DEFROSTER_BOARD
		{
				.spiNum     = spi_1                 ,
				.baudrate   = baudrateprescaler_64  ,   // Frequency = 1MHz
				.mode       = master                ,
				.direction  = fullDuplex            ,   // FULL DUPLEX
				//The MAX31865 supports SPI modes 1 and 3 :		// Used mode     = 1 --->
				.cpol       = SPI_POLARITY_LOW      ,   // CPOL      = 0;
				.cpha       = SPI_PHASE_2EDGE       ,   // CPHA      = 1;
				.firstBit   = SPI_FIRSTBIT_MSB      ,   // Send first to MSB.
				.nss        = SPI_NSS_SOFT          ,   // The microcontroller's SPI driver does not handle the NSS signal automatically. Instead, the user's software is responsible for controlling this signal.
		},
		{
				.spiNum     = spi_1                 ,
				.baudrate   = baudrateprescaler_32  ,   // Frequency = 2MHz
				.mode       = master                ,
				.direction  = fullDuplex            ,   // FULL DUPLEX
				.cpol       = SPI_POLARITY_LOW      ,   // CPOL      = 0;
				.cpha       = SPI_PHASE_2EDGE       ,   // CPHA      = 1;
				.firstBit   = SPI_FIRSTBIT_MSB      ,   // Send first to MSB.
				.nss        = SPI_NSS_SOFT          ,   // The microcontroller's SPI driver does not handle the NSS signal automatically. Instead, the user's software is responsible for controlling this signal.
				.sclkPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin5,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
				.misoPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin6,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
				.mosiPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin7,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
		}
#elif BOARD == FROSTER_BOARD
		{
				.spiNum     = spi_1                 ,
				.baudrate   = baudrateprescaler_64  ,   // Frequency = 1MHz
				.mode       = master                ,
				.direction  = fullDuplex            ,   // FULL DUPLEX
				//The MAX31865 supports SPI modes 1 and 3 :		// Used mode     = 1 --->
				.cpol       = SPI_POLARITY_LOW      ,   // CPOL      = 0;
				.cpha       = SPI_PHASE_2EDGE       ,   // CPHA      = 1;
				.firstBit   = SPI_FIRSTBIT_MSB      ,   // Send first to MSB.
				.nss        = SPI_NSS_SOFT          ,   // The microcontroller's SPI driver does not handle the NSS signal automatically. Instead, the user's software is responsible for controlling this signal.
		},
		{
				.spiNum     = spi_1                 ,
				.baudrate   = baudrateprescaler_32  ,   // Frequency = 2MHz
				.mode       = master                ,
				.direction  = fullDuplex            ,   // FULL DUPLEX
				.cpol       = SPI_POLARITY_LOW      ,   // CPOL      = 0;
				.cpha       = SPI_PHASE_2EDGE       ,   // CPHA      = 1;
				.firstBit   = SPI_FIRSTBIT_MSB      ,   // Send first to MSB.
				.nss        = SPI_NSS_SOFT          ,   // The microcontroller's SPI driver does not handle the NSS signal automatically. Instead, the user's software is responsible for controlling this signal.
				.sclkPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin5,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
				.misoPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin6,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
				.mosiPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin7,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
		}
#elif BOARD == DAQ_BOARD
		{
				.spiNum     = spi_1                 ,
				.baudrate   = baudrateprescaler_64  ,   // Frequency = 1MHz
				.mode       = master                ,
				.direction  = fullDuplex            ,   // FULL DUPLEX
				//The MAX31865 supports SPI modes 1 and 3 :		// Used mode     = 1 --->
				.cpol       = SPI_POLARITY_LOW      ,   // CPOL      = 0;
				.cpha       = SPI_PHASE_2EDGE       ,   // CPHA      = 1;
				.firstBit   = SPI_FIRSTBIT_MSB      ,   // Send first to MSB.
				.nss        = SPI_NSS_SOFT          ,   // The microcontroller's SPI driver does not handle the NSS signal automatically. Instead, the user's software is responsible for controlling this signal.
		},
		{
				.spiNum     = spi_1                 ,
				.baudrate   = baudrateprescaler_64  ,   // Frequency = 1MHz
				.mode       = master                ,
				.direction  = fullDuplex            ,   // FULL DUPLEX
				.cpol       = SPI_POLARITY_LOW      ,   // CPOL      = 0;
				.cpha       = SPI_PHASE_2EDGE       ,   // CPHA      = 1;
				.firstBit   = SPI_FIRSTBIT_MSB      ,   // Send first to MSB.
				.nss        = SPI_NSS_SOFT          ,   // The microcontroller's SPI driver does not handle the NSS signal automatically. Instead, the user's software is responsible for controlling this signal.
				.sclkPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin5,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
				.misoPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin6,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
				.mosiPin	= {
						.enum_GPIO=enum_gpioA,
						.Pin=pin7,
						.Mode=alternate_push_pull,
						.Pull=noPull,
						.Speed=speed_freq_very_high,
						.Alternate=alternate_function_5,
						.logic=positiva
				},
		}
#endif
};
//#elif defined(OTHER)
#else
#endif

st_basicSpi spiOnSystem[spi_inSystem_total];    // An array is created with all the Spi buses available for use.
st_spi spiDev[spi_inSystem_total];				// This array is the devices that connect to the available SPI.

SPI_ERR spi_configInit(st_spi* this)
{
	basicSpi_InstallFunctions(this->spi);
	this->spi->spi_phy.sclkPin.pin_config = &this->spi->spi_config->sclkPin;
	this->spi->spi_phy.misoPin.pin_config = &this->spi->spi_config->misoPin;
	this->spi->spi_phy.mosiPin.pin_config = &this->spi->spi_config->mosiPin;

	this->spi->spi_func.pin_init(&this->spi->spi_phy.sclkPin.pin_phy,this->spi->spi_phy.sclkPin.pin_config);
	this->spi->spi_func.pin_init(&this->spi->spi_phy.misoPin.pin_phy,this->spi->spi_phy.misoPin.pin_config);
	this->spi->spi_func.pin_init(&this->spi->spi_phy.mosiPin.pin_phy,this->spi->spi_phy.mosiPin.pin_config);

	if(this->spi->spi_func.init(&this->spi->spi_phy, this->spi->spi_config)!=SPI_ERROR_NONE)
	{
		return SPI_INIT_ERROR;
	}
	return SPI_ERROR_NONE;
}

// This function assigns the configuration of one of the buses to a device.
st_spi *spi_configInitPhy(uint32_t index)
{
	st_spi *this = &spiDev[index];

	spiOnSystem[index].spi_config = spi_configGetConfig(index);
	this->spi = &spiOnSystem[index];
	return this;
}

st_spiConfig *spi_configGetConfig(uint32_t index)
{
	return &spi_Config[index];
}


SPI_ERR spi_config_writeData(st_spi* this, uint8_t addrReg, uint8_t sizeAddr, uint8_t* writeData, uint8_t sizeData)
{
	// The MSB (A7) of this byte determines whether the following byte is written or read. If A7 is 0, 
	// one or more  byte reads follow the address byte. If A7 is 1, one or more byte writes follow the 
	// address byte.
	addrReg |= 0x80;

	// Send address of register to writing :
	this->spi->spi_phy.pTxData   	= 	&addrReg;
	this->spi->spi_phy.sizeTxData	=	sizeAddr;
	this->spi->spi_phy.timeout		=	100;
	if (this->spi->spi_func.transmit(&this->spi->spi_phy) != SPI_ERROR)
		return SPI_WRITE_ERROR;
	// Data to write in register:
	this->spi->spi_phy.pTxData   	= 	writeData;
	this->spi->spi_phy.sizeTxData	=	sizeData;
	this->spi->spi_phy.timeout		=	100;
	if (this->spi->spi_func.transmit(&this->spi->spi_phy) != SPI_ERROR)
		return SPI_WRITE_ERROR;

	return SPI_ERROR_NONE;
}



SPI_ERR spi_config_readData(st_spi* this, uint8_t* addrReg, uint8_t sizeAddr, uint8_t* readData, uint8_t sizeData)
{
	// The MSB (A7) of this byte determines whether the following byte is written or read. If A7 is 0, 
	// one or more  byte reads follow the address byte. If A7 is 1, one or more byte writes follow the 
	// address byte.
	*addrReg = *(addrReg + sizeAddr - 1) &0x7F	;

	// Send address of register to read :
	this->spi->spi_phy.pTxData   	= 	addrReg;
	this->spi->spi_phy.sizeTxData	=	sizeAddr;
	this->spi->spi_phy.timeout		=	100;
	if (this->spi->spi_func.transmit(&this->spi->spi_phy) != SPI_ERROR)
		return SPI_WRITE_ERROR;

	this->spi->spi_phy.pRxData   	= 	readData;
	this->spi->spi_phy.sizeRxData	=	sizeof(uint8_t);
	this->spi->spi_phy.timeout		=	100;

	// Luego chequear por leer todo el paquete junto en funcion del largo colocado en vez de guardar y leer de a un byte.
	while (sizeData--)
	{
		if (this->spi->spi_func.receive(&this->spi->spi_phy) != SPI_ERROR)
			return SPI_READ_ERROR;
		readData++;
		this->spi->spi_phy.pRxData = readData;
	}

	return SPI_ERROR_NONE;

}

uint8_t spi_config_readRegister8(st_spi* this, uint8_t addr)
{
	uint8_t readData = 0;
	spi_config_readData(this, &addr, 1, &readData, 1);
	return readData;
}

uint16_t spi_config_readRegister16(st_spi* this, uint8_t addr)
{
	uint8_t buffer[2];

	spi_config_readData(this, &addr, 1,buffer, 2);

	uint16_t ret = buffer[0];
	ret <<= 8;
	ret |=  buffer[1];
	return ret;
}

void spi_config_writeRegister8(st_spi* this, uint8_t addr, uint8_t data)
{

	addr |= 0x80;
	this->spi->spi_phy.pTxData   	= 	&addr;
	this->spi->spi_phy.sizeTxData	=	sizeof(uint8_t);
	this->spi->spi_phy.timeout		=	100;
	this->spi->spi_func.transmit(&this->spi->spi_phy);

	this->spi->spi_phy.pTxData   	= 	&data;
	this->spi->spi_phy.sizeTxData	=	sizeof(uint8_t);
	this->spi->spi_phy.timeout		=	100;
	this->spi->spi_func.transmit(&this->spi->spi_phy);

}

SPI_ERR spi_transmitReceive8 (st_spi* this, uint8_t* TxData, uint8_t* RxData)
{
	this->spi->spi_phy.pTxData   	= 	TxData;
	this->spi->spi_phy.pRxData   	= 	RxData;
	this->spi->spi_phy.sizeData		=	sizeof(uint8_t);
	this->spi->spi_phy.timeout		=	1000;
	if (this->spi->spi_func.transmitReceive(&this->spi->spi_phy) != SPI_ERROR_NONE)
	{
		return SPI_WRITE_AND_READ_ERROR;
	}
	return SPI_ERROR_NONE;
}
