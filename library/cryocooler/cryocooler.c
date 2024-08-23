/*
 * cryocooler.c
 *
 *  Created on: May 13, 2024
 *      Author: CRINSURANCE 1
 */
/***********************************************************************
 *							INCLUDES
 ***********************************************************************/
#include "cryocooler.h"
#define DEF_DISCONNECTION_TIME 10000 //Time that the board waits for a cryocooler's response

/***********************************************************************
 *							VARIABLES
 ***********************************************************************/
st_ControllerParameters DefaultParameters={
		.MODE	= 2.000	,
		.PID	= 2.000	,
		.TEMP_KI= 1.000	,
		.TEMP_KP= 50.000,
		.SSTOPM = 0.000	,
		.SSTOP	= 0.000	,
		.PWOUT	= 0.000	,
		.TTARGET= 77.00	,
		.TBAND	= 0.50	,
		.TSTATM	= 0.000	,
		.TSTAT	= 0.000	,
		.MAX	= 300.00,
		.MIN	= 0.000	,
		.LOCK	= 0.000	,
		.PASS	= {'S','T','I','R','L','I','N','G'}
};

enum{
	uart_comm=enum_uart_inSystem_1
};
enum{
	ss_pin=enum_DigitalOutput_1
};

st_Cryocooler_func cryocoolerFunc={
		.init_output	= &digital_outputs_Init,
		.set_output		= &digital_output_Write,
		.init_uart		= &uart_Init,
		.send_uart		= &uart_send,
		.receive_uart	= &uart_receive
};

const char *valid_commands[] = {
		"RESET=F",
		"TC",
		"SET PID=",
		"SET PID",
		"SAVE PID",
		"MODE",
		"VERSION",
		"SERIAL",
		"ERROR",
		"P",
		"E",
		"SET KI=",
		"SET KI",
		"STATE",
		"SET KP=",
		"SET KP",
		"SET SSTOPM=",
		"SET SSTOPM",
		"SET SSTOP=",
		"SET SSTOP",
		"SET PWOUT=",
		"SET PWOUT",
		"SET TTARGET=",
		"SET TTARGET",
		"SET TBAND=",
		"SET TBAND",
		"SET TSTATM=",
		"SET TSTATM",
		"TSTAT",
		"SET MIN=",
		"SET MIN",
		"SET MAX=",
		"SET MAX",
		"SHOW MX",
		"LOCK=",
		"UNLOCK=",
		"SET PASS=",
		"LOCK",
		"FACTORY RESET COMPLETE!"
};
const int num_commands = sizeof(valid_commands) / sizeof(valid_commands[0]);


st_Cryocooler *cryocooler;

Initialization_SM_States SM_initialization_state = INIT_STATE_RESET_CONTROLLER;
Off_SM_States SM_off_state = OFF_STATE_DISPLAY_ERROR_CODE;
On_SM_States SM_on_state = ON_STATE_DISPLAY_ERROR_CODE;
Error_SM_States SM_error_state = ERROR_STATE_NO_ERROR;


char		backupCommand[10];
uint64_t	disconnectionTime = 0;


/***********************************************************************
 *							CALLBACKS
 ***********************************************************************/

//void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
//{
//	if (huart->Instance == cryocooler->communicationPort->uart->uart_phy.handlerUART.Instance)
//	{
//		execute_command_action(cryocooler->uart_buffer.rxBuffer);
//		// Reiniciar la recepción
//		cryocooler->functions->receive_uart(cryocooler->communicationPort);
//		cryocooler->rxComplete = yes;
//	}
//
//}

/***********************************************************************
 *						INTERNAL FUNCTIONS
 ***********************************************************************/

void turn_on_cryocooler(st_Cryocooler *this)
{
	this->functions->set_output(this->soft_stop_pin, off_state);
//	this->operatingParameters.SSTOP = 0;
}

void turn_off_cryocooler(st_Cryocooler *this)
{
	this->functions->set_output(this->soft_stop_pin, on_state);
//	this->operatingParameters.SSTOP = 1;
}

