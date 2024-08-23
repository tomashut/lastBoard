///*
// * pressure_sensor.h
// *
// *  Created on: May 8, 2024
// *      Author: Usuario
// */
//#ifndef LIBRARY_PRESSURE_SENSOR_PRESSURE_SENSOR_H_
//#define LIBRARY_PRESSURE_SENSOR_PRESSURE_SENSOR_H_
//
//#include "i2cConfig.h"
//
//
//#define CHECK_ARG(ARG) do { if (!ARG) return HAL_ERROR; } while (0)			// Verifies that you do not enter a null argument.
//
//#define TAG_HONEYWELL_SENSOR_PRESION		"PRESSURE SENSOR SSC SERIE"
//
//#define HONEYWELL_SENSOR_PRESION_ADDRESS	0x28    						// The default address of pressure sensor.
//
//#define kPaToPSI 0.14503773800722               							// Conversion constant from kPa to PSI.
//#define kPaToBar 0.01                           							// Conversion constant from kPa to Bares.
//
//typedef enum {
//    NORMAL_OPERATION    = 0 ,                   							// S1 = 0 , S2 = 0 ---> Normal operation, valid data
//	COMMAND_MODE            ,                   							// S1 = 0 , S2 = 1 ---> Device in command mode  is used for programming the sensor. This mode should not be seen during normal operation.
//	STALE_DATA              ,                   							// S1 = 1 , S2 = 0 ---> Data that has already been fetched since the last measurement cycle, or data fetched before the first measurement has been completed.
//    DIAGNOSTIC_CONDITION                        							// S1 = 1 , S2 = 1 ---> Diagnostic condition
//} SSCDANN015PD2A5_statusBits;
//
//extern const uint32_t outputMax;
//extern const uint32_t outputMin;
//extern const float pressureMax;
//extern const float pressureMin;
//
//
//typedef enum SSCDANN015PD2A5_ERR_T
//{
//	SSCDANN015PD2A5_ERROR_NONE,
//	SSCDANN015PD2A5_INIT_ERROR,
//	SSCDANN015PD2A5_I2C_ERROR,
//	SSCDANN015PD2A5_errorInSystem
//}SSCDANN015PD2A5_ERR;
//
//typedef enum{
//	SSCDANN015PD2A5_initialization,
//	SSCDANN015PD2A5_sleepMode,
//	SSCDANN015PD2A5_measurement,
//	SSCDANN015PD2A5_error
//}SSCDANN015PD2A5_SM_states;
//
//typedef struct SSCDANN015PD2A5_Functions{
//	I2C_ERR (*i2c_init)		(st_i2c*);
//	I2C_ERR (*i2c_writeData)(st_i2c*, uint8_t*, uint8_t);
//	I2C_ERR (*i2c_readData)	(st_i2c* ,uint16_t , uint8_t* , uint8_t );
//	I2C_ERR (*i2c_readData2)	(st_i2c* , uint8_t* , uint8_t );
//}st_SSCDANN015PD2A5_func;
//
//typedef struct SSCDANN015PD2A5_Params{
//	uint64_t 					*milisecElapsed;
//	float						temperature;
//	float						pressure;
//}st_SSCDANN015PD2A5_params;
//
//typedef struct SSCDANN015PD2A5{
//	st_i2c						*i2c_bus;
//	st_SSCDANN015PD2A5_params	Params;
//	SSCDANN015PD2A5_statusBits	status_bits;
//	st_SSCDANN015PD2A5_func		*function;
//	SSCDANN015PD2A5_SM_states	state;
//	SSCDANN015PD2A5_ERR			errorCode;
//}st_SSCDANN015PD2A5;
//
/////***********************************************************************
//// *							FUNCTIONS
//// ***********************************************************************/
//
//SSCDANN015PD2A5_ERR SSCDANN015PD2A5_getMeasurement	(st_SSCDANN015PD2A5 *this);
//SSCDANN015PD2A5_ERR SSCDANN015PD2A5_init			(st_SSCDANN015PD2A5 *this);
//
//#endif /* LIBRARY_PRESSURE_SENSOR_PRESSURE_SENSOR_H_ */


