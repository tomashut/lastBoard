/******************************************************************************
 *                                   Includes                                 *
 ******************************************************************************/
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#endif

#include "indWatchdog_config.h"
/******************************************************************************
*                                  Definitions                               *
******************************************************************************/

/******************************************************************************
*                                  Variables                                  *
******************************************************************************/
st_basicIwdg 	iWdg_PHY[watchdogInSystem];
st_iwdg_t 		iWdg[watchdogInSystem];

st_basicIndependentWatchdog_config iwdg_config[watchdogInSystem]= {
			{
					.mode		= 	independent,
					.prescaler	=	preescaler_256,
					.reload		=	4095
			},


};

/******************************************************************************
* WATCH DOG CONFIGURATIONS FUNCTION DEFINITIONS*
******************************************************************************/
/**
 * @brief Retrieves the independent watchdog timer configuration for a given index.
 *
 * This function returns a pointer to the independent watchdog timer configuration
 * corresponding to the specified index from the `iwdg_config` array.
 *
 * @param index The index of the desired watchdog timer configuration.
 * @return st_basicIndependentWatchdog_config* Pointer to the watchdog timer configuration at the specified index.
 */
st_basicIndependentWatchdog_config* iwdg_config_GetTimConfig(uint8_t index)
{
	return &iwdg_config[index];
}

/**
 * @brief Initializes the independent watchdog configuration.
 *
 * This function installs the functions for the independent watchdog and initializes
 * it with the provided configuration. It also refreshes the watchdog timer.
 *
 * @param this Pointer to the `st_iwdg_t` structure containing the watchdog instance.
 * @return IWDG_ERR Returns `IWDG_ERROR_NONE` upon successful initialization.
 */
IWDG_ERR iwdg_config_Init(st_iwdg_t* this)
{
	basicIndependentWatchdog_InstallFunctions(this->iwdg);
	this->iwdg->iwdg_func.init(&this->iwdg->iwdg_phy,this->iwdg->iwdg_config);
	this->iwdg->iwdg_func.refresh(&this->iwdg->iwdg_phy);
	return IWDG_ERROR_NONE;
}

/**
 * @brief Initializes a physical watchdog instance.
 *
 * This function initializes a physical watchdog instance based on the provided index.
 * It retrieves the timing configuration for the watchdog and sets up the structure
 * to hold the configured watchdog instance.
 *
 * @param index Index of the watchdog instance to initialize.
 * @return st_iwdg_t* Returns a pointer to the initialized `st_iwdg_t` structure.
 */
st_iwdg_t*	iwdg_config_InitPhyWatchdog(uint8_t index)
{
	st_iwdg_t *this = &iWdg[index];
	iWdg_PHY[index].iwdg_config = iwdg_config_GetTimConfig(index);
	this->iwdg = &iWdg_PHY[index];
	return this;
}

/**
 * @brief Refreshes the watchdog timer.
 *
 * This function refreshes the watchdog timer to prevent it from triggering a timeout.
 * It calls the refresh function associated with the watchdog instance.
 *
 * @param this Pointer to the `st_iwdg_t` structure containing the watchdog instance.
 * @return IWDG_ERR Returns `IWDG_ERROR_NONE` upon successful refresh.
 */
IWDG_ERR iwdg_config_Refresh(st_iwdg_t* this)
{
	this->iwdg->iwdg_func.refresh(&this->iwdg->iwdg_phy);
	return IWDG_ERROR_NONE;
}
