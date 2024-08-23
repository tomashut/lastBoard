/*
 * basicCAN.h
 *
 *  Created on: Apr 3, 2024
 *      Author: CRINSURANCE 1
 */

#ifndef LIBRARY_BASICCAN_BASICCAN_H_
#define LIBRARY_BASICCAN_BASICCAN_H_

#include "hardwareConfig.h"
#include "typdef_basicLib.h"
//#include "basicPin.h"
#include "digital_outputs_config.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "stm32f4xx_hal_can.h"
//#elif defined(OTHER)
#else

#endif

//Definition of CAN Error. Used for all architectures :
typedef enum CAN_ERR_T
{
	CAN_ERROR_NONE=0,
	CAN_INIT_ERROR,
	CAN_ERROR,
	CAN_BUSY,
	CAN_TRANSMIT_ERROR,
	CAN_RECEIVE_ERROR
}CAN_ERR;

typedef enum{
	can_1,
	can_2,
	can_3
}enum_can;

typedef enum{
	can_normalMode,
	can_LoopBackMode,
	can_SilentMode,
	can_SilentLoopbackMode
}enum_can_mode;

typedef enum{
	can_sjw_1tq,
	can_sjw_2tq,
	can_sjw_3tq,
	can_sjw_4tq
}enum_can_SyncJumpWidth;

typedef enum{
	can_bs1_1tq,
	can_bs1_2tq,
	can_bs1_3tq,
	can_bs1_4tq,
	can_bs1_5tq,
	can_bs1_6tq,
	can_bs1_7tq,
	can_bs1_8tq,
	can_bs1_9tq,
	can_bs1_10tq,
	can_bs1_11tq,
	can_bs1_12tq,
	can_bs1_13tq,
	can_bs1_14tq,
	can_bs1_15tq,
	can_bs1_16tq
}enum_can_TimeSeg1;

typedef enum{
	can_bs2_1tq,
	can_bs2_2tq,
	can_bs2_3tq,
	can_bs2_4tq,
	can_bs2_5tq,
	can_bs2_6tq,
	can_bs2_7tq,
	can_bs2_8tq
}enum_can_TimeSeg2;

typedef enum{
	can_filter_disable,
	can_filter_enable
}can_filter_state;

typedef enum{
	can_fifo0,
	can_fifo1
}can_fifo_assignment;

typedef enum{
	can_filterMode_IDMask,
	can_filterMode_IDList
}can_filter_mode;

typedef enum{
	can_filterScale_16bits,
	can_filterScale_32bits
}can_filter_scale;

typedef enum{
	can_tx_IRQn,
	can_rx0_IRQn,
	can_rx1_IRQn,
	can_sce_IRQn
}can_interrupts;

typedef enum{
	/* Transmit Interrupt */
	can_it_tx_mailbox_empty,
	/* Receive Interrupts */
	can_it_rx_fifo0_msg_pending,
	can_it_rx_fifo0_full,
	can_it_rx_fifo0_overrun,
	can_it_rx_fifo1_msg_pending,
	can_it_rx_fifo1_full,
	can_it_rx_fifo1_overrun,
	/* Operating Mode Interrupts */
	can_it_wakeup,
	can_it_sleep_ack,
	/* Error Interrupts */
	can_it_error_warning,
	can_it_error_passive,
	can_it_busoff,
	can_it_last_error_code,
	can_it_error
}IT_notification;
/****************************************************************************/
/* 						CAN PHYSICAL STRUCTURE 								*/
/****************************************************************************/
typedef struct can_phy
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	CAN_HandleTypeDef 		handlerCan  	;      	// CAN controller.
	CAN_FilterTypeDef		canFilterConfig	;
	CAN_TxHeaderTypeDef		txHeader		;
	uint8_t					txData[8]		;
	uint32_t				txMailBox		;
	CAN_RxHeaderTypeDef		rxHeader		;
	uint8_t					rxData[8]		;
	uint8_t					rxFIFO			;
	GPIO_TypeDef			GPIOn			;	// Selection of the GPIO to use
	st_pin					txPin			;
	st_pin					rxPin			;
	IRQn_Type				canIRQn			;
	uint32_t				activeITs		;

//#elif defined(OTHER)
#else
#endif
}st_canPhy;

/****************************************************************************/
/* 					BASIC CONFIGURATION STRUCTURE 							*/
/****************************************************************************/
typedef struct can_config
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
/******************* GPIO Config *******************/
	st_pin_config				rxPin_config		;
	st_pin_config				txPin_config		;
/******************* CAN Handler *******************/
	enum_can					canNum		 		;
	uint32_t	 				prescaler	 		;
	enum_can_mode				mode		 		;
	enum_can_SyncJumpWidth		syncJumpWidth		;
	enum_can_TimeSeg1			timeSeg1	 		;
	enum_can_TimeSeg2			timeSeg2	 		;
/******************* CAN Filter ********************/
	can_filter_state			filter_On_Off		;
	uint32_t					filterBank			;
	can_fifo_assignment			filterFIFOx			;
	uint32_t					filterIdHigh		;
	uint32_t					filterIdLow			;
	uint32_t					filterMaskIdHigh	;
	uint32_t					filterMaskIdLow		;
	can_filter_mode				filterMode			;
	can_filter_scale			filterScale			;
	uint32_t					slaveStartFilterBank;
/******************* CAN IT ************************/
	hasInterrupt				hasInterrupt		;
	can_interrupts				canIT				;
	IT_notification				activeITs			;
	//#elif defined(OTHER)
#else
#endif
}st_canConfig;

/****************************************************************************/
/* 						CAN FUNCTION STRUCTURE 								*/
/****************************************************************************/
typedef struct can_functions
{
	CAN_ERR (*init)		(st_canPhy*, st_canConfig*);
	CAN_ERR (*enable)	(st_canPhy*, uint32_t);
	CAN_ERR (*send)		(st_canPhy*);
	CAN_ERR (*read)		(st_canPhy*);
	CAN_ERR (*reset)	(st_canPhy*);
	CAN_ERR (*close)	(st_canPhy*);
	state	(*pinInit)	(st_pin_phy *, st_pin_config *);
}st_canFunctions;

//extern const CO_IF_CAN_DRV SimCanDriver;

/****************************************************************************/
/* 							CAN STRUCTURE 									*/
/****************************************************************************/
typedef struct basicCAN
{
	st_canConfig* 	can_config;		//Pointer to a basic configuration.
	st_canPhy 		can_phy;		//Physical structure of the CAN bus.
	st_canFunctions can_func;		//Function structure for the CAN bus.
}st_basicCan;
/****************************************************************************/

// Fuctions used for all architectures :

CAN_ERR basicCAN_InstallFunctions(st_basicCan *);


#endif /* LIBRARY_BASICCAN_BASICCAN_H_ */
