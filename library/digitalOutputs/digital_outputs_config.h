/*
 * digital_outputs_config.h
 *
 *  Created on: 16 jul. 2020
 *      Author: Laptop-Dell
 */

#ifndef FDX_LIBS_DIGITAL_OUTPUTS_CONFIG_H_
#define FDX_LIBS_DIGITAL_OUTPUTS_CONFIG_H_

#include "basicPin.h"

enum{
	enum_DigitalOutput_0,
	enum_DigitalOutput_1,
	enum_DigitalOutput_2,
	enum_DigitalOutput_3,
	enum_DigitalOutput_4,
	enum_DigitalOutput_5,
	enum_DigitalOutput_6,
	enum_DigitalOutput_7,
	enum_DigitalOutput_8,
	enum_DigitalOutput_9,
	enum_DigitalOutput_10,
	enum_DigitalOutput_11,
	enum_DigitalOutput_12,
	enum_DigitalOutput_13,
	enum_DigitalOutput_14,
	enum_DigitalOutput_15,
	enum_DigitalOutput_inSystem
};


typedef struct dig_output{
	st_pin *pin;
}st_dig_output;

st_pin_config *digital_OutputsEna24VConfig();
st_dig_output *digital_outputs_Get24VEna();

state digital_outputs_Init(st_dig_output *);
state digital_output_Write(st_dig_output *, uint8_t);
state digital_output_Read(st_dig_output *);

st_dig_output *digital_output_config_GetDigitalOutput(uint32_t);
st_dig_output *digital_output_config_InitPhyDigitalOutput(uint32_t);

#endif /* FDX_LIBS_DIGITAL_OUTPUTS_CONFIG_H_ */
