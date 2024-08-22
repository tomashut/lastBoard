/*
 * basicPin.c
 *
 *  Created on: 14 jul. 2020
 *      Author: Laptop-Dell
 */

#include "basicPin.h"

st_portInfoList PortList[enum_gpioE + 1]; //Arreglo de lista de informacion para interrupciones

uint64_t *SysTime;

void basicPin_SetSysTime(uint64_t *sysTime) {
	SysTime = sysTime;
}

/* HANDLERS DE INTERRUPCION DE PUERTOS */
/* Lo que se hace en estos handles es detectar cual es el pin de la interrupcion y sumar en
 * el contador y actualizar el flag para procesar luego con mayor tiempo en el proceso principal
 *
 * */
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
void PORTA_IRQHandler (void){
	uint32_t interruptFlag, i=0;

	interruptFlag = GPIO_PortGetInterruptFlags(GPIOA);//busca los flags de interrupcion del puerto
	while(PortList[enum_gpioA].pin_list[i].this){	//busca elemento por elemento hasta llegar el final de la lista (NULL)
		if(PortList[enum_gpioA].pin_list[i].this->IRQ_pin.Port_Pin == PORTA){//se aseura que sea el puerto correcto
			if(interruptFlag & (1U << PortList[enum_gpioA].pin_list[i].this->numberPin)){//verifica que el pin de la lista se el causante de la IRQ
				if(GPIO_PinRead(PortList[enum_gpioA].pin_list[i].this->GPIO_Pin, PortList[enum_gpioA].pin_list[i].this->numberPin)){
					PortList[enum_gpioA].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioA].pin_list[i].this->actualState = on_state;
					PortList[enum_gpioA].pin_list[i].this->lowTimePulse = *SysTime - PortList[enum_gpioA].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}else{
					PortList[enum_gpioA].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioA].pin_list[i].this->actualState = off_state;
					PortList[enum_gpioA].pin_list[i].this->highTimePulse = *SysTime - PortList[enum_gpioA].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}
				PortList[enum_gpioA].pin_list[i].this->IRQ_pin.IRQflag = true;
				PortList[enum_gpioA].pin_list[i].this->IRQ_pin.timeOnInterrupt = *SysTime;//tomo el tiempo de systema
				GPIO_PortClearInterruptFlags(PortList[enum_gpioA].pin_list[i].this->GPIO_Pin, 1U << PortList[enum_gpioA].pin_list[i].this->numberPin);
				break;
			}
		}
		i++;//aumente el indice de recorrido por la lista
	}
}
void PORTB_IRQHandler (void){
	uint32_t interruptFlag, i=0;

	interruptFlag = GPIO_PortGetInterruptFlags(GPIOB);
	while(PortList[enum_gpioB].pin_list[i].this){
		if(PortList[enum_gpioB].pin_list[i].this->IRQ_pin.Port_Pin == PORTB){
			if(interruptFlag & (1U << PortList[enum_gpioB].pin_list[i].this->numberPin)){
				if(GPIO_PinRead(PortList[enum_gpioB].pin_list[i].this->GPIO_Pin, PortList[enum_gpioB].pin_list[i].this->numberPin)){
					PortList[enum_gpioB].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioB].pin_list[i].this->actualState = on_state;
					PortList[enum_gpioB].pin_list[i].this->lowTimePulse = *SysTime - PortList[enum_gpioB].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}else{
					PortList[enum_gpioB].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioB].pin_list[i].this->actualState = off_state;
					PortList[enum_gpioB].pin_list[i].this->highTimePulse = *SysTime - PortList[enum_gpioB].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}
				PortList[enum_gpioB].pin_list[i].this->IRQ_pin.IRQflag = true;
				PortList[enum_gpioB].pin_list[i].this->IRQ_pin.timeOnInterrupt = *SysTime;//tomo el tiempo de systema
				GPIO_PortClearInterruptFlags(PortList[enum_gpioB].pin_list[i].this->GPIO_Pin, 1U << PortList[enum_gpioB].pin_list[i].this->numberPin);
				break;
			}
		}
		i++;
	}
}
void PORTC_IRQHandler (void){
	uint32_t interruptFlag, i=0, estado;

	interruptFlag = GPIO_PortGetInterruptFlags(GPIOC);
	while(PortList[enum_gpioC].pin_list[i].this){
		if(PortList[enum_gpioC].pin_list[i].this->IRQ_pin.Port_Pin == PORTC){
			if(interruptFlag & (1U << PortList[enum_gpioC].pin_list[i].this->numberPin)){
				if(GPIO_PinRead(PortList[enum_gpioC].pin_list[i].this->GPIO_Pin, PortList[enum_gpioC].pin_list[i].this->numberPin)){
					PortList[enum_gpioC].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioC].pin_list[i].this->actualState = on_state;
					PortList[enum_gpioC].pin_list[i].this->lowTimePulse = *SysTime - PortList[enum_gpioC].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}else{
					PortList[enum_gpioC].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioC].pin_list[i].this->actualState = off_state;
					PortList[enum_gpioC].pin_list[i].this->highTimePulse = *SysTime - PortList[enum_gpioC].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}
				PortList[enum_gpioC].pin_list[i].this->IRQ_pin.IRQflag = true;
				PortList[enum_gpioC].pin_list[i].this->IRQ_pin.timeOnInterrupt = *SysTime;//tomo el tiempo de systema
				GPIO_PortClearInterruptFlags(PortList[enum_gpioC].pin_list[i].this->GPIO_Pin, 1U << PortList[enum_gpioC].pin_list[i].this->numberPin);
				break;
			}
		}
		i++;
	}

}
void PORTD_IRQHandler (void){
	uint32_t interruptFlag, i=0;

	interruptFlag = GPIO_PortGetInterruptFlags(GPIOD);
	while(PortList[enum_gpioD].pin_list[i].this){
		if(PortList[enum_gpioD].pin_list[i].this->IRQ_pin.Port_Pin == PORTD){
			if(interruptFlag & (1U << PortList[enum_gpioD].pin_list[i].this->numberPin)){
				if(GPIO_PinRead(PortList[enum_gpioD].pin_list[i].this->GPIO_Pin, PortList[enum_gpioD].pin_list[i].this->numberPin)){
					PortList[enum_gpioD].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioD].pin_list[i].this->actualState = on_state;
					PortList[enum_gpioD].pin_list[i].this->lowTimePulse = *SysTime - PortList[enum_gpioD].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}else{
					PortList[enum_gpioD].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioD].pin_list[i].this->actualState = off_state;
					PortList[enum_gpioD].pin_list[i].this->highTimePulse = *SysTime - PortList[enum_gpioD].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}
				PortList[enum_gpioD].pin_list[i].this->IRQ_pin.IRQflag = true;
				PortList[enum_gpioD].pin_list[i].this->IRQ_pin.timeOnInterrupt = *SysTime;//tomo el tiempo de systema
				GPIO_PortClearInterruptFlags(PortList[enum_gpioD].pin_list[i].this->GPIO_Pin, 1U << PortList[enum_gpioD].pin_list[i].this->numberPin);
				break;
			}
		}
		i++;
	}
}
void PORTE_IRQHandler (void){
	uint32_t interruptFlag, i=0;

	interruptFlag = GPIO_PortGetInterruptFlags(GPIOE);
	while(PortList[enum_gpioE].pin_list[i].this){
		if(PortList[enum_gpioE].pin_list[i].this->IRQ_pin.Port_Pin == PORTE){
			if(interruptFlag & (1U << PortList[enum_gpioE].pin_list[i].this->numberPin)){
				if(GPIO_PinRead(PortList[enum_gpioE].pin_list[i].this->GPIO_Pin, PortList[enum_gpioE].pin_list[i].this->numberPin)){
					PortList[enum_gpioE].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioE].pin_list[i].this->actualState = on_state;
					PortList[enum_gpioE].pin_list[i].this->lowTimePulse = *SysTime - PortList[enum_gpioE].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}else{
					PortList[enum_gpioE].pin_list[i].this->IRQ_pin.counter++;
					PortList[enum_gpioE].pin_list[i].this->actualState = off_state;
					PortList[enum_gpioE].pin_list[i].this->highTimePulse = *SysTime - PortList[enum_gpioE].pin_list[i].this->IRQ_pin.timeOnInterrupt;
				}
				PortList[enum_gpioE].pin_list[i].this->IRQ_pin.IRQflag = true;
				PortList[enum_gpioE].pin_list[i].this->IRQ_pin.timeOnInterrupt = *SysTime;//tomo el tiempo de systema
				GPIO_PortClearInterruptFlags(PortList[enum_gpioE].pin_list[i].this->GPIO_Pin, 1U << PortList[enum_gpioE].pin_list[i].this->numberPin);
				break;
			}
		}
		i++;
	}
}
#elif ARCHITECTURE == STM32F4xx
#endif
/**************************************/

