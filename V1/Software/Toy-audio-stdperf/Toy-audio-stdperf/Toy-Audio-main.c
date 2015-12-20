#include <stm32f0xx_gpio.h>
#include <stm32f0xx_rcc.h>
#include <stm32f0xx_tim.h>
#include <stm32f0xx_misc.h>
#include <stm32f0xx.h>
#include "WAVplayer.h"
#include "sFlash.h"
#include "usart.h"
#include "common.h"
#include "Terminal.h"
#include "ok-sound.h"
#include "stm32f0xx_pwr.h"
#include "stm32f0xx_dbgmcu.h"
#include "stm32f0xx_rtc.h"
#include "stm32f0xx_exti.h"
#include "stm32f0xx_syscfg.h"


uint16_t CCR4_Val = 0x80;
uint8_t PWMvalue, Prev_WAVdata;
uint8_t ITcounter = 0;
uint32_t WAVindex=0;
uint32_t counter = 0;
uint16_t x = 0;
//uint32_t WAV_Filesize;
//uint32_t WAV_File_Index;

// deplop, 
// use 0.5s (4000 counts) to ramp pwm op to mid value (128)
#define  WaitCount 4000/128
			  

extern void TIM3_IRQHandler(); // reference to TIM3 interrupt vector

void InitTIM3GPIO(void);
void DeInitTIM3GPIO(void);
void InitTIM3(void);
void InitClocks(void);
void SelectHSI(void);
void Sleep(void);
void InitAudioGPIO(void);
void InitButtonGPIO(void);
void InitWkupGPIO(void);
void InitEXTI(void);

//Define time keeping variables
volatile uint32_t Milliseconds = 0, Seconds = 0;
typedef enum {
	start1 = 0, start2, playing1, played1, playing2, played2, waitingfor1, waitingfor2
} StateTypeDef;

void SysTick_Handler(void) {
	Milliseconds++; //Increment millisecond variable
	if (Milliseconds % 1000 == 999) { //If 1000 milliseconds have passed, increment seconds
		Seconds++;
	}
}


void Delay(uint32_t MilS) 
	{
	uint32_t MSStart = Milliseconds;
		while ((Milliseconds - MSStart) < MilS) 
			Sleep(); //wait for a (systick) interrupt
			//asm("nop");
}

//Delay function for second delay 
void DelaySec(uint32_t S)
{
	uint32_t Ss = Seconds;
	while ((Seconds - Ss) < S)
		asm("nop");
}

WAV_Player_File_8bitMono aWAV_File;	// global WAV file struct
uint8_t WAVdata;
uint8_t *WAVdataPointer = &WAVdata;
uint8_t WAV_DataPending = 0;

void InitClocks(void) {
    /*
    HSI: 8 MHz
    PLL: RCC_PLLSource_HSI_Div2 * 4 => 16 MHz
    */
	RCC_DeInit(); //free PF0 and PF1
	RCC_PLLConfig(RCC_PLLSource_HSI_Div2, 8);
	RCC_PLLCmd(ENABLE);

	    // Wait
	while (RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET) continue;

	    // Use PLL
	RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

	while (RCC_GetSYSCLKSource() != 0x08) continue;	// 0x08: PLL used as system clock
	
	//RCC_PREDIV1Config(RCC_PREDIV1_Div1);
	RCC_HCLKConfig(RCC_SYSCLK_Div1); // 16MHz
	RCC_PCLKConfig(RCC_SYSCLK_Div1); // 16MHz
	
	//FLASH_SetLatency(FLASH_Latency_1);
	//FLASH_PrefetchBufferCmd(ENABLE);

}
void SelectHSI(void)
{
	RCC_DeInit(); //free PF0 and PF1
	RCC_SYSCLKConfig(RCC_SYSCLKSource_HSI);
	while (RCC_GetFlagStatus(RCC_FLAG_HSIRDY) == RESET)
		;
	RCC_PREDIV1Config(RCC_PREDIV1_Div1);
	RCC_HCLKConfig(RCC_SYSCLK_Div1);
	RCC_PCLKConfig(RCC_SYSCLK_Div1);
}

