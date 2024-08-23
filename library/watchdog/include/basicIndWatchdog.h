#ifndef BASICINDWATCHDOG_H_
#define BASICINDWATCHDOG_H_
/******************************************************************************
 *                                   Includes                                 *
 ******************************************************************************/
#include "hardwareConfig.h"
#include "typdef_basicLib.h"
/******************************************************************************
*                                  Definitions                               *
******************************************************************************/
#if   ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "stm32f4xx_hal.h"
//#elif defined(OTHER)
#else
#endif

/******************************************************************************
*                                  Variables                                  *
******************************************************************************/
//Definition of SPI Error. Used for all architectures :
typedef enum IWDG_ERR_T
{
	IWDG_ERROR_NONE=0,
	IWDG_INIT_ERROR,
	IWDG_ERROR,
	IWDG_REFRESH_ERROR

}IWDG_ERR;

/******************************************************************************
* WATCH DOG PHYSICAL STRUCTURE *
******************************************************************************/
typedef struct basicIwdg
{
	#if   ARCHITECTURE == ESP32_BOARD
	#elif ARCHITECTURE == KINTEIS
	#elif ARCHITECTURE == STM32F4xx

		IWDG_HandleTypeDef	handlerIndepWatchDog	;      	// Pointer to WatchDog controller.

	//#elif defined(OTHER)
	#else


	#endif
}st_basicIndependentWatchdog_phy;

/******************************************************************************
* BASIC CONFIGURATION STRUCTURE *
******************************************************************************/
typedef struct basicIwdg_config{
	enum_watchdog_mode			mode		;	// It can be Independent or Window. But only the first one is valid in this library.
	enum_watchdog_preescaaler	prescaler	;
	uint32_t 					reload		;
}st_basicIndependentWatchdog_config;


/******************************************************************************
* INDEPENDENT WATCH DOG FUNCTION STRUCTURE *
******************************************************************************/
typedef struct basicIwdg_functions{
	IWDG_ERR (*init)	(st_basicIndependentWatchdog_phy*, st_basicIndependentWatchdog_config*);
	IWDG_ERR (*refresh)	(st_basicIndependentWatchdog_phy*)									   ;

}st_basicIndependentWatchdog_functions;

/******************************************************************************
* INDEPENDENT WATCH DOG PARAMETERS STRUCTURE *
******************************************************************************/

/******************************************************************************
* INDEPENDENT WATCH DOG STRUCTURE *
******************************************************************************/
typedef struct baicIwdg{
	st_basicIndependentWatchdog_config*		iwdg_config	;
	st_basicIndependentWatchdog_phy 		iwdg_phy	;
	st_basicIndependentWatchdog_functions 	iwdg_func	;
}st_basicIwdg;
/******************************************************************************
* WATCH DOG FUNCTION *
******************************************************************************/

void basicIndependentWatchdog_InstallFunctions(st_basicIwdg*);

#endif	//BASICINDWATCHDOG_H_
