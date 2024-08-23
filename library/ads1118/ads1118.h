/**
 * @file ads1118.h
 * @brief Librería para controlar el ADS1118.
 * @author Francisco
 * @date Jan 17, 2024
 */

#ifndef INC_ADS1118_H_
#define INC_ADS1118_H_


/***********************************************************************
 *							INCLUDES
 ***********************************************************************/
#include "hardwareConfig.h"
#include "typdef_basicLib.h"
#include <stdio.h>
#include <stdint.h>
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "digital_outputs_config.h"
#include "spiConfig.h"
#include "uart_config.h"
#include "systemTime.h"
#endif
/***********************************************************************
 *							GLOBAL DEFINITIONS
 ***********************************************************************/

/*-------------------------- SS bit input ----------------------------*/
#define NO_EFFECT		0
#define START_NOW		1		///< Start of conversion in single-shot mode

/*-------------------------- MUX inputs ----------------------------*/
#define DIFF_0_1		0b000 	///< Differential input: Vin=A0-A1
#define DIFF_0_3		0b001 	///< Differential input: Vin=A0-A3
#define DIFF_1_3		0b010 	///< Differential input: Vin=A1-A3
#define DIFF_2_3		0b011 	///< Differential input: Vin=A2-A3
#define AIN_0			0b100	///< Single ended input: Vin=A0
#define AIN_1			0b101	///< Single ended input: Vin=A1
#define AIN_2			0b110	///< Single ended input: Vin=A2
#define AIN_3			0b111	///< Single ended input: Vin=A3

/*-------------------------- PGA inputs ----------------------------*/
 //[Warning: this could increase the noise and the effective number of bits (ENOB).]
#define FSR_6144		0b000	///< Range: ±6.144 v. LSB SIZE = 187.5μV
#define FSR_4096		0b001	///< Range: ±4.096 v. LSB SIZE = 125μV
#define FSR_2048		0b010	///< Range: ±2.048 v. LSB SIZE = 62.5μV ***DEFAULT
#define FSR_1024		0b011	///< Range: ±1.024 v. LSB SIZE = 31.25μV
#define FSR_0512		0b100	///< Range: ±0.512 v. LSB SIZE = 15.625μV
#define FSR_0256		0b111	///< Range: ±0.256 v. LSB SIZE = 7.8125μV

/*-------------------------- MODE inputs ---------------------------*/
#define CONTINUOUS		0		///< Continuous conversion mode
#define SINGLE_SHOT		1		///< Single-shot conversion and power down mode

/*-------------------------- DR inputs ----------------------------*/
//[Warning: this could increase the noise and the effective number of bits (ENOB).]
#define RATE_8SPS		0b000	///< 8 samples/s, Tconv=125ms
#define RATE_16SPS		0b001	///< 16 samples/s, Tconv=62.5ms
#define RATE_32SPS		0b010	///< 32 samples/s, Tconv=31.25ms
#define RATE_64SPS		0b011	///< 64 samples/s, Tconv=15.625ms
#define RATE_128SPS		0b100	///< 128 samples/s, Tconv=7.8125ms
#define RATE_250SPS		0b101	///< 250 samples/s, Tconv=4ms
#define RATE_475SPS		0b110	///< 475 samples/s, Tconv=2.105ms
#define RATE_860SPS		0b111	///< 860 samples/s, Tconv=1.163ms

/*------------------------ TS_MODE inputs --------------------------*/
#define ADC_MODE		0		///< External (inputs) voltage reading mode
#define TEMP_MODE		1		///< Internal temperature sensor reading mode

/*----------------------- PULL_UP_EN inputs ------------------------*/
#define DOUT_NO_PULLUP	0		///< Internal pull-up resistor disabled
#define DOUT_PULLUP		1		///< Internal pull-up resistor enabled for DOUT ***DEFAULT

/*-------------------------- NOP inputs ----------------------------*/
#define NO_VALID_CFG	0b00	///< Data won't be written to Config register
#define VALID_CFG		0b01	///< Data will be written to Config register

/*------------------------ Reserved input --------------------------*/
#define RESERVED		1		///< Its value is always 1, reserved

typedef enum ADS1118_ERR_T
{
	ADS1118_ERROR_NONE,
	ADS1118_INIT_ERROR,
	ADS1118_ADC_ERROR,
	ADS1118_TS_ERROR,
	ADS1118_SPI_ERROR,
	ADS1118_SENSOR_DISCONNECTED,
	ads1118_errorInSystem
}ADS1118_ERR;

