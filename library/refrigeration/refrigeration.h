/*
 * refrigeration.h
 *
 *  Created on: May 8, 2024
 *      Author: Usuario
 */

#ifndef LIBRARY_REFRIGERATION_H_
#define LIBRARY_REFRIGERATION_H_

#include "chiller.h"
#include "pump.h"
#include "ads1118.h"

#define COOLANT_LIQUID_TEMPERATURE_LIMIT 7
#define HOT_HEAT_SINK_TEMPERATURE_SETPOINT 20
typedef enum{
	refrigeration_init,
	refrigeration_off,
	refrigeration_start,
	refrigeration_working,
	refrigeration_stop,
	refrigeration_error
}st_refrigerartionSystem_states;

typedef enum{
	REFRIGERATION_ERROR_NONE,
	REFRIGERATION_INIT_ERROR,
	REFRIGERATION_START_ERROR,
	CHILLER_PARAMS_ERROR,
	CHILLER_DISCONNECT,
	COOLANT_LIQUID_ERROR,
	PUMP_ERROR
}REFRIGERATION_ERR;

typedef enum{
	parameters_OK,
	parameters_FAULT
}st_regrigeration_flags;

typedef struct refrigeration_functions{
	FSCH027Z24BT_ERR 	(*chiller_init)			(st_FSCH027Z24BT *);
	FSCH027Z24BT_ERR 	(*chiller_sendConfig)	(st_FSCH027Z24BT *);
	FSCH027Z24BT_ERR 	(*chiller_receiveData)	(st_FSCH027Z24BT *);
	FSCH027Z24BT_ERR 	(*chiller_stop) 		(st_FSCH027Z24BT *);
	void				(*update_configChiller)	(void);
	void				(*pump_init)			(st_PUMP *);
	void				(*pump_ON)				(st_PUMP *);
	void				(*pump_OFF)				(st_PUMP *);
}st_refrigeration_func;

typedef struct refrigeration{
	st_refrigerartionSystem_states 	state;
	st_regrigeration_flags			flag;
	REFRIGERATION_ERR				error;
	st_FSCH027Z24BT					chiller;
	st_PUMP							pump;
	st_ADS1118						*ads1118;
	st_refrigeration_func			*functions;
	uint64_t 						*millisecElapsed;
	float							liquidTemperature;
}st_refrigeration;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/
REFRIGERATION_ERR	refrigerationSystem_init	(st_refrigeration *this);
REFRIGERATION_ERR	refrigerationSystem_start	(st_refrigeration *this);
void 				refrigerationSystem_stop	(st_refrigeration *this);
void 				refrigerationStateMachine	(void);

#endif /* LIBRARY_REFRIGERATION_H_ */
