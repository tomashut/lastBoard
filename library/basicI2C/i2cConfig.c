//#include "i2cConfig.h"
//
//#if ARCHITECTURE == ESP32_BOARD
//#elif ARCHITECTURE == KINTEIS
//#elif ARCHITECTURE == STM32F4xx
//st_i2cConfig i2c_Config[i2c_inSystem_total] ={
//#if BOARD == DEFROSTER_BOARD
//#elif BOARD == FROSTER_BOARD
//	{
//		.sclk_PinConfig={
//				.enum_GPIO=enum_gpioA,
//				.Pin=pin8,
//				.Mode=alternate_open_drain,
//				.Pull=noPull,
//				.Speed=speed_freq_very_high,
//				.Alternate=alternate_function_4,
//				.logic=positiva
//		},
//		.sda_PinConfig={
//			.enum_GPIO=enum_gpioC,
//			.Pin=pin9,
//			.Mode=alternate_open_drain,
//			.Pull=noPull,
//			.Speed=speed_freq_very_high,
//			.Alternate=alternate_function_4,
//			.logic=positiva
//		},
//		.i2cNum			= i2c_3,
//		.ClockSpeed		= 100000,
//		.DutyCycle		= i2c_dutyCycle_2,
//		.OwnAddress1	= 0,
//		.AddressingMode = i2c_addressingMode_7bit,
//		.DualAddressMode= i2c_dualAddress_disable,
//		.OwnAddress2	= 0,
//		.GeneralCallMode= i2c_generalCall_disable,
//		.NoStretchMode	= i2c_nostretch_disable,
//		.timeout		= I2C_MASTER_TIMEOUT_MS,
//	}
//#elif BOARD == DAQ_BOARD
//	{
//		.sclk_PinConfig={
//				.enum_GPIO=enum_gpioA,
//				.Pin=pin8,
//				.Mode=alternate_open_drain,
//				.Pull=noPull,
//				.Speed=speed_freq_very_high,
//				.Alternate=alternate_function_4,
//				.logic=positiva
//		},
//		.sda_PinConfig={
//			.enum_GPIO=enum_gpioC,
//			.Pin=pin9,
//			.Mode=alternate_open_drain,
//			.Pull=noPull,
//			.Speed=speed_freq_very_high,
//			.Alternate=alternate_function_4,
//			.logic=positiva
//		},
//		.i2cNum			= i2c_3,
//		.ClockSpeed		= 100000,
//		.DutyCycle		= i2c_dutyCycle_2,
//		.OwnAddress1	= 0x01,
//		.AddressingMode = i2c_addressingMode_7bit,
//		.DualAddressMode= i2c_dualAddress_disable,
//		.OwnAddress2	= 0,
//		.GeneralCallMode= i2c_generalCall_disable,
//		.NoStretchMode	= i2c_nostretch_disable,
//		.timeout		= I2C_MASTER_TIMEOUT_MS,
//	}
//#endif
//};
////#elif defined(OTHER)
//#else
//
//#endif
//
//st_basicI2C i2cOnSystem[i2c_inSystem_total];    // An array is created with all the i2c buses available for use.
//st_i2c i2cDev[i2c_inSystem_total];				// This array is the devices that connect to the available i2c.
//
//I2C_ERR i2c_configInit(st_i2c* this)
//{
//	basicI2C_InstallFunctions(this->i2c);
//	this->i2c->i2c_phy.sclk_Pin.pin_config = &this->i2c->i2c_config->sclk_PinConfig;
//	this->i2c->i2c_phy.sda_Pin.pin_config = &this->i2c->i2c_config->sda_PinConfig;
//
//	this->i2c->i2c_func.pin_init(&this->i2c->i2c_phy.sclk_Pin.pin_phy,this->i2c->i2c_phy.sclk_Pin.pin_config);
//	this->i2c->i2c_func.pin_init(&this->i2c->i2c_phy.sda_Pin.pin_phy,this->i2c->i2c_phy.sda_Pin.pin_config);
//
//	if(this->i2c->i2c_func.init(&this->i2c->i2c_phy, this->i2c->i2c_config) != I2C_ERROR_NONE)
//	{
//		return I2C_INIT_ERROR;
//	}
//	return I2C_ERROR_NONE;
//}
//
//// This function assigns the configuration of one of the buses to a device.
//st_i2c *i2c_configInitPhy(uint32_t index)
//{
//	st_i2c *this = &i2cDev[index];
//
//	i2cOnSystem[index].i2c_config = i2c_configGetConfig(index);
//	this->i2c = &i2cOnSystem[index];
//	return this;
//}
//
//st_i2cConfig *i2c_configGetConfig(uint32_t index)
//{
//	return &i2c_Config[index];
//}
//
//
//I2C_ERR i2c_writeData(st_i2c* this, uint16_t addrDev, uint8_t* writeData, uint8_t sizeData)
//{
//	memset(&this->i2c->i2c_phy.pData, 0, sizeof(this->i2c->i2c_phy.pData));
//	this->i2c->i2c_phy.pData   		= 	writeData;
//	this->i2c->i2c_phy.dataSize		=	sizeData ;
//	this->i2c->i2c_phy.DevAddress	=	addrDev	 ;
//	if (this->i2c->i2c_func.transmit(&this->i2c->i2c_phy) != I2C_ERROR_NONE)
//	{
//		return I2C_WRITE_ERROR;
//	}
//	return I2C_ERROR_NONE;
//}
//
//
//
//I2C_ERR i2c_readData(st_i2c* this, uint16_t addrDev, uint8_t* readData, uint8_t sizeData)
//{
//	memset(&this->i2c->i2c_phy.pData, 0, sizeof(this->i2c->i2c_phy.pData));
//	this->i2c->i2c_phy.pData		= 	readData;
//	this->i2c->i2c_phy.dataSize		=	sizeData;
//	this->i2c->i2c_phy.DevAddress	=	addrDev	;
//
//	if (this->i2c->i2c_func.receive(&this->i2c->i2c_phy) != I2C_ERROR_NONE)
//	{
//		return I2C_READ_ERROR;
//	}
//	return I2C_ERROR_NONE;
//}
//
//




