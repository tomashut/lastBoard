/**
 * @file ads1118.c
 * @brief Librería para controlar el ADS1118.
 * @author Francisco
 * @date Jan 17, 2024
 */
/***********************************************************************
 *							INCLUDES
 ***********************************************************************/
#include "ads1118.h"
#include "string.h"
#include "stdlib.h"
#include "math.h"

/***********************************************************************
 *							VARIABLES
 ***********************************************************************/
enum{
	cs_pin=enum_DigitalOutput_2
};

enum{
	spi_bus=spi_inSystem_2,
};


st_ADS1118_func ads1118Functions ={
		.init_output		= &digital_outputs_Init,
		.set_output			= &digital_output_Write,
		.init_spi			= &spi_configInit,
		.spi_transmitReceive= &spi_transmitReceive8
};

uint64_t ads1118_timeCapture = 0;
uint64_t asd1118_internal_timeCapture = 0;
uint8_t  ads1118_resets = 0;
float	 lastSample=0;
st_ADS1118 *ads1118;

st_ADS1118_config rebootADS1118Config={
		.singleShotConvStart	= startSingleConversion,
		.multiplexer			= imput_A0_A1,
		.gainAmplifierConfig	= fullScaleRange_0256,
		.deviceOperatingMode	= powerDown_singleShotMode,
		.dataRate				= dataRate_128sps,
		.temperatureSensorMode	= temperatureSensorMode,
		.pullUpEnable			= pullUpEnable,
		.noOperation			= validConfig,
		.reserved				= reservedBit
};

/***********************************************************************
 *						INTERNAL FUNCTIONS
 ***********************************************************************/

void ads1118_ParamsInstall(st_ADS1118 *this, st_ADS1118_config *config){

	/*-------------------------- SS bit input ----------------------------*/
	switch (config->singleShotConvStart) {
	case noEffect:
		this->ConfigReg.bits.singleStart=NO_EFFECT;
		break;
	case startSingleConversion:
		this->ConfigReg.bits.singleStart=START_NOW;
		break;
	default:
		this->ConfigReg.bits.singleStart=NO_EFFECT;
		break;
	}
	/*-------------------------- MUX inputs ----------------------------*/
	switch (config->multiplexer) {
	case imput_A0_A1:
		this->ConfigReg.bits.mux=DIFF_0_1;
		break;
	case imput_A0_A3:
		this->ConfigReg.bits.mux=DIFF_0_3;
		break;
	case imput_A1_A3:
		this->ConfigReg.bits.mux=DIFF_1_3;
		break;
	case imput_A2_A3:
		this->ConfigReg.bits.mux=DIFF_2_3;
		break;
	case imput_A0_GND:
		this->ConfigReg.bits.mux=AIN_0;
		break;
	case imput_A1_GND:
		this->ConfigReg.bits.mux=AIN_1;
		break;
	case imput_A2_GND:
		this->ConfigReg.bits.mux=AIN_2;
		break;
	case imput_A3_GND:
		this->ConfigReg.bits.mux=AIN_3;
		break;
	default:
		this->ConfigReg.bits.mux=DIFF_0_1;
		break;
	}
	/*-------------------------- PGA inputs ----------------------------*/
	switch (config->gainAmplifierConfig) {
	case fullScaleRange_6144:
		this->ConfigReg.bits.pga=FSR_6144;
		break;
	case fullScaleRange_4096:
		this->ConfigReg.bits.pga=FSR_4096;
		break;
	case fullScaleRange_2048:
		this->ConfigReg.bits.pga=FSR_2048;
		break;
	case fullScaleRange_1024:
		this->ConfigReg.bits.pga=FSR_1024;
		break;
	case fullScaleRange_0512:
		this->ConfigReg.bits.pga=FSR_0512;
		break;
	case fullScaleRange_0256:
		this->ConfigReg.bits.pga=FSR_0256;
		break;
	default:
		this->ConfigReg.bits.pga=FSR_2048;
		break;
	}
	/*-------------------------- MODE inputs ---------------------------*/
	switch (config->deviceOperatingMode) {
	case ContinuousConversionMode:
		this->ConfigReg.bits.operatingMode=CONTINUOUS;
		break;
	case powerDown_singleShotMode:
		this->ConfigReg.bits.operatingMode=SINGLE_SHOT;
		break;
	default:
		this->ConfigReg.bits.operatingMode=SINGLE_SHOT;
		break;
	}
	/*-------------------------- DR inputs ----------------------------*/
	switch (config->dataRate) {
	case dataRate_8sps:
		this->ConfigReg.bits.rate=RATE_8SPS;
		break;
	case dataRate_16sps:
		this->ConfigReg.bits.rate=RATE_16SPS;
		break;
	case dataRate_32sps:
		this->ConfigReg.bits.rate=RATE_32SPS;
		break;
	case dataRate_64sps:
		this->ConfigReg.bits.rate=RATE_64SPS;
		break;
	case dataRate_128sps:
		this->ConfigReg.bits.rate=RATE_128SPS;
		break;
	case dataRate_250sps:
		this->ConfigReg.bits.rate=RATE_250SPS;
		break;
	case dataRate_475sps:
		this->ConfigReg.bits.rate=RATE_475SPS;
		break;
	case dataRate_860sps:
		this->ConfigReg.bits.rate=RATE_860SPS;
		break;
	default:
		this->ConfigReg.bits.rate=RATE_128SPS;
		break;
	}
	/*------------------------ TS_MODE inputs --------------------------*/
	switch (config->temperatureSensorMode) {
	case adcMode:
		this->ConfigReg.bits.sensorMode=ADC_MODE;
		break;
	case temperatureSensorMode:
		this->ConfigReg.bits.sensorMode=TEMP_MODE;
		break;
	default:
		this->ConfigReg.bits.sensorMode=ADC_MODE;
		break;
	}
	/*----------------------- PULL_UP_EN inputs ------------------------*/
	switch (config->pullUpEnable) {
	case pullUpDisable:
		this->ConfigReg.bits.pullUp=DOUT_NO_PULLUP;
		break;
	case pullUpEnable:
		this->ConfigReg.bits.pullUp=DOUT_PULLUP;
		break;
	default:
		this->ConfigReg.bits.pullUp=DOUT_PULLUP;
		break;
	}
	/*-------------------------- NOP inputs ----------------------------*/
	switch (config->noOperation) {
	case invalidConfig:
		this->ConfigReg.bits.noOperation=NO_VALID_CFG;
		break;
	case validConfig:
		this->ConfigReg.bits.noOperation=VALID_CFG;
		break;
	default:
		this->ConfigReg.bits.noOperation=VALID_CFG;
		break;
	}
	/*------------------------ Reserved input --------------------------*/
	this->ConfigReg.bits.reserved=RESERVED;

}

