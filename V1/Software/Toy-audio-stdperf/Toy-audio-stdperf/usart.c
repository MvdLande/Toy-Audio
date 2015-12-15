#include "usart.h"
#include "ymodem.h"
#include "common.h"


/**
**===========================================================================
**
**  Abstract: Initialize USART1
**
**===========================================================================
*/
void InitUSART1(void)
{

	// USART peripheral initialization settings    
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_ClockInitTypeDef USART_ClockInitStructure;

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	//Configure USART1 pins: Rx (PA2), Tx(PA3)
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	// configure GPIO pins with GPIO_Mode_AF before setting the AF config!
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_1);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_1);
	
	//Configure USART1 setting: ----------------------------
	USART_StructInit(&USART_InitStructure);			// default 8bit, 9600 baud, stopbit=1, parity=none, full duplex, no hardware flowcontrol
	USART_InitStructure.USART_BaudRate = 115200;	// set baudrate to 115k2
	//USART_InitStructure.USART_BaudRate = 19200;	// set baudrate to 19k2
	
	USART_OverSampling8Cmd(USART1, ENABLE); // standard oversampling = 16

	USART_Init(USART1, &USART_InitStructure); // USART is disabled after calling the USART_Init function
	
	USART_Cmd(USART1, ENABLE);
	
	//Serial_PutString(USART1, "USART1 Init done...\r\n");
}


/**
**===========================================================================
**
**  Abstract: Get_Byte (blocking mode)
**
**===========================================================================
*/

/*
uint8_t Serial_GetByte(USART_TypeDef *USARTx)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_RXNE) == RESET)
		;
	return USART_ReceiveData(USARTx);
}
*/
/**
**===========================================================================
**
**  Abstract: Send_Byte (blocking mode)
**
**===========================================================================
*/
/*
void Serial_PutByte(USART_TypeDef *USARTx, uint8_t byte)
{
	while (USART_GetFlagStatus(USARTx, USART_FLAG_TXE) == RESET)
		;
	USART_SendData(USARTx, byte);
}
*/
/**
**===========================================================================
**
**  Abstract: SendPacket
**
**===========================================================================
*/
/*
void Serial_SendPacket(USART_TypeDef *USARTx, uint8_t *data, uint16_t length)
{
	uint16_t i;
	i = 0;
	while (i < length)
	{
		Serial_PutByte(USARTx, data[i]);
		i++;
	}
}
*/
/**
**===========================================================================
**
**  Abstract: SendString
**
**===========================================================================
*/
/*
void Serial_PutString(USART_TypeDef *USARTx, uint8_t *p_string)
{
	uint16_t length = 0;

	while (p_string[length] != '\0')
	{
		Serial_PutByte(USARTx, p_string[length]);
		length++;
	}
}

HAL_StatusTypeDef UART_WaitOnFlagUntilTimeout(USART_TypeDef *USARTx, uint32_t USART_FLAG, uint32_t Timeout)
{
	uint32_t MSStart = Milliseconds; 
	while (USART_GetFlagStatus(USARTx, USART_FLAG) == RESET)
	{	
		if ((Milliseconds - MSStart) < Timeout) 
			asm("nop");
		else
			return HAL_TIMEOUT;
		
	}
	return HAL_OK;
}
		

HAL_StatusTypeDef HAL_UART_Receive(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	uint32_t i=0;
	if (Size == 0)
		return HAL_ERROR;
	if (UART_WaitOnFlagUntilTimeout(USARTx, USART_FLAG_RXNE, Timeout) != HAL_OK)
		return HAL_TIMEOUT;
	else
	{
		pData[i] = USART_ReceiveData(USARTx);
		if (++i >= Size)
			return HAL_OK;
	}
}

HAL_StatusTypeDef HAL_UART_Transmit(USART_TypeDef *USARTx, uint8_t *pData, uint16_t Size, uint32_t Timeout)
{
	uint32_t i = 0;
	if (Size == 0)
		return HAL_ERROR;
	if (UART_WaitOnFlagUntilTimeout(USARTx, USART_FLAG_TXE, Timeout) != HAL_OK)
		return HAL_TIMEOUT;
	else
	{
		USART_SendData(USARTx, pData[i]);
		if (++i >= Size)
			return HAL_OK;
	}
}
*/
