
/***********************************************************************
 *							INCLUDES
 ***********************************************************************/
#include "basicCAN.h"

/***********************************************************************
 *							VARIABLES
 ***********************************************************************/

#define CAN_MESSAGE_BUF_NUM   16
CAN_HandleTypeDef *hcan1;
CAN_HandleTypeDef *hcan2;

//st_pin_config can_RxConfig={
//		.Mode=alternate_push_pull,
//		.Pull=pullUp,
//		.Speed=speed_freq_very_high,
//		.Alternate=alternate_function_9,
//		.logic=positiva
//};
//st_pin_config can_TxConfig={
//		.Mode=alternate_push_pull,
//		.Pull=noPull,
//		.Speed=speed_freq_very_high,
//		.Alternate=alternate_function_9,
//		.logic=positiva
//};

void CAN1_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */

  /* USER CODE END CAN1_RX0_IRQn 0 */
HAL_CAN_IRQHandler(hcan1);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}

void CAN2_RX0_IRQHandler(void)
{
  /* USER CODE BEGIN CAN1_RX0_IRQn 0 */

  /* USER CODE END CAN1_RX0_IRQn 0 */
HAL_CAN_IRQHandler(hcan2);
  /* USER CODE BEGIN CAN1_RX0_IRQn 1 */

  /* USER CODE END CAN1_RX0_IRQn 1 */
}
/***********************************************************************
 *							FUNCTIONS
 ***********************************************************************/
CAN_ERR basicCAN_InstallIRQ(st_canPhy *this){
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
    HAL_NVIC_SetPriority(this->canIRQn, 0, 0);
    HAL_NVIC_EnableIRQ(this->canIRQn);
#endif
    return CAN_ERROR_NONE;

}