uint32_t basicPin_InterruptConfig(st_pin_phy *this) {
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	DisableIRQ(this->IRQ_pin.IRQ_type);
	PORT_SetPinInterruptConfig(this->IRQ_pin.Port_Pin, this->numberPin, this->IRQ_pin.interrupt_cond);
	EnableIRQ(this->IRQ_pin.IRQ_type);
	return 0;
#elif ARCHITECTURE == STM32F4xx
	HAL_NVIC_DisableIRQ(this->IRQ_pin.IRQ_type);
	HAL_NVIC_SetPriority(this->IRQ_pin.IRQ_type, this->IRQ_pin.PreemptPriority, this->IRQ_pin.SubPriority);
	HAL_NVIC_EnableIRQ(this->IRQ_pin.IRQ_type);
	return 0;
#endif

}

/********************************************************************************************
 * funcion: basicPin_Read
 * param:
 * 			-st_pin_phy *this: puntero a estructura fisica del pin
 * Descripcion:
 * 			Esta funcion lee el estado del pin apuntado por *this.
 * Devuelve:
 * 			Estado actual del pin teniendo en cuenta la logica instalada
 *
 * ******************************************************************************************/
state basicPin_Read(st_pin_phy *this) {
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	state actualState = GPIO_PinRead(this->GPIO_Pin, this->numberPin);
	if(!this->logic){
		actualState = !actualState;
	}
	return actualState;//lee directo el valor del pin
#elif ARCHITECTURE == STM32F4xx
	state actualState = HAL_GPIO_ReadPin(this->GPIOn, this->pinConfig.Pin);
	if (!this->logic) {
		actualState = !actualState;
	}
	return actualState;	//lee directo el valor del pin
#endif
}

