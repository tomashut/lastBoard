/*
 * timer_config.h
 *
 *  Created on: Mar 22, 2024
 *      Author: CRINSURANCE 1
 */

#ifndef INC_TIMER_CONFIG_H_
#define INC_TIMER_CONFIG_H_
#include <basicTimer.h>


#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#include <basicPitTimer.h>

enum{
	enum_pitChannel_config_0,
	enum_pitChannel_config_1,
	enum_pitChannel_inSystem
};


typedef struct pit{
	st_pitTimer *pit;
}st_pit;

st_pitTimer_config *pit_config_GetPitConfig(uint32_t);
uint32_t pit_config_Init(st_pit *);
st_pit *pit_config_InitPhyPit(uint32_t);
#elif ARCHITECTURE == STM32F4xx
#endif


enum{
	enum_timer_1,
	enum_timer_2,
	enum_timer_3,
	enum_timers_inSystem
};


typedef struct tim{
	st_timer *timer;
}st_tim;

st_timer_config *tim_config_GetTimConfig(uint32_t);
uint32_t 		tim_config_Init			(st_tim *);
st_tim 			*tim_config_InitPhyTimer(uint32_t);


#endif /* INC_TIMER_CONFIG_H_ */