CAN_ERR basicCAN_ParamsInstall(st_canPhy* this, st_canConfig* config)
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

	switch(config->canNum)
	{
	case can_1: this->handlerCan.Instance = CAN1; __HAL_RCC_CAN1_CLK_ENABLE(); break;
	case can_2: this->handlerCan.Instance = CAN2; __HAL_RCC_CAN2_CLK_ENABLE(); break;
	case can_3: this->handlerCan.Instance = CAN3; __HAL_RCC_CAN3_CLK_ENABLE(); break;
	default	: break;
	}

	switch(config->mode)
	{
	case can_normalMode:		 this->handlerCan.Init.Mode = CAN_MODE_NORMAL; 			break;
	case can_LoopBackMode:		 this->handlerCan.Init.Mode = CAN_MODE_LOOPBACK; 		break;
	case can_SilentMode:		 this->handlerCan.Init.Mode = CAN_MODE_SILENT; 			break;
	case can_SilentLoopbackMode: this->handlerCan.Init.Mode = CAN_MODE_SILENT_LOOPBACK; break;
	}

	switch(config->syncJumpWidth)
	{
	case can_sjw_1tq: this->handlerCan.Init.SyncJumpWidth = CAN_SJW_1TQ; break;
	case can_sjw_2tq: this->handlerCan.Init.SyncJumpWidth = CAN_SJW_2TQ; break;
	case can_sjw_3tq: this->handlerCan.Init.SyncJumpWidth = CAN_SJW_3TQ; break;
	case can_sjw_4tq: this->handlerCan.Init.SyncJumpWidth = CAN_SJW_4TQ; break;
	}

	switch (config->timeSeg1)
	{
	case can_bs1_1tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_1TQ;  break;
	case can_bs1_2tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_2TQ;  break;
	case can_bs1_3tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_3TQ;  break;
	case can_bs1_4tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_4TQ;  break;
	case can_bs1_5tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_5TQ;  break;
	case can_bs1_6tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_6TQ;  break;
	case can_bs1_7tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_7TQ;  break;
	case can_bs1_8tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_8TQ;  break;
	case can_bs1_9tq:  this->handlerCan.Init.TimeSeg1 = CAN_BS1_9TQ;  break;
	case can_bs1_10tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_10TQ; break;
	case can_bs1_11tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_11TQ; break;
	case can_bs1_12tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_12TQ; break;
	case can_bs1_13tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_13TQ; break;
	case can_bs1_14tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_14TQ; break;
	case can_bs1_15tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_15TQ; break;
	case can_bs1_16tq: this->handlerCan.Init.TimeSeg1 = CAN_BS1_16TQ; break;
	default: break;
	}

	switch (config->timeSeg2)
	{
	case can_bs2_1tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_1TQ; break;
	case can_bs2_2tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_2TQ; break;
	case can_bs2_3tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_3TQ; break;
	case can_bs2_4tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_4TQ; break;
	case can_bs2_5tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_5TQ; break;
	case can_bs2_6tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_6TQ; break;
	case can_bs2_7tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_7TQ; break;
	case can_bs2_8tq: this->handlerCan.Init.TimeSeg2 = CAN_BS2_8TQ; break;
	default: break;
	}

	this->handlerCan.Init.Prescaler				= config->prescaler;
	this->handlerCan.Init.TimeTriggeredMode		= DISABLE;
	this->handlerCan.Init.AutoBusOff			= DISABLE;
	this->handlerCan.Init.AutoWakeUp			= DISABLE;
	this->handlerCan.Init.AutoRetransmission	= DISABLE;
	this->handlerCan.Init.ReceiveFifoLocked		= DISABLE;
	this->handlerCan.Init.TransmitFifoPriority	= DISABLE;

	if (config->filter_On_Off == can_filter_enable)
	{
		this->canFilterConfig.FilterActivation = CAN_FILTER_ENABLE;
		switch (config->filterFIFOx)
		{
		case can_fifo0: this->canFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO0; this->rxFIFO = CAN_RX_FIFO0; break;
		case can_fifo1: this->canFilterConfig.FilterFIFOAssignment = CAN_FILTER_FIFO1; this->rxFIFO = CAN_RX_FIFO1; break;
		}
		switch (config->filterMode)
		{
		case can_filterMode_IDMask: this->canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK; break;
		case can_filterMode_IDList: this->canFilterConfig.FilterMode = CAN_FILTERMODE_IDLIST; break;
		}
		switch (config->filterScale)
		{
		case can_filterScale_16bits: this->canFilterConfig.FilterScale = CAN_FILTERSCALE_16BIT; break;
		case can_filterScale_32bits: this->canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT; break;
		}

		this->canFilterConfig.FilterBank			= config->filterBank;
		this->canFilterConfig.FilterIdHigh			= config->filterIdHigh;
		this->canFilterConfig.FilterIdLow			= config->filterIdLow;
		this->canFilterConfig.FilterMaskIdHigh		= config->filterMaskIdHigh;
		this->canFilterConfig.FilterMaskIdLow		= config->filterMaskIdLow;
		this->canFilterConfig.SlaveStartFilterBank	= config->slaveStartFilterBank;
	}
	else {
	this->canFilterConfig.FilterActivation = CAN_FILTER_DISABLE;
	}

	if (config->hasInterrupt == yes)
	{
		switch (config->canNum)
		{
		case can_1:
			switch (config->canIT)
			{
			case can_tx_IRQn:  this->canIRQn = CAN1_TX_IRQn;  break;
			case can_rx0_IRQn: this->canIRQn = CAN1_RX0_IRQn; break;
			case can_rx1_IRQn: this->canIRQn = CAN1_RX1_IRQn; break;
			case can_sce_IRQn: this->canIRQn = CAN1_SCE_IRQn; break;
			}
		break;
		case can_2:
			switch (config->canIT)
			{
			case can_tx_IRQn:  this->canIRQn = CAN2_TX_IRQn;  break;
			case can_rx0_IRQn: this->canIRQn = CAN2_RX0_IRQn; break;
			case can_rx1_IRQn: this->canIRQn = CAN2_RX1_IRQn; break;
			case can_sce_IRQn: this->canIRQn = CAN2_SCE_IRQn; break;
			}
		break;
		case can_3:
			switch (config->canIT)
			{
			case can_tx_IRQn:  this->canIRQn = CAN3_TX_IRQn;  break;
			case can_rx0_IRQn: this->canIRQn = CAN3_RX0_IRQn; break;
			case can_rx1_IRQn: this->canIRQn = CAN3_RX1_IRQn; break;
			case can_sce_IRQn: this->canIRQn = CAN3_SCE_IRQn; break;
			}
		break;
		}
		switch (config->activeITs)
		{
			case can_it_tx_mailbox_empty:	  this->activeITs = CAN_IT_TX_MAILBOX_EMPTY;	 break;
			case can_it_rx_fifo0_msg_pending: this->activeITs = CAN_IT_RX_FIFO0_MSG_PENDING; break;
			case can_it_rx_fifo0_full:		  this->activeITs = CAN_IT_RX_FIFO0_FULL;		 break;
			case can_it_rx_fifo0_overrun:	  this->activeITs = CAN_IT_RX_FIFO0_OVERRUN;	 break;
			case can_it_rx_fifo1_msg_pending: this->activeITs = CAN_IT_RX_FIFO1_MSG_PENDING; break;
			case can_it_rx_fifo1_full:		  this->activeITs = CAN_IT_RX_FIFO1_FULL;		 break;
			case can_it_rx_fifo1_overrun:	  this->activeITs = CAN_IT_RX_FIFO1_OVERRUN;	 break;
			case can_it_wakeup:				  this->activeITs = CAN_IT_WAKEUP;				 break;
			case can_it_sleep_ack:			  this->activeITs = CAN_IT_SLEEP_ACK;			 break;
			case can_it_error_warning:		  this->activeITs = CAN_IT_ERROR_WARNING;		 break;
			case can_it_error_passive:		  this->activeITs = CAN_IT_ERROR_PASSIVE;		 break;
			case can_it_busoff:				  this->activeITs = CAN_IT_BUSOFF;				 break;
			case can_it_last_error_code:	  this->activeITs = CAN_IT_LAST_ERROR_CODE;		 break;
			case can_it_error:				  this->activeITs = CAN_IT_ERROR;				 break;
		}
	}