/********************************************************************************************
 * funcion: basicPin_Write
 * param:
 * 			-st_pin_phy *this: puntero a estructura fisica del pin
 * 			-uint8_t NewState: nuevo estado del pin
 * Descripcion:
 * 			Esta funcion escribe el pin con el estado NewState. Tiene en cuenta la logica del
 * 			fisica del pin.
 * Devuelve:
 * 			Estado actual del pin teniendo en cuenta la logica instalada.
 *
 * ******************************************************************************************/
state basicPin_Write(st_pin_phy *this, uint8_t NewState) {
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	if(!this->logic){
		NewState = !NewState;
	}
	GPIO_PinWrite(this->GPIO_Pin, this->numberPin, NewState);//coloca el estado en el pin
	return basicPin_Read(this);//actualiza y confirma el estado del pin con una lectura
#elif ARCHITECTURE == STM32F4xx
	if (!this->logic) {
		NewState = !NewState;
	}
	HAL_GPIO_WritePin(this->GPIOn, this->pinConfig.Pin, NewState);//coloca el estado en el pin
	return basicPin_Read(this);	//actualiza y confirma el estado del pin con una lectura
#endif
}

/********************************************************************************************
 * funcion: basicPin_installFunctions
 * param:
 * 			-st_pin_phy *this: puntero a estructura fisica del pin
 * Descripcion:
 * 			Esta funcion instala las funciones báscias del pin
 * Devuelve:
 * 			Nada
 *
 * ******************************************************************************************/
