#pragma once
#include "stm32f0xx.h"
#include "WAVplayer.h"
#include <stm32f0xx_usart.h>


/* Constants used by Serial Command Line Mode */
#define CMD_STRING_SIZE       128

/* Exported macro ------------------------------------------------------------*/
/* Common routines */
#define IS_AF(c)             ((c >= 'A') && (c <= 'F'))
#define IS_af(c)             ((c >= 'a') && (c <= 'f'))
#define IS_09(c)             ((c >= '0') && (c <= '9'))
#define ISVALIDHEX(c)        IS_AF(c) || IS_af(c) || IS_09(c)
#define ISVALIDDEC(c)        IS_09(c)
#define CONVERTDEC(c)        (c - '0')

#define CONVERTHEX_alpha(c)  (IS_AF(c) ? (c - 'A'+10) : (c - 'a'+10))
#define CONVERTHEX(c)        (IS_09(c) ? (c - '0') : CONVERTHEX_alpha(c))

#define SerialPutString(x)   Serial_PutString((uint8_t*)(x))

/* Exported functions ------------------------------------------------------- */

/**
  * @brief  Receive byte from sender
  * @param  c: Character
  * @param  timeout: Timeout
  * @retval 0: Byte received
  *         -1: Timeout
  */
int32_t Receive_Byte(uint8_t *c, uint32_t timeout);
uint32_t Send_Byte(uint8_t c);
void SerialPutChar(uint8_t c);
void Serial_PutString(uint8_t *s);



uint32_t SerialKeyPressed(uint8_t *key);
uint8_t GetKey(void);
void SerialPutChar(uint8_t c);
void Serial_PutString(uint8_t *s);
void GetInputString(uint8_t * buffP);

void Int2HEX(uint8_t *p_str, uint32_t intnum);
void Int2Str(uint8_t* str, int32_t intnum);
uint32_t Str2Int(uint8_t *inputstr, int32_t *intnum);
uint32_t GetIntegerInput(int32_t * num);
void Delay(uint32_t MilS);
void DelaySec(uint32_t S);
//Define time keeping variables
extern volatile uint32_t Milliseconds, Seconds;

