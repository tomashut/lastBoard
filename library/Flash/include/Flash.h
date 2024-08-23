/*
 * Flash.h
 *
 *  Created on: Jul 1, 2024
 *      Author: Usuario
 */

#ifndef LIBRARY_FLASH_INCLUDE_FLASH_H_
#define LIBRARY_FLASH_INCLUDE_FLASH_H_

#include "stm32f4xx_hal.h"
#include "string.h"
#include "stdint.h"
#include "stdio.h"
#include "stdbool.h"

typedef enum Flash_ERR_T{
	Flash_ERROR_NONE,
	Flash_ERROR
}FLASH_ERR;

typedef struct{
	bool 		allow_writing;
	FLASH_ERR 	errorCode;
}st_flashInfo;

uint32_t Flash_Write_Data (uint32_t StartSectorAddress, uint32_t *Data, uint16_t numberofwords);

void Flash_Read_Data (uint32_t StartSectorAddress, uint32_t *RxBuf, uint16_t numberofwords);

void Convert_To_Str (uint32_t *Data, char *Buf);

void Flash_Write_NUM (uint32_t StartSectorAddress, float Num);

float Flash_Read_NUM (uint32_t StartSectorAddress);

#endif /* LIBRARY_FLASH_INCLUDE_FLASH_H_ */