void basicPin_installFunctions(st_pin *this) {
	this->pin_func.init = basicPin_Init;
	this->pin_func.read = basicPin_Read;
	this->pin_func.write = basicPin_Write;
}

/********************************************************************************************
 * funcion: basicPin_ParamsInstall
 * param:
 * 			-st_pin_phy *this: puntero a estructura fisica del pin
 * 			-st_pin_config *config: puntero a configuración basica del pin
 * Descripcion:
 * 			Esta funcion instala los parametros configurados en *config en las estructuras
 * 			internas de *this
 * Devuelve:
 * 			devuelve el estado de la operación. En general es 0
 *
 * ******************************************************************************************/
uint32_t basicPin_ParamsInstall(st_pin_phy *this, st_pin_config *config) {
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	this->actualState = config->initState;
	this->logic = config->logic;
	this->hasIRQ = config->hasIRQ;
	this->pinConfig.pinDirection = config->pin_direction;
	if(!this->logic){
		this->pinConfig.outputLogic = !config->initState;
	}else{
		this->pinConfig.outputLogic = config->initState;
	}
	this->numberPin = config->numberPin;
	this->IRQ_pin.interrupt_cond = config->interrupt_cond;
	switch(config->enum_GPIO){
	case enum_gpioA:
		this->GPIO_Pin = GPIOA;
		this->IRQ_pin.Port_Pin = PORTA;
		this->IRQ_pin.IRQ_type = PORTA_IRQn;
		this->clockName = kCLOCK_PortA;
		break;
	case enum_gpioB:
		this->GPIO_Pin = GPIOB;
		this->IRQ_pin.Port_Pin = PORTB;
		this->IRQ_pin.IRQ_type = PORTB_IRQn;
		this->clockName = kCLOCK_PortB;
		break;
	case enum_gpioC:
		this->GPIO_Pin = GPIOC;
		this->IRQ_pin.Port_Pin = PORTC;
		this->IRQ_pin.IRQ_type = PORTC_IRQn;
		this->clockName = kCLOCK_PortC;
		break;
	case enum_gpioD:
		this->GPIO_Pin = GPIOD;
		this->IRQ_pin.Port_Pin = PORTD;
		this->IRQ_pin.IRQ_type = PORTD_IRQn;
		this->clockName = kCLOCK_PortD;
		break;
	case enum_gpioE:
		this->GPIO_Pin = GPIOE;
		this->IRQ_pin.Port_Pin = PORTE;
		this->IRQ_pin.IRQ_type = PORTE_IRQn;
		this->clockName = kCLOCK_PortE;
		break;
	default:
		break;
	}
	this->listPlace = 0;
	this->highTimePulse = 0;
	this->lowTimePulse = 0;
	this->IRQ_pin.counter = 0;
	this->IRQ_pin.timeOnInterrupt = 0;
	this->IRQ_pin.IRQflag = false;
	return 0;
#elif ARCHITECTURE == STM32F4xx
	__HAL_RCC_GPIOH_CLK_ENABLE();
	switch (config->enum_GPIO) {
	case enum_gpioA:
		this->GPIOn = GPIOA;
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case enum_gpioB:
		this->GPIOn = GPIOB;
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	case enum_gpioC:
		this->GPIOn = GPIOC;
		__HAL_RCC_GPIOC_CLK_ENABLE();
		break;
	case enum_gpioD:
		this->GPIOn = GPIOD;
		__HAL_RCC_GPIOD_CLK_ENABLE();
		break;
	case enum_gpioE:
		this->GPIOn = GPIOE;
		__HAL_RCC_GPIOE_CLK_ENABLE();
		break;
	case enum_gpioF:
		this->GPIOn = GPIOF;
		__HAL_RCC_GPIOF_CLK_ENABLE();
		break;
	case enum_gpioG:
		this->GPIOn = GPIOG;
		__HAL_RCC_GPIOG_CLK_ENABLE();
		break;
	case enum_gpioH:
		this->GPIOn = GPIOH;
//		__HAL_RCC_GPIOH_CLK_ENABLE();
		break;
	default:
		break;
	}
	switch (config->Mode) {
	case input:
		this->pinConfig.Mode = GPIO_MODE_INPUT;
		this->hasIRQ = no;
		break;
	case output_push_pull:
		this->pinConfig.Mode = GPIO_MODE_OUTPUT_PP;
		this->hasIRQ = no;
		break;
	case output_open_drain:
		this->pinConfig.Mode = GPIO_MODE_OUTPUT_OD;
		this->hasIRQ = no;
		break;
	case alternate_push_pull:
		this->pinConfig.Mode = GPIO_MODE_AF_PP;
		this->hasIRQ = no;
		break;
	case alternate_open_drain:
		this->pinConfig.Mode = GPIO_MODE_AF_OD;
		this->hasIRQ = no;
		break;
	case analog_mode:
		this->pinConfig.Mode = GPIO_MODE_ANALOG;
		this->hasIRQ = no;
		break;
	case ext_interr_rising_edge:
		this->pinConfig.Mode = GPIO_MODE_IT_RISING;
		this->hasIRQ = yes;
		break;
	case ext_interr_falling_edge:
		this->pinConfig.Mode = GPIO_MODE_IT_FALLING;
		this->hasIRQ = yes;
		break;
	case ext_interr_rising_falling_edge:
		this->pinConfig.Mode = GPIO_MODE_IT_RISING_FALLING;
		this->hasIRQ = yes;
		break;
	case ext_event_rising_edge:
		this->pinConfig.Mode = GPIO_MODE_EVT_RISING;
		this->hasIRQ = yes;
		break;
	case ext_event_falling_edge:
		this->pinConfig.Mode = GPIO_MODE_EVT_FALLING;
		this->hasIRQ = yes;
		break;
	case ext_event_rising_falling_edge:
		this->pinConfig.Mode = GPIO_MODE_EVT_RISING_FALLING;
		this->hasIRQ = yes;
		break;
	default:
		break;
	}

	this->pinConfig.Pin |= (1 << config->Pin);

	if (this->hasIRQ == yes)
	{
		if (config->Pin < pin5)
		{
			this->IRQ_pin.IRQ_type = EXTI0_IRQn + config->Pin;
			this->IRQ_pin.PreemptPriority = 0;
			this->IRQ_pin.SubPriority = 0;
		}
		else if ((config->Pin >= pin5) & (config->Pin < pin10))
		{
			this->IRQ_pin.IRQ_type = EXTI9_5_IRQn;
			this->IRQ_pin.PreemptPriority = 0;
			this->IRQ_pin.SubPriority = 0;
		}
		else if ((config->Pin >= pin10))
		{
			this->IRQ_pin.IRQ_type = EXTI15_10_IRQn;
			this->IRQ_pin.PreemptPriority = 0;
			this->IRQ_pin.SubPriority = 0;
		}

	}

	switch (config->Pull) {
		case noPull:
			this->pinConfig.Pull=GPIO_NOPULL;
			break;
		case pullUp:
			this->pinConfig.Pull=GPIO_PULLUP;
			break;
		case pullDown:
			this->pinConfig.Pull=GPIO_PULLDOWN;
			break;
		default:
			break;
	}

	switch (config->Speed) {
		case speed_freq_low:
			this->pinConfig.Speed=GPIO_SPEED_FREQ_LOW;
			break;
		case speed_freq_medium:
			this->pinConfig.Speed=GPIO_SPEED_FREQ_MEDIUM;
			break;
		case speed_freq_high:
			this->pinConfig.Speed=GPIO_SPEED_FREQ_HIGH;
			break;
		case speed_freq_very_high:
			this->pinConfig.Speed=GPIO_SPEED_FREQ_VERY_HIGH;
			break;
		default:
			break;
	}
	if (config->Alternate!= no_alternate_funtion)
	{
		this->pinConfig.Alternate=(uint8_t)(config->Alternate - 1);
	}


	this->actualState = config->initState;
	this->logic = config->logic;
	this->listPlace = 0;
	this->highTimePulse = 0;
	this->lowTimePulse = 0;
	return 0;
#endif
}

