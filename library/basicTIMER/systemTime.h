/*
 * systemTime.h
 *
 *  Created on: Mar 22, 2024
 *      Author: Usuario
 */

#ifndef INC_SYSTEMTIME_H_
#define INC_SYSTEMTIME_H_

#include "hardwareConfig.h"
#include "typdef_basicLib.h"
#include "timer_config.h"
#ifdef KINETICS
#include "fsl_pit.h"

#elif defined(STM32F4XX)

#endif
enum{
	systemTime_tim = enum_timer_3,
	systemTime_tim2 = enum_timer_2,
	systemTime_pwm = enum_timer_1
};

typedef struct systemTime_registers{
	uint64_t milisecElapsed;
	uint64_t milisecElapsedLast;
	uint32_t milisec;
	uint32_t secs;
	uint32_t mins;
	uint32_t hours;
	uint32_t days;
}st_systemTime_registers;

typedef struct systemTime_functions{
	uint32_t (*init_systemTime)(st_tim *);
}st_systemTime_functions;

typedef struct systemTime{
	st_tim *tim;
	st_systemTime_functions *functions;
	st_systemTime_registers *registers;
	uint64_t time5sec;
	uint32_t timer5sec;
}st_systemTime;

uint32_t systemTime_Init(st_systemTime *);
uint32_t systemPWM_Init(st_systemTime *this);
uint64_t systemTime_GetTimeElapsed(st_systemTime *);

#endif /* INC_SYSTEMTIME_H_ */
