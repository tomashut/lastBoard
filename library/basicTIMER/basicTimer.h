/*
 * basicTimer.h
 *
 *  Created on: Mar 21, 2024
 *      Author: CRINSURANCE 1
 */

#ifndef INC_BASICTIMER_H_
#define INC_BASICTIMER_H_


#include "hardwareConfig.h"
#include "typdef_basicLib.h"
//#include "stm32f4xx_it.h"
#include "basicPin.h"
#ifdef KINETICS
#include "fsl_pit.h"
#elif defined(STM32F4XX)

#endif

typedef struct timer_config{

	enum_timer			TIMn;
	enum_gpio			GPIOn;
	pinNumber			pwmPin;
	uint32_t			prescaler;
	counterMode			counterMode;
	uint32_t			period;
	clockDiv			clockDivision;
	autoReloadPreload	autoReloadPreload;
	clockSource			clockSource;
//	enum_channel		channel;
	masterOutputTrigger	masterOutputTrigger;
	masterSlaveMode		masterSlaveMode;
	hasInterrupt		hasInterrupt;
	enum_timerMode		mode;
	void (*irq_function)(void);
}st_timer_config;

typedef struct basictimer{
	TIM_HandleTypeDef				handlerTIMER;
	GPIO_TypeDef					GPIOn;
	st_pin							pwmPin;
	TIM_ClockConfigTypeDef			sClockSourceConfig;
	TIM_MasterConfigTypeDef			sMasterConfig;
	TIM_OC_InitTypeDef				sConfigOC;
	TIM_BreakDeadTimeConfigTypeDef 	sBreakDeadTimeConfig;
	IRQn_Type 						IRQn;
	uint16_t						counter;
}st_timer_phy;

typedef struct timer_functions{
	uint32_t (*init)	(st_timer_phy *, st_timer_config *);
	state	 (*pinInit)	(st_pin_phy *, st_pin_config *);
}st_timier_functions;

typedef struct timer{
	st_timer_config 	*config;
	st_timer_phy 		tim_phy;
	st_timier_functions tim_func;
}st_timer;

void basicTimer_InstallFunctions(st_timer *);
#endif /* INC_BASICTIMER_H_ */
