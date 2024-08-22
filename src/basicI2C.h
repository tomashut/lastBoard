/*
 * basicI2C.h
 *
 *  Created on: May 7, 2024
 *      Author: franR
 */

#ifndef LIBRARY_BASICI2C_BASICI2C_H_
#define LIBRARY_BASICI2C_BASICI2C_H_

#include "hardwareConfig.h"
#include "typdef_basicLib.h"
#include "basicPin.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "stm32f4xx_hal_i2c.h"
//#elif defined(OTHER)
#else

#endif

//Definition of I2C Error. Used for all architectures :
typedef enum I2C_ERR_T
{
	I2C_ERROR_NONE=0,
	I2C_INIT_ERROR,
	I2C_ERROR,
	I2C_BUSY,
	I2C_WRITE_ERROR,
	I2C_READ_ERROR,
	I2C_WRITE_AND_READ_ERROR

}I2C_ERR;

/****************************************************************************/
/****************************************************************************/
/* I2C PHYSICAL STRUCTURE */
typedef struct i2c_phy
{
	#if ARCHITECTURE == ESP32_BOARD
	#elif ARCHITECTURE == KINTEIS
	#elif ARCHITECTURE == STM32F4xx
		I2C_HandleTypeDef 	handlerI2C  ;      	// Pointer to I2C controller.
		uint8_t 			*pData		;		// pTxData pointer to transmission data buffer.
		uint16_t 			dataSize	;		// Size amount of data to be sent/received
		uint32_t 			timeout		;		// timeout Timeout duration.
		uint16_t 			DevAddress	;
		uint16_t 			MemAddress	;

		st_pin				sclk_Pin	;
		st_pin				sda_Pin		;
	//#elif defined(OTHER)
	#else


	#endif
}st_i2cPhy;

/****************************************************************************/
/****************************************************************************/
/* BASIC CONFIGURATION STRUCTURE */
typedef struct i2c_config
{

	#if ARCHITECTURE == ESP32_BOARD
	#elif ARCHITECTURE == KINTEIS
	#elif ARCHITECTURE == STM32F4xx
		enum_i2c					i2cNum			;		// Selection of the I2C to use.
		uint32_t					ClockSpeed		;
		enum_i2c_dutyCycle			DutyCycle		;
		uint32_t					OwnAddress1		;
		enum_AddressingMode			AddressingMode	;
		DualAddressingMode			DualAddressMode	;
		uint32_t					OwnAddress2		;
		GeneralCallAddressingMode	GeneralCallMode	;
		NostretchModeMode			NoStretchMode	;
		uint32_t					timeout			;

    	st_pin_config				sclk_PinConfig	;
    	st_pin_config				sda_PinConfig	;
    //#elif defined(OTHER)
    #else

	#endif
}st_i2cConfig;

/****************************************************************************/
/****************************************************************************/
/* I2C FUNCTION STRUCTURE */
typedef struct i2c_functions
{
	I2C_ERR (*init)		(st_i2cPhy*, st_i2cConfig*);
	I2C_ERR (*receive)	(st_i2cPhy*);
	I2C_ERR (*transmit)	(st_i2cPhy*);
	state	(*pin_init)	(st_pin_phy *, st_pin_config *); 	//funcion de inicializacion

}st_i2cFunctions;

/****************************************************************************/
/****************************************************************************/
/* I2C STRUCTURE */
typedef struct basicI2C
{
	st_i2cConfig* 	i2c_config;		//Pointer to a basic configuration.
	st_i2cPhy 		i2c_phy;		//Physical structure of the I2C bus.
	st_i2cFunctions i2c_func;		//Function structure for the I2C bus.
}st_basicI2C;
/****************************************************************************/
/****************************************************************************/

// Fuctions used for all architectures :

I2C_ERR basicI2C_InstallFunctions(st_basicI2C *);

#endif /* LIBRARY_BASICI2C_BASICI2C_H_ */
