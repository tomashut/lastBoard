/*
 * basicUART.h
 *
 *  Created on: 14 ago. 2020
 *      Author: Laptop-Dell
 */

#ifndef FDX_LIBS_BASICUART_H_
#define FDX_LIBS_BASICUART_H_

#include "hardwareConfig.h"
#include "typdef_basicLib.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#include "fsl_uart.h"
#include "clock_config.h"
#elif ARCHITECTURE == STM32F4xx
#include "basicPin.h"
#endif

#define RX_TX_BUFF_SIZE	500

typedef enum UART_ERR_T
{
	UART_ERROR_NONE = 0,
	UART_ERROR,
	UART_INIT_ERROR,
	UART_TRANSMIT_ERROR,
	UART_RECEIVE_ERROR

}UART_ERR;

/************************************************************************/
/*					UART PHYSICAL STRUCTURE								*/
/************************************************************************/
typedef struct uart_phy{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	uart_config_t uartConfig;
	PORT_Type *Port_Pin;
	port_mux_t portmux_select;
	GPIO_Type *GPIO_Pin;			//puerto del pin
	pinNumber numberPinRX;			//numero del pin
	pinNumber numberPinTX;			//numero del pin
	clock_ip_name_t clockName;
	UART_Type *UART;
	uint32_t srcClock_Hz;
	IRQn_Type IRQn;
	hasInterrupt hasIRQ;
	st_uart_buffer buffer;
#elif ARCHITECTURE == STM32F4xx
	GPIO_TypeDef		GPIOn	;		// Selection of the GPIO to use
	st_pin				rxPin	;		// Rx pin selected
	st_pin				txPin	;		// Tx pin selected
	UART_HandleTypeDef  handlerUART	;	// Pointer to UART controller
	uint8_t 			*pTxBuffPtr	;	// Pointer to UART Tx transfer Buffer
	uint16_t 			TxXferSize	;	// UART Tx Transfer size
	uint8_t 			*pRxBuffPtr	;	// Pointer to UART Rx transfer Buffer
	uint16_t 			RxXferSize	;	// UART Rx Transfer size
	uint32_t 			timeout		;	// Timeout duration.
	IRQn_Type 			IRQn		;	// Global Interrupt Number
#endif
}st_uart_phy;

/************************************************************************/
/*					UART BASIC CONFIG									*/
/************************************************************************/
typedef struct basicConfig{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	enum_uarts uart_n;
	uint32_t baudrate;
	enum_gpio enum_GPIO;				//enumaracion del gpio donde esta el pin
	pinNumber numberPinRX;				//nuemro de pin dentro del puerto
	pinNumber numberPinTX;
	hasInterrupt has_interrupt;
	port_mux_t mux_select;
	void (*onInterrupt)(uint8_t);
	uint8_t *rxBuffer;
	uint8_t *txBuffer;
#elif ARCHITECTURE == STM32F4xx
/******************* GPIO Config *******************/
	st_pin_config			rxPin_config	;
	st_pin_config			txPin_config	;
	enum_uarts				uartNum			;	// Selection of the UART to use
	uint32_t 				baudrate		;	// UART communication baud rate
	enum_uart_word_lenth	wordLength		;	// The number of data bits transmitted or received in a frame
	enum_uart_parity		parity			;	// The parity mode
	enum_uart_stopBits		stopBits		;	// The number of stop bits transmitted
	enum_uart_hfc			hwFlowControl	;	// The hardware flow control mode is enabled or disabled
	enum_uart_modes			mode			;	// The Receive or Transmit mode is enabled or disabled
	enum_uart_oversampling	oversampling	;	// The Over sampling 8 is enabled or disabled
	uint8_t					*rxBuffer		;	// Pointer to UART Rx transfer Buffer
	uint8_t					*txBuffer		;	// Pointer to UART Tx transfer Buffer
	hasInterrupt 			has_interrupt	;	// Set global interrupt
	uint32_t				timeout			;	// Timeout duration
#endif
}st_uart_config;

/************************************************************************/
/*					UART FNCTIONS STRUCTURE								*/
/************************************************************************/
typedef struct uart_functions{
	UART_ERR (*init)	(st_uart_phy *, st_uart_config *);
	UART_ERR (*receive)	(st_uart_phy *);
	UART_ERR (*send)	(st_uart_phy *, uint32_t);
	state	 (*pinInit)	(st_pin_phy *, st_pin_config *);
}st_uart_functions;

/************************************************************************/
/*						BASIC UART STRUCTURE							*/
/************************************************************************/
typedef struct basicUART{
	st_uart_config		*uart_config;
	st_uart_phy			uart_phy;
	st_uart_functions	uart_func;
}st_uart;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

UART_ERR basicUart_InstallFunctions(st_uart *);

#endif /* FDX_LIBS_BASICUART_H_ */
