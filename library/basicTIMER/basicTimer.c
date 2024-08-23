/*
 * basicTimer.c
 *
 *  Created on: Mar 21, 2024
 *      Author: CRINSURANCE 1
 */
#include "basicTimer.h"
#include "stdio.h"

st_timer_phy copia;
st_timer_phy count;
TIM_HandleTypeDef htim1;

st_pin_config pwmConfig={
		//		.enum_GPIO=enum_gpioE,
		//		.Pin=pin,
		.Mode=alternate_push_pull,
		.Pull=noPull,
		.Speed=speed_freq_low,
		.Alternate=alternate_function_1,
		.logic=positiva
};

void (*TIM3_OnInterrupt) (void);
/**
 * @brief This function handles TIM3 global interrupt.
 */
void TIM3_IRQHandler(void)
{

	/* USER CODE BEGIN TIM3_IRQn 0 */
	//	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, SET);
	/* USER CODE END TIM3_IRQn 0 */
	HAL_TIM_IRQHandler(&copia.handlerTIMER);
	/* USER CODE BEGIN TIM3_IRQn 1 */
	TIM3_OnInterrupt();
	/* USER CODE END TIM3_IRQn 1 */
}



uint32_t basicTimer_InstallParams(st_timer_phy *this, st_timer_config *config){
#if ARCHITECTURE == ESP32_BOARD

#elif ARCHITECTURE == KINTEIS

#elif ARCHITECTURE == STM32F4xx

	switch(config->TIMn){
	case tim1:
	{
		this->handlerTIMER.Instance=TIM1;
		__HAL_RCC_TIM1_CLK_ENABLE();
		//		this->IRQn =TIM1_IRQn;

		pwmConfig.enum_GPIO=config->GPIOn;
		pwmConfig.Pin=config->pwmPin;
		this->pwmPin.pin_config=&pwmConfig;

		//		this->handlerTIMER.Init.Prescaler = 18-1;//
		//		this->handlerTIMER.Init.CounterMode = TIM_COUNTERMODE_UP; //
		//		this->handlerTIMER.Init.Period =200-1 ;//
		//		this->handlerTIMER.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;//
		this->handlerTIMER.Init.RepetitionCounter 	= 0;
		//		this->handlerTIMER.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;//
		//		this->sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL; //
		//		this->sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET; //
		//		this->sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE; //
		this->sConfigOC.OCMode 						= TIM_OCMODE_PWM1;
		this->sConfigOC.Pulse 						= 0;
		this->sConfigOC.OCPolarity 					= TIM_OCPOLARITY_HIGH;
		this->sConfigOC.OCNPolarity 				= TIM_OCNPOLARITY_HIGH;
		this->sConfigOC.OCFastMode 					= TIM_OCFAST_DISABLE;
		this->sConfigOC.OCIdleState 				= TIM_OCIDLESTATE_RESET;
		this->sConfigOC.OCNIdleState 				= TIM_OCNIDLESTATE_RESET;
		this->sBreakDeadTimeConfig.OffStateRunMode 	= TIM_OSSR_DISABLE;
		this->sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
		this->sBreakDeadTimeConfig.LockLevel 		= TIM_LOCKLEVEL_OFF;
		this->sBreakDeadTimeConfig.DeadTime 		= 0;
		this->sBreakDeadTimeConfig.BreakState 		= TIM_BREAK_DISABLE;
		this->sBreakDeadTimeConfig.BreakPolarity 	= TIM_BREAKPOLARITY_HIGH;
		this->sBreakDeadTimeConfig.AutomaticOutput 	= TIM_AUTOMATICOUTPUT_DISABLE;

		return 0;
	}

	break;
	case tim2:
		this->handlerTIMER.Instance=TIM2;
		__HAL_RCC_TIM2_CLK_ENABLE();
		this->IRQn =TIM2_IRQn;
		break;
	case tim3:
		this->handlerTIMER.Instance=TIM3;
		__HAL_RCC_TIM3_CLK_ENABLE();
		this->IRQn =TIM3_IRQn;
		break;
	case tim4:
		this->handlerTIMER.Instance=TIM4;
		__HAL_RCC_TIM4_CLK_ENABLE();
		this->IRQn =TIM4_IRQn;
		break;
	case tim5:
		this->handlerTIMER.Instance=TIM5;
		__HAL_RCC_TIM5_CLK_ENABLE();
		this->IRQn =TIM5_IRQn;
		break;
	case tim6:
		this->handlerTIMER.Instance=TIM6;
		__HAL_RCC_TIM6_CLK_ENABLE();
		this->IRQn =TIM6_DAC_IRQn;
		break;
	case tim7:
		this->handlerTIMER.Instance=TIM7;
		__HAL_RCC_TIM7_CLK_ENABLE();
		this->IRQn =TIM7_IRQn;
		break;
	case tim8:
		this->handlerTIMER.Instance=TIM8;
		__HAL_RCC_TIM8_CLK_ENABLE();
		//		this->IRQn =;
		break;
	case tim9:
		this->handlerTIMER.Instance=TIM9;
		__HAL_RCC_TIM9_CLK_ENABLE();
		this->IRQn =TIM1_BRK_TIM9_IRQn;
		break;
	case tim10:
		this->handlerTIMER.Instance=TIM10;
		__HAL_RCC_TIM10_CLK_ENABLE();
		this->IRQn =TIM1_UP_TIM10_IRQn;
		break;
	case tim11:
		this->handlerTIMER.Instance=TIM11;
		__HAL_RCC_TIM11_CLK_ENABLE();
		this->IRQn =TIM1_TRG_COM_TIM11_IRQn;
		break;
	case tim12:
		this->handlerTIMER.Instance=TIM12;
		__HAL_RCC_TIM12_CLK_ENABLE();
		this->IRQn =TIM8_BRK_TIM12_IRQn;
		break;
	case tim13:
		this->handlerTIMER.Instance=TIM13;
		__HAL_RCC_TIM13_CLK_ENABLE();
		this->IRQn =TIM8_UP_TIM13_IRQn;
		break;
	case tim14:
		this->handlerTIMER.Instance=TIM14;
		__HAL_RCC_TIM14_CLK_ENABLE();
		this->IRQn =TIM8_TRG_COM_TIM14_IRQn;
		break;
	default:
		break;
	}

	this->handlerTIMER.Init.Prescaler=config->prescaler;

	switch (config->counterMode) {
	case countermode_up:
		this->handlerTIMER.Init.CounterMode	= TIM_COUNTERMODE_UP;
		break;
	case countermode_down:
		this->handlerTIMER.Init.CounterMode	= TIM_COUNTERMODE_DOWN;
		break;
	default:
		break;
	}

	this->handlerTIMER.Init.Period=config->period;

	switch (config->clockDivision) {
	case clockdivision_1:
		this->handlerTIMER.Init.ClockDivision	= TIM_CLOCKDIVISION_DIV1;
		break;
	case clockdivision_2:
		this->handlerTIMER.Init.ClockDivision	= TIM_CLOCKDIVISION_DIV2;
		break;
	case clockdivision_4:
		this->handlerTIMER.Init.ClockDivision	= TIM_CLOCKDIVISION_DIV4;
		break;
	default:
		break;
	}

	switch (config->autoReloadPreload) {
	case auto_is_disable:
		this->handlerTIMER.Init.AutoReloadPreload	= TIM_AUTORELOAD_PRELOAD_DISABLE;
		break;
	case auto_is_enable:
		this->handlerTIMER.Init.AutoReloadPreload	= TIM_AUTORELOAD_PRELOAD_ENABLE;
		break;
	default:
		break;
	}

	switch (config->clockSource) {
	case clockSource_internal:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_INTERNAL;
		break;
	case clockSource_etrmode1:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_ETRMODE1;
		break;
	case clockSource_etrmode2:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_ETRMODE2;
		break;
	case clockSource_ti1ed:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_TI1ED;
		break;
	case clockSource_ti1:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_TI1;
		break;
	case clockSource_ti2:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_TI2;
		break;
	case clockSource_itr0:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_ITR0;
		break;
	case clockSource_itr1:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_ITR1;
		break;
	case clockSource_itr2:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_ITR2;
		break;
	case clockSource_itr3:
		this->sClockSourceConfig.ClockSource	= TIM_CLOCKSOURCE_ITR3;
		break;
	default:
		break;
	}
	switch (config->masterOutputTrigger) {
	case trgo_reset:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_RESET;
		break;
	case trgo_enable:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_ENABLE;
		break;
	case trgo_update:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_UPDATE;
		break;
	case trgo_oc1:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_OC1;
		break;
	case trgo_oc1ref:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_OC1REF;
		break;
	case trgo_oc2ref:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_OC2REF;
		break;
	case trgo_oc3ref:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_OC3REF;
		break;
	case trgo_oc4ref:
		this->sMasterConfig.MasterOutputTrigger	= TIM_TRGO_OC4REF;
		break;
	default:
		break;
	}
	switch (config->masterSlaveMode) {
	case slaveMode_enable:
		this->sMasterConfig.MasterSlaveMode	= TIM_MASTERSLAVEMODE_ENABLE;
		break;
	case slaveMode_disable:
		this->sMasterConfig.MasterSlaveMode	= TIM_MASTERSLAVEMODE_DISABLE;
		break;
	default:
		break;
	}

	copia = *this;

	return 0;
#endif
}

