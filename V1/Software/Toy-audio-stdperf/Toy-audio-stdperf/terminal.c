//-----------------------------------------------------------------------------
// Simple terminal program LF is used to indicate end of line
//-----------------------------------------------------------------------------


#include "Terminal.h"
#include "sFlash.h"
#include "common.h"
#include "SimpleFS.h"
#include "WAVplayer.h"

#define CR 13
#define LF 10

// usart received data buffer
//#define RXBUFFERSIZE 1
//uint8_t aRxBuffer[RXBUFFERSIZE];
uint8_t aRxBuffer;

uint8_t TerminalState;



/* Buffer used for reception */
#define sFLASHBUFFERSIZE 256
uint8_t sFLASHBUFFER[sFLASHBUFFERSIZE];

/* Buffer used for transmission */
#define TXSTARTMESSAGESIZE 25
//static uint8_t aTxStartMessage[] = "Terminal Initialized...\n>";

uint8_t tab_1024[1024] =
{
	0
};


/**
  * @brief  Download a file via serial port
  * @param  None
  * @retval None
  */
void SerialDownload(void)
{
	uint8_t Number[10] = { 0 };
	int32_t Size = 0;

	SerialPutString("Waiting for the file to be sent ... (press 'a' to abort)\n\r");
	Size = Ymodem_Receive(&tab_1024[0]);
	if (Size > 0)
	{
		SerialPutString("\n\n\r Programming Completed Successfully!\n\rName: ");
		SerialPutString(aFileName);
		Int2Str(Number, Size);
		SerialPutString("\n\r Size: ");
		SerialPutString(Number);
		SerialPutString(" Bytes\r\n");
		SerialPutString("-------------------\n");
	}
	else if (Size == -1)
	{
		SerialPutString("\n\n\rThe image size is higher than the allowed space memory!\n\r");
	}
	else if (Size == -2)
	{
		SerialPutString("\n\n\rVerification failed!\n\r");
	}
	else if (Size == -3)
	{
		SerialPutString("\r\n\nAborted by user.\n\r");
	}
	else
	{
		SerialPutString("\n\rFailed to receive the file!\n\r");
	}
}

/**
  * @brief  Upload a file via serial port.
  * @param  None
  * @retval None
  */
void SerialUpload(void)
{
	uint8_t status = 0; 

	SerialPutString("\n\n\rSelect Receive File\n\r");

	if (GetKey() == CRC16)
	{
	  /* Transmit the flash image through ymodem protocol */
		status = Ymodem_Transmit((uint8_t*)WAV_FILE_ADDRESS, (const uint8_t*)"WAVfilefromTOY-Audio.wav", USER_FLASH_SIZE);

		if (status != 0) 
		{
			SerialPutString("\n\rError Occurred while Transmitting File\n\r");
		}
		else
		{
			SerialPutString("\n\rFile uploaded successfully \n\r");
		}
	}
}

void Main_Menu(void)
{
	uint8_t key = 0;
	uint8_t wait = 0;

	  /* Test if any sector of Flash memory where user application will be loaded is write protected */
	//FlashProtection = FLASH_If_GetWriteProtectionStatus();
	//Terminal_cls();
	while (1)
	{
		uint32_t sFLASH_ID;
		uint8_t array[]  = "\0\0\0\0\0\0\0\0\0\0";

		SerialPutString("\r Main Menu \r\n\n");
		SerialPutString("  Download file1 to SPI Flash -- 1\r\n\n");
		SerialPutString("  Download file2 to SPI Flash -- 2\r\n\n");
		SerialPutString("  Get SPI FLASH ID ------------- 3\r\n\n");
		SerialPutString("  Get WAV data length ---------- 4\r\n\n");
		SerialPutString("  Print filename from SPI Flash  5\r\n\n");
		SerialPutString("  Bulk erase SPI Flash --------- 6\r\n\n");

		    /* Clean the input path */
		//__HAL_UART_SEND_REQ(&huart1, UART_RXDATA_FLUSH_REQUEST);
		USART_RequestCmd(USART1, USART_Request_SBKRQ, ENABLE);
	
		// Receive key
		key = GetKey();

		switch (key)
		{
		case '1' :
		    // Download user application in the SPI Flash
			WAV_FILE_ADDRESS = WAV_FILE_ADDRESS1;
			SerialDownload();
			break;
		case '2' :
			WAV_FILE_ADDRESS = WAV_FILE_ADDRESS2;
			SerialDownload();
		    // Upload user application from the Flash
			//SerialUpload();
			break;
		case '3' :
			sFLASH_ID = sFLASH_ReadID();
			Int2HEX(array, sFLASH_ID);
			SerialPutString("SPI FLASH ID = 0x");
			SerialPutString(array);
			SerialPutString("\r\n");
			Delay(3000);
			break;
		case '4' :
			sFLASH_ID = GetWAVdataSize(&aWAV_File);
			Int2Str(array, sFLASH_ID);
			SerialPutString("WAV data size = ");
			SerialPutString(array);
			SerialPutString("\r\n");
			Delay(3000);
			break;
		case '5':
			sFLASH_ReadBuffer((uint8_t*)&sFLASHBUFFER, WAV_FILE_ADDRESS + 0x60, 100);
			sFLASHBUFFER[100] = '\0';
			SerialPutString("\r\n");
			SerialPutString(sFLASHBUFFER);
			SerialPutString("\r\n");
			Delay(3000);
			break;
		case '6':
			SerialPutString("SPI Flash bulk erase started...  \n");
			sFLASH_EraseBulk();
			Delay(3000);
			SerialPutString("SPI Flash bulk erase finished...  \n");
			break;
		default:
			SerialPutString("Invalid Number ! ==> The number should be either 1, 2, 3, 4,5 or 6\r");
			break;
		}
	}
}

/*
void Terminal_cls(void) 
{
	Serial_PutString((uint8_t*) & "\033[2J");
}
*/
/*
void Terminal_Locate(int column, int row) {
    // Cursor Home    <ESC>[{ROW};{COLUMN}H
	//Terminal_Send_TXT("\033[%d;%dH%c", row + 1, column + 1);
}
*/
/*
static int rgb888tobgr111(int colour) 
{
	int r = (colour >> 23) & 1;
	int g = (colour >> 15) & 1;
	int b = (colour >> 7) & 1;
	return (b << 2) | (g << 1) | (r << 0);
}
 
void Terminal_Foreground(int colour) {
    // Set Attribute Mode    <ESC>[{n}m
    // Foreground Colours : 30 + bgr
	int c = 30 + rgb888tobgr111(colour);
	//Terminal_Send_TXT("\033[%dm", c);
}
 
void Terminal_background(int colour) {
    // Set Attribute Mode    <ESC>[{n}m
    // Background Colours : 40 + bgr
	int c = 40 + rgb888tobgr111(colour);
	//Terminal_Send_TXT("\033[%dm", c);
}

*/