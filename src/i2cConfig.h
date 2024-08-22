/*
 * i2cConfig.h
 *
 *  Created on: May 7, 2024
 *      Author: franR
 */

#ifndef LIBRARY_BASICI2C_I2CCONFIG_H_
#define LIBRARY_BASICI2C_I2CCONFIG_H_

// #include "basicI2C.h"
#include "stdint.h"
#define I2C_MASTER_TIMEOUT_MS      			1000							// Time out maximum to transmit or receive data.
#define I2C_WRITE_BIT						1								// Bits number to shifting slave address and read it.

//Indicates the number of buses available in the system.
enum i2c_PortCount{
	i2c_inSystem_1,
	i2c_inSystem_2,
    i2c_inSystem_3,
    i2c_inSystem_total
};

typedef enum i2c_error_t{
	i2c_error,
	i2c_error_none,
}i2c_errors;

i2c_errors i2c_configInit(int i2c_PortCount);
i2c_errors i2c_writeData(int, uint16_t, uint8_t*, uint8_t);
i2c_errors i2c_readData(int, uint16_t, uint8_t*, uint8_t);


#endif /* LIBRARY_BASICI2C_I2CCONFIG_H_ */