typedef enum{
	ads1118_initialization,
	ads1118_sleepMode,
	ads1118_measurement,
	ads1118_error
}ads1118_SM_states;

typedef enum{
	ads1118_requestInternalTemp,
	ads1118_getInternalTemp,
	ads1118_waitConversionInternalTemp,
	ads1118_requestThermocoupleVoltage,
	ads1118_getThermocoupleVoltage,
	ads1118_waitConversionThermocoupleVoltage,
	ads1118_getTotalTemperature,
	ads1118_temperatureMeasurementReady
}ads1118_internal_SM_states;


/***********************************************************************
 *								STRUCTURES
 ***********************************************************************/

typedef struct ads1118Config{
	ss_bit			singleShotConvStart;
	mux_bits		multiplexer;
	pga_bits		gainAmplifierConfig;
	mode_bit		deviceOperatingMode;
	dr_bits			dataRate;
	tsMode_bit		temperatureSensorMode;
	pullUp_bit		pullUpEnable;
	nop_bits		noOperation;
	reserved_bit	reserved;
}st_ADS1118_config;

typedef union Register {
	///Structure of the config register of the ADS1118. (See datasheet [1])
	struct {
		uint8_t reserved:1;    	///< "Reserved" bit
		uint8_t noOperation:2; 	///< "NOP" bits
		uint8_t pullUp:1;	   	///< "PULL_UP_EN" bit
		uint8_t sensorMode:1;  	///< "TS_MODE" bit
		uint8_t rate:3;		   	///< "DR" bits
		uint8_t operatingMode:1;///< "MODE" bit
		uint8_t pga:3;			///< "PGA" bits
		uint8_t mux:3;			///< "MUX" bits
		uint8_t singleStart:1;  ///< "SS" bit
	} bits;
	uint16_t word;				///< Representation in word (16-bits) format
	struct {
		uint8_t lsb;			///< Byte LSB
		uint8_t msb;			///< Byte MSB
	} byte;						///< Representation in bytes (8-bits) format
}st_ADS1118_ConfigRegister;

typedef struct ADS1118_Functions{
	state	(*init_output)			(st_dig_output *);
	state	(*set_output)			(st_dig_output *, state);
	SPI_ERR	(*init_spi)				(st_spi*);
	SPI_ERR	(*spi_transmitReceive)	(st_spi*, uint8_t*, uint8_t*);
}st_ADS1118_func;

typedef struct ADS1118_Params{
	uint64_t 					*milisecElapsed;
	float						internalTemp;
	float						millivolts;
	float						temperature;
}st_ADS1118_params;

typedef struct ADS1118{
	st_spi						*spi_bus;
	st_dig_output				*cs_pin;
	st_ADS1118_params			Params;
	st_ADS1118_ConfigRegister	ConfigReg;
	st_ADS1118_func				*function;
	ads1118_internal_SM_states	measure_state;
	ads1118_SM_states			state;
	ADS1118_ERR					errorCode;
	bool						disconnection_flag;
}st_ADS1118;

typedef struct ads1118{
st_ADS1118 *ads1118;
}st_ads1118_module;
/***********************************************************************
 *					EXPORTED FUNCTIONS PROTOTYPES
 ***********************************************************************/

/**
 * @brief Initializes the configuration of the ADS1118.
 *
 * This function sets the initial configuration parameters of the ADS1118.
 *
 * @param[in] this Pointer to the st_ADS1118 structure representing the ADS1118 device.
 * @param[in] config Pointer to the st_ADS1118_config structure containing the initial configuration.
 *
 * @return Operation status (ADS1118_ERROR_NONE if successful, ADS1118_INIT_ERROR if there is an initialization error).
 */
ADS1118_ERR ads1118_init(st_ADS1118 *this, st_ADS1118_config *config);

/**
 * @brief Performs a single measurement using the ADS1118.
 *
 * This function implements a state machine to perform a single measurement using the ADS1118.
 * The state machine transitions through the necessary steps to initiate and complete a measurement.
 *
 * @param[in] this Pointer to the st_ADS1118 structure representing the ADS1118 device.
 */
void ads1118Measurement(st_ADS1118 *this);

/**
 * @brief Implements the state machine for controlling the ADS1118 device.
 *
 * This function implements a state machine to control the behavior of the ADS1118 device.
 * It manages the initialization, measurement, and error handling states of the ADS1118.
 * The state machine transitions through different states based on the current state and conditions.
 *
 * @param[in] this Pointer to the st_ADS1118 structure representing the ADS1118 device.
 */
void ads1118_StateMachine();

#endif /* INC_ADS1118_H_ */
