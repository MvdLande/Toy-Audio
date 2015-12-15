#pragma once
#include "stm32f0xx.h"
#include "stm32f0xx_usart.h"
#include "usart.h"
#include "ymodem.h"
#include <string.h>

#define TermNewDataFlag 0x80
#define TermInit	0
#define TermFlashErase 1
#define TermFlashPGM 2

/* Constants used by Serial Command Line Mode */
#define TX_TIMEOUT          ((uint32_t)100)
#define RX_TIMEOUT          300000

extern uint8_t *Terminalbuffer;
extern uint8_t TerminalState;
uint8_t Terminal_Init(void);
void Terminal_Send_TXT(uint8_t *Data);
void Terminal_Command_Handler(uint8_t *Data);
void Terminal_cls(void);
void Terminal_Locate(int column, int row);
void Terminal_Foreground(int colour);
void Terminal_background(int colour);

void Main_Menu(void);
