/*
 * uart_config.c
 *
 *  Created on: 18 ago. 2020
 *      Author: Laptop-Dell
 */


#include <uart_config.h>

/*********** CONFIGURACION DE UARTS EN SISTEMA **********/
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
st_uart_config UART_config[eunm_uart_inSystem] = {
		//UART MODBUS
		{	.uart_n = enum_uart3,
				.baudrate = 19200,
				.enum_GPIO = enum_gpioC,
				.numberPinRX = pin16,
				.numberPinTX = pin17,
				.has_interrupt = yes,
				.mux_select = kPORT_MuxAlt3,
				.onInterrupt = NULL,
				.rxBuffer = NULL,
				.txBuffer = NULL
		},
		{//UART SIM7000
				.uart_n = enum_uart4,
				.baudrate = 115200,
				.enum_GPIO = enum_gpioE,
				.numberPinRX = pin25,
				.numberPinTX = pin24,
				.has_interrupt = yes,
				.mux_select = kPORT_MuxAlt3,
				.onInterrupt = NULL,
				.rxBuffer = NULL,
				.txBuffer = NULL
		},
		{//ESP32
				.uart_n = enum_uart2,
				.baudrate = 115200,
				.enum_GPIO = enum_gpioD,
				.numberPinRX = pin2,
				.numberPinTX = pin3,
				.has_interrupt = yes,
				.mux_select = kPORT_MuxAlt3,
				.onInterrupt = NULL,
				.rxBuffer = NULL,
				.txBuffer = NULL
		}
};
#elif ARCHITECTURE == STM32F4xx
st_uart_config UART_config[eunm_uart_inSystem]={
#if BOARD == DEFROSTER_BOARD
		{
			.rxPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin1,
					.Mode		= alternate_push_pull,
					.Pull		= noPull,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_8,
					.logic		= positiva
			},
			.txPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin0,
					.Mode		= alternate_push_pull,
					.Pull		= noPull,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_8,
					.logic		= positiva
			},
			.uartNum		= enum_uart4,
			.baudrate		= 9600,
			.mode			= rx_tx_mode,
			.stopBits		= stopbits_1,
			.wordLength		= wordlength8B,
			.parity			= parity_none,
			.hwFlowControl	= hwcontrol_none,
			.oversampling	= oversampling_16,
			.timeout		= 1000,
			.txBuffer		= NULL,
			.rxBuffer		= NULL,
			.has_interrupt	= no
		}
#elif BOARD == FROSTER_BOARD
		{
			.rxPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin1,
					.Mode		= alternate_push_pull,
					.Pull		= noPull,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_8,
					.logic		= positiva
			},
			.txPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin0,
					.Mode		= alternate_push_pull,
					.Pull		= noPull,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_8,
					.logic		= positiva
			},
			.uartNum		= enum_uart4,
			.baudrate		= 600,
			.mode			= rx_tx_mode,
			.stopBits		= stopbits_1,
			.wordLength		= wordlength8B,
			.parity			= parity_none,
			.hwFlowControl	= hwcontrol_none,
			.oversampling	= oversampling_16,
			.timeout		= 5000,
			.txBuffer		= NULL,
			.rxBuffer		= NULL,
			.has_interrupt	= yes
		},
		{
			.rxPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin3,
					.Mode		= alternate_push_pull,
					.Pull		= pullDown,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_7,
					.logic		= positiva
			},
			.txPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin2,
					.Mode		= alternate_push_pull,
					.Pull		= noPull,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_7,
					.logic		= positiva
			},
			.uartNum		= enum_usart2,
			.baudrate		= 4800,
			.mode			= rx_tx_mode,
			.stopBits		= stopbits_1,
			.wordLength		= wordlength8B,
			.parity			= parity_none,
			.hwFlowControl	= hwcontrol_none,
			.oversampling	= oversampling_16,
			.timeout		= HAL_MAX_DELAY,
			.txBuffer		= NULL,
			.rxBuffer		= NULL,
			.has_interrupt	= yes
		}
#elif BOARD == DAQ_BOARD
		{
			.rxPin_config={
					.enum_GPIO	= enum_gpioA,
					.Pin		= pin1,
					.Mode		= alternate_push_pull,
					.Pull		= noPull,
					.Speed		= speed_freq_very_high,
					.Alternate	= alternate_function_8,
					.logic		= positiva
			},
					.txPin_config={
							.enum_GPIO	= enum_gpioA,
							.Pin		= pin0,
							.Mode		= alternate_push_pull,
							.Pull		= noPull,
							.Speed		= speed_freq_very_high,
							.Alternate	= alternate_function_8,
							.logic		= positiva
			},
			.uartNum		= enum_uart4,
			.baudrate		= 9600,
			.mode			= rx_tx_mode,
			.stopBits		= stopbits_1,
			.wordLength		= wordlength8B,
			.parity			= parity_none,
			.hwFlowControl	= hwcontrol_none,
			.oversampling	= oversampling_16,
			.timeout		= 1000,
			.txBuffer		= NULL,
			.rxBuffer		= NULL,
			.has_interrupt	= no
		}
#endif
};
#endif

st_uart UartsOnSystem[eunm_uart_inSystem];
st_uart_module Uart_module[eunm_uart_inSystem];

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

st_uart_config *uart_GetConfig(uint32_t index){
	return &UART_config[index];
}

uint32_t uart_Init(st_uart_module *this)
{
	basicUart_InstallFunctions(this->uart);
	this->uart->uart_phy.rxPin.pin_config = &this->uart->uart_config->rxPin_config;
	this->uart->uart_phy.txPin.pin_config = &this->uart->uart_config->txPin_config;

	this->uart->uart_func.pinInit(&this->uart->uart_phy.rxPin.pin_phy,this->uart->uart_phy.rxPin.pin_config);
	this->uart->uart_func.pinInit(&this->uart->uart_phy.txPin.pin_phy,this->uart->uart_phy.txPin.pin_config);

	if(this->uart->uart_func.init(&this->uart->uart_phy, this->uart->uart_config) != UART_ERROR_NONE)
	{
		return -1;
	}
	return 0;
}
uint32_t uart_receive(st_uart_module *this){
	this->uart->uart_func.receive(&this->uart->uart_phy);
	return 0;
}
uint32_t uart_send(st_uart_module *this, uint32_t len){
	this->uart->uart_func.send(&this->uart->uart_phy, len);
	return 0;
}

st_uart_module *uart_config_InitPhyUart(uint32_t index){
	st_uart_module *this = &Uart_module[index];

	UartsOnSystem[index].uart_config = uart_GetConfig(index);
	this->uart = &UartsOnSystem[index];
	return this;
}
