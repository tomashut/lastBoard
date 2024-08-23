/*
 * pump.c
 *
 *  Created on: May 14, 2024
 *      Author: Usuario
 */
#include "pump.h"

enum{
	PB10=enum_DigitalOutput_0,
};


st_PUMP_func PUMP_Functions = {
		.init_pumpPin	= &digital_outputs_Init,
		.get_pumpPin	= &digital_output_Read,
		.set_pumpPin	= &digital_output_Write,
		};

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void pumpInit(st_PUMP *this){
	this->functions = &PUMP_Functions;
	this->Pin = digital_output_config_InitPhyDigitalOutput(PB10);
	this->functions->init_pumpPin(this->Pin);
}
void pumpStart(st_PUMP *this){
	this->functions->set_pumpPin(this->Pin,on_state);
}
void pumpStop(st_PUMP *this){
	this->functions->set_pumpPin(this->Pin,off_state);
}

