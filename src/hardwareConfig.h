//#define ESP32_BOARD
// #define STM32F4XX
//#define KINETICS

// #ifdef ESP32_BOARD
// #elif defined(STM32F4XX)
// #include "stm32f4xx_hal.h"
// #else
	//Default architecture.
// #endif

#define ESP32 1
#define STM32F4xx 2
#define KINTETIS 3

#define ARCHITECTURE STM32F4xx

#define DEFROSTER_BOARD 1
#define FROSTER_BOARD 2
#define DAQ_BOARD 3

#define BOARD FROSTER_BOARD

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
#include "stm32f4xx_hal.h"
#include "stm32f4xx.h"
#include "stdio.h"
#include "string.h"

//#include "Flash.h"
#else
	//Default architecture.
#endif
