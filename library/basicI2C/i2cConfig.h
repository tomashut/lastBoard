///*
// * i2cConfig.h
// *
// *  Created on: May 7, 2024
// *      Author: franR
// */
//
//#ifndef LIBRARY_BASICI2C_I2CCONFIG_H_
//#define LIBRARY_BASICI2C_I2CCONFIG_H_
//
//#include "basicI2C.h"
//
//#define I2C_MASTER_TIMEOUT_MS      			1000							// Time out maximum to transmit or receive data.
//#define I2C_WRITE_BIT						1								// Bits number to shifting slave address and read it.
//
////Indicates the number of buses available in the system.
//enum i2c_PortCount{
//	i2c_inSystem_1,
//	i2c_inSystem_2,
//    i2c_inSystem_3,
//    i2c_inSystem_total
//};
//
//// Structure used by a device using I2C bus.
//typedef struct i2c{
//	st_basicI2C *i2c;
//}st_i2c;
//
//I2C_ERR i2c_configInit(st_i2c*);
//
//st_i2c* i2c_configInitPhy(uint32_t);
//st_i2cConfig *i2c_configGetConfig(uint32_t);
//
//I2C_ERR i2c_writeData(st_i2c*, uint16_t, uint8_t*, uint8_t);
//I2C_ERR i2c_readData(st_i2c*, uint16_t, uint8_t*, uint8_t);
//
//
//
//#endif /* LIBRARY_BASICI2C_I2CCONFIG_H_ */




/*
 * i2cConfig.h
 *
 *  Created on: May 7, 2024
 *      Author: franR
 */

#ifndef LIBRARY_BASICI2C_I2CCONFIG_H_
#define LIBRARY_BASICI2C_I2CCONFIG_H_

#include "basicI2C.h"

#define I2C_MASTER_TIMEOUT_MS      			1000							// Time out maximum to transmit or receive data.
#define I2C_WRITE_BIT						1								// Bits number to shifting slave address and read it.

//Indicates the number of buses available in the system.
enum i2c_PortCount{
	i2c_inSystem_1,
	i2c_inSystem_2,
    i2c_inSystem_3,
    i2c_inSystem_total
};

// Structure used by a device using I2C bus.
typedef struct i2c{
	st_basicI2C *i2c;
}st_i2c;

I2C_ERR i2c_configInit(st_i2c*);

st_i2c* i2c_configInitPhy(uint32_t);
st_i2cConfig *i2c_configGetConfig(uint32_t);

I2C_ERR i2c_writeData(st_i2c*, uint8_t*, uint8_t);
I2C_ERR i2c_readData(st_i2c*, uint8_t*, uint8_t);



#endif /* LIBRARY_BASICI2C_I2CCONFIG_H_ */

