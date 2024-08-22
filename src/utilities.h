#include "stdint.h"
#include "string.h"

void floatToBytes(float value, uint8_t byteArr[4]);

uint32_t floatToUint32(float value);

float uint32ToFloat(uint32_t value);