uint32_t basicTimer_Init(st_timer_phy *this, st_timer_config *config){
#if ARCHITECTURE == ESP32_BOARD

#elif ARCHITECTURE == KINTEIS

#elif ARCHITECTURE == STM32F4xx
	basicTimer_InstallParams(this, config);
	if(config->mode == timer_interrupt)//	if(this->handlerTIMER.Instance == TIM3)
	{
		if (HAL_TIM_Base_Init(&this->handlerTIMER) != HAL_OK)
		{
			return -1;
		}
		if (HAL_TIM_ConfigClockSource(&this->handlerTIMER,&this->sClockSourceConfig) != HAL_OK)
		{
			return -1;
		}
		if (HAL_TIMEx_MasterConfigSynchronization(&this->handlerTIMER,&this->sMasterConfig) != HAL_OK)
		{
			return -1;
		}
		if (config->hasInterrupt == yes)
		{
			TIM3_OnInterrupt=config->irq_function;
			HAL_NVIC_SetPriority(this->IRQn, 0, 0);
			HAL_NVIC_EnableIRQ(this->IRQn);
		}
	}
	else if(config->mode == timer_PWM)
	{
		if (HAL_TIM_Base_Init(&this->handlerTIMER) != HAL_OK)
		{
			return -1;
		}

		if (HAL_TIM_ConfigClockSource(&this->handlerTIMER, &this->sClockSourceConfig) != HAL_OK)
		{
			return -1;
		}
		if (HAL_TIM_PWM_Init(&this->handlerTIMER) != HAL_OK)
		{
			return -1;
		}

		if (HAL_TIMEx_MasterConfigSynchronization(&this->handlerTIMER, &this->sMasterConfig) != HAL_OK)
		{
			return -1;
		}

		if (HAL_TIM_PWM_ConfigChannel(&this->handlerTIMER, &this->sConfigOC, TIM_CHANNEL_3) != HAL_OK)
		{
			return -1;
		}

		if (HAL_TIMEx_ConfigBreakDeadTime(&this->handlerTIMER, &this->sBreakDeadTimeConfig) != HAL_OK)
		{
			return -1;
		}
	}
	return 0;
#endif
}

void basicTimer_InstallFunctions(st_timer *this){
	this->tim_func.init 	= basicTimer_Init;
	this->tim_func.pinInit	= &basicPin_Init;
}
