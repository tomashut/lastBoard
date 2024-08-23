/*
 * chiller.c
 *
 *  Created on: May 8, 2024
 *      Author: Usuario
 */
#include <chiller.h>

#define START_COMMUNICATION 0xAA
#define END_COMMUNICATION 0x55
#define SLAVE_ID 0x01
enum{
	uart_debug=enum_uart_inSystem_0
};
st_FSCH027Z24BT *chiller;
st_FSCH027Z24BT_masterData default_masterConfig ={
		.startCommunication = 0xAA,
		.masterID 			= 0x00,
		.instruction		= 0x01,
		.speed				= 1700,
		//reserve
		.setTemperature		= 0x00,
		.protectionVoltage	= 0x00,
		//6bytes faltantes
		.checksum			= 0x00,
		.endCommunication	= 0x55
};

st_FSCH027Z24BT_func FSCH027Z24BT_Functions ={
		.init_uart			 = &uart_Init,
		.send_uart			 = &uart_send,
		.receive_uart        = &uart_receive,
};

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void read_ChillerResponse(void){
	if(chiller->bufferUart.rxBuffer[0] ==0xAA && chiller->bufferUart.rxBuffer[1] ==0x01 && chiller->bufferUart.rxBuffer[15] ==0x55)
	{
		chiller->FSCH027Z24BT_slave.startCommunication 		= chiller->bufferUart.rxBuffer[0];
		chiller->FSCH027Z24BT_slave.slaveID			 		= chiller->bufferUart.rxBuffer[1];
		chiller->FSCH027Z24BT_slave.compressorSpeed	 		= (uint16_t)((chiller->bufferUart.rxBuffer[3] << 8)|chiller->bufferUart.rxBuffer[2]);
		chiller->FSCH027Z24BT_slave.compressorCurrent		= (uint16_t)((chiller->bufferUart.rxBuffer[5] << 8)|chiller->bufferUart.rxBuffer[4]);
		chiller->FSCH027Z24BT_slave.busbarVoltage			= (uint16_t)((chiller->bufferUart.rxBuffer[7] << 8)|chiller->bufferUart.rxBuffer[6]);
		chiller->FSCH027Z24BT_slave.radiatorTemperature 	= chiller->bufferUart.rxBuffer[8];
		chiller->FSCH027Z24BT_slave.troubleCode.byte		= chiller->bufferUart.rxBuffer[9];
		chiller->FSCH027Z24BT_slave.temperature1			= chiller->bufferUart.rxBuffer[10];
		chiller->FSCH027Z24BT_slave.mosfetTemperature		= chiller->bufferUart.rxBuffer[11];
		chiller->FSCH027Z24BT_slave.read_faultUnit			= chiller->bufferUart.rxBuffer[13];
		chiller->FSCH027Z24BT_slave.checksum				= chiller->bufferUart.rxBuffer[14];
		chiller->FSCH027Z24BT_slave.endCommunication		= chiller->bufferUart.rxBuffer[15];
	}

	chiller->FSCH027Z24BT_function->receive_uart(chiller->uart_port);

	chiller->rxComplete = 1;
}
void FSCH027Z24BT_setConfigFrame(st_FSCH027Z24BT *this)
{
	this->bufferUart.txBuffer[0]	= this->FSCH027Z24BT_master.startCommunication;
	this->bufferUart.txBuffer[1]	= this->FSCH027Z24BT_master.masterID;
	this->bufferUart.txBuffer[2]	= this->FSCH027Z24BT_master.instruction;
	this->bufferUart.txBuffer[3]	= (uint8_t)this->FSCH027Z24BT_master.speed;
	this->bufferUart.txBuffer[4]	= (uint8_t)(this->FSCH027Z24BT_master.speed >> 8);
	this->bufferUart.txBuffer[5]	= 0x00; //reserved
	this->bufferUart.txBuffer[6]	= this->FSCH027Z24BT_master.setTemperature;
	this->bufferUart.txBuffer[7]	= this->FSCH027Z24BT_master.protectionVoltage;
	this->bufferUart.txBuffer[8]	= 0x00;
	this->bufferUart.txBuffer[9]	= 0x00;
	this->bufferUart.txBuffer[10]	= 0x00;
	this->bufferUart.txBuffer[11]	= 0x00;
	this->bufferUart.txBuffer[12]	= 0x00;
	this->bufferUart.txBuffer[13]	= 0x00;
	this->FSCH027Z24BT_master.checksum = 0;
	for (int i = 1; i < 14; ++i) {
		this->FSCH027Z24BT_master.checksum += this->bufferUart.txBuffer[i];
	}
	this->bufferUart.txBuffer[14]	= (~(this->FSCH027Z24BT_master.checksum))+1;
	this->bufferUart.txBuffer[15]	= this->FSCH027Z24BT_master.endCommunication;
}

