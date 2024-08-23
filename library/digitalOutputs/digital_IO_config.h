#ifndef FDX_LIBS_DIGITAL_IO_CONFIG_H_
#define FDX_LIBS_DIGITAL_IO_CONFIG_H_

#include "basicPin.h"

enum{
	enum_Digital_IO_0,
	enum_Digital_IO_1,
	enum_Digital_IO_2,
	enum_Digital_IO_3,
	enum_Digital_IO_4,
	enum_Digital_IO_5,
	enum_Digital_IO_6,
	enum_Digital_IO_7,
	enum_Digital_IO_8,
	enum_Digital_IO_9,
	enum_Digital_IO_10,
	enum_Digital_IO_11,
	enum_Digital_IO_12,
	enum_Digital_IO_13,
	enum_Digital_IO_14,
	enum_Digital_IO_15,
	enum_Digital_IO_inSystem
};


typedef struct dig_io{
	st_pin *pin;
}st_dig_io;

state digital_ios_Init(st_dig_io *);
state digital_io_Write(st_dig_io *, uint8_t);
state digital_io_Read(st_dig_io *);

st_dig_io *digital_io_config_InitPhyDigitalIO(uint32_t);
st_dig_io *digital_io_config_GetDigitalIO(uint32_t);

#endif /* FDX_LIBS_DIGITAL_IO_CONFIG_H_ */
