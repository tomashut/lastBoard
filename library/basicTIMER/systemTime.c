/*
 * systemTime.c
 *
 *  Created on: Mar 22, 2024
 *      Author: Usuario
 */

/*
 * systemTime.h
 *
 *  Created on: 12 sep. 2020
 *      Author: Laptop-Dell
 */


#ifdef KINETICS
#include "fsl_pit.h"
#include <pit_config.h>
#elif defined(STM32F4XX)

#endif

#include <systemTime.h>

st_systemTime_functions SystemTime_Functions = {
		.init_systemTime = &tim_config_Init
};

st_systemTime_registers SystemTime_Registers = {
		.milisecElapsed = 0,
		.milisecElapsedLast = 0,
		.milisec = 0,
		.secs = 0,
		.mins = 0,
		.hours = 0,
		.days = 0,
};



void systemTime_onInterrupt(void){
	SystemTime_Registers.milisecElapsed++;
	SystemTime_Registers.milisec++;
	if(SystemTime_Registers.milisec > 999){
		SystemTime_Registers.secs++;
		SystemTime_Registers.milisec -= 1000;
		if(SystemTime_Registers.secs > 59){
			SystemTime_Registers.mins++;
			SystemTime_Registers.secs -= 60;
			if(SystemTime_Registers.mins > 59){
				SystemTime_Registers.hours++;
				SystemTime_Registers.mins -= 60;
				if(SystemTime_Registers.hours > 23){
					SystemTime_Registers.days++;
					SystemTime_Registers.hours -= 24;
				}
			}
		}
	}
}

uint32_t systemTime_Init(st_systemTime *this){
	this->functions = &SystemTime_Functions;
	this->tim = tim_config_InitPhyTimer(systemTime_tim);
	this->registers = &SystemTime_Registers;
	this->tim->timer->config->irq_function = &systemTime_onInterrupt;
	this->functions->init_systemTime(this->tim);
	return 0;
}

uint32_t systemPWM_Init(st_systemTime *this){
	this->functions = &SystemTime_Functions;
	this->tim = tim_config_InitPhyTimer(systemTime_pwm);
	this->registers = &SystemTime_Registers;
//	this->tim->timer->config->irq_function = &systemTime_onInterrupt;
	this->functions->init_systemTime(this->tim);
	return 0;
}

uint64_t systemTime_GetTimeElapsed(st_systemTime *this){
	return this->registers->milisecElapsed;
}

