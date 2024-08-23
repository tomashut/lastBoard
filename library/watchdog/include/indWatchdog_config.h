#ifndef WATCHDOG_CONFIG_H_
#define WATCHDOG_CONFIG_H_
/******************************************************************************
 *                                   Includes                                 *
 ******************************************************************************/
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#endif

#include "basicIndWatchdog.h"

/******************************************************************************
*                                  Definitions                               *
******************************************************************************/
/******************************************************************************
*                                  Linked                                     *
******************************************************************************/
enum
{
	watchdogNumber0,
	watchdogInSystem
};

/******************************************************************************
*                                  Variables                                  *
******************************************************************************/
typedef struct iwdg_t
{
	st_basicIwdg*	iwdg;
}st_iwdg_t;

/******************************************************************************
* WATCH DOG FUNCTION *
******************************************************************************/
st_basicIndependentWatchdog_config*	iwdg_config_GetTimConfig(uint8_t)   ;
IWDG_ERR 							iwdg_config_Init(st_iwdg_t*)		;
IWDG_ERR							iwdg_config_Refresh(st_iwdg_t*)		;
st_iwdg_t*							iwdg_config_InitPhyWatchdog(uint8_t);


#endif	//WATCHDOG_CONFIG_H_
