#include "WAVplayer.h"
#include "usart.h"
#include "common.h"
#include "main.h"
#include <stm32f0xx_tim.h>


uint32_t GetWAVdataSize(WAV_Player_File_8bitMono* WAV_File)
{
	uint32_t size = 0;
	uint8_t buffer[4];

	// Read chunkID, must be 'RIFF'  ----------------------------------------------*/
		/*
	sFLASH_ReadBuffer(buffer, WAV_File->FileStartAddress, 4); //read chunkID at offset 0x00
	if (Temp != CHUNK_ID)
	{
		return (Unvalid_RIFF_ID);
	}
*/
	WAV_File->DataSizeOffset = 0x28; //audacity -- todo get address from file, in stead of hardcodeing it
	
	
	sFLASH_ReadBuffer(buffer, WAV_File->FileStartAddress + WAV_File->DataSizeOffset, 4); //read filesize at offset 0x100
	size = buffer[0] | (buffer[1] << 8) | (buffer[2] << 16) | (buffer[3] << 24);
	return size;
}

void Start_WAV_Player(WAV_Player_File_8bitMono* WAV_File)
{	
	SelectHSI(); //8MHz clock
	SystemCoreClockUpdate(); //Update SystemCoreClock variable to current clock 
	SysTick_Config(SystemCoreClock / 1000); //Set up a systick interrupt systick clock
	sFLASH_Init();
	InitAudioGPIO();
	InitTIM3();
	// disable systick timer
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk; //~SysTick_CTRL_TICKINT_Msk;
	WAV_File->DataBlockSize = GetWAVdataSize(WAV_File);
	WAV_File->DataStartAddress = WAV_File->DataSizeOffset + 4;
	WAV_File->DataPointer = 0x0;
	sFLASH_StartReadSequence(WAV_File->FileStartAddress + WAV_File->DataStartAddress + WAV_File->DataPointer);
	InitTIM3GPIO();
	TIM_Cmd(TIM3, ENABLE);	//Start PWM generator
	//GPIO_SetBits(GPIOA, GPIO_Pin_4); //Enable Audio Amp
}

uint8_t WAV_Player_GetByte(WAV_Player_File_8bitMono* WAV_File, uint8_t* data)
{
	//uint8_t buffer[2], temp;
	
	if (WAV_File->DataPointer < WAV_File->DataBlockSize) // get next byte
	{

		*data = sFLASH_ReadByte();
		WAV_File->DataPointer++;

		if (WAV_File->DataPointer > 800)
			GPIO_SetBits(GPIOA, GPIO_Pin_4); //Enable Audio Amp
		if (WAV_File->DataPointer > (WAV_File->DataBlockSize - 800))
			GPIO_ResetBits(GPIOA, GPIO_Pin_4); //Disable Audio Amp

		return 1;
	}
	else
	{
		sFLASH_CS_HIGH();
		//GPIO_ResetBits(GPIOA, GPIO_Pin_4); //Disable Audio Amp
		TIM_Cmd(TIM3, DISABLE);				//Stop PWM generator
		DeInitTIM3GPIO();					// deinit pwm output
		// TIM3 clock disable 
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE); //SAVE POWER
		// enable systick timer
		SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk; //~SysTick_CTRL_TICKINT_Msk;
		return 0; // end of file
	}
		

}

uint8_t WAV_Player_GetBlock(WAV_Player_File_8bitMono* WAV_File, uint8_t* data)
{
	uint8_t buffer[2], temp;
	if (WAV_File->DataPointer < WAV_File->DataBlockSize) // get next byte
	{

		sFLASH_ReadBuffer(buffer, WAV_File->FileStartAddress + WAV_File->DataStartAddress + WAV_File->DataPointer, 1);
		temp = buffer[0];

		WAV_File->DataPointer++;
		*data = temp;
		return 1;
	}
	else
	{
		return 0; // end of file
	}
		

}