FSCH027Z24BT_ERR FSCH027Z24BT_sendFrame(st_FSCH027Z24BT *this)
{
	this->bufferUart.txBuffer[0]	= this->FSCH027Z24BT_master.startCommunication;
	this->bufferUart.txBuffer[1]	= this->FSCH027Z24BT_master.masterID;
	this->bufferUart.txBuffer[2]	= this->FSCH027Z24BT_master.instruction;
	this->bufferUart.txBuffer[3]	= (uint8_t)this->FSCH027Z24BT_master.speed;
	this->bufferUart.txBuffer[4]	= (uint8_t)(this->FSCH027Z24BT_master.speed >> 8);
	this->bufferUart.txBuffer[5]	= 0x00; //reserved
	this->bufferUart.txBuffer[6]	= this->FSCH027Z24BT_master.setTemperature;
	this->bufferUart.txBuffer[7]	= this->FSCH027Z24BT_master.protectionVoltage;
	this->bufferUart.txBuffer[8]	= 0x00;
	this->bufferUart.txBuffer[9]	= 0x00;
	this->bufferUart.txBuffer[10]	= 0x00;
	this->bufferUart.txBuffer[11]	= 0x00;
	this->bufferUart.txBuffer[12]	= 0x00;
	this->bufferUart.txBuffer[13]	= 0x00;
	this->FSCH027Z24BT_master.checksum = 0;
	for (int i = 1; i < 14; ++i) {
		this->FSCH027Z24BT_master.checksum += this->bufferUart.txBuffer[i];
	}
	this->bufferUart.txBuffer[14]	= (~(this->FSCH027Z24BT_master.checksum))+1;
	this->bufferUart.txBuffer[15]	= this->FSCH027Z24BT_master.endCommunication;

	if (this->FSCH027Z24BT_function->send_uart(this->uart_port,TXBUFFERSIZE_CHILLER) != 0)
	{
		return FSCH027Z24BT_UART_ERROR;
	}

	HAL_Delay(1000);

	return FSCH027Z24BT_ERROR_NONE;
}

void FSCH027Z24BT_setInstruction(st_FSCH027Z24BT *this)
{
	//	CODictRdWord(&this->node->Dict, , &this->FSCH027Z24BT_master.instruction);
	this->bufferUart.txBuffer[2]=this->FSCH027Z24BT_master.instruction;
}

void FSCH027Z24BT_setSpeed(st_FSCH027Z24BT *this)
{
	//	CODictRdWord(&this->node->Dict, DICT_CHILLER_C_SPEED, &this->FSCH027Z24BT_master.speed);
	this->bufferUart.txBuffer[3]=(uint8_t)this->FSCH027Z24BT_master.speed;
	this->bufferUart.txBuffer[4]=(uint8_t)this->FSCH027Z24BT_master.speed >> 8;
}
void FSCH027Z24BT_setTemperature(st_FSCH027Z24BT *this){
	//	CODictRdByte(&this->node->Dict, DICT_CHILLER_TEMPERATURE, &this->FSCH027Z24BT_master.setTemperature);
	this->bufferUart.txBuffer[6]=this->FSCH027Z24BT_master.setTemperature;

}
FSCH027Z24BT_ERR FSCH027Z24BT_init(st_FSCH027Z24BT *this){

	this->FSCH027Z24BT_function = &FSCH027Z24BT_Functions;

	this->uart_port = uart_config_InitPhyUart(uart_debug);
	this->uart_port->uart->uart_config->rxBuffer = (uint8_t *)&this->bufferUart.rxBuffer;
	this->uart_port->uart->uart_phy.RxXferSize= RXBUFFERSIZE_CHILLER;
	this->uart_port->uart->uart_config->txBuffer = (uint8_t *)&this->bufferUart.txBuffer;
	this->uart_port->uart->uart_phy.TxXferSize= TXBUFFERSIZE_CHILLER;
	if (this->FSCH027Z24BT_function->init_uart(this->uart_port) != 0){
		return FSCH027Z24BT_INIT_ERROR;
	}
	this->FSCH027Z24BT_master=default_masterConfig;
	chiller=this;
	chiller->FSCH027Z24BT_function->receive_uart(chiller->uart_port);
	FSCH027Z24BT_setConfigFrame(chiller);
	FSCH027Z24BT_sendFrame(chiller);

	return FSCH027Z24BT_ERROR_NONE;
}

FSCH027Z24BT_ERR FSCH027Z24BT_stop (st_FSCH027Z24BT *this)
{
	this->FSCH027Z24BT_master=default_masterConfig;
	FSCH027Z24BT_setConfigFrame(this);
	return FSCH027Z24BT_ERROR_NONE;
}
FSCH027Z24BT_ERR FSCH027Z24BT_receiveFrame(st_FSCH027Z24BT *this)
{
	if (this->FSCH027Z24BT_function->receive_uart(this->uart_port) != 0)
	{
		return FSCH027Z24BT_UART_ERROR;
	}
	return FSCH027Z24BT_ERROR_NONE;

}

void send_configChiller(void)
{
	//	FSCH027Z24BT_setSpeed(chiller);
	//	FSCH027Z24BT_setTemperature(chiller);
	//	FSCH027Z24BT_setInstruction(chiller);
	//	FSCH027Z24BT_sendFrame(chiller);
}
