#ifndef TYPEDEF_BASICLIB_H_ 
#define TYPEDEF_BASICLIB_H_ 

#include "hardwareConfig.h"

typedef enum{
	negativa,
	positiva
}enum_logica;

typedef enum{
	no,
	yes
}enum_no_yes_q;

typedef enum{
	off_state,
	on_state,
}enum_states;

typedef enum{
	off,
	on,
	disable,
}enum_extended_state;

typedef enum {
	enum_gpioA,
	enum_gpioB,
	enum_gpioC,
	enum_gpioD,
	enum_gpioE,
	enum_gpioF,
	enum_gpioG,
	enum_gpioH
}enum_gpio;

typedef enum {
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	enum_uart0,
	enum_uart1,
	enum_uart2,
	enum_uart3,
	enum_uart4,
#ifdef UART5
	enum_uart5,
#endif
	enum_uarts_onChip
#elif ARCHITECTURE == STM32F4xx
	enum_uart4,
	enum_uart5,
	reserved,
	enum_uart7,
	enum_uart8,
	enum_uart9,
	enum_uart10,
	enum_usart1,
	enum_usart2,
	enum_usart3,
	enum_usart6
	//#elif defined(OTHER)
#else
#endif
}enum_uarts;

typedef enum {
	wordlength8B,
	wordlength9B
}enum_uart_word_lenth;

typedef enum {
	stopbits_1,
	stopbits_2
}enum_uart_stopBits;

typedef enum {
	parity_none,
	parity_even,
	parity_odd
}enum_uart_parity;

typedef enum {
	hwcontrol_none,
	hwcontrol_rts,
	hwcontrol_cts,
	hwcontrol_rts_cts
}enum_uart_hfc;

typedef enum {
	rx_mode,
	tx_mode,
	rx_tx_mode
}enum_uart_modes;

typedef enum {
	oversampling_16,
	oversampling_8
}enum_uart_oversampling;

typedef enum{
	i2c_1,
	i2c_2,
	i2c_3,
	enum_i2c_onchip
}enum_i2c;

typedef enum{
	i2c_dutyCycle_2,
	i2c_dutyCycle_16_9
}enum_i2c_dutyCycle;

typedef enum{
	i2c_addressingMode_7bit,
	i2c_addressingMode_10bit
}enum_i2c_addressingMode;
typedef enum_i2c_addressingMode enum_AddressingMode;

typedef enum{
	i2c_dualAddress_disable,
	i2c_dualAddress_enable
}enum_i2c_dualAddressingMode;
typedef enum_i2c_dualAddressingMode DualAddressingMode;

typedef enum{
	i2c_generalCall_disable,
	i2c_generalCall_enable
}enum_i2c_generalCallAddressingMode;
typedef enum_i2c_generalCallAddressingMode GeneralCallAddressingMode;

typedef enum{
	i2c_nostretch_disable,
	i2c_nostretch_enable
}enum_i2c_nostretchMode;
typedef enum_i2c_nostretchMode NostretchModeMode;


typedef enum{
	write,
	read
}enum_directionMode;

typedef enum{
	spi_1,
	spi_2,
	spi_3,
	spi_4,
	spi_5
}enum_spi;

typedef enum{
	slave,
	master
}enum_mode;

typedef enum{
	simplex,
	halfDuplex,
	fullDuplex
}enum_typeCommunication;

typedef enum{
	baudrateprescaler_2,
	baudrateprescaler_4,
	baudrateprescaler_8,
	baudrateprescaler_16,
	baudrateprescaler_32,
	baudrateprescaler_64,
	baudrateprescaler_128,
	baudrateprescaler_256
}enum_prescaler;

typedef enum{
    adcprescaler_2,
    adcprescaler_4,
    adcprescaler_8
}enum_adc_prescaler;
typedef enum{
    resolution_12bit,
    resolution_10bit,
    resolution_8bit
}enum_adc_resolution;

typedef enum{
	adcDefaultConfig,
	adcCustomConfig
}enum_adc_config;

typedef enum{
	adcPortA,
	adcPortB,
	adcPortC,
	adcPortD,
	adcPortE,
	dedicated
}enum_adc_port;

typedef enum{
	adc0,
	adc1
}enum_ADCn;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	pin0,
	pin1,
	pin2,
	pin3,
	pin4,
	pin5,
	pin6,
	pin7,
	pin8,
	pin9,
	pin10,
	pin11,
	pin12,
	pin13,
	pin14,
	pin15,
	pin16,
	pin17,
	pin18,
	pin19,
	pin20,
	pin21,
	pin22,
	pin23,
	pin24,
	pin25,
	pin26,
	pin27,
	pin28,
	pin29,
	pin30,
	pin31,
	dontCare,
#elif ARCHITECTURE == STM32F4xx
	pin0,
	pin1,
	pin2,
	pin3,
	pin4,
	pin5,
	pin6,
	pin7,
	pin8,
	pin9,
	pin10,
	pin11,
	pin12,
	pin13,
	pin14,
	pin15,
	allPins
#endif
}enum_pinNumber;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
input,
output_push_pull,
output_open_drain,
alternate_push_pull,
alternate_open_drain,
analog_mode,
ext_interr_rising_edge,
ext_interr_falling_edge,
ext_interr_rising_falling_edge,
ext_event_rising_edge,
ext_event_falling_edge,
ext_event_rising_falling_edge
#endif
}enum_pinMode;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	noPull,
	pullUp,
	pullDown