/* Wait for the corresponding conversion time according to the configured data rate
 *
 *	 DR		|	CONV_TIME
 * ---------|-------------
 *	8SPS	|	125	ms
 *	16SPS	|	63	ms
 *	32SPS	|	32	ms
 *	64SPS	|	16	ms
 *	128SPS	|	8	ms
 *	250SPS	|	4	ms
 *	475SPS	|	3	ms
 *	860SPS	|	2	ms
 */
void waitConversionTime(uint8_t rate)
{
	uint8_t CONV_TIME[8]={125,63,32,16,8,4,3,2};

	for(int i=0;i<CONV_TIME[rate];i++)
	{
		HAL_Delay(1);
	}
}

void delayMilliseconds(st_ADS1118 *ads, uint64_t delay){
	uint64_t initialTime = *ads->Params.milisecElapsed;

	while(*ads->Params.milisecElapsed < (initialTime + delay)){}
}

/* Convierte milivolts en Temperatura segun la tabla de la termocupla tipo K
 *
 * y = -0,0007x^6 + 0,0067x^5 + 0,0185x^4 - 0,1596x^3 - 0,6247x^2 + 27,027x + 0,159
 *
 */
float ads1118_milivoltsToTemp(float x) {
	float y;
	y = -0.0007 * pow(x, 6) + 0.0067 * pow(x, 5) + 0.0185 * pow(x, 4) + 0.1596 * pow(x, 3) - 0.6247 * pow(x, 2) + 27.027 * x + 0.159;
	return y;
}

/* Convierte la temperatura en milivolts segun la tabla de la termocupla tipo K
 *
 * y = 1E-15x^6 + 4E-13x^5 - 2E-11x^4 - 1E-07x^3 + 3E-05x^2 + 0,0395x - 0,0006
 *
 */
