/*
 * basicPin.h
 *
 *  Created on: 14 jul. 2020
 *      Author: Laptop-Dell
 */

#ifndef BASICPIN_H_
#define BASICPIN_H_

#include "hardwareConfig.h"
#include "typdef_basicLib.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_clock.h"
#elif ARCHITECTURE == STM32F4xx
#include "stdbool.h"

#endif




/* ESTRUCTURA DE IRQ DEL PIN */
typedef struct pin_phy_IRQ{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	PORT_Type *Port_Pin;			//puerto
	IRQn_Type IRQ_type;				//numero de interrupcion en el vector
	port_interrupt_t interrupt_cond;//interrupt_cond: condición que genera la interrupcion
	uint64_t counter;				//variable para contar las entradas a la interrupcion
	uint64_t timeOnInterrupt;		//toma el timepo de systema cuando interrumpe
	bool IRQflag;					//flag que indica que hay que atender información de la IRQ

#elif ARCHITECTURE == STM32F4xx
	IRQn_Type IRQ_type;				//numero de interrupcion en el vector
	uint32_t PreemptPriority;		//The preemption priority for the IRQn channel (value between 0 and 15). A lower priority value indicates a higher priority
	uint32_t SubPriority;			//SubPriority the subpriority level for the IRQ channel (value between 0 and 15). A lower priority value indicates a higher priority
#endif
}st_pin_phy_IRQ;
/*******************************/

/* ESTRUCTURA FISICA DEL PIN */
typedef struct pin_phy{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	gpio_pin_config_t pinConfig;	//estructura de pin
	GPIO_Type *GPIO_Pin;			//puerto del pin
	pinNumber numberPin;			//numero del pin
	uint32_t listPlace;				//lugar en la lista enlazada de pines
	st_pin_phy_IRQ IRQ_pin;			//interrupcion del pin
	state actualState;				//estado actual del pin, teniendo en cuenta la logica que tiene
	uint32_t highTime;
	uint32_t lowTime;
	uint32_t highTimePulse;				//variable que guarda el tiempo en alto del pin
	uint32_t lowTimePulse;				//variable que guarda el tiempo en bajo del pin
	hasInterrupt hasIRQ;			//tiene interrupcion o no
	logica	logic;					//logica del pin, positiva o negativa
	clock_ip_name_t clockName;		//clock name del puerto para activar el clock
#elif ARCHITECTURE == STM32F4xx
	GPIO_TypeDef *GPIOn;			//puerto del pin
	GPIO_InitTypeDef pinConfig;		//estructura de pin
	uint32_t listPlace;				//lugar en la lista enlazada de pines
	st_pin_phy_IRQ IRQ_pin;			//interrupcion del pin
	state actualState;				//estado actual del pin, teniendo en cuenta la logica que tiene
	hasInterrupt hasIRQ;			//tiene interrupcion o no
	logica	logic;					//logica del pin, positiva o negativa
	uint32_t highTime;
	uint32_t lowTime;
	uint32_t highTimePulse;			//variable que guarda el tiempo en alto del pin
	uint32_t lowTimePulse;			//variable que guarda el tiempo en bajo del pin
#endif
}st_pin_phy;
/*****************************/

/* ESTRUCTURA DE CONFIGRUACION BASICA DEL PIN  */
/* Debe llamarse desde digital_inputs_config.c */
typedef struct pin_config{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS

	gpio_pin_direction_t pin_direction;	//direccion del pin, input u output
	enum_gpio enum_GPIO;				//enumaracion del gpio donde esta el pin
	pinNumber numberPin;					//nuemro de pin dentro del puerto
	port_interrupt_t interrupt_cond;	//condicion del la interupcion, si no tiene hay una condicion para eso
	hasInterrupt hasIRQ;				//tiene interrupcion o no
	logica	logic;						//logica del pin
	state initState;					//estado inicial como arranca el pin
#elif ARCHITECTURE == STM32F4xx
	enum_gpio		enum_GPIO;	/*!< Enumaración del gpio donde esta el pin */
	pinNumber		Pin;       	/*!< Specifies the GPIO pins to be configured. This parameter can be any value of @ref GPIO_pins_define */
	pinMode			Mode;      	/*!< Specifies the operating mode for the selected pins. This parameter can be a value of @ref GPIO_mode_define */
	pinPull			Pull;      	/*!< Specifies the Pull-up or Pull-Down activation for the selected pins. This parameter can be a value of @ref GPIO_pull_define */
	pinSpeed		Speed;     	/*!< Specifies the speed for the selected pins. This parameter can be a value of @ref GPIO_speed_define */
	pinAlternate	Alternate;	/*!< Peripheral to be connected to the selected pins. This parameter can be a value of @ref GPIO_Alternate_function_selection */
	state			initState;	/*!< Estado inicial del pin (En caso de ser configurado como salida) */
	logica			logic;		/*!< Logica del pin */
#endif
}st_pin_config;
/**********************************************/

/* FUNCIONES BASICAS DEL PIN */
typedef struct pin_functions{
	state (*init)(st_pin_phy *, st_pin_config *); 	//funcion de inicializacion
	state (*read)(st_pin_phy *);					//funcion para leer el estado del pin
	state (*write)(st_pin_phy *, uint8_t);			//funcion para escribir el estado del pin
}st_pin_functions;
/**************************/

/* ESTRUCTURA DE LISTA PARA PUERTOS */
typedef struct pinInfoList{
	st_pin_phy *prev;	//puntero al pin previo instalado en la lista
	st_pin_phy *this;	//puntero a este pin
	st_pin_phy *next;	//puntero al proximo pin instalado en la lista
}st_pin_list;
/***********************************/
/* ESTRUCTURA DE LISTA POR PUERTO */
typedef struct portInfoList{
	st_pin_list pin_list[32];	//array con 32 listas (uno por cada pin posibles)
	uint32_t index;				//indice de ocupacion
}st_portInfoList;

/* ESTRUCTURA DE PIN */
typedef struct pin{
	st_pin_config *pin_config;	//puntero a configuracion basica del pin. Debe ser instalada en digital_inputs_config.c
	st_pin_phy pin_phy;			//estructuta fisica del pin
	st_pin_functions pin_func;	//estructura de funciones basicas de pines. deben ser instaladas dentro de una funcion init
}st_pin;
/***********************/

void basicPin_SetSysTime(uint64_t *);
void basicPin_installFunctions(st_pin *);
uint32_t basicPin_InterruptConfig(st_pin_phy *);
state basicPin_Read(st_pin_phy *);
state basicPin_Write(st_pin_phy *, uint8_t);
state basicPin_Init(st_pin_phy *, st_pin_config *);

#endif /* BASICPIN_H_ */