void send_uart_command(char* command)
{
	cryocooler->rxComplete = no;
	cryocooler->communicationPort->uart->uart_phy.pTxBuffPtr=(uint8_t *)command;
	strcat(command,"\r");
	cryocooler->communicationPort->uart->uart_phy.TxXferSize = strlen(command);
	strcpy(backupCommand,command);
	memset(cryocooler->uart_buffer.rxBuffer,'\0', sizeof(cryocooler->uart_buffer.rxBuffer));
	cryocooler->communicationPort->uart->uart_func.send(&cryocooler->communicationPort->uart->uart_phy,sizeof(cryocooler->uart_buffer.txBuffer));
	HAL_Delay(1000);
	disconnectionTime = *cryocooler->millisecElapsed;
}

void resendCommand(void)
{
	memset(cryocooler->uart_buffer.rxBuffer,'\0', sizeof(cryocooler->uart_buffer.rxBuffer));
	cryocooler->rxComplete = no;
	cryocooler->communicationPort->uart->uart_phy.pTxBuffPtr=(uint8_t*)backupCommand;
	cryocooler->communicationPort->uart->uart_func.send(&cryocooler->communicationPort->uart->uart_phy,sizeof(cryocooler->uart_buffer.txBuffer));
	HAL_Delay(1000);
}

