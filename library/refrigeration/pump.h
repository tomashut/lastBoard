/*
 * pump.h
 *
 *  Created on: May 14, 2024
 *      Author: Usuario
 */

#ifndef LIBRARY_REFRIGERATION_PUMP_H_
#define LIBRARY_REFRIGERATION_PUMP_H_

#include "digital_outputs_config.h"

typedef enum{
	pump_ON,
	pump_OFF,
	pump_error
}PUMP_SM_states;

typedef struct PUMP_Functions{
	state (*init_pumpPin) 	(st_dig_output *);
	state (*get_pumpPin)	(st_dig_output *);
	state (*set_pumpPin) 	(st_dig_output *,uint8_t);
}st_PUMP_func;

typedef struct PUMP{
	st_dig_output		*Pin;
	st_PUMP_func		*functions;
	PUMP_SM_states		state;
}st_PUMP;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void pumpInit	(st_PUMP *this);
void pumpStart	(st_PUMP *this);
void pumpStop	(st_PUMP *this);
#endif /* LIBRARY_REFRIGERATION_PUMP_H_ */