/********************************************************************************************
 * funcion: basicPin_ListInstall
 * param:
 * 			-st_pin_phy *this: puntero a estructura fisica del pin
 * 			-st_pin_config *config: puntero a configuración basica del pin
 * Descripcion:
 * 			Esta funcion installa el pin en una lista para poder procesar la interrupción de forma
 * 			eficiente. Hay una lista por cada puerto que el micro tiene. La funcion instala
 * 			segun la configuración *config
 * Devuelve:
 * 			Estado de la funcion. En general es 0.
 *
 * ******************************************************************************************/
uint32_t basicPin_ListInstall(st_pin_phy *this, st_pin_config *config) {
	if (PortList[config->enum_GPIO].index) {
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index - 1].next = this;
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index].prev =	PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index - 1].next;
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index].this =	this;
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index].next =	NULL;
		this->listPlace = PortList[config->enum_GPIO].index;
		PortList[config->enum_GPIO].index++;
	} else {
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index].prev =	NULL;
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index].this =	this;
		PortList[config->enum_GPIO].pin_list[PortList[config->enum_GPIO].index].next =	NULL;
		this->listPlace = PortList[config->enum_GPIO].index;
		PortList[config->enum_GPIO].index++;
	}
	return 0;
}

/********************************************************************************************
 * funcion: basicPin_Init
 * param:
 * 			-st_pin_phy *this: puntero a estructura fisica del pin
 * 			-st_pin_config *config: puntero a configuración basica del pin
 * Descripcion:
 * 			Instala la configuración del pin *config en el pin fisico *this
 * Devuelve:
 * 			Estado actual del pin.
 *
 * ******************************************************************************************/