void Stop(void)
{
	InitButtonGPIO();
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);  //disable audio amp
	GPIO_SetBits(GPIOF, GPIO_Pin_0);  //deselect SPI Flash
	DeInitTIM3GPIO();
	while ((GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET))
		;  //wait
	SysTick->CTRL  |= SysTick_CTRL_ENABLE_Msk; // start systick timer
	Delay(100); // wait for button to debounce
		// disable systick timer
	SysTick->CTRL  &= ~SysTick_CTRL_ENABLE_Msk; //stop systick timer

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, DISABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, DISABLE);
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOF, DISABLE);
	InitEXTI();
	RCC_PREDIV1Config(RCC_PREDIV1_Div16); // Slow down the clock
	//DBGMCU_Config(DBGMCU_STOP, ENABLE); //enable debugging during standy mode
	PWR_ClearFlag(PWR_FLAG_WU | PWR_FLAG_SB);
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
	PWR_EnterSTOPMode(PWR_Regulator_LowPower, PWR_STOPEntry_WFE);
	RCC_PREDIV1Config(RCC_PREDIV1_Div1);
}

void InitEXTI(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Event; 
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	
	EXTI_Init(&EXTI_InitStructure);

	EXTI->PR &= ~EXTI_Line0; // clear pending event
	
}


void Sleep(void)
{
	PWR_EnterSleepMode(PWR_SLEEPEntry_WFI | PWR_SLEEPEntry_WFE);
}

void Standby(void)
{
	uint32_t i;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE); 
	//RCC_APB1PeriphClockCmd(RCC_APB2Periph_DBGMCU, ENABLE); 
	
	//PWR_ClearFlag(PWR_FLAG_SB);
	// Check if the StandBy flag is cleared 
	//if (PWR_GetFlagStatus(PWR_FLAG_SB) != RESET)
	//{
	//	while (1)
	//		;
	//}
	
	/*
	// Enable the LSI OSC 
	RCC_LSICmd(ENABLE);
	// Wait till LSI is ready 
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{}
	*/
	//InitWkupGPIO(); // not needed
	//RTC_DeInit();

	//PWR_WakeUpPinCmd(PWR_WakeUpPin_1 | PWR_WakeUpPin_2, DISABLE);
	//DBGMCU_Config(DBGMCU_STANDBY, ENABLE); //enable debugging during standy mode
	PWR_ClearFlag(PWR_FLAG_WU | PWR_FLAG_SB);
	//PWR->CR |= PWR_CR_CWUF;
	//RTC_ClearFlag(RTC_FLAG_ALRAF);
	PWR_WakeUpPinCmd(PWR_WakeUpPin_1, ENABLE);
	//for (i = 0; i++; i < 5000)
	//	;
	PWR_EnterSTANDBYMode();
	// the device will be reset when exiting standby mode
	//InitButtonGPIO();
}



	

int main()
{
	int32_t i,j, temp;
	StateTypeDef  State;
	//InitClocks();
	InitAudioGPIO();
	InitButtonGPIO();
	SelectHSI(); //8MHz clock
	SystemCoreClockUpdate(); //Update SystemCoreClock variable to current clock 
	SysTick_Config(SystemCoreClock / 1000); //Set up a systick interrupt systick clock
	//Delay(1000);
	//InitTIM3();
	//sFLASH_Init();
	//sFLASH_BitBangInit();
	//InitUSART1();
	DeInitTIM3GPIO();

/*
	for (;;)
	{
		//load music to spi flash
		Main_Menu();
	}
*/
	//RTC_RefClockCmd(ENABLE); // The RTC registers are used to store the song status
	  /* Enable the PWR clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
	  /* Disable the write protection for RTC registers */
	  /* Allow access to RTC */
	PWR_BackupAccessCmd(ENABLE);
	/*
    //Enter RTC Init mode
	RTC->ISR = 0; 
	RTC->ISR |= RTC_ISR_INIT; 
	while ((RTC->ISR & RTC_ISR_INITF) == 0)
		;
	// Set 24-h clock
	RTC->CR |= RTC_CR_FMT; 
*/

	/*
	RCC_LSICmd(ENABLE);
	// Wait till LSI is ready 
	while (RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
	{
	}
	RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
	RCC_RTCCLKCmd(ENABLE);
	RTC_WriteProtectionCmd(DISABLE);
	RTC_EnterInitMode();
	// Wait for RTC APB registers synchronisation 
	//RTC_WaitForSynchro();
	*/
	Delay(100);
	//RTC->CR |= RTC_CR_FMT;
	//Delay(1);
	i = 0;
	if ((RTC->CR & RTC_CR_FMT) == RTC_CR_FMT)
		State = waitingfor1; // Enlish song
	else
		State = waitingfor2; // Dutch song
	//RCC_RTCCLKCmd(DISABLE);
	for (;;)
	{
		if (WAV_DataPending == 1)
		{
			if (State == playing1 || State == playing2)
			{
				temp = WAV_Player_GetByte(&aWAV_File, &WAVdata);
				if (temp == 1)
				{
					WAV_DataPending = 0;
				}
				else
				{
					WAV_DataPending = 0;
					if (State == playing1)
						State = played1;
					if (State == playing2)
						State = played2;
				}	
				if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) == Bit_SET)
				{
					if (i == 24000)	// 3 seconds
					{
						//stop playing
						if (State == playing1)
							State = played1;
						if (State == playing2)
							State = played2;
					}
					if (i == 1500)	// 
					{
						//next
						if (State == playing1)
							State = start2;
						if (State == playing2)
							State = start1;
					}
					i++;
				}
				else
				{	
					if (j < 2000)
						j++;
					else
					{
						i = 0;
						j = 0;
					}

				}
			}
		}
	
		if (State == played1 || State == played2)
		{
			//uint32_t temp;
			WAV_DataPending = 0;  
			RTC_EnterInitMode();
			//temp = (RTC->CR)&(~(RTC_CR_WUCKSEL_0 | RTC_CR_WUCKSEL_1));
			if (State == played1)
			{
				State = waitingfor2;
				RTC->CR &= ~RTC_CR_FMT;				
			}

			if (State == played2)
			{
				State = waitingfor1;
				RTC->CR |= RTC_CR_FMT;				
			};
			//Delay(1);
			//RCC_LSICmd(DISABLE);
			Standby();
		}
		
		if (State == waitingfor1 || State == waitingfor2)
		{
			//Stop();	// goto stop mode, wait for trigger event
			if (State == waitingfor1)
				State = start1;
			if (State == waitingfor2)
				State = start2;	
		}
		if (State == start1 || State == start2)
		{
			if (State == start1)
			{
				WAV_FILE_ADDRESS = WAV_FILE_ADDRESS1;
				State = playing1;
			}
			if (State == start2)
			{
				WAV_FILE_ADDRESS = WAV_FILE_ADDRESS2;
				State = playing2;
			}			  
			WAV_DataPending = 1;  
			aWAV_File.FileStartAddress = WAV_FILE_ADDRESS;
			Start_WAV_Player(&aWAV_File);
		}

		//Sleep();
	}
}



