/*
 * timer_config.c
 *
 *  Created on: Mar 22, 2024
 *      Author: CRINSURANCE 1
 */


#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#include <pit_config.h>

st_pitTimer_config Pit_Config[enum_pitChannel_inSystem] = {
		{kPIT_Chnl_0, 1000, NULL},
		{kPIT_Chnl_1, 5000000, NULL}
};

st_pitTimer Pit_PHY[enum_pitChannel_inSystem];
st_pit Pit[enum_pitChannel_inSystem];

st_pitTimer_config *pit_config_GetPitConfig(uint32_t index){
	return &Pit_Config[index];
}

uint32_t pit_config_Init(st_pit *this){
	basicPitTimer_InstallFunctions(this->pit);
	return this->pit->pit_func.init(&this->pit->pit_phy, this->pit->config);
}

st_pit *pit_config_InitPhyPit(uint32_t index){
	st_pit *this = &Pit[index];

	Pit_PHY[index].config = pit_config_GetPitConfig(index);
	this->pit = &Pit_PHY[index];
	return this;
}
#elif ARCHITECTURE == STM32F4xx
#endif
#include <timer_config.h>


st_timer_config Tim_Config[enum_timers_inSystem] = {
		{
				.TIMn					=tim1,
				.GPIOn					=enum_gpioA,
				.pwmPin					=pin10,
				.prescaler				=18-1,
				.counterMode			=countermode_up,
				.period					=200-1,
				.clockDivision			=clockdivision_1,
				.autoReloadPreload		=auto_is_disable,
				.clockSource			=clockSource_internal,
				.masterOutputTrigger	=trgo_reset,
				.masterSlaveMode		=slaveMode_disable,
				.hasInterrupt			=no,
				.mode					=timer_PWM
		},

		{},

		{
				.TIMn					=tim3,
				.prescaler				=72-1,
				.counterMode			=countermode_up,
				.period					=1000-1,
				.clockDivision			=clockdivision_1,
				.autoReloadPreload		=auto_is_disable,
				.clockSource			=clockSource_internal,
				.masterOutputTrigger	=trgo_reset,
				.masterSlaveMode		=slaveMode_disable,
				.hasInterrupt			=yes,
				.mode					=timer_interrupt
		}
};

st_timer Tim_PHY[enum_timers_inSystem];
st_tim Tim[enum_timers_inSystem];

st_timer_config *tim_config_GetTimConfig(uint32_t index){
	return &Tim_Config[index];
}

uint32_t tim_config_Init(st_tim *this){
	basicTimer_InstallFunctions(this->timer);
	this->timer->tim_func.init(&this->timer->tim_phy, this->timer->config);
	this->timer->tim_func.pinInit(&this->timer->tim_phy.pwmPin.pin_phy,this->timer->tim_phy.pwmPin.pin_config);
	HAL_TIM_Base_Start_IT(&this->timer->tim_phy.handlerTIMER);
	return 0;
}

st_tim *tim_config_InitPhyTimer(uint32_t index){
	st_tim *this = &Tim[index];
	Tim_PHY[index].config = tim_config_GetTimConfig(index);
	this->timer = &Tim_PHY[index];
	return this;
}