float ads1118_tempToMilivolts(float x) {
	float y;
	y = 1E-15 * pow(x, 6) + 4E-13 * pow(x, 5) - 2E-11 * pow(x, 4) - 1E-07 * pow(x, 3) + 3E-05 * pow(x, 2) + 0.0395 * x - 0.0006;
	return y;
}


ADS1118_ERR getSensorMeasurement(st_ADS1118 *this, tsMode_bit mode)
{
	float		pgaFSR[8]={6.144, 4.096, 2.048, 1.024, 0.512, 0.256, 0.256, 0.256};
	float		fsr=pgaFSR[this->ConfigReg.bits.pga];	// FSR (Rango completo de escala) según la ganancia configurada
	uint8_t 	dataMSB=0,dataLSB=0,configMSB=0,configLSB=0, count=0;
	uint16_t	data=0, config=0;

	switch (mode)
	{
	case adcMode:
		this->ConfigReg.bits.sensorMode=ADC_MODE;
		break;
	case temperatureSensorMode:
		this->ConfigReg.bits.sensorMode=TEMP_MODE;
		break;
	}

	do
	{
		this->function->set_output(this->cs_pin,off_state);
		if(this->function->spi_transmitReceive(this->spi_bus,&this->ConfigReg.byte.msb,&dataMSB)	 != SPI_ERROR_NONE){return ADS1118_SPI_ERROR;}
		if(this->function->spi_transmitReceive(this->spi_bus,&this->ConfigReg.byte.lsb,&dataLSB)  != SPI_ERROR_NONE){return ADS1118_SPI_ERROR;}
		if(this->function->spi_transmitReceive(this->spi_bus,&this->ConfigReg.byte.msb,&configMSB)!= SPI_ERROR_NONE){return ADS1118_SPI_ERROR;}
		if(this->function->spi_transmitReceive(this->spi_bus,&this->ConfigReg.byte.lsb,&configLSB)!= SPI_ERROR_NONE){return ADS1118_SPI_ERROR;}
		this->function->set_output(this->cs_pin,on_state);

		waitConversionTime(this->ConfigReg.bits.rate);	// Esperar el tiempo de conversión del ADS1118
		count++;
	}while(count<=1);

	switch (this->ConfigReg.bits.sensorMode)
	{
	case ADC_MODE:
		data=(uint16_t)(dataMSB<<8)|dataLSB;						// Combina los bytes MSB y LSB para formar el valor ADC final
		config=(uint16_t)(((configMSB<<8)|configLSB)|0x8000);		// Combina los bytes MSB y LSB para formar el registro de configuración (en la lectura se pierde el MSB, por eso el OR con 0x8000)

		if (this->ConfigReg.word != config)					// Si el regitro de configuracón que responde el ads1118 es distinto del
		{															// que se le envía, hay un error en la comunicación
			return ADS1118_ADC_ERROR;
		}
		else if (data == 0x7FFF)
		{
			return ADS1118_SENSOR_DISCONNECTED;
		}

		if(data>=0x8000)
		{// Aplica formato de complemento a dos si es necesario y calcula milivoltios
			data=((~data)+1);
			this->Params.millivolts=((float)1000*(data*fsr/(32768))*(-1));
		}
		else
		{
			this->Params.millivolts=(float)(1000*(data*fsr/(32768)));
		}
		break;

	case TEMP_MODE:
		data=(uint16_t)(((dataMSB<<8)|dataLSB)>>2);				// Combinar los bytes de datos recibidos en un valor de 16 bits
		config=(uint16_t)(((configMSB<<8)|configLSB)|0x8000);

		if (this->ConfigReg.word != config)					// Si el regitro de configuracón que responde el ads1118 es distinto del
		{															// que se le envía, hay un error en la comunicación
			return ADS1118_TS_ERROR;
		}
		if ((data<<2) >= 0x8000)
		{// Aplica formato de complemento a dos si es necesario y calcula la temperatura en grados Celsius
			data=(~data)+1;
			this->Params.internalTemp=(float)data*(-1)*0.03125;
		}
		else
		{
			this->Params.internalTemp=(float)data*0.03125;
		}
		break;
	}
	return ADS1118_ERROR_NONE;
}


/***********************************************************************
 *						PUBLIC FUNCTIONS
 ***********************************************************************/