/*
 * pressure_sensor.h
 *
 *  Created on: May 8, 2024
 *      Author: Usuario
 */
#ifndef LIBRARY_PRESSURE_SENSOR_PRESSURE_SENSOR_H_
#define LIBRARY_PRESSURE_SENSOR_PRESSURE_SENSOR_H_

#include "i2cConfig.h"


#define CHECK_ARG(ARG) do { if (!ARG) return HAL_ERROR; } while (0)			// Verifies that you do not enter a null argument.

#define TAG_HONEYWELL_SENSOR_PRESION		"PRESSURE SENSOR SSC SERIE"

#define HONEYWELL_SENSOR_PRESION_ADDRESS	0x28    						// The default address of pressure sensor.

#define kPaToPSI 0.14503773800722               							// Conversion constant from kPa to PSI.
#define kPaToBar 0.01                           							// Conversion constant from kPa to Bares.

typedef enum {
    NORMAL_OPERATION    = 0 ,                   							// S1 = 0 , S2 = 0 ---> Normal operation, valid data
	COMMAND_MODE            ,                   							// S1 = 0 , S2 = 1 ---> Device in command mode  is used for programming the sensor. This mode should not be seen during normal operation.
	STALE_DATA              ,                   							// S1 = 1 , S2 = 0 ---> Data that has already been fetched since the last measurement cycle, or data fetched before the first measurement has been completed.
    DIAGNOSTIC_CONDITION                        							// S1 = 1 , S2 = 1 ---> Diagnostic condition
} SSCDANN015PD2A5_statusBits;

extern const uint32_t outputMax;
extern const uint32_t outputMin;
extern const float pressureMax;
extern const float pressureMin;


typedef enum SSCDANN015PD2A5_ERR_T
{
	SSCDANN015PD2A5_ERROR_NONE,
	SSCDANN015PD2A5_INIT_ERROR,
	SSCDANN015PD2A5_I2C_ERROR,
	SSCDANN015PD2A5_errorInSystem
}SSCDANN015PD2A5_ERR;

typedef enum{
	SSCDANN015PD2A5_initialization,
	SSCDANN015PD2A5_sleepMode,
	SSCDANN015PD2A5_measurement,
	SSCDANN015PD2A5_error
}SSCDANN015PD2A5_SM_states;

typedef struct SSCDANN015PD2A5_Functions{
	I2C_ERR (*i2c_init)		(st_i2c*);
	I2C_ERR (*i2c_writeData)(st_i2c*, uint8_t*, uint8_t);
	I2C_ERR (*i2c_readData)	(st_i2c* , uint8_t* , uint8_t );
}st_SSCDANN015PD2A5_func;

typedef struct SSCDANN015PD2A5_Params{
	uint64_t 					*milisecElapsed;
	float						temperature;
	float						pressure;
}st_SSCDANN015PD2A5_params;

typedef struct SSCDANN015PD2A5{
	st_i2c						*i2c_bus;
	st_SSCDANN015PD2A5_params	Params;
	SSCDANN015PD2A5_statusBits	status_bits;
	st_SSCDANN015PD2A5_func		*function;
	SSCDANN015PD2A5_SM_states	state;
	SSCDANN015PD2A5_ERR			errorCode;
}st_SSCDANN015PD2A5;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

SSCDANN015PD2A5_ERR SSCDANN015PD2A5_getMeasurement	(st_SSCDANN015PD2A5 *this);
SSCDANN015PD2A5_ERR SSCDANN015PD2A5_init			(st_SSCDANN015PD2A5 *this);

#endif /* LIBRARY_PRESSURE_SENSOR_PRESSURE_SENSOR_H_ */
