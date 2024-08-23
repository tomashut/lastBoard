/*
 * can_config.c
 *
 *  Created on: Apr 4, 2024
 *      Author: CRINSURANCE 1
 */


#include <can_config.h>

/*********** CONFIGURACION DE BUS CAN EN SISTEMA *************/
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
st_canConfig CAN_config[eunm_can_inSystem]={
		{
				.rxPin_config={
						.enum_GPIO	= enum_gpioB,
						.Pin		= pin8,
						.Mode		= alternate_push_pull,
						.Pull		= pullUp,
						.Speed		= speed_freq_very_high,
						.Alternate	= alternate_function_8,
						.logic		= positiva
				},
				.txPin_config={
						.enum_GPIO	= enum_gpioB,
						.Pin		= pin9,
						.Mode		= alternate_push_pull,
						.Pull		= noPull,
						.Speed		= speed_freq_very_high,
						.Alternate	= alternate_function_8,
						.logic		= positiva
				},
				.canNum				  = can_1,
				.prescaler			  = 18,
				.mode				  = can_normalMode,
				.syncJumpWidth		  = can_sjw_1tq,
				.timeSeg1			  = can_bs1_4tq,
				.timeSeg2			  = can_bs2_2tq,
				.filter_On_Off		  = can_filter_enable,
				.filterBank			  = 14,
				.filterFIFOx		  = can_fifo0,
				.filterIdHigh		  = 0,
				.filterIdLow		  = 0,
				.filterMaskIdHigh	  = 0,
				.filterMaskIdLow	  = 0,
				.filterMode			  = can_filterMode_IDMask,
				.filterScale		  = can_filterScale_32bits,
				.slaveStartFilterBank = 14,
				.hasInterrupt		  = yes,
				.canIT				  = can_rx0_IRQn,
				.activeITs			  = can_it_rx_fifo0_msg_pending
		},
		{
				.rxPin_config={
						.enum_GPIO	= enum_gpioB,
						.Pin		= pin12,
						.Mode		= alternate_push_pull,
						.Pull		= pullUp,
						.Speed		= speed_freq_very_high,
						.Alternate	= alternate_function_9,
						.logic		= positiva
				},
				.txPin_config={
						.enum_GPIO	= enum_gpioB,
						.Pin		= pin13,
						.Mode		= alternate_push_pull,
						.Pull		= noPull,
						.Speed		= speed_freq_very_high,
						.Alternate	= alternate_function_9,
						.logic		= positiva
				},
				.canNum				  = can_2,
				.prescaler			  = 18,
				.mode				  = can_normalMode,
				.syncJumpWidth		  = can_sjw_1tq,
				.timeSeg1			  = can_bs1_4tq,
				.timeSeg2			  = can_bs2_2tq,
				.filter_On_Off		  = can_filter_disable,
//				.filterBank			  = 20,
//				.filterFIFOx		  = can_fifo0,
//				.filterIdHigh		  = 0,
//				.filterIdLow		  = 0,
//				.filterMaskIdHigh	  = 0,
//				.filterMaskIdLow	  = 0,
//				.filterMode			  = can_filterMode_IDMask,
//				.filterScale		  = can_filterScale_32bits,
//				.slaveStartFilterBank = 14,
				.hasInterrupt		  = yes,
				.canIT				  = can_rx0_IRQn,
				.activeITs			  = can_it_rx_fifo0_msg_pending
		}

};
#endif

st_basicCan	canBusOnSystem[eunm_can_inSystem];
st_can_bus	can_bus[eunm_can_inSystem];

st_can_bus *aux;

/**********************************************************/

st_canConfig *can_GetConfig(uint32_t index){
	return &CAN_config[index];
}

CAN_ERR can_Init(st_can_bus *this)
{
	aux=this;
	CAN_ERR err;
	basicCAN_InstallFunctions(this->CAN);

	aux->CAN->can_phy.rxPin.pin_config = &aux->CAN->can_config->rxPin_config;
	aux->CAN->can_phy.txPin.pin_config = &aux->CAN->can_config->txPin_config;
	aux->CAN->can_func.pinInit(&aux->CAN->can_phy.rxPin.pin_phy,aux->CAN->can_phy.rxPin.pin_config);
	aux->CAN->can_func.pinInit(&aux->CAN->can_phy.txPin.pin_phy,aux->CAN->can_phy.txPin.pin_config);

	err=this->CAN->can_func.init(&this->CAN->can_phy, this->CAN->can_config);
	if (err!= CAN_ERROR_NONE)
	{
		return err;
	}

	return CAN_ERROR_NONE;
}

CAN_ERR can_receive(st_can_bus *this)
{
	return this->CAN->can_func.read(&this->CAN->can_phy);

}

CAN_ERR can_send(st_can_bus *this)
{
	return this->CAN->can_func.send(&this->CAN->can_phy);
}

CAN_ERR can_enable(st_can_bus *this, uint32_t baudrate)
{
	return this->CAN->can_func.enable(&this->CAN->can_phy, baudrate);
}

CAN_ERR can_reset(st_can_bus *this)
{
	return this->CAN->can_func.reset(&this->CAN->can_phy);
}

CAN_ERR can_close(st_can_bus *this)
{
	return this->CAN->can_func.close(&this->CAN->can_phy);
}

st_can_bus *can_config_InitPhyCAN(uint32_t index)
{
	st_can_bus *this = &can_bus[index];
	canBusOnSystem[index].can_config = can_GetConfig(index);
	this->CAN = &canBusOnSystem[index];
	return this;
}
