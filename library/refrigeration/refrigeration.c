/*
 * refrigeration.c
 *
 *  Created on: May 8, 2024
 *      Author: Usuario
 */

#include "refrigeration.h"

st_refrigeration_func refrigerationFunctions ={
		.chiller_init			= &FSCH027Z24BT_init,
		.chiller_sendConfig 	= &FSCH027Z24BT_sendFrame,
		.chiller_receiveData	= &FSCH027Z24BT_receiveFrame,
		.chiller_stop			= &FSCH027Z24BT_stop,
		.pump_init				= &pumpInit,
		.pump_OFF				= &pumpStop,
		.pump_ON				= &pumpStart,
};

st_refrigeration *refrigerationSystem;
uint64_t time_checkRefrigeration = 0;
uint64_t time_checkWorkingTemperature = 0;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void manageChillerCommunication(void){
	if(*refrigerationSystem->millisecElapsed > time_checkRefrigeration + 1000)

	{

		if (refrigerationSystem->chiller.txEnable == 1 && refrigerationSystem->chiller.rxComplete == 1)
		{
			refrigerationSystem->chiller.rxComplete = 0;
			refrigerationSystem->chiller.txEnable = 0;
			refrigerationSystem->functions->chiller_sendConfig(&refrigerationSystem->chiller);

		}
		if(refrigerationSystem->chiller.rxComplete == 1) // Cuando entra "Chiller Disconnect" deja de entrar acá
		{
			refrigerationSystem->chiller.txEnable = 1;
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.byte == 0x00)
			{
				refrigerationSystem->flag 	= parameters_OK;
				refrigerationSystem->error  = REFRIGERATION_ERROR_NONE;

			}
			else{
				refrigerationSystem->flag	= parameters_FAULT;
				refrigerationSystem->state 	= refrigeration_error;
				refrigerationSystem->error 	= CHILLER_PARAMS_ERROR;
			}
			time_checkRefrigeration = *refrigerationSystem->millisecElapsed;
		}
		if ((*refrigerationSystem->millisecElapsed-time_checkRefrigeration) >= 15000)
		{
			refrigerationSystem->chiller.rxComplete = 1;
			refrigerationSystem->chiller.txEnable = 1;
			refrigerationSystem->state = refrigeration_error;
			refrigerationSystem->error = CHILLER_DISCONNECT;
			time_checkRefrigeration = *refrigerationSystem->millisecElapsed;
		}

	}
}

