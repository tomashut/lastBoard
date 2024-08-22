#include "basicI2C.h"

I2C_ERR basicI2C_ParamsInstall(st_i2cPhy* this, st_i2cConfig* config)
{
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	switch(config->i2cNum)
	{
	case i2c_1:
		this->handlerI2C.Instance = I2C1;
		__HAL_RCC_I2C1_CLK_ENABLE();
		break;
	case i2c_2:
		this->handlerI2C.Instance = I2C2;
		__HAL_RCC_I2C2_CLK_ENABLE();
		break;
	case i2c_3:
		this->handlerI2C.Instance = I2C3;
		__HAL_RCC_I2C3_CLK_ENABLE();
		break;
	default :
		break;
	}

	switch(config->DutyCycle)
	{
	case i2c_dutyCycle_2:
		this->handlerI2C.Init.DutyCycle	= I2C_DUTYCYCLE_2;
		break;
	case i2c_dutyCycle_16_9:
		this->handlerI2C.Init.DutyCycle = I2C_DUTYCYCLE_16_9;
		break;
	}

	switch(config->AddressingMode)
	{
	case i2c_addressingMode_7bit:
		this->handlerI2C.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		break;
	case i2c_addressingMode_10bit:
		this->handlerI2C.Init.AddressingMode = I2C_ADDRESSINGMODE_10BIT;
		break;
	}

	switch(config->DualAddressMode)
	{
	case i2c_dualAddress_disable:
		this->handlerI2C.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		break;
	case i2c_dualAddress_enable:
		this->handlerI2C.Init.DualAddressMode = I2C_DUALADDRESS_ENABLE;
		break;
	}

	switch(config->GeneralCallMode)
	{
	case i2c_generalCall_disable:
		this->handlerI2C.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		break;
	case i2c_generalCall_enable:
		this->handlerI2C.Init.GeneralCallMode = I2C_GENERALCALL_ENABLE;
		break;
	}

	switch(config->NoStretchMode)
	{
	case i2c_nostretch_disable:
		this->handlerI2C.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
		break;
	case i2c_nostretch_enable:
		this->handlerI2C.Init.NoStretchMode = I2C_NOSTRETCH_ENABLE;
		break;
	}

	this->handlerI2C.Init.ClockSpeed 		= config->ClockSpeed;
	this->handlerI2C.Init.OwnAddress1 		= config->OwnAddress1;
	this->handlerI2C.Init.OwnAddress2 		= config->OwnAddress2;
	this->timeout							= config->timeout;

	//#elif defined(OTHER)
#else

#endif

	return I2C_ERROR_NONE;

}
I2C_ERR basicI2C_Init(st_i2cPhy* this, st_i2cConfig* config)
{
	basicI2C_ParamsInstall(this, config);
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

	if(HAL_I2C_Init(&this->handlerI2C) != HAL_OK)
	{
		return I2C_INIT_ERROR;
	}
#else
	//#elif defined(OTHER)
#endif
	return I2C_ERROR_NONE;
}

I2C_ERR basicI2C_transferData(st_i2cPhy* this)
{

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	if (HAL_I2C_Master_Transmit(&this->handlerI2C, this->DevAddress << 1, this->pData, this->dataSize, this->timeout) != HAL_OK)
	{
		return I2C_ERROR;
	}
	//#elif defined(OTHER)
#else

#endif

	return I2C_ERROR_NONE;
}

I2C_ERR	basicI2C_receiverData(st_i2cPhy* this)
{

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
	if (HAL_I2C_Master_Receive(&this->handlerI2C, this->DevAddress << 1, this->pData, this->dataSize, this->timeout) != HAL_OK)
	{
		return I2C_ERROR;
	}
#else
	//#elif defined(OTHER)
#endif

	return I2C_ERROR_NONE;
}

I2C_ERR basicI2C_transferData2MemAddress(st_i2cPhy *this, uint16_t MemAddress, uint16_t MemAddSize)
{
    if(HAL_I2C_Mem_Write(&this->handlerI2C, this->DevAddress << 1, MemAddress, MemAddSize, this->pData , this->dataSize, this->timeout) != HAL_OK)
		return I2C_WRITE_ERROR;

	return I2C_ERROR_NONE;
}

I2C_ERR basicI2C_receiverData2MemAddress(st_i2cPhy *this, uint16_t MemAddress, uint16_t MemAddSize)
{

	if(HAL_I2C_Mem_Read(&this->handlerI2C, this->DevAddress << 1, MemAddress, MemAddSize, this->pData, this->dataSize, this->timeout) != HAL_OK)
		return I2C_READ_ERROR;

	return I2C_ERROR_NONE;
}

I2C_ERR basicI2C_InstallFunctions(st_basicI2C *this)
{
	this->i2c_func.init 			 = basicI2C_Init			;
	this->i2c_func.transmit 		 = basicI2C_transferData	;
	this->i2c_func.receive 			 = basicI2C_receiverData	;
	this->i2c_func.pin_init			 = &basicPin_Init			;

	return I2C_ERROR_NONE;
}
