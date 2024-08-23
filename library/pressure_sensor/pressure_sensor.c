///*
// * pressure_sensor.c
// *
// *  Created on: May 8, 2024
// *      Author: Usuario
// */
//
//#include "pressure_sensor.h"
//#include <stdlib.h> //borrar
//
////Sensor measurement limits. This part number has available as measurement range between 10% and 90% in conversion counts.
//const uint32_t outputMin    = 1638      ;                   // 10% of 2^14 counts or 0x0666.
//const uint32_t outputMax    = 14745     ;                   // 90% of 2^14 counts or 0x3999.
//// This sensor have a range differential pressure of ±15 psi = ±103.42kPa = ±1.03421 bar.
//const float pressureMax     =   103.42 ;                   // Units in kPa.
//const float pressureMin     =   -103.42  ;                   // Units in kPa.
//
//float conversionConstant = kPaToBar;
//
//enum{
//	i2c_bus=i2c_inSystem_1,
//};
//st_SSCDANN015PD2A5_func functions ={
//		.i2c_init		= &i2c_configInit,
//		.i2c_readData	= &i2c_readData
//
//
//};
//
/////***********************************************************************
//// *							FUNCTIONS
//// ***********************************************************************/
//
//float generar_valor_random() {
//    float min_val = 0.004f;
//    float max_val = 0.006f;
//    float step = 0.0001f;
//
//    // Número de pasos en el rango
//    int num_steps = (int)((max_val - min_val) / step) + 1;
//
//    // Generar un valor aleatorio dentro del número de pasos
//    int random_step = rand() % num_steps;
//
//    // Calcular el valor aleatorio
//    float random_val = min_val + (random_step * step);
//
//    return random_val;
//}
//
//void sscSerie_convertDataRAW2Float(st_SSCDANN015PD2A5 *this, int16_t pressureRaw, float conversionConstant, int16_t temperatureRaw)
//{
//	this->Params.pressure       =	(float)(((pressureRaw-outputMin)*(pressureMax-pressureMin)/(outputMax-outputMin))+pressureMin)*conversionConstant;
//    this->Params.temperature    =	(float)(temperatureRaw*200)/2047 - 50.0;
//}
//
//SSCDANN015PD2A5_ERR SSCDANN015PD2A5_init(st_SSCDANN015PD2A5 *this)
//{
//	this->function = &functions;
//
//	//	Init I2C Bus:
//	this->i2c_bus=i2c_configInitPhy(i2c_bus);
//	if (this->function->i2c_init(this->i2c_bus) != I2C_ERROR_NONE)
//	{
//		return SSCDANN015PD2A5_INIT_ERROR;
//	}
//	this->i2c_bus->i2c->i2c_phy.DevAddress = 0x28;
//	this->state = SSCDANN015PD2A5_initialization;
//	return SSCDANN015PD2A5_ERROR_NONE;
//}
//
//SSCDANN015PD2A5_ERR SSCDANN015PD2A5_getMeasurement(st_SSCDANN015PD2A5 *this)
//{
//    CHECK_ARG(this);
//	int16_t pressureRaw = 0;
//	int16_t temperatureRaw = 0;
//    uint8_t data[4];
//
//    if(this->function->i2c_readData(this->i2c_bus,HONEYWELL_SENSOR_PRESION_ADDRESS,data,sizeof(data)) != I2C_ERROR_NONE)
//    	{
//    		this->errorCode = SSCDANN015PD2A5_I2C_ERROR;
//    	//	SSCDANN015PD2A5_init(this);
//    		return SSCDANN015PD2A5_I2C_ERROR;
//    	}
//
//	this->status_bits = (data[0] & 0xC0) >>6; // The diagnostic states are indicated by the first two Most Significant Bits of Data Byte 1
//	switch (this->status_bits)
//	{
//		case NORMAL_OPERATION:
////				printf("Valid data.\n");
//			pressureRaw = (int16_t)(data[0] & 0x3F)<<8 | data[1];
//            temperatureRaw = (int16_t)data[2]<<3 | ((data[3] & 0xE0)>>5);
//            break;
//
//            case COMMAND_MODE :
////            	printf("Command mode is used for programming the sensor.\n");
//            break;
//
//            case STALE_DATA :
////            	printf("Data not updated, reads slower.\n");
//            break;
//
//            case DIAGNOSTIC_CONDITION :
////            	printf("Fault detected.\n");
//                pressureRaw    = 0;
//                temperatureRaw = 0;
//            break;
//
//            default:
////            	printf("Status Bits Error.\n");
//            break;
//        }
//	sscSerie_convertDataRAW2Float(this, pressureRaw,conversionConstant,temperatureRaw);
////	this->Params.pressure = generar_valor_random();
//
//
//	return SSCDANN015PD2A5_ERROR_NONE;
//    }
//


