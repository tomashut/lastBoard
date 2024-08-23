#ifndef INDWATCHDOG_H_
#define INDWATCHDOG_H_
/******************************************************************************
* INCLUDES
******************************************************************************/
#include "indWatchdog_config.h"

/******************************************************************************
* DEFINES *
******************************************************************************/
#define	WATCHDOG_TIMEOUT 60000 // Variable used in case the watchdog refresh time range needs to be extended to more than 32.8s. In this case is 1min = 60000ms
/******************************************************************************
* VARIABLES *
******************************************************************************/
enum{
	watchdogSystemSelect = watchdogNumber0,
};
/******************************************************************************
* INDEPENDENT WATCHDOG PARAMETERS STRUCTURE *
******************************************************************************/
typedef struct iwdg_params
{
	uint64_t*	milisecElapsed	;	// Time spent in the highest ranking system. Must be linked to an external timer.
	uint64_t 	timeCapture		;	// Time recorded in the library to check that the time has not exceeded the time set for the previous update.
}st_iwdg_params;

/******************************************************************************
* INDEPENDENT WATCHDOG PHYSICAL STRUCTURE *
******************************************************************************/

/******************************************************************************
* INDEPENDENT WATCHDOG CONFIGURATION STRUCTURE *
******************************************************************************/

/******************************************************************************
* INDEPENDENT WATCHDOG FUNCTION STRUCTURE *
******************************************************************************/
typedef struct iwgd_functions
{
	IWDG_ERR	(*iwdg_init)	(st_iwdg_t*);
	IWDG_ERR	(*iwdg_refresh)	(st_iwdg_t*);
}st_iwdg_functions;
/******************************************************************************
* INDEPENDENT WATCHDOG STRUCTURE *
******************************************************************************/

typedef struct indWatchdog
{
	st_iwdg_t			wg		 ;
	st_iwdg_params		param	 ;
	st_iwdg_functions*	functions;

}st_indWatchdog;
/******************************************************************************
* INDEPENDENT WATCHDOG FUNCTION *
******************************************************************************/
IWDG_ERR iwg_init(st_indWatchdog*);
IWDG_ERR iwg_refresh(st_indWatchdog*);

#endif	// INDWATCHDOG_H_
