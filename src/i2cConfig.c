#include "i2cConfig.h"
#include "basicI2C.h"
#if ARCHITECTURE == ESP32_BOARD
#elif ARCHITECTURE == KINTEIS
#elif ARCHITECTURE == STM32F4xx

typedef struct i2c{
	st_basicI2C *i2c;
}st_i2c;

st_i2c i2c_port[i2c_inSystem_total];

st_i2cConfig i2c_Config[i2c_inSystem_total] ={
#if BOARD == DEFROSTER_BOARD
#elif BOARD == FROSTER_BOARD
	{
		.sclk_PinConfig={
				.enum_GPIO=enum_gpioA,
				.Pin=pin8,
				.Mode=alternate_open_drain,
				.Pull=noPull,
				.Speed=speed_freq_very_high,
				.Alternate=alternate_function_4,
				.logic=positiva
		},
		.sda_PinConfig={
			.enum_GPIO=enum_gpioC,
			.Pin=pin9,
			.Mode=alternate_open_drain,
			.Pull=noPull,
			.Speed=speed_freq_very_high,
			.Alternate=alternate_function_4,
			.logic=positiva
		},
		.i2cNum			= i2c_3,
		.ClockSpeed		= 100000,
		.DutyCycle		= i2c_dutyCycle_2,
		.OwnAddress1	= 0,
		.AddressingMode = i2c_addressingMode_7bit,
		.DualAddressMode= i2c_dualAddress_disable,
		.OwnAddress2	= 0,
		.GeneralCallMode= i2c_generalCall_disable,
		.NoStretchMode	= i2c_nostretch_disable,
		.timeout		= I2C_MASTER_TIMEOUT_MS,
	}
#elif BOARD == DAQ_BOARD
	{
		.sclk_PinConfig={
				.enum_GPIO=enum_gpioA,
				.Pin=pin8,
				.Mode=alternate_open_drain,
				.Pull=noPull,
				.Speed=speed_freq_very_high,
				.Alternate=alternate_function_4,
				.logic=positiva
		},
		.sda_PinConfig={
			.enum_GPIO=enum_gpioC,
			.Pin=pin9,
			.Mode=alternate_open_drain,
			.Pull=noPull,
			.Speed=speed_freq_very_high,
			.Alternate=alternate_function_4,
			.logic=positiva
		},
		.i2cNum			= i2c_3,
		.ClockSpeed		= 100000,
		.DutyCycle		= i2c_dutyCycle_2,
		.OwnAddress1	= 0x01,
		.AddressingMode = i2c_addressingMode_7bit,
		.DualAddressMode= i2c_dualAddress_disable,
		.OwnAddress2	= 0,
		.GeneralCallMode= i2c_generalCall_disable,
		.NoStretchMode	= i2c_nostretch_disable,
		.timeout		= I2C_MASTER_TIMEOUT_MS,
	}
#endif
};
//#elif defined(OTHER)
#else

#endif

//st_basicI2C i2cOnSystem[i2c_inSystem_total];    // An array is created with all the i2c buses available for use.
//st_i2c i2cDev[i2c_inSystem_total];				// This array is the devices that connect to the available i2c.

i2c_errors i2c_configInit(int i2c_PortCount)
{

	i2c_port[i2c_PortCount].i2c->i2c_config = &i2c_Config[i2c_PortCount];
	basicI2C_InstallFunctions(i2c_port[i2c_PortCount].i2c);
	i2c_port[i2c_PortCount].i2c->i2c_phy.sclk_Pin.pin_config = &i2c_port[i2c_PortCount].i2c->i2c_config->sclk_PinConfig;
	i2c_port[i2c_PortCount].i2c->i2c_phy.sda_Pin.pin_config = &i2c_port[i2c_PortCount].i2c->i2c_config->sda_PinConfig;

	i2c_port[i2c_PortCount].i2c->i2c_func.pin_init(&i2c_port[i2c_PortCount].i2c->i2c_phy.sclk_Pin.pin_phy,i2c_port[i2c_PortCount].i2c->i2c_phy.sclk_Pin.pin_config);
	i2c_port[i2c_PortCount].i2c->i2c_func.pin_init(&i2c_port[i2c_PortCount].i2c->i2c_phy.sda_Pin.pin_phy,i2c_port[i2c_PortCount].i2c->i2c_phy.sda_Pin.pin_config);

	if(i2c_port[i2c_PortCount].i2c->i2c_func.init(&i2c_port[i2c_PortCount].i2c->i2c_phy, i2c_port[i2c_PortCount].i2c->i2c_config) != i2c_error_none)
	{
		return i2c_error;	//cambiar error a init
	}
	return i2c_error_none;
}

// // This function assigns the configuration of one of the buses to a device.
// st_i2c *i2c_configInitPhy(uint32_t index)
// {
// 	st_i2c *this = &i2cDev[index];

// 	i2cOnSystem[index].i2c_config = i2c_configGetConfig(index);
// 	this->i2c = &i2cOnSystem[index];
// 	return this;
// }

// st_i2cConfig *i2c_configGetConfig(uint32_t index)
// {
// 	return &i2c_Config[index];
// }


i2c_errors i2c_writeData(int i2c_ID, uint16_t addrDev, uint8_t* writeData, uint8_t sizeData)
{	
	memset(&i2c_port[i2c_ID].i2c->i2c_phy.pData, 0, sizeof(i2c_port[i2c_ID].i2c->i2c_phy.pData));
	i2c_port[i2c_ID].i2c->i2c_phy.pData   		= 	writeData;
	i2c_port[i2c_ID].i2c->i2c_phy.dataSize		=	sizeData ;
	i2c_port[i2c_ID].i2c->i2c_phy.DevAddress	=	addrDev	 ;
	if (i2c_port[i2c_ID].i2c->i2c_func.transmit(&i2c_port[i2c_ID].i2c->i2c_phy) != I2C_ERROR_NONE)
	{
		return i2c_error;
	}
	return i2c_error_none;
}


i2c_errors i2c_readData(int i2c_ID, uint16_t addrDev, uint8_t* readData, uint8_t sizeData)
{
	memset(&i2c_port[i2c_ID].i2c->i2c_phy.pData, 0, sizeof(i2c_port[i2c_ID].i2c->i2c_phy.pData));
	i2c_port[i2c_ID].i2c->i2c_phy.pData			= 	readData;
	i2c_port[i2c_ID].i2c->i2c_phy.dataSize		=	sizeData;
	i2c_port[i2c_ID].i2c->i2c_phy.DevAddress	=	addrDev	;

	if (i2c_port[i2c_ID].i2c->i2c_func.receive(&i2c_port[i2c_ID].i2c->i2c_phy) != I2C_ERROR_NONE)
	{
		return i2c_error;
	}
	return i2c_error_none;
}