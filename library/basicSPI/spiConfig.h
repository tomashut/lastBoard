#ifndef SPICONFIG_H_
#define SPICONFIG_H_

#include "basicSpi.h"

//Indicates the number of buses available in the system.
enum spi_PortCount{
	spi_inSystem_1,
	spi_inSystem_2,
    spi_inSystem_3,
    spi_inSystem_4,
    spi_inSystem_5,
    spi_inSystem_total
};

// Structure used by a device using SPI bus.
typedef struct spi{
	st_basicSpi *spi;
}st_spi;

SPI_ERR spi_configInit(st_spi*);
st_spi* spi_configInitPhy(uint32_t);
st_spiConfig *spi_configGetConfig(uint32_t);
SPI_ERR spi_config_writeData(st_spi*, uint8_t, uint8_t, uint8_t*, uint8_t);
void spi_config_writeRegister8(st_spi*, uint8_t, uint8_t);
SPI_ERR spi_config_readData(st_spi*, uint8_t*, uint8_t, uint8_t*, uint8_t);
uint8_t spi_config_readRegister8(st_spi*, uint8_t);
uint16_t spi_config_readRegister16(st_spi*, uint8_t);
SPI_ERR spi_transmitReceive8 (st_spi*, uint8_t*, uint8_t*);

#endif
