#include "SimpleFS.h"
#include "sFlash.h"

uint8_t aFileName[FILE_NAME_LENGTH];
uint32_t USER_FLASH_SIZE = 0x1FFF00;
uint32_t USER_FLASH_END_ADDRESS = 0x3fffff; //32Mbit 4MB
uint32_t WAV_FILE_ADDRESS = 256; //preserve block 0 for file meta data like filename and size


void FLASH_If_Erase(uint32_t address, uint32_t size)
{
	// currently, the complete SPI FLASH IC is erased
	//sFLASH_EraseBulk();
}

uint32_t FLASH_If_Write(uint32_t* destination, uint8_t* p_source, uint32_t length)
{
	uint32_t i = 0;
	
	sFLASH_WriteBuffer(p_source, *destination, length); 
	*destination += length;
	//if (sFLASH_Verify(p_source, destination, length) == 0) 
		return (FLASHIF_OK);
	//else
	//	return (FLASHIF_WRITING_ERROR);
}

