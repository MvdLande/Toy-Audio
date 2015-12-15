#pragma once
#include "common.h"


#define FILE_NAME_LENGTH        (256)
#define FILE_SIZE_LENGTH        (16)

#define WAV_FILE_ADDRESS1  256
#define WAV_FILE_ADDRESS2  0x200000 + 256

extern uint32_t WAV_FILE_ADDRESS;
extern uint32_t USER_FLASH_END_ADDRESS;
extern uint8_t aFileName[FILE_NAME_LENGTH];
extern uint32_t USER_FLASH_SIZE;

void FLASH_If_Erase(uint32_t address, uint32_t size);
uint32_t FLASH_If_Write(uint32_t* destination, uint8_t* p_source, uint32_t length);

/* Error code */
enum 
{
	FLASHIF_OK                = 0,
	FLASHIF_ERASEKO,
	FLASHIF_WRITINGCTRL_ERROR,
	FLASHIF_WRITING_ERROR,
	FLASHIF_PROTECTION_ERRROR
};