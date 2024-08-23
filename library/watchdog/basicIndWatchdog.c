#include "basicIndWatchdog.h"

uint32_t basicIndepeendetWatchDog_InstallParams(st_basicIndependentWatchdog_phy* this, st_basicIndependentWatchdog_config* config)
{
#if ARCHITECTURE == ESP32_BOARD

#elif ARCHITECTURE == KINTEIS

#elif ARCHITECTURE == STM32F4xx

	switch(config->mode)
	{
		case independent:
			this->handlerIndepWatchDog.Instance 		= 	IWDG				;
		break;

		default:
		break;
	}
	switch(config->prescaler)
	{

		case preescaler_4:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_4	;
		break;

		case preescaler_8:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_8	;
		break;

		case preescaler_16:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_16	;
		break;

		case preescaler_32:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_32	;
		break;

		case preescaler_64:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_64	;
		break;

		case preescaler_128:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_128	;
		break;

		case preescaler_256:
			this->handlerIndepWatchDog.Init.Prescaler 	=	IWDG_PRESCALER_256	;
		break;

		default:
		break;
	}

	this->handlerIndepWatchDog.Init.Prescaler 	= 	config->prescaler	;
	this->handlerIndepWatchDog.Init.Reload		= 	config->reload		;
//#elif defined(OTHER)
#else

#endif

	return 0;
}

/**
 * @brief Initializes the independent watchdog timer.
 *
 * This function installs the watchdog parameters from the provided configuration and initializes
 * the independent watchdog timer.
 *
 * @param this Pointer to the `st_basicIndependentWatchdog_phy` structure containing the watchdog handler.
 * @param config Pointer to the `st_basicIndependentWatchdog_config` structure containing the configuration parameters for the watchdog.
 * @return uint32_t Returns IWDG_ERROR_NONE upon successful initialization, or IWDG_INIT_ERROR if the initialization fails.
 */
IWDG_ERR basicIndependentWatchdog_Init(st_basicIndependentWatchdog_phy* this, st_basicIndependentWatchdog_config* config)
{
#if ARCHITECTURE == ESP32_BOARD

#elif ARCHITECTURE == KINTEIS

#elif ARCHITECTURE == STM32F4xx

	basicIndepeendetWatchDog_InstallParams(this, config);

	if (HAL_IWDG_Init(&this->handlerIndepWatchDog) != HAL_OK)
	{
		return IWDG_INIT_ERROR;
	}

    return IWDG_ERROR_NONE;

#endif
}

/**
 * @brief Refreshes (reloads) the independent watchdog timer.
 *
 * This function reloads the independent watchdog timer to prevent it from expiring.
 * It writes the reload key to the watchdog's key register.
 *
 * @param this Pointer to the `st_basicIndependentWatchdog_phy` structure containing the watchdog handler.
 * @return uint32_t Returns IWDG_ERROR_NONE upon successful reload.
 */
IWDG_ERR refreshIndependentWatchdog(st_basicIndependentWatchdog_phy* this)
{
#if ARCHITECTURE == ESP32_BOARD

#elif ARCHITECTURE == KINTEIS

#elif ARCHITECTURE == STM32F4xx
    // Recarga el contador del IWDG
	this->handlerIndepWatchDog.Instance->KR = IWDG_KEY_RELOAD;

    return IWDG_ERROR_NONE;
#endif
}


void basicIndependentWatchdog_InstallFunctions(st_basicIwdg* this)
{
	this->iwdg_func.init 	= &basicIndependentWatchdog_Init;
	this->iwdg_func.refresh = &refreshIndependentWatchdog;
}
