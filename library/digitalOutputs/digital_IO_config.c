/*
 * digital_outputs_config.c
 *
 *  Created on: 16 jul. 2020
 *      Author: Laptop-Dell
 */

#include "digital_IO_config.h"

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
st_pin_config Digital_IO_Config[enum_Digital_IO_inSystem] = {
//		 enum_gpio		pinNumber	pinMode						pinPull		pinSpeed		 		pinAlternate			initState	logica
		{enum_gpioB,	pin0,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_0
		{enum_gpioB,	pin1,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_1
		{enum_gpioB,	pin2,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_2
		{enum_gpioA,	pin4,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//CS Pin ADS1118
		{enum_gpioA,	pin3,		output_push_pull,			noPull,		speed_freq_low,			no_alternate_funtion,	off_state,	positiva},	//SSR Pin
		{enum_gpioD,	pin2,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//LED ERROR
		{enum_gpioB,	pin10,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_10
		{enum_gpioB,	pin14,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_14
		{enum_gpioB,	pin15,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_B_15
		{enum_gpioC,	pin6,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_C_6
		{enum_gpioC,	pin7,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//GPIO_C_7
		{enum_gpioC,	pin4,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//CS Pin TLE9201SG
		{enum_gpioC,	pin8,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//DIR Pin TLE9201SG
		{enum_gpioA,	pin11,		output_push_pull,			noPull,		speed_freq_low,	 		no_alternate_funtion,	off_state,	positiva},	//DIS Pin TLE9201SG

		// Completar segun aplicación
};
#endif
st_pin Digital_IOs_PHY[enum_Digital_IO_inSystem];
st_dig_io Digital_IOs[enum_Digital_IO_inSystem];

st_pin_config *digital_io_config_GetDigitalIOConfig(uint32_t index){
	return &Digital_IO_Config[index];
}

/* FUNCIONES DE DIGITAL OUTPUTS */
state digital_ios_Init(st_dig_io *this){
	basicPin_installFunctions(this->pin);
	return this->pin->pin_phy.actualState = this->pin->pin_func.init(&this->pin->pin_phy, this->pin->pin_config);
}
state digital_io_Write(st_dig_io *this, uint8_t newState){
	return this->pin->pin_phy.actualState = this->pin->pin_func.write(&this->pin->pin_phy, newState);
}
state digital_io_Read(st_dig_io *this){
	return this->pin->pin_phy.actualState = this->pin->pin_func.read(&this->pin->pin_phy);
}
/********************************/

st_dig_io *digital_io_config_GetDigitalIO(uint32_t index){
	return &Digital_IOs[index];
}

st_dig_io *digital_io_config_InitPhyDigitalIO(uint32_t index){
	st_dig_io *this = &Digital_IOs[index];

	Digital_IOs_PHY[index].pin_config = digital_io_config_GetDigitalIOConfig(index);
	this->pin = &Digital_IOs_PHY[index];
	return this;
}