/*
 * pressure_sensor.c
 *
 *  Created on: May 8, 2024
 *      Author: Usuario
 */

#include "pressure_sensor.h"

//Sensor measurement limits. This part number has available as measurement range between 10% and 90% in conversion counts.
const uint32_t outputMin    = 1638      ;                   // 10% of 2^14 counts or 0x0666.
const uint32_t outputMax    = 14745     ;                   // 90% of 2^14 counts or 0x3999.
// This sensor have a range differential pressure of ±15 psi = ±103.42kPa = ±1.03421 bar.
const float pressureMax     =   103.42 ;                   // Units in kPa.
const float pressureMin     =   -103.42  ;                   // Units in kPa.

float conversionConstant = kPaToBar;

enum{
	i2c_bus=i2c_inSystem_1,
};
st_SSCDANN015PD2A5_func functions ={
		.i2c_init		= &i2c_configInit,
		.i2c_readData	= &i2c_readData
};

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void sscSerie_convertDataRAW2Float(st_SSCDANN015PD2A5 *this, int16_t pressureRaw, float conversionConstant, int16_t temperatureRaw)
{
	this->Params.pressure       =	(float)(((pressureRaw-outputMin)*(pressureMax-pressureMin)/(outputMax-outputMin))+pressureMin)*conversionConstant;
    this->Params.temperature    =	(float)(temperatureRaw*200)/2047 - 50.0;
}

SSCDANN015PD2A5_ERR SSCDANN015PD2A5_init(st_SSCDANN015PD2A5 *this)
{
	this->function = &functions;

	//	Init I2C Bus:
	this->i2c_bus=i2c_configInitPhy(i2c_bus);
	if (this->function->i2c_init(this->i2c_bus) != I2C_ERROR_NONE)
	{
		return SSCDANN015PD2A5_INIT_ERROR;
	}
	this->i2c_bus->i2c->i2c_phy.DevAddress = 0x28;
	this->state = SSCDANN015PD2A5_initialization;
	return SSCDANN015PD2A5_ERROR_NONE;
}

SSCDANN015PD2A5_ERR SSCDANN015PD2A5_getMeasurement(st_SSCDANN015PD2A5 *this)
{
    CHECK_ARG(this);
	int16_t pressureRaw = 0;
	int16_t temperatureRaw = 0;
    uint8_t data[4];

    if(this->function->i2c_readData(this->i2c_bus,data,sizeof(data)) != I2C_ERROR_NONE)
    	{
    		this->errorCode = SSCDANN015PD2A5_I2C_ERROR;
    		return SSCDANN015PD2A5_I2C_ERROR;
    	}

	this->status_bits = (data[0] & 0xC0) >>6; // The diagnostic states are indicated by the first two Most Significant Bits of Data Byte 1
	switch (this->status_bits)
	{
		case NORMAL_OPERATION:
//				printf("Valid data.\n");
			pressureRaw = (int16_t)(data[0] & 0x3F)<<8 | data[1];
            temperatureRaw = (int16_t)data[2]<<3 | ((data[3] & 0xE0)>>5);
            break;

            case COMMAND_MODE :
//            	printf("Command mode is used for programming the sensor.\n");
            break;

            case STALE_DATA :
//            	printf("Data not updated, reads slower.\n");
            break;

            case DIAGNOSTIC_CONDITION :
//            	printf("Fault detected.\n");
                pressureRaw    = 0;
                temperatureRaw = 0;
            break;

            default:
//            	printf("Status Bits Error.\n");
            break;
        }
	sscSerie_convertDataRAW2Float(this, pressureRaw,conversionConstant,temperatureRaw);


	return SSCDANN015PD2A5_ERROR_NONE;
    }