ADS1118_ERR ads1118_init(st_ADS1118 *this, st_ADS1118_config *config)
{
	this->function = &ads1118Functions;

	//	Init SPI Bus :
	this->spi_bus=spi_configInitPhy(spi_bus);
	if (this->function->init_spi(this->spi_bus)!=SPI_ERROR_NONE)
	{
		return ADS1118_INIT_ERROR;
	}
	//	Init CS/SS :
	this->cs_pin=digital_output_config_InitPhyDigitalOutput(cs_pin);
	this->function->init_output(this->cs_pin);

	// Configuración inicial del registro de control del ADS1118 con valores predeterminados
	ads1118_ParamsInstall(this, config);

	this->function->set_output(this->cs_pin,on_state);

	this->state = ads1118_initialization;
	this->disconnection_flag = no;
	ads1118 = this;

	return ADS1118_ERROR_NONE;
}


void ads1118Measurement(st_ADS1118 *this)
{
	float coldJunctionVoltage = 0, totalVoltage = 0, temperatureSum = 0;

	for (int i = 0; i < 5; i++)
	{
		if((this->errorCode=getSensorMeasurement(this,temperatureSensorMode)) != ADS1118_ERROR_NONE)
		{
			this->state 		= ads1118_error;
			this->Params.internalTemp	= 0;
		}
		if((this->errorCode=getSensorMeasurement(this, adcMode)) != ADS1118_ERROR_NONE)
		{
			this->state		= ads1118_error;
			this->Params.millivolts	= 0;
		}
		coldJunctionVoltage=ads1118_tempToMilivolts(this->Params.internalTemp);

		totalVoltage = coldJunctionVoltage + this->Params.millivolts;

		temperatureSum+=ads1118_milivoltsToTemp(totalVoltage);
	}
	if (this->errorCode != ADS1118_ERROR_NONE)
	{
		this->Params.temperature = 0;
	}
	else if (this->disconnection_flag == yes)
	{
		if(abs((int)((temperatureSum/5)-lastSample)) <= 1)
		{
			this->disconnection_flag = no;
		}
		lastSample =temperatureSum/5;
		this->Params.temperature = 0;
	}
	else
	{
		this->Params.temperature=temperatureSum/5;
		ads1118->state	= ads1118_sleepMode;
	}
	ads1118_timeCapture	= *ads1118->Params.milisecElapsed;
}


void ads1118_StateMachine(){

	switch (ads1118->state) {
	case ads1118_initialization:
		ads1118->state	= ads1118_sleepMode;
		ads1118_timeCapture	= *ads1118->Params.milisecElapsed;
		break;
	case ads1118_sleepMode:
		if(*ads1118->Params.milisecElapsed > (ads1118_timeCapture + 1000))
		{
			ads1118->state = ads1118_measurement;
		}
		break;
	case ads1118_measurement:
		ads1118Measurement(ads1118);
		break;
	case ads1118_error:
		switch (ads1118->errorCode)
		{
		case ADS1118_INIT_ERROR:
			if(ads1118_resets < 5)
			{
				ads1118_resets++;
				ads1118->errorCode=ads1118_init(ads1118,&rebootADS1118Config);
				if (ads1118->errorCode == ADS1118_ERROR_NONE)
				{
					ads1118->state=ads1118_initialization;
					ads1118_resets=0;
				}
			}
			else
			{
				//No se soluciono el problema: Verificar conexiones físicas y reiniciar el dispositivo
			}
			break;
		case ADS1118_SPI_ERROR:
			if (ads1118->function->init_spi(ads1118->spi_bus)!=SPI_ERROR_NONE)
			{
				ads1118->errorCode = ADS1118_INIT_ERROR;
			}
			ads1118->state=ads1118_initialization;
			break;
		case ADS1118_TS_ERROR:
			if(*ads1118->Params.milisecElapsed > (ads1118_timeCapture + 1000))
			{
				ads1118Measurement(ads1118);
			}
			break;
		case ADS1118_ADC_ERROR:
			if(*ads1118->Params.milisecElapsed > (ads1118_timeCapture + 1000))
			{
				ads1118Measurement(ads1118);
			}
			break;
		case ADS1118_SENSOR_DISCONNECTED:
			ads1118->disconnection_flag = yes;
			if(*ads1118->Params.milisecElapsed > (ads1118_timeCapture + 1000))
			{
				ads1118Measurement(ads1118);
			}
			break;
		case ADS1118_ERROR_NONE:
			ads1118->state	= ads1118_sleepMode;
			break;
		default:
			break;
		}
		break;
	}
}

