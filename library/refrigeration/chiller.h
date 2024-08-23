/*
 * chiller.h
 *
 *  Created on: May 8, 2024
 *      Author: Usuario
 */

#ifndef LIBRARY_REFRIGERATION_CHILLER_H_
#define LIBRARY_REFRIGERATION_CHILLER_H_

#include "uart_config.h"
#include "co_core.h"

#define RXBUFFERSIZE_CHILLER 16
#define TXBUFFERSIZE_CHILLER 16


typedef enum FSCH027Z24BT_ERR_T{
	FSCH027Z24BT_ERROR_NONE,
	FSCH027Z24BT_INIT_ERROR,
	FSCH027Z24BT_UART_ERROR,
	FSCH027Z24BT_errorInSystem
}FSCH027Z24BT_ERR;

typedef enum FSCH027Z24BT_FLAGS{
	troubleCode_ok,
	overcurrent_error,
	overvoltage_error,
	undervoltage_error,
	lack_phase_error,
	lose_speed_error,
	hw_oc_protection_error,
	phase_current_anomaly_error
}FSCH027Z24BT_FLAG;

typedef enum{
	FSCH027Z24BT_initialization,
	FSCH027Z24BT_sleepMode,
	FSCH027Z24BT_measurement,
	FSCH027Z24BT_error
}FSCH027Z24BT_SM_states;

typedef struct FSCH027Z24BT_Functions{
	uint32_t (*init_uart)	(st_uart_module *);
	uint32_t (*receive_uart)(st_uart_module *);
	uint32_t (*send_uart)	(st_uart_module *, uint32_t);
}st_FSCH027Z24BT_func;

typedef struct buffer_UART_chiller{
	uint8_t rxBuffer[RXBUFFERSIZE_CHILLER];	//buffer de recepcion
	uint8_t txBuffer[TXBUFFERSIZE_CHILLER];	//buffer de transmision
}st_buffer_UART_chiller;

typedef struct FSCH027Z24BT_Params{

}st_FSCH027Z24BT_params;

typedef union{
	struct{
		uint8_t	overcurrent:1;
		uint8_t overvoltage:1;
		uint8_t undervoltage:1;
		uint8_t lack_phase:1;
		uint8_t lose_speed:1;
		uint8_t hardware_oc_protection:1;
		uint8_t phase_current_anomaly:1;
	}bits;
	uint8_t byte;
}st_troubleCode;

typedef struct FSCH027Z24BT_masterData{
	uint8_t		startCommunication;
	uint8_t		masterID;
	uint8_t		instruction;
	uint16_t	speed;
	//Reserve
	uint8_t		setTemperature;
	uint8_t		protectionVoltage;
	//Faltan 6 bytes vacios
	uint8_t		checksum;
	uint8_t		endCommunication;
}st_FSCH027Z24BT_masterData;

typedef struct FSCH027Z24BT_slaveData{
	uint8_t			startCommunication;
	uint8_t			slaveID;
	uint16_t		compressorSpeed;
	uint16_t		compressorCurrent;
	uint16_t		busbarVoltage;
	uint8_t			radiatorTemperature;  //Reserve
	st_troubleCode	troubleCode; /*Bit0: overcurrent Bit1: over-volt Bit2: under-volt Bit3: Lack phase Bit4: lose speed Bit5: Hardware Overcurrent Protection Bit6: Phase current anomaly*/
	uint8_t			temperature1;
	uint8_t			mosfetTemperature; //0-120
	//0x00
	uint8_t			read_faultUnit;
	uint8_t			checksum;
	uint8_t			endCommunication;
}st_FSCH027Z24BT_slaveData;


typedef struct FSCH027Z24BT{
	st_uart_module	 			*uart_port;
	st_buffer_UART_chiller		bufferUart;
	//	st_uart						*uart;
	uint8_t						data[16];
	st_FSCH027Z24BT_params		Params;
	st_FSCH027Z24BT_func		*FSCH027Z24BT_function;
//	FSCH027Z24BT_SM_states		FSCH027Z24BT_state;
	FSCH027Z24BT_FLAG			flag;
//	FSCH027Z24BT_ERR			FSCH027Z24BT_errorCode;
	st_FSCH027Z24BT_masterData	FSCH027Z24BT_master;
	st_FSCH027Z24BT_slaveData	FSCH027Z24BT_slave;
	CO_NODE						*node;
	bool						txEnable;
	bool						rxComplete;
}st_FSCH027Z24BT;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

FSCH027Z24BT_ERR 	FSCH027Z24BT_init			(st_FSCH027Z24BT *this);
FSCH027Z24BT_ERR 	FSCH027Z24BT_sendFrame		(st_FSCH027Z24BT *this);
FSCH027Z24BT_ERR	FSCH027Z24BT_receiveFrame	(st_FSCH027Z24BT *this);
FSCH027Z24BT_ERR 	FSCH027Z24BT_stop			(st_FSCH027Z24BT *this);
void				send_configChiller			(void);
void 				read_ChillerResponse		(void);
#endif /* LIBRARY_REFRIGERATION_CHILLER_H_ */