void cryocooler_getOperatingParameters(st_Cryocooler *this){
	if(sscanf(this->uart_buffer.rxBuffer,
			"STATE\r\n"
			"MODE     = %f\r\n"
			"TSTATM   = %f\r\n"
			"TSTAT    = %f\r\n"
			"SSTOPM   = %f\r\n"
			"SSTOP    = %f\r\n"
			"PID      = %f\r\n"
			"LOCK     = %f\r\n"
			"MAX      = %f\r\n"
			"MIN      = %f\r\n"
			"PWOUT    = %f\r\n"
			"TTARGET  = %f\r\n"
			"TBAND    = %f\r\n"
			"TEMP KP  = %f\r\n"
			"TEMP KI  = %f\r\n",
			&this->operatingParameters.MODE, &this->operatingParameters.TSTATM,&this->operatingParameters.TSTAT,
			&this->operatingParameters.SSTOPM, &this->operatingParameters.SSTOP,&this->operatingParameters.PID,
			&this->operatingParameters.LOCK, &this->operatingParameters.MAX, &this->operatingParameters.MIN,
			&this->operatingParameters.PWOUT, &this->operatingParameters.TTARGET, &this->operatingParameters.TBAND,
			&this->operatingParameters.TEMP_KP, &this->operatingParameters.TEMP_KI) == 14)
	{
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_getErrorRegister(st_Cryocooler *this)
{
	uint32_t auxiliar;
	if(sscanf(this->uart_buffer.rxBuffer,"ERROR\r\n%lu\r\n",&auxiliar) == 1)
	{
		this->errorRegister.bits.OverCurrent				= ((auxiliar/1)%10);
		this->errorRegister.bits.JumperError				= ((auxiliar/10)%10);
		this->errorRegister.bits.SerialCommunicationError	= ((auxiliar/100)%10);
		this->errorRegister.bits.Non_VolatileMemoryError	= ((auxiliar/1000)%10);
		this->errorRegister.bits.WatchdogError				= ((auxiliar/10000)%10);
		this->errorRegister.bits.TemperatureSensorError		= ((auxiliar/100000)%10);

		if(this->errorRegister.byte != 0x00)
		{
			this->flag = cryo_parameters_FAULT;
		}
		else
		{
			this->flag = cryo_parameters_OK;
		}
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}


void cryocooler_getTemperature(st_Cryocooler *this)
{
	if(sscanf(this->uart_buffer.rxBuffer,"TC\r\n%f\r\n",&this->measurements.coldTipTemperature) == 1)
	{
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_getConsumedPower(st_Cryocooler *this)
{
	if(sscanf(this->uart_buffer.rxBuffer,"P\r\n%f\r\n",&this->measurements.coolerPowerConsumed) == 1)
	{
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_getLockState(st_Cryocooler *this)
{
	if(sscanf(this->uart_buffer.rxBuffer,"LOCK\r\n%f\r\n",&this->operatingParameters.LOCK) == 1)
	{
		if(this->operatingParameters.LOCK == cryo_parameters_LOCKED)
		{
			UNLOCK_USER_LOCKABLE_COMMANDS(this->operatingParameters.PASS);
		}
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_UnlockParameters(st_Cryocooler *this)
{
	char string[30];
	sprintf(string, "UNLOCK=%s\r\n", cryocooler->operatingParameters.PASS);
	if(strstr(this->uart_buffer.rxBuffer,string) != NULL)
	{
		sprintf(string, "UNLOCK=%s\r\n000.00", cryocooler->operatingParameters.PASS);
		if(strstr(this->uart_buffer.rxBuffer,string) != NULL)
		{
			this->operatingParameters.LOCK = cryo_parameters_UNLOCKED;
		}
		sprintf(string, "UNLOCK=%s\r\n001.00", cryocooler->operatingParameters.PASS);
		if(strstr(this->uart_buffer.rxBuffer,string) != NULL)
		{
			this->operatingParameters.LOCK	= cryo_parameters_LOCKED;
			cryocooler->state				= cryocooler_error;

		}
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_setDefaultParameters(st_Cryocooler *this)
{
	if (strstr(cryocooler->uart_buffer.rxBuffer,"RESET=F\r\n") != NULL)
	{
		memset(cryocooler->uart_buffer.rxBuffer,'\0', sizeof(cryocooler->uart_buffer.rxBuffer));
	}
	// Buscar la cadena "FACTORY RESET COMPLETE!" en el buffer de recepción
	else if (strstr(this->uart_buffer.rxBuffer, "FACTORY RESET COMPLETE!") != NULL)
	{
		this->operatingParameters = DefaultParameters;
		cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_setSoftStopMode(st_Cryocooler *this)
{
	// Verificar si la cadena contiene "SET SSTOPM=1\r\n" o "SET SSTOPM=0\r\n"
	if (strstr(this->uart_buffer.rxBuffer, "SET SSTOPM=1\r\n") != NULL)
	{
		if (sscanf(this->uart_buffer.rxBuffer, "SET SSTOPM=1\r\n%f\r\n", &this->operatingParameters.SSTOPM) == 1)
		{
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
	}
	else if (strstr(this->uart_buffer.rxBuffer, "SET SSTOPM=0\r\n") != NULL)
	{
		if (sscanf(this->uart_buffer.rxBuffer, "SET SSTOPM=0\r\n%f\r\n", &this->operatingParameters.SSTOPM) == 1)
		{
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_setThermostatMode(st_Cryocooler *this)
{
	// Verificar si la cadena contiene "SET TSTATM=1\r\n" o "SET TSTATM=0\r\n"
	if (strstr(this->uart_buffer.rxBuffer, "SET TSTATM=1\r\n") != NULL)
	{
		if (sscanf(this->uart_buffer.rxBuffer, "SET TSTATM=1\r\n%f\r\n", &this->operatingParameters.TSTATM) == 1)
		{
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
	}
	else if (strstr(this->uart_buffer.rxBuffer, "SET TSTATM=0\r\n") != NULL)
	{
		if (sscanf(this->uart_buffer.rxBuffer, "SET TSTATM=0\r\n%f\r\n", &this->operatingParameters.TSTATM) == 1)
		{
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_setControlMode(st_Cryocooler *this)
{
	// Verificar si la cadena contiene "SET TSTATM=1\r\n" o "SET TSTATM=0\r\n"
	if (strstr(this->uart_buffer.rxBuffer, "SET PID=0\r\n") != NULL)
	{
		if (sscanf(this->uart_buffer.rxBuffer, "SET PID=0\r\n%f\r\n", &this->operatingParameters.PID) == 1)
		{
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
	}
	else if (strstr(this->uart_buffer.rxBuffer, "SET PID=2\r\n") != NULL)
	{
		if (sscanf(this->uart_buffer.rxBuffer, "SET PID=2\r\n%f\r\n", &this->operatingParameters.PID) == 1)
		{
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
	}
	else
	{
		cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
		cryocooler->state		= cryocooler_error;
	}
}

void cryocooler_setPowerOutput (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET PWOUT
	if (sscanf(this->uart_buffer.rxBuffer, "SET PWOUT=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.PWOUT = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void cryocooler_setMaxPowerLimit (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET MAX
	if (sscanf(this->uart_buffer.rxBuffer, "SET MAX=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.MAX = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void cryocooler_setMinPowerLimit (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET MIN
	if (sscanf(this->uart_buffer.rxBuffer, "SET MIN=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.MIN = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void cryocooler_setTarguetTemmperature (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET TTARGET
	if (sscanf(this->uart_buffer.rxBuffer, "SET TTARGET=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.TTARGET = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void cryocooler_setTemmperatureBand (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET TBAND
	if (sscanf(this->uart_buffer.rxBuffer, "SET TBAND=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.TBAND = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void cryocooler_setTemmperatureKp (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET KP
	if (sscanf(this->uart_buffer.rxBuffer, "SET KP=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.TEMP_KP = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void cryocooler_setTemmperatureKi (st_Cryocooler *this)
{
	float valueReceived;
	float valueSet;

	// Verificar y extraer el valor del comando SET KI
	if (sscanf(this->uart_buffer.rxBuffer, "SET KI=%f\r\n%f\r\n", &valueSet, &valueReceived) == 2)
	{
		if (valueSet == valueReceived)
		{
			this->operatingParameters.TEMP_KI = valueReceived;
			cryocooler->errorCode = CRYOCOOLER_ERROR_NONE;
		}
		else
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
		}
	}
}

void execute_command_action(char *received_command) {
	for (int i = 0; i < num_commands; i++)
	{
		if (strncmp(received_command, valid_commands[i], strlen(valid_commands[i])) == 0)
		{
			switch (i) {
			case GET_LOCK:
				cryocooler_getLockState(cryocooler);
				break;
			case SET_UNLOCK:
				cryocooler_UnlockParameters(cryocooler);
				break;
			case STATE:
				cryocooler_getOperatingParameters(cryocooler);
				break;
			case GET_ERROR:
				cryocooler_getErrorRegister(cryocooler);
				break;
			case TC:
				cryocooler_getTemperature(cryocooler);
				break;
			case P:
				cryocooler_getConsumedPower(cryocooler);
				break;
			case RESET_F:
				cryocooler_setDefaultParameters(cryocooler);
				break;
			case SET_SSTOPM:
				cryocooler_setSoftStopMode(cryocooler);
				break;
			case SET_TSTATM:
				cryocooler_setThermostatMode(cryocooler);
				break;
			case SET_PID:
				cryocooler_setControlMode(cryocooler);
				break;
			case SET_PWOUT:
				cryocooler_setPowerOutput(cryocooler);
				break;
			case SET_MAX:
				cryocooler_setMaxPowerLimit(cryocooler);
				break;
			case SET_MIN:
				cryocooler_setMinPowerLimit(cryocooler);
				break;
			case SET_TTARGET:
				cryocooler_setTarguetTemmperature(cryocooler);
				break;
			case SET_TBAND:
				cryocooler_setTemmperatureBand(cryocooler);
				break;
			case SET_KP:
				cryocooler_setTemmperatureKp(cryocooler);
				break;
			case SET_KI:
				cryocooler_setTemmperatureKi(cryocooler);
				break;
			case RESET_COMPLETE:
				cryocooler_setDefaultParameters(cryocooler);
				break;
			default:
				break;
			}
			break; // Comando encontrado, salimos del bucle
		}
		else if(strstr(received_command,"UNKNOWN COMMAND\r\n") != NULL)
		{
			cryocooler->errorCode 	= CRYOCOOLER_ERROR_INVALID_RESPONSE;
			cryocooler->state		= cryocooler_error;
			break;
		}
	}
	disconnectionTime = *cryocooler->millisecElapsed;
}

void cryocooler_initialization_StateMachine(void)
{
	if (cryocooler->rxComplete == no)
	{
		if (*cryocooler->millisecElapsed > (disconnectionTime + DEF_DISCONNECTION_TIME))
		{
			cryocooler->errorCode 	= CRYOCOOLER_DISCONNECTION_ERROR;
			cryocooler->state		= cryocooler_error;
			cryocooler->flag		= cryo_parameters_FAULT;
		}
		return;
	}
	if(cryocooler->operatingParameters.LOCK == cryo_parameters_UNLOCKED)
	{
		cryocooler->rxComplete = no; 					// Resetear flag de recepción completa previo al envio de los comandos

		switch (SM_initialization_state)
		{
		case INIT_STATE_RESET_CONTROLLER:
			RESET_CONTROLLER_PARAMETERS_TO_FACTORY_DEFAULTS();
			SM_initialization_state = INIT_STATE_SET_SOFT_STOP_MODE;
			break;
		case INIT_STATE_SET_SOFT_STOP_MODE:
			SET_SOFT_STOP_CONTROL_MODE(1);
			SM_initialization_state = INIT_STATE_SET_THERMOSTAT_MODE;
			break;
		case INIT_STATE_SET_THERMOSTAT_MODE:
			SET_THERMOSTAT_MODE(1);
			SM_initialization_state = INIT_STATE_SET_CONTROL_MODE;
			break;
		case INIT_STATE_SET_CONTROL_MODE:
			SET_CONTROL_MODE(0);
			SM_initialization_state = INIT_STATE_SET_TARGET_POWER_OUTPUT;
			break;
		case INIT_STATE_SET_TARGET_POWER_OUTPUT:
			SET_TARGET_POWER_OUTPUT(70);
			SM_initialization_state = INIT_STATE_SET_MINIMUM_POWER_OUTPUT;
			break;
		case INIT_STATE_SET_MINIMUM_POWER_OUTPUT:
			SET_USER_DEFINED_MINIMUM_POWER_OUTPUT(50.00);
			SM_initialization_state = INIT_STATE_SET_MAXIMUM_POWER_OUTPUT;
			break;
		case INIT_STATE_SET_MAXIMUM_POWER_OUTPUT:
			SET_USER_DEFINED_MAXIMUM_POWER_OUTPUT(240.00);
			SM_initialization_state = INIT_STATE_DISPLAY_OPERATING_STATE;
			break;
		case INIT_STATE_DISPLAY_OPERATING_STATE:
			DISPLAY_OPERATING_STATE();
			SM_initialization_state = INIT_STATE_DONE;
			break;
		case INIT_STATE_DONE:
			// Máquina de estados completa
			cryocooler->rxComplete = yes;
			cryocooler->state = cryocooler_OFF;
			break;
		default:
			break;
		}
	}
	else
	{
		UNLOCK_USER_LOCKABLE_COMMANDS(cryocooler->operatingParameters.PASS);
	}
}

void cryocooler_OFF_StateMachine(void)
{
	if (cryocooler->rxComplete == no)
	{
		if (*cryocooler->millisecElapsed > (disconnectionTime + DEF_DISCONNECTION_TIME))
		{
			cryocooler->errorCode 	= CRYOCOOLER_DISCONNECTION_ERROR;
			cryocooler->state		= cryocooler_error;
			cryocooler->flag		= cryo_parameters_FAULT;
		}
		return;
	}
	switch (SM_off_state)
	{
	case OFF_STATE_DISPLAY_ERROR_CODE:
		cryocooler->rxComplete = no; 					// Resetear flag de recepción completa previo al envio del comando
		DISPLAY_ERROR_CODE();
		SM_off_state = OFF_STATE_DISPLAY_COLD_TIP_TEMPERATURE;
		break;
	case OFF_STATE_DISPLAY_COLD_TIP_TEMPERATURE:
		cryocooler->rxComplete = no;
		DISPLAY_COLD_TIP_TEMPERATURE();
		SM_off_state = OFF_STATE_DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER;
		break;
	case OFF_STATE_DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER:
		cryocooler->rxComplete = no;
		DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER();
		SM_off_state = OFF_STATE_CHECK_PARAMETERS;
		break;
	case OFF_STATE_CHECK_PARAMETERS:
		if(cryocooler->flag == cryo_parameters_FAULT)
		{
			cryocooler->errorCode	= CRYOCOOLER_INTERNAL_ERROR;
			cryocooler->state		= cryocooler_error;
			SM_off_state			= OFF_STATE_CHECK_PARAMETERS;
		}
		else if(cryocooler->measurements.coldTipTemperature < MIN_TEMP_LIMIT || cryocooler->measurements.coldTipTemperature > MAX_TEMP_LIMIT)
		{
			cryocooler->errorCode	= CRYOCOOLER_TEMP_ERROR;
			cryocooler->state		= cryocooler_error;
			SM_off_state			= OFF_STATE_CHECK_PARAMETERS;
		}
		else if(cryocooler->measurements.coolerPowerConsumed > MAX_POWER_LIMIT )
		{
			cryocooler->errorCode	= CRYOCOOLER_PWR_ERROR;
			cryocooler->state		= cryocooler_error;
			SM_off_state			= OFF_STATE_CHECK_PARAMETERS;
		}
		else
		{
			cryocooler->errorCode	= CRYOCOOLER_ERROR_NONE;
			SM_off_state 			= OFF_STATE_DISPLAY_ERROR_CODE;
		}
		break;
	default:
		break;
	}
		// Debería avanzar por una acción externa
		//cryocooler->state = cryocooler_Start;
}

void cryocooler_ON_StateMachine(void)
{
	if (cryocooler->rxComplete == no)
	{
		if (*cryocooler->millisecElapsed > (disconnectionTime + DEF_DISCONNECTION_TIME))
		{
			cryocooler->errorCode 	= CRYOCOOLER_DISCONNECTION_ERROR;
			cryocooler->state		= cryocooler_error;
			cryocooler->flag		= cryo_parameters_FAULT;
		}
		return;
	}
	switch (SM_on_state)
	{
	case ON_STATE_DISPLAY_ERROR_CODE:
		cryocooler->rxComplete = no; 					// Resetear flag de recepción completa previo al envio del comando
		DISPLAY_ERROR_CODE();
		SM_on_state = ON_STATE_DISPLAY_COLD_TIP_TEMPERATURE;
		break;
	case ON_STATE_DISPLAY_COLD_TIP_TEMPERATURE:
		cryocooler->rxComplete = no;
		DISPLAY_COLD_TIP_TEMPERATURE();
		SM_on_state = ON_STATE_DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER;
		break;
	case ON_STATE_DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER:
		cryocooler->rxComplete = no;
		DISPLAY_COOLER_POWER_MEASURED_BY_CONTROLLER();
		SM_on_state = ON_STATE_CHECK_PARAMETERS;
		break;
	case ON_STATE_CHECK_PARAMETERS:
		if(cryocooler->flag == cryo_parameters_FAULT)/*cryocooler->errorRegister.byte != 0x00*/
		{
			cryocooler->errorCode	= CRYOCOOLER_INTERNAL_ERROR;
			cryocooler->state		= cryocooler_error;
			SM_on_state				= ON_STATE_CHECK_PARAMETERS;
		}
		else if(cryocooler->measurements.coldTipTemperature < MIN_TEMP_LIMIT || cryocooler->measurements.coldTipTemperature > MAX_TEMP_LIMIT)
		{
			cryocooler->errorCode	= CRYOCOOLER_TEMP_ERROR;
			cryocooler->state		= cryocooler_error;
			SM_on_state				= ON_STATE_CHECK_PARAMETERS;
		}
		else if(cryocooler->measurements.coolerPowerConsumed > MAX_POWER_LIMIT )
		{
			cryocooler->errorCode	= CRYOCOOLER_PWR_ERROR;
			cryocooler->state		= cryocooler_error;
			SM_on_state				= ON_STATE_CHECK_PARAMETERS;
		}
		else
		{
			cryocooler->errorCode	= CRYOCOOLER_ERROR_NONE;
			SM_on_state				= ON_STATE_DISPLAY_COLD_TIP_TEMPERATURE;
		}
		break;
	default:
		break;
	}
	// Debería avanzar por una acción externa
	//cryocooler->state = cryocooler_Stop;
}


void cryocooler_ERROR_StateMachine(void)
{
	switch (cryocooler->errorCode)
	{
		case CRYOCOOLER_TEMP_ERROR:	// Cold-tip temperature out of range
//			turn_off_cryocooler(cryocooler);
			if(cryocooler->measurements.coldTipTemperature < MIN_TEMP_LIMIT)
			{

			}
			else if(cryocooler->measurements.coldTipTemperature > MAX_TEMP_LIMIT)
			{

			}
			resendCommand();
			break;
		case CRYOCOOLER_PWR_ERROR:	// Power limitation exceeded
			turn_off_cryocooler(cryocooler);
			resendCommand();
			break;
		case CRYOCOOLER_INTERNAL_ERROR:
			if(cryocooler->errorRegister.bits.OverCurrent != no)
			{
				// If the controller detects an overcurrent, it will immediately shut off power to the cryocooler.
				turn_off_cryocooler(cryocooler);
				cryocooler->state = cryocooler_OFF;

			}
			else if((cryocooler->errorRegister.byte & 0b00111110) != no)
			{
				// Power cycle the controller
				turn_off_cryocooler(cryocooler);
				cryocooler->state = cryocooler_OFF;
			}
			break;
		case CRYOCOOLER_ERROR_INVALID_RESPONSE:	//Try to forward command
			resendCommand();
			break;
		case CRYOCOOLER_DISCONNECTION_ERROR:	//Try to forward command
			resendCommand();
			break;
		case CRYOCOOLER_ERROR_NONE:
			cryocooler->flag  = cryo_parameters_OK;
			cryocooler->state = cryocooler_OFF;
			break;
	}


}
/***********************************************************************
 *						PUBLIC FUNCTIONS
 ***********************************************************************/

CRYOCOOLER_ERR cryocooler_Init(st_Cryocooler *this)
{
	this->functions=&cryocoolerFunc;

	/* Init Soft-Stop Pin: */
	this->soft_stop_pin=digital_output_config_InitPhyDigitalOutput(ss_pin);
	this->functions->init_output(this->soft_stop_pin);

	/* UART initialization: */
	this->communicationPort = uart_config_InitPhyUart(uart_comm);
	this->communicationPort->uart->uart_config->rxBuffer=(uint8_t *)&this->uart_buffer.rxBuffer;
	this->communicationPort->uart->uart_phy.RxXferSize= sizeof(this->uart_buffer.rxBuffer);
	this->communicationPort->uart->uart_config->txBuffer=(uint8_t *)&this->uart_buffer.txBuffer;
	this->communicationPort->uart->uart_phy.TxXferSize= sizeof(this->uart_buffer.txBuffer);
	this->functions->init_uart(this->communicationPort);

	/*Default parameters*/
	this->operatingParameters=DefaultParameters;
	this->errorRegister.byte=0x00;
	this->rxComplete=yes;
	//Cryocooler initial condition: stopped
	turn_off_cryocooler(this);
//
//	/*copy handler*/
	cryocooler=this;
//
//	//Clean Rx buffer and Tx Pointer
	cryocooler->communicationPort->uart->uart_phy.pTxBuffPtr=NULL;
	cryocooler->communicationPort->uart->uart_phy.TxXferSize =0;
	memset(cryocooler->uart_buffer.rxBuffer,'\0', sizeof(cryocooler->uart_buffer.rxBuffer));
	cryocooler->functions->receive_uart(cryocooler->communicationPort);

//	/*Check lockable commands state*/
	DISPLAY_USER_LOCK_STATE();
	cryocooler->state = cryocooler_initialization;

	return CRYOCOOLER_ERROR_NONE;
}

void cryocoolerStateMachine(void)
{
	switch (cryocooler->state)
	{
	case cryocooler_initialization:
		cryocooler_initialization_StateMachine();
		break;
	case cryocooler_OFF:
		cryocooler_OFF_StateMachine();
		break;
	case cryocooler_Start:
		turn_on_cryocooler(cryocooler);
		cryocooler->state = cryocooler_ON;
		break;
	case cryocooler_ON:
		cryocooler_ON_StateMachine();
		break;
	case cryocooler_Stop:
		turn_off_cryocooler(cryocooler);
		cryocooler->state = cryocooler_OFF;
		break;
	case cryocooler_error:
		cryocooler_ERROR_StateMachine();
		break;
	}
}