void refrigerationStateMachine(void)
{
	manageChillerCommunication();
	switch (refrigerationSystem->state)
	{
	case refrigeration_init:
		refrigerationSystem->chiller.txEnable = 1;
		refrigerationSystem->chiller.rxComplete = 1;
		time_checkRefrigeration = *refrigerationSystem->millisecElapsed;
		refrigerationSystem->state = refrigeration_off;
		break;

	case refrigeration_start:
		if (refrigerationSystem_start(refrigerationSystem) != REFRIGERATION_ERROR_NONE)
		{
			refrigerationSystem->state 	= refrigeration_error;
			refrigerationSystem->error 	= REFRIGERATION_START_ERROR;
		}
		else
		{
			refrigerationSystem->state = refrigeration_working;
			refrigerationSystem->error 	= REFRIGERATION_ERROR_NONE;
		}
		break;
	case refrigeration_off:
		break;
	case refrigeration_stop:
		refrigerationSystem_stop(refrigerationSystem);
		refrigerationSystem->state = refrigeration_off;
		break;
	case refrigeration_working:
		//		"ChillerON";
		//		"PumpON";
		if(*refrigerationSystem->millisecElapsed >= time_checkWorkingTemperature + 5000)
		{
			if(refrigerationSystem->liquidTemperature > COOLANT_LIQUID_TEMPERATURE_LIMIT)
			{
				if(HOT_HEAT_SINK_TEMPERATURE_SETPOINT - refrigerationSystem->ads1118->Params.temperature > 4)
				{
					//Disminuir velocidad
					refrigerationSystem->chiller.FSCH027Z24BT_master.speed -= 200;
				}
				else if(HOT_HEAT_SINK_TEMPERATURE_SETPOINT - refrigerationSystem->ads1118->Params.temperature < -4)
				{
					//Aumentar la velocidad
					refrigerationSystem->chiller.FSCH027Z24BT_master.speed += 200;
				}
			}
			else //--> Se esta por congelar el agua
			{
				if(HOT_HEAT_SINK_TEMPERATURE_SETPOINT - refrigerationSystem->ads1118->Params.temperature > -10)
				{
					refrigerationSystem->chiller.FSCH027Z24BT_master.speed -= 300;
				}
				else if(HOT_HEAT_SINK_TEMPERATURE_SETPOINT - refrigerationSystem->ads1118->Params.temperature < -10)
				{
					//apagar el cryocooler
					refrigerationSystem->state = refrigeration_error;
					refrigerationSystem->error = COOLANT_LIQUID_ERROR;
					refrigerationSystem->chiller.FSCH027Z24BT_master.speed = 1000;
				}
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_master.speed > 3000)
			{
				refrigerationSystem->chiller.FSCH027Z24BT_master.speed = 3000;
			}
			else if(refrigerationSystem->chiller.FSCH027Z24BT_master.speed < 1000)
			{
				refrigerationSystem->chiller.FSCH027Z24BT_master.speed = 1000;
			}

			time_checkWorkingTemperature = *refrigerationSystem->millisecElapsed;
		}

		break;
	case refrigeration_error: //Quizas haya que volver a mandar con una funcion una vez que no existe error
		switch (refrigerationSystem->error) {
		case REFRIGERATION_ERROR_NONE:
			refrigerationSystem->state = refrigeration_working;
			break;
		case REFRIGERATION_START_ERROR:

			break;
		case CHILLER_DISCONNECT:

			break;
		case COOLANT_LIQUID_ERROR:
			if(HOT_HEAT_SINK_TEMPERATURE_SETPOINT - refrigerationSystem->ads1118->Params.temperature > 0)
			{
				refrigerationSystem->error = REFRIGERATION_ERROR_NONE;
			}
			break;
		case CHILLER_PARAMS_ERROR:
			//			refrigerationSystem_stop(refrigerationSystem);
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.overcurrent == true)
			{
				refrigerationSystem->chiller.flag = overcurrent_error;
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.overvoltage == true)
			{
				refrigerationSystem->chiller.flag = overvoltage_error;
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.undervoltage == true)
			{
				refrigerationSystem->chiller.flag = undervoltage_error;
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.lack_phase == true)
			{
				refrigerationSystem->chiller.flag = lack_phase_error;
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.lose_speed == true)
			{
				refrigerationSystem->chiller.flag = lose_speed_error;
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.hardware_oc_protection == true)
			{
				refrigerationSystem->chiller.flag = hw_oc_protection_error;
			}
			if(refrigerationSystem->chiller.FSCH027Z24BT_slave.troubleCode.bits.phase_current_anomaly == true)
			{
				refrigerationSystem->chiller.flag = phase_current_anomaly_error;
			}
			break;
		default:
			break;
		}

		break;
	}
}


REFRIGERATION_ERR refrigerationSystem_init(st_refrigeration *this)
{
	this->functions = &refrigerationFunctions;
	if (this->functions->chiller_init(&this->chiller) != FSCH027Z24BT_ERROR_NONE)
	{
		return REFRIGERATION_INIT_ERROR;
	}
	this->functions->pump_init(&this->pump);
	refrigerationSystem = this;

	return REFRIGERATION_ERROR_NONE;
}

REFRIGERATION_ERR refrigerationSystem_start(st_refrigeration *this)
{
	this->functions->pump_ON(&this->pump);

	if (this->functions->chiller_sendConfig(&this->chiller) != FSCH027Z24BT_ERROR_NONE)
	{
		return REFRIGERATION_START_ERROR;
	}

	return REFRIGERATION_ERROR_NONE;
}

void refrigerationSystem_stop(st_refrigeration *this)
{
	this->functions->chiller_stop(&this->chiller);
	this->functions->pump_OFF(&this->pump);
}