void InitButtonGPIO(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void InitWkupGPIO(void)
{

	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// PA0 = WKUP1
	// GPIO_PinAFConfig(GPIOA, GPIO_PinSource0, GPIO_AF_0); // select WKUP
}


void InitAudioGPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_ResetBits(GPIOA, GPIO_Pin_4);  //disable audio amp

	
}

void InitTIM3GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF; //TIM3
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource1, GPIO_AF_1);
	// Turn Speaker on
	GPIO_SetBits(GPIOA, GPIO_Pin_4);
	
}
void DeInitTIM3GPIO(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	// Turn Speaker off
	//GPIO_ResetBits(GPIOA, GPIO_Pin_4);

}
			  

void InitTIM3(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	TIM_DeInit(TIM3);
	
	/* TIM3 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_InternalClockConfig(TIM3);
	
    /* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = 250;
	TIM_TimeBaseStructure.TIM_Prescaler = 0; //8MHz clock 32KHz PWM
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Down;

	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);


	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	//TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	//TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;
	//TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset; 



	 /* PWM1 Mode configuration: Channel4 */	
	TIM_OCInitStructure.TIM_Pulse =0x80; // 50% duty cycle
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);
	// enable preload feature CCR4 shadow registers, copy shadow register to CCR4 when an update event occurs
	//TIM3->CCMR2 |= TIM_CCMR2_OC4PE;
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM3, ENABLE);



	/* TIM3 enable counter */
	//TIM_Cmd(TIM3, ENABLE);
	
	/* TIM3 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM3, ENABLE);
	

	TIM_ClearITPendingBit(TIM3, TIM_EventSource_Update); // clear UIF flag
	
	//enable TIM3 interrupt
	//NVIC_InitTypeDef nvicStructure;
	//nvicStructure.NVIC_IRQChannel = TIM3_IRQn;
	//nvicStructure.NVIC_IRQChannelPriority = 0;
	//nvicStructure.NVIC_IRQChannelCmd = ENABLE;
	//NVIC_Init(&nvicStructure);
	NVIC_EnableIRQ(TIM3_IRQn);
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);

}

void TIM3_IRQHandler(void)
{
	TIM_ClearITPendingBit(TIM3,TIM_EventSource_Update); // clear UIF flag

	if (ITcounter < 3)  // 8kHz data 32kHz pwm
		ITcounter++;
	else
	{
		TIM3->CCR4 = WAVdata;	// write next sample		
		WAV_DataPending = 1;	
		ITcounter = 0;
	}
	
}