#include "i2cConfig.h"

#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx
st_i2cConfig i2c_Config[i2c_inSystem_total] =
{
		{
				.i2cNum			= i2c_3,
				.ClockSpeed		= 300000,
				.DutyCycle		= i2c_dutyCycle_16_9,
				.OwnAddress1	= 0,
				.AddressingMode = i2c_addressingMode_7bit,
				.DualAddressMode= i2c_dualAddress_disable,
				.OwnAddress2	= 0,
				.GeneralCallMode= i2c_generalCall_disable,
				.NoStretchMode	= i2c_nostretch_disable,
				.timeout		= I2C_MASTER_TIMEOUT_MS,
				.sclk_GPIO		= enum_gpioA,
				.sda_GPIO		= enum_gpioC,
				.sclk_Pin		= pin8,
				.sda_Pin		= pin9
		}
};
//#elif defined(OTHER)
#else

#endif

st_basicI2C i2cOnSystem[i2c_inSystem_total];    // An array is created with all the i2c buses available for use.
st_i2c i2cDev[i2c_inSystem_total];				// This array is the devices that connect to the available i2c.

I2C_ERR i2c_configInit(st_i2c* this)
{
    basicI2C_InstallFunctions(this->i2c);
	if(this->i2c->i2c_func.init(&this->i2c->i2c_phy, this->i2c->i2c_config) != I2C_ERROR_NONE)
	{
		return I2C_INIT_ERROR;
	}
    this->i2c->i2c_func.pin_init(&this->i2c->i2c_phy.sclk_Pin.pin_phy,this->i2c->i2c_phy.sclk_Pin.pin_config);
    this->i2c->i2c_func.pin_init(&this->i2c->i2c_phy.sda_Pin.pin_phy,this->i2c->i2c_phy.sda_Pin.pin_config);
    return I2C_ERROR_NONE;
}

// This function assigns the configuration of one of the buses to a device.
st_i2c *i2c_configInitPhy(uint32_t index)
{
	st_i2c *this = &i2cDev[index];

	i2cOnSystem[index].i2c_config = i2c_configGetConfig(index);
	this->i2c = &i2cOnSystem[index];
	return this;
}

st_i2cConfig *i2c_configGetConfig(uint32_t index)
{
	return &i2c_Config[index];
}


I2C_ERR i2c_writeData(st_i2c* this, uint8_t* writeData, uint8_t sizeData)
{
	this->i2c->i2c_phy.pData   	= 	writeData;
	this->i2c->i2c_phy.dataSize	=	sizeData;
	if (this->i2c->i2c_func.transmit(&this->i2c->i2c_phy) != I2C_ERROR_NONE)
	{
		return I2C_WRITE_ERROR;
	}
	return I2C_ERROR_NONE;
}



I2C_ERR i2c_readData(st_i2c* this, uint8_t* readData, uint8_t sizeData)
{
	this->i2c->i2c_phy.pData	= 	readData;
	this->i2c->i2c_phy.dataSize	=	sizeData;
 	if (this->i2c->i2c_func.receive(&this->i2c->i2c_phy) != I2C_ERROR_NONE)
	{
		return I2C_WRITE_ERROR;
	}
	return I2C_ERROR_NONE;
}


