/*
 * digital_outputs_config.c
 *
 *  Created on: 16 jul. 2020
 *      Author: Laptop-Dell
 */

#include <digital_outputs_config.h>

#define ENA_IN_24V_PORT			PORTE
#define ENA_IN_24V_PORTIRQ		PORTE_IRQn
#define ENA_IN24V_GPIOPIN 		GPIOE
#define ENA_IN_24V_PINNUM 		26


#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
st_pin_config DigitalOutputs_Config[enum_DigitalOutput_inSystem] = {
//		pin_direction			enum_GPIO	numberPin	interrupt_cond					hasIRQ	logic		initState
		{kGPIO_DigitalOutput, 	enum_gpioD, pin15, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},// Control Entradas Digitales 24V
		{kGPIO_DigitalOutput, 	enum_gpioC, pin15, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	on_state},//RE control RS485
		{kGPIO_DigitalOutput, 	enum_gpioC, pin14, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	on_state},//DE control RS485
		{kGPIO_DigitalOutput, 	enum_gpioA, pin27, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	on_state},//Enable fuente 3.4V
		{kGPIO_DigitalOutput, 	enum_gpioE, pin3, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//Enable fuente 24V
		{kGPIO_DigitalOutput, 	enum_gpioE, pin8, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//Enable entrada analogica 0
		{kGPIO_DigitalOutput, 	enum_gpioE, pin11, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//Enable entrada analogica 1
		{kGPIO_DigitalOutput, 	enum_gpioE, pin12, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//Enable entrada analogica 2
		{kGPIO_DigitalOutput, 	enum_gpioD, pin11, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//Enable entrada analogica 3
		{kGPIO_DigitalOutput, 	enum_gpioB, pin20, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//PWRKEY de sim7000
		{kGPIO_DigitalOutput, 	enum_gpioB, pin21, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	off_state},//Reset de sim7000
		{kGPIO_DigitalOutput, 	enum_gpioE, pin26, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	on_state},//write protect CAT24M01_1
		{kGPIO_DigitalOutput, 	enum_gpioE, pin27, 		kPORT_InterruptOrDMADisabled, 	no, 	positiva, 	on_state},//write protect CAT24M01_2
		{kGPIO_DigitalOutput, 	enum_gpioC, pin18, 		kPORT_InterruptOrDMADisabled, 	no, 	negativa, 	on_state},//Reset de Wifi
};
#elif ARCHITECTURE == STM32F4xx
st_pin_config DigitalOutputs_Config[enum_DigitalOutput_inSystem] = {
//		 enum_gpio		pinNumber	pinMode						pinPull		pinSpeed		 		pinAlternate			initState	logica
		{enum_gpioB,	pin10,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//PUMP ON/OFF GPIO_B_10
		{enum_gpioC,	pin3,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//SOFT STOP CRYOCOOLER GPIO_C_3
		{enum_gpioA,	pin4,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//CS Pin ADS1118
		{enum_gpioD,	pin2,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//LED ERROR

//		{enum_gpioB,	pin14,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_14
//		{enum_gpioB,	pin15,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_15
//		{enum_gpioC,	pin6,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_C_6
//		{enum_gpioC,	pin7,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_C_7


		// Completar segun aplicación
};
#endif
st_pin DigitalOutputs_PHY[enum_DigitalOutput_inSystem];
st_dig_output DigitalOutputs[enum_DigitalOutput_inSystem];

st_pin_config *digital_output_config_GetDigitalOutputConfig(uint32_t index){
	return &DigitalOutputs_Config[index];
}

/* FUNCIONES DE DIGITAL OUTPUTS */
state digital_outputs_Init(st_dig_output *this){
	basicPin_installFunctions(this->pin);
	return this->pin->pin_phy.actualState = this->pin->pin_func.init(&this->pin->pin_phy, this->pin->pin_config);
}
state digital_output_Write(st_dig_output *this, uint8_t newState){
	return this->pin->pin_phy.actualState = this->pin->pin_func.write(&this->pin->pin_phy, newState);
}
state digital_output_Read(st_dig_output *this){
	return this->pin->pin_phy.actualState = this->pin->pin_func.read(&this->pin->pin_phy);
}
/********************************/

st_dig_output *digital_output_config_GetDigitalOutput(uint32_t index){
	return &DigitalOutputs[index];
}

st_dig_output *digital_output_config_InitPhyDigitalOutput(uint32_t index){
	st_dig_output *this = &DigitalOutputs[index];

	DigitalOutputs_PHY[index].pin_config = digital_output_config_GetDigitalOutputConfig(index);
	this->pin = &DigitalOutputs_PHY[index];
	return this;
}
