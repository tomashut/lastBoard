/*
 * basicUART.c
 *
 *  Created on: 14 ago. 2020
 *      Author: Laptop-Dell
 */
#include "basicUART.h"

UART_HandleTypeDef *huart4;
UART_HandleTypeDef *husart2;

///***********************************************************************
// *							FUNCTIONS
// ***********************************************************************/

void UART4_IRQHandler(void)
{
  /* USER CODE BEGIN UART4_IRQn 0 */
//
  /* USER CODE END UART4_IRQn 0 */

	HAL_UART_IRQHandler(huart4);

  /* USER CODE BEGIN UART4_IRQn 1 */

  /* USER CODE END UART4_IRQn 1 */
}

void USART2_IRQHandler(void)
{
  /* USER CODE BEGIN USART2_IRQn 0 */

  /* USER CODE END USART2_IRQn 0 */
  HAL_UART_IRQHandler(husart2);
  /* USER CODE BEGIN USART2_IRQn 1 */

  /* USER CODE END USART2_IRQn 1 */
}
//st_uart_buffer UartBuffers[enum_uarts_onChip];
#ifdef KINETICS
void (*uart0_onInterrupt)(uint8_t data);
void (*uart1_onInterrupt)(uint8_t data);
void (*uart2_onInterrupt)(uint8_t data);
void (*uart3_onInterrupt)(uint8_t data);
void (*uart4_onInterrupt)(uint8_t data);
void (*uart5_onInterrupt)(uint8_t data);

