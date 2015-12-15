#pragma once
#include "common.h"
#include "sFLASH.h"
#include "SimpleFS.h"

typedef struct
{
	uint32_t FileStartAddress;			// Begin of File address
	uint32_t DataSizeOffset;			// offset to Datasize info
	uint32_t DataStartAddress;			// Begin of Data block
	uint32_t DataBlockSize;				// Datablock size
	uint32_t DataPointer;				// Datapointer for WAV player
}WAV_Player_File_8bitMono;

extern WAV_Player_File_8bitMono aWAV_File;	// global WAV file struct

uint32_t GetWAVdataSize(WAV_Player_File_8bitMono* WAV_File);
void Start_WAV_Player(WAV_Player_File_8bitMono* WAV_File);
uint8_t WAV_Player_GetByte(WAV_Player_File_8bitMono* WAV_File, uint8_t* data);