//	can_RxConfig.enum_GPIO=config->GPIOn;
//	can_TxConfig.enum_GPIO=config->GPIOn;
//	can_RxConfig.Pin=config->rxPin;
//	can_TxConfig.Pin=config->txPin;
//	this->rxPin.pin_config = config->rxPin_config;
//	this->txPin.pin_config = config->txPin_config;
//#elif defined(OTHER)
#else
#endif
	return CAN_ERROR_NONE;
}


CAN_ERR basicCanInit(st_canPhy* this, st_canConfig* config)
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

	basicCAN_ParamsInstall(this, config);

	if(HAL_CAN_Init(&this->handlerCan) != HAL_OK)
	{
		return CAN_INIT_ERROR;
	}
	if(HAL_CAN_ConfigFilter(&this->handlerCan, &this->canFilterConfig)!= HAL_OK)
	{
		return CAN_INIT_ERROR;
	}
	if(HAL_CAN_Start(&this->handlerCan)!= HAL_OK)
	{
		return CAN_INIT_ERROR;
	}

	if (config->hasInterrupt == yes)
	{
//		HAL_CAN_ActivateNotification(&this->handlerCan, this->activeITs);
		basicCAN_InstallIRQ(this);
	}

	switch (config->canNum) {
		case can_1:
			hcan1 = &this->handlerCan;
			break;
		case can_2:
			hcan2 = &this->handlerCan;
			break;
		default:
			break;
	}
//#elif defined(OTHER)
#else
#endif
	return CAN_ERROR_NONE;
}

CAN_ERR basicCanSend(st_canPhy* this)
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

	/*Enviar el mensaje*/
    if(HAL_CAN_AddTxMessage(&this->handlerCan, &this->txHeader, this->txData, &this->txMailBox) != HAL_OK)
    {
		return CAN_TRANSMIT_ERROR;
	}
    HAL_CAN_IsTxMessagePending(&this->handlerCan,this->txMailBox);
//#elif defined(OTHER)
#else
#endif

	return CAN_ERROR_NONE;
}

CAN_ERR	basicCanRead(st_canPhy* this)
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

	/* Recibir el mensaje */
	if (HAL_CAN_GetRxMessage(&this->handlerCan, this->rxFIFO, &this->rxHeader, this->rxData) != HAL_OK)
	{
		return CAN_RECEIVE_ERROR;
	}
//#elif defined(OTHER)
#else
#endif
	return CAN_ERROR_NONE;
}

CAN_ERR basicCanEnable(st_canPhy *this, uint32_t baudrate)
{
    // No es necesario, ya que la inicialización del CAN lo habilita
	(void)this;
	return CAN_ERROR_NONE;
}

CAN_ERR basicCanReset(st_canPhy *this)
{
    // Reiniciar el controlador CAN si es necesario
	(void)this;
	return CAN_ERROR_NONE;
}

CAN_ERR basicCanClose(st_canPhy *this)
{
//	HAL_CAN_Stop()
	(void)this;
	return CAN_ERROR_NONE;
}


CAN_ERR basicCAN_InstallFunctions(st_basicCan *this)
{
	this->can_func.init 	 = basicCanInit;
	this->can_func.send 	 = basicCanSend;
	this->can_func.read 	 = basicCanRead;
	this->can_func.enable	 = basicCanEnable;
	this->can_func.reset	 = basicCanReset;
	this->can_func.close	 = basicCanClose;
	this->can_func.pinInit	 = &basicPin_Init;

	return CAN_ERROR_NONE;
}