state basicPin_Init(st_pin_phy *this, st_pin_config *config) {
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	basicPin_ParamsInstall(this, config);	//instala los parametros del pin fisico
	basicPin_ListInstall(this, config);		//instala el pin en la lista

	CLOCK_EnableClock(this->clockName);		//habilita el clock al puerto
	PORT_SetPinMux(this->IRQ_pin.Port_Pin, this->numberPin, kPORT_MuxAsGpio); //configura el pin como GPIO
	if(this->hasIRQ){	//instala la interrupcion si fue configurada en *this
		basicPin_InterruptConfig(this);//se instala la interrupcion
	}
	GPIO_PinInit(this->GPIO_Pin, this->numberPin, &this->pinConfig);//inicia el pin
	return basicPin_Read(this);//devuelve el estado del pin

#elif ARCHITECTURE == STM32F4xx
	basicPin_ParamsInstall(this, config);//instala los parametros del pin fisico
	basicPin_ListInstall(this, config);		//instala el pin en la lista

	if (this->hasIRQ) {	//instala la interrupcion si fue configurada en *this
		basicPin_InterruptConfig(this);	//se instala la interrupcion
	}

	if ((this->pinConfig.Mode & MODE_OUTPUT) != 0) {
		HAL_GPIO_WritePin(this->GPIOn, this->pinConfig.Pin, config->initState);
	}
	HAL_GPIO_Init(this->GPIOn, &this->pinConfig);
	return basicPin_Read(this);	//devuelve el estado del pin
#endif
}