#endif
}enum_pinPull;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	speed_freq_low,
	speed_freq_medium,
	speed_freq_high,
	speed_freq_very_high
#endif
}enum_pinSpeed;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	no_alternate_funtion,
	alternate_function_0,
	alternate_function_1,
	alternate_function_2,
	alternate_function_3,
	alternate_function_4,
	alternate_function_5,
	alternate_function_6,
	alternate_function_7,
	alternate_function_8,
	alternate_function_9,
	alternate_function_10,
	alternate_function_11,
	alternate_function_12,
	alternate_function_13,
	alternate_function_14,
	alternate_function_15
#endif
}enum_pinAlternate;

typedef enum{
	typeof_uint32_t,
	typeof_float,
	typeof_string,
}enum_typeof;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	tim1,
	tim2,
	tim3,
	tim4,
	tim5,
	tim6,
	tim7,
	tim8,
	tim9,
	tim10,
	tim11,
	tim12,
	tim13,
	tim14
#endif
}enum_timer;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	timer_interrupt,
	timer_PWM
#endif
}enum_timerMode;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	countermode_up,
	countermode_down,
	countermode_centraligned1,
	countermode_centraligned2,
	countermode_centraligned3
#endif
}enum_timer_counter_mode;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	clockdivision_1,
	clockdivision_2,
	clockdivision_4
#endif
}enum_timer_clock_division;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	auto_is_disable,
	auto_is_enable
#endif
}enum_timer_reload_preload;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	clockSource_internal,
	clockSource_etrmode1,
	clockSource_etrmode2,
	clockSource_ti1ed,
	clockSource_ti1,
	clockSource_ti2,
	clockSource_itr0,
	clockSource_itr1,
	clockSource_itr2,
	clockSource_itr3
#endif
}enum_timer_clock_source;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	trgo_reset,
	trgo_enable,
	trgo_update,
	trgo_oc1,
	trgo_oc1ref,
	trgo_oc2ref,
	trgo_oc3ref,
	trgo_oc4ref
#endif
}enum_timer_master_mode_selection;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	slaveMode_enable,
	slaveMode_disable
#endif
}enum_timer_master_slave_mode;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	active_channel_1,
	active_channel_2,
	active_channel_3,
	active_channel_4,
	active_channel_cleared
#endif
}enum_timer_channel;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	noEffect,
	startSingleConversion
#endif
}ss_bit_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	imput_A0_A1,
	imput_A0_A3,
	imput_A1_A3,
	imput_A2_A3,
	imput_A0_GND,
	imput_A1_GND,
	imput_A2_GND,
	imput_A3_GND
#endif
}mux_bits_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	fullScaleRange_6144,
	fullScaleRange_4096,
	fullScaleRange_2048,
	fullScaleRange_1024,
	fullScaleRange_0512,
	fullScaleRange_0256
#endif
}pga_bits_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	ContinuousConversionMode,
	powerDown_singleShotMode
#endif
}mode_bit_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	dataRate_8sps,
	dataRate_16sps,
	dataRate_32sps,
	dataRate_64sps,
	dataRate_128sps,
	dataRate_250sps,
	dataRate_475sps,
	dataRate_860sps
#endif
}dr_bits_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	adcMode,
	temperatureSensorMode
#endif
}tsMode_bit_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	pullUpDisable,
	pullUpEnable
#endif
}pullUp_bit_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
invalidConfig,
validConfig
#endif
}nop_bits_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	dontCare,
	reservedBit
#endif
}reserved_bit_t;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	independent,
	windows
#endif
}enum_watchdog_mode;

typedef enum{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	preescaler_4,
	preescaler_8,
	preescaler_16,
	preescaler_32,
	preescaler_64,
	preescaler_128,
	preescaler_256
#endif
}enum_watchdog_preescaaler;

typedef enum_ADCn ADCn;
typedef enum_adc_config ADC_Config;
typedef enum_adc_port ADC_Port;
typedef enum_states state;
typedef enum_extended_state extState;
typedef enum_no_yes_q hasInterrupt;
typedef enum_no_yes_q resourceUsed;
typedef enum_logica logica;
typedef enum_pinNumber pinNumber;
typedef enum_pinMode pinMode;
typedef enum_pinPull pinPull;
typedef enum_pinSpeed pinSpeed;
typedef enum_pinAlternate pinAlternate;
typedef enum_typeof typeOf;
typedef enum_timer_counter_mode counterMode;
typedef enum_timer_clock_division clockDiv;
typedef enum_timer_reload_preload autoReloadPreload;
typedef enum_timer_clock_source clockSource;
typedef enum_timer_master_mode_selection masterOutputTrigger;
typedef enum_timer_master_slave_mode masterSlaveMode;
typedef enum_timer_channel enum_channel;
typedef ss_bit_t ss_bit;
typedef mux_bits_t mux_bits;
typedef pga_bits_t pga_bits;
typedef mode_bit_t mode_bit;
typedef dr_bits_t dr_bits;
typedef tsMode_bit_t tsMode_bit;
typedef pullUp_bit_t pullUp_bit;
typedef nop_bits_t nop_bits;
typedef reserved_bit_t reserved_bit;
#endif /*TYPEDEF_BASICLIB_H_ */
