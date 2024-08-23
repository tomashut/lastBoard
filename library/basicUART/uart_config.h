/*
 * uart_config.h
 *
 *  Created on: 18 ago. 2020
 *      Author: Laptop-Dell
 */

#ifndef FDX_LIBS_UART_CONFIG_H_
#define FDX_LIBS_UART_CONFIG_H_

#include "basicUART.h"

enum{
#if BOARD == DEFROSTER_BOARD
	enum_uart_inSystem_0,
#elif BOARD == FROSTER_BOARD
	enum_uart_inSystem_0,
	enum_uart_inSystem_1,
#elif BOARD == DAQ_BOARD
	enum_uart_inSystem_0,
#endif
	eunm_uart_inSystem
};

typedef struct uart_module{
	st_uart *uart;
}st_uart_module;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

uint32_t 		uart_Init						(st_uart_module *);
uint32_t 		uart_receive					(st_uart_module *);
uint32_t 		uart_send						(st_uart_module *, uint32_t);
st_uart_module *uart_config_InitPhyUart			(uint32_t);

#endif /* FDX_LIBS_UART_CONFIG_H_ */
