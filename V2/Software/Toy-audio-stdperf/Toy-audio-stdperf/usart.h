#pragma once
#include <stm32f0xx.h>
#include <stm32f0xx_usart.h>
#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>

/*
typedef enum 
{
	HAL_OK      = 0x00,
	HAL_ERROR   = 0x01,
	HAL_BUSY    = 0x02,
	HAL_TIMEOUT = 0x03
} HAL_StatusTypeDef;
*/

void InitUSART1(void);
//void Serial_PutByte(USART_TypeDef *USARTx, uint8_t byte);
//uint8_t Serial_GetByte(USART_TypeDef *USARTx);
//void Serial_SendPacket(USART_TypeDef *USARTx, uint8_t *data, uint16_t length);
//void Serial_PutString(USART_TypeDef *USARTx, uint8_t *p_string);
//HAL_StatusTypeDef HAL_UART_Receive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout);
//HAL_StatusTypeDef HAL_UART_Transmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout);


