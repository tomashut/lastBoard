#include "indWatchdog.h"


/******************************************************************************
* LINK TO LOWER LAYERS *
******************************************************************************/
//The relationship of the module with the functions found in the lower levels is established.
st_iwdg_functions iwg_func = {

		.iwdg_init 		= &iwdg_config_Init,
		.iwdg_refresh 	= &iwdg_config_Refresh,
};

/******************************************************************************
* VARIABLES *
******************************************************************************/

/******************************************************************************
* FUNCTIONS DEFINITION *
******************************************************************************/

/**
 * @brief Initializes the independent watchdog configuration.
 *
 * This function initializes the independent watchdog configuration by setting up its
 * function pointers and initializing the physical watchdog instance. It calls the
 * initialization function for the physical watchdog and sets up the watchdog functions.
 *
 * @param this Pointer to the `st_indWatchdog` structure containing the watchdog instance.
 * @return IWDG_ERR Returns `IWDG_ERROR_NONE` upon successful initialization.
 */
IWDG_ERR iwg_init(st_indWatchdog* this)
{
	this->functions = &iwg_func;
	this->wg = *(iwdg_config_InitPhyWatchdog(watchdogSystemSelect));
	this->functions->iwdg_init(&this->wg);

	return IWDG_ERROR_NONE;
}

/**
 * @brief Refreshes the independent watchdog timer.
 *
 * This function refreshes the independent watchdog timer by calling its refresh function
 * through its function pointers.
 *
 * @param this Pointer to the `st_indWatchdog` structure containing the watchdog instance.
 * @return IWDG_ERR Returns `IWDG_ERROR_NONE` upon successful refresh.
 */
IWDG_ERR iwg_refresh(st_indWatchdog* this)
{
	this->functions->iwdg_refresh(&this->wg);
	return IWDG_ERROR_NONE;
}