void UART0_RX_TX_IRQHandler(void){
	uint32_t flags;
	uint8_t data;

	flags = UART_GetStatusFlags(UART0);
	if((kUART_FramingErrorFlag | kUART_NoiseErrorFlag) & flags){
		UART_ReadByte(UART0);//lectura para borrar los flags de error
	}
	else if((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags){
		data = UART_ReadByte(UART0);
		uart0_onInterrupt(data);

	}
	    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
	      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}

void UART1_RX_TX_IRQHandler(void){
	uint32_t flags;
	uint8_t data;

	flags = UART_GetStatusFlags(UART1);
	if((kUART_FramingErrorFlag | kUART_NoiseErrorFlag) & flags){
		UART_ReadByte(UART1);//lectura para borrar los flags de error
	}
	else if((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags){
		data = UART_ReadByte(UART1);
		uart1_onInterrupt(data);

	}
	    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
	      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}

void UART2_RX_TX_IRQHandler(void){
	uint32_t flags;
	uint8_t data;

	flags = UART_GetStatusFlags(UART2);
	if((kUART_FramingErrorFlag | kUART_NoiseErrorFlag) & flags){
		UART_ReadByte(UART2);//lectura para borrar los flags de error
	}
	else if((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags){
		data = UART_ReadByte(UART2);
		uart2_onInterrupt(data);
	}
	    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
	      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}

void UART3_RX_TX_IRQHandler(void){
	uint32_t flags;
	uint8_t data;


	flags = UART_GetStatusFlags(UART3);
	if((kUART_FramingErrorFlag | kUART_NoiseErrorFlag) & flags){
		UART_ReadByte(UART3);//lectura para borrar los flags de error
	}
	else if((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags){
		data = UART_ReadByte(UART3);
		uart3_onInterrupt(data);
	}
	    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
	      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}

void UART4_RX_TX_IRQHandler(void){
	uint32_t flags;
	uint8_t data;


	flags = UART_GetStatusFlags(UART4);
	if((kUART_FramingErrorFlag | kUART_NoiseErrorFlag) & flags){
		UART_ReadByte(UART4);//lectura para borrar los flags de error
	}
	else if((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags){
		data = UART_ReadByte(UART4);
		uart4_onInterrupt(data);

	}
	    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
	      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}

#ifdef UART5
void UART5_RX_TX_IRQHandler(void){
	uint32_t flags;
	uint8_t data;

	flags = UART_GetStatusFlags(UART5);
	if((kUART_FramingErrorFlag | kUART_NoiseErrorFlag) & flags){
		UART_ReadByte(UART5);//lectura para borrar los flags de error
	}
	else if((kUART_RxDataRegFullFlag | kUART_RxOverrunFlag) & flags){
		data = UART_ReadByte(UART5);
		uart5_onInterrupt(data);

	}
	    /* Add for ARM errata 838869, affects Cortex-M4, Cortex-M4F Store immediate overlapping
	      exception return operation might vector to incorrect interrupt */
#if defined __CORTEX_M && (__CORTEX_M == 4U)
	__DSB();
#endif
}
#endif
#endif

UART_ERR basicUART_InstallIRQ(st_uart_phy *this){
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	UART_EnableInterrupts(this->UART, kUART_RxDataRegFullInterruptEnable | kUART_RxOverrunInterruptEnable);
    EnableIRQ(this->IRQn);
    NVIC_SetPriority(this->IRQn, 2);
#elif ARCHITECTURE == STM32F4xx
    HAL_NVIC_SetPriority(this->IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(this->IRQn);
#endif
    return UART_ERROR_NONE;

}

/**
 * @brief Instala los parámetros del UART.
 *
 * Esta función instala los parámetros del UART según la configuración proporcionada.
 *
 * @param[in] this Puntero a la estructura de configuración física del UART.
 * @param[in] config Puntero a la estructura de configuración del UART.
 *
 * @return Estado de la operación (UART_ERROR_NONE si es exitosa).
 */
UART_ERR basicUART_ParamsInstall(st_uart_phy *this, st_uart_config *config){
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	switch(config->enum_GPIO){
	case enum_gpioA:
		this->Port_Pin = PORTA;
		this->GPIO_Pin = GPIOA;
		this->clockName = kCLOCK_PortA;
		break;
	case enum_gpioB:
		this->Port_Pin = PORTB;
		this->GPIO_Pin = GPIOB;
		this->clockName = kCLOCK_PortB;
		break;
	case enum_gpioC:
		this->Port_Pin = PORTC;
		this->GPIO_Pin = GPIOC;
		this->clockName = kCLOCK_PortC;
		break;
	case enum_gpioD:
		this->Port_Pin = PORTD;
		this->GPIO_Pin = GPIOD;
		this->clockName = kCLOCK_PortD;
		break;
	case enum_gpioE:
		this->Port_Pin = PORTE;
		this->GPIO_Pin = GPIOE;
		this->clockName = kCLOCK_PortE;
		break;
	default:
		break;
	}
	switch(config->uart_n){
#ifdef UART0
	case enum_uart0:
		this->UART = UART0;
		this->IRQn = UART0_RX_TX_IRQn;
		this->srcClock_Hz = CLOCK_GetFreq(UART0_CLK_SRC);
		uart0_onInterrupt = config->onInterrupt;
		break;
#endif
#ifdef UART1
	case enum_uart1:
		this->UART = UART1;
		this->IRQn = UART1_RX_TX_IRQn;
		this->srcClock_Hz = CLOCK_GetFreq(UART1_CLK_SRC);
		uart1_onInterrupt = config->onInterrupt;
		break;
#endif
#ifdef UART2
	case enum_uart2:
		this->UART = UART2;
		this->IRQn = UART2_RX_TX_IRQn;
		this->srcClock_Hz = CLOCK_GetFreq(UART2_CLK_SRC);
		uart2_onInterrupt = config->onInterrupt;
		break;
#endif
#ifdef UART3
	case enum_uart3:
		this->UART = UART3;
		this->IRQn = UART3_RX_TX_IRQn;
		this->srcClock_Hz = CLOCK_GetFreq(UART3_CLK_SRC);
		uart3_onInterrupt = config->onInterrupt;
		break;
#endif
#ifdef UART4
	case enum_uart4:
		this->UART = UART4;
		this->IRQn = UART4_RX_TX_IRQn;
		this->srcClock_Hz = CLOCK_GetFreq(UART4_CLK_SRC);
		uart4_onInterrupt = config->onInterrupt;
		break;
#endif
#ifdef UART5
	case enum_uart5:
		this->UART = UART5;
		this->IRQn = UART5_RX_TX_IRQn;
		uart5_onInterrupt = config->onInterrupt;
		break;
#endif
	default:
		break;
	}
	this->buffer.rx_buff = config->rxBuffer;
	this->buffer.tx_buff = config->txBuffer;
	this->portmux_select = config->mux_select;
	this->numberPinRX = config->numberPinRX;
	this->numberPinTX = config->numberPinTX;
	this->hasIRQ = config->has_interrupt;

#elif ARCHITECTURE == STM32F4xx
	switch(config->uartNum)
		{
			case enum_uart4:
				this->handlerUART.Instance = UART4;
			    __HAL_RCC_UART4_CLK_ENABLE();
			    this->IRQn=UART4_IRQn;
			break;
			case enum_uart5:
				this->handlerUART.Instance = UART5;
				__HAL_RCC_UART5_CLK_ENABLE();
				this->IRQn=UART5_IRQn;
			break;
			case reserved:
			break;
			case enum_uart7:
				this->handlerUART.Instance = UART7;
				__HAL_RCC_UART7_CLK_ENABLE();
				this->IRQn=UART7_IRQn;
			break;
			case enum_uart8:
				this->handlerUART.Instance = UART8;
				__HAL_RCC_UART8_CLK_ENABLE();
				this->IRQn=UART8_IRQn;
			break;
			case enum_uart9:
				this->handlerUART.Instance = UART9;
				__HAL_RCC_UART9_CLK_ENABLE();
				this->IRQn=UART9_IRQn;
			break;
			case enum_uart10:
				this->handlerUART.Instance = UART10;
				__HAL_RCC_UART10_CLK_ENABLE();
				this->IRQn=UART10_IRQn;
			break;
			case enum_usart1:
				this->handlerUART.Instance = USART1;
				__HAL_RCC_USART1_CLK_ENABLE();
				this->IRQn=USART1_IRQn;
			break;
			case enum_usart2:
				this->handlerUART.Instance = USART2;
				__HAL_RCC_USART2_CLK_ENABLE();
				this->IRQn=USART2_IRQn;
			break;
			case enum_usart3:
				this->handlerUART.Instance = USART3;
				__HAL_RCC_USART3_CLK_ENABLE();
				this->IRQn=USART3_IRQn;
			break;
			case enum_usart6:
				this->handlerUART.Instance = USART6;
				__HAL_RCC_USART6_CLK_ENABLE();
				this->IRQn=USART6_IRQn;
			break;
		}
	switch(config->wordLength)
	{
		case wordlength8B:
			this->handlerUART.Init.WordLength = UART_WORDLENGTH_8B ;
		break;
		case wordlength9B:
			this->handlerUART.Init.WordLength = UART_WORDLENGTH_9B;
		break;
	}

	switch(config->parity)
	{
		case parity_none:
			this->handlerUART.Init.Parity = UART_PARITY_NONE ;
		break;
		case parity_even:
			this->handlerUART.Init.Parity = UART_PARITY_EVEN;
		break;
		case parity_odd:
			this->handlerUART.Init.Parity = UART_PARITY_ODD;
		break;
	}

	switch(config->stopBits)
	{
		case stopbits_1:
			this->handlerUART.Init.StopBits = UART_STOPBITS_1 ;
		break;
		case stopbits_2:
			this->handlerUART.Init.StopBits = UART_STOPBITS_2;
		break;
	}

	switch(config->hwFlowControl)
	{
		case hwcontrol_none:
			this->handlerUART.Init.HwFlowCtl = UART_HWCONTROL_NONE ;
		break;
		case hwcontrol_rts:
			this->handlerUART.Init.HwFlowCtl = UART_HWCONTROL_RTS;
		break;
		case hwcontrol_cts:
			this->handlerUART.Init.HwFlowCtl = UART_HWCONTROL_CTS;
		break;
		case hwcontrol_rts_cts:
			this->handlerUART.Init.HwFlowCtl = UART_HWCONTROL_RTS_CTS;
		break;
	}

	switch(config->mode)
	{
		case rx_mode:
			this->handlerUART.Init.Mode = UART_MODE_RX ;
		break;
		case tx_mode:
			this->handlerUART.Init.Mode = UART_MODE_TX;
		break;
		case rx_tx_mode:
			this->handlerUART.Init.Mode = UART_MODE_TX_RX;
		break;
	}

	switch(config->oversampling)
	{
		case oversampling_16:
			this->handlerUART.Init.OverSampling = UART_OVERSAMPLING_16 ;
		break;
		case oversampling_8:
			this->handlerUART.Init.OverSampling = UART_OVERSAMPLING_8;
		break;
	}

	this->handlerUART.Init.BaudRate = config->baudrate;
	this->pRxBuffPtr	 			= config->rxBuffer;
	this->pTxBuffPtr	 			= config->txBuffer;
	this->handlerUART.pRxBuffPtr	= config->rxBuffer;
	this->handlerUART.pTxBuffPtr 	= config->txBuffer;
	this->timeout					= config->timeout;

#endif
	return UART_ERROR_NONE;
}

/**
 * @brief Recibe datos a través del UART.
 *
 * Esta función recibe datos a través del UART según la configuración proporcionada.
 *
 * @param[in] this Puntero a la estructura de configuración física del UART.
 *
 * @return Estado de la operación (UART_ERROR_NONE si es exitosa, UART_RECEIVE_ERROR si hay un error durante la recepción).
 */
UART_ERR basicUART_Receive(st_uart_phy *this){
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	UART_WriteBlocking(this->UART, this->buffer.tx_buff, len);
	return UART_ERROR_NONE;
#elif ARCHITECTURE == STM32F4xx
	if((HAL_UARTEx_ReceiveToIdle_IT(&this->handlerUART,this->pRxBuffPtr,this->RxXferSize)) != HAL_OK)
	{
		return UART_RECEIVE_ERROR;
	}
	return UART_ERROR_NONE;

//	if((HAL_UART_Receive(&this->handlerUART,this->pRxBuffPtr,this->RxXferSize,this->timeout)) != HAL_OK)
//	{
//		return UART_RECEIVE_ERROR;
//	}
//	return UART_ERROR_NONE;

#endif
}

/**
 * @brief Envía datos a través del UART.
 *
 * Esta función envía datos a través del UART según la configuración proporcionada.
 *
 * @param[in] this Puntero a la estructura de configuración física del UART.
 * @param[in] len Longitud de los datos a enviar.
 *
 * @return Estado de la operación (UART_ERROR_NONE si es exitosa, UART_TRANSMIT_ERROR si hay un error durante la transmisión).
 */
UART_ERR basicUART_Send(st_uart_phy *this, uint32_t len){
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	UART_WriteBlocking(this->UART, this->buffer.tx_buff, len);
	return UART_ERROR_NONE;
#elif ARCHITECTURE == STM32F4xx
	if((HAL_UART_Transmit(&this->handlerUART,this->pTxBuffPtr,this->TxXferSize, this->timeout)) != HAL_OK)
	{
		return UART_TRANSMIT_ERROR;
	}
 	return UART_ERROR_NONE;
#endif
}

/**
 * @brief Inicializa el UART.
 *
 * Esta función inicializa el UART según la configuración proporcionada.
 *
 * @param[in] this Puntero a la estructura de configuración física del UART.
 * @param[in] config Puntero a la estructura de configuración del UART.
 *
 * @return Estado de la operación (UART_ERROR_NONE si es exitosa, UART_INIT_ERROR si hay un error durante la inicialización).
 */
UART_ERR basicUART_Init(st_uart_phy *this, st_uart_config *config){
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
	basicUART_ParamsInstall(this,  config);
	CLOCK_EnableClock(this->clockName);
	PORT_SetPinMux(this->Port_Pin, this->numberPinRX, this->portmux_select);
	PORT_SetPinMux(this->Port_Pin, this->numberPinTX, this->portmux_select);
	UART_GetDefaultConfig(&this->uartConfig);
	this->uartConfig.enableTx = true;
	this->uartConfig.enableRx = true;
	this->uartConfig.baudRate_Bps = config->baudrate;
	UART_Init(this->UART, &this->uartConfig, this->srcClock_Hz);
	if(this->hasIRQ){
		basicUART_InstallIRQ(this);
	}
	return UART_ERROR_NONE;
#elif ARCHITECTURE == STM32F4xx
	basicUART_ParamsInstall(this, config);
	if (HAL_UART_Init(&this->handlerUART) != HAL_OK)
	{
		return UART_INIT_ERROR;
	/*Error Handler*/
		while(1);
	}

	if(config->has_interrupt)
	{
		basicUART_InstallIRQ(this);
	}

	if (this->handlerUART.Instance == UART4)
	{
		huart4=&this->handlerUART;
	}
	else if (this->handlerUART.Instance == USART2)
	{
		husart2=&this->handlerUART;
	}

	return UART_ERROR_NONE;
#endif
}

/**
 * @brief Instala las funciones del UART.
 *
 * Esta función instala las funciones del UART en una estructura específica.
 *
 * @param[in] this Puntero a la estructura de configuración del UART.
 *
 * @return Estado de la operación (UART_ERROR_NONE si es exitosa).
 */
UART_ERR basicUart_InstallFunctions(st_uart *this){
	this->uart_func.init 	= basicUART_Init;
	this->uart_func.receive = basicUART_Receive;
	this->uart_func.send 	= basicUART_Send;
	this->uart_func.pinInit = &basicPin_Init;
	return UART_ERROR_NONE;
}

