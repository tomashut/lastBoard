#include "utilities.h"

void floatToBytes(float value, uint8_t byteArr[4]) {
	uint32_t temp;
	memcpy(&temp, &value, sizeof(float));
	byteArr[0] = (temp >> 24) & 0xFF;
	byteArr[1] = (temp >> 16) & 0xFF;
	byteArr[2] = (temp >> 8) & 0xFF;
	byteArr[3] = temp & 0xFF;
}

uint32_t floatToUint32(float value){
	uint32_t result;
	memcpy(&result ,&value,sizeof(uint32_t));
	return result;
}

float uint32ToFloat(uint32_t value) {
    float result;
    memcpy(&result, &value, sizeof(uint32_t));
    return result;
}