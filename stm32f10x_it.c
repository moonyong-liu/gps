/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include <string.h>
#include "gps.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define TOPFLASH  0x08163840
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
unsigned int p;
//extern unsigned char *top;
//extern unsigned char *temp;
extern unsigned char Flag_one_message;

/* GPS *************/
unsigned char GPS_keyword[5];
unsigned char GPS_data_buff[80];
unsigned char *p_GPS_data_buff = GPS_data_buff;
unsigned char *p_GPS_keyword = GPS_keyword;
unsigned char Buffer_Remessage[100];

t_GPS_data GPS_data;

unsigned char flag_GPS_data_updated = 1;
unsigned char flag_GPS_data_processed = 0;
unsigned char flag_usart3Rx;	//if received some data, this will be set


/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}



/* 
** brief: receive GPS message by UART1 
** param: none 
** date:  6/14/2013 
*/
#if 0
unsigned int Flag_Re_Data = 0;      //  flag of already received message
unsigned int Flag_Checksum = 0;     //  flag of two checksum numbers
unsigned int Flag_Checksum_A = 1;   //  flag of already received all message and should be receive one '*' and two checksum numbers
void USART1_IRQHandler(void)
{		
	uint16_t tmp_data;
	tmp_data = USART_ReceiveData(USART1);
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET && Flag_Re_Data < 100 )   // if receive message amount doesn't overflow
	{
		
		USART_ClearITPendingBit(USART1,  USART_IT_RXNE);
//		flag_usart3Rx = 1;
			if((tmp_data == '$') || Flag_Re_Data ){               // if received data is '$' or Flag_Re_Data was set ture
				if( tmp_data != '*' && Flag_Checksum_A ){			     // Flag_Checksum_A control when receive the "*" (end flag),
																																						 // by "else if" receive checksum continue		
					Buffer_Remessage[Flag_Re_Data++] = tmp_data;
				}
				else if( Flag_Checksum < 3 ){       // loop three times, receive one "*" and two checksum numbers
					Flag_Checksum_A = 0;              
					Flag_Checksum += 1;
					Buffer_Remessage[Flag_Re_Data++] = tmp_data;
				}
				else{
					Flag_one_message = 1;               // receive a whole message 
					Flag_Re_Data = 0;                   // clear receive data flag 
					Flag_Checksum = 0;                  // reset flag
					Flag_Checksum_A = 1;                // reset flag
					USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
			    }
      }
	}
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)	    	//  发生溢出需先读SR,再读DR
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);	                //读SR
		USART_ReceiveData(USART1);			       	            //读DR
	}
}
#endif 

#define FRAMENUMBER 10
// one frame buffer struct
typedef struct{
	u16 OneFrameBuf[100];	
}_OneF; 
_OneF DBuf[FRAMENUMBER]; // data buffer 10*100
u8 OneFrameRe; // receive a new frame
u8 OneFramePr; //process a frame
u8 OneByte;
u8 CheckByte;
void USART1_IRQHandler(void)
{
	u16  rdata;
	u16* pdata = (u16*)&DBuf[OneFrameRe];
	rdata = USART_ReceiveData(USART1);
	
	if( USART_GetITStatus(USART1, USART_IT_RXNE) != RESET ){
		USART_ClearITPendingBit(USART1,  USART_IT_RXNE);
		if( rdata == '$' ){
			pdata[OneByte] = rdata;
			OneByte++;
		}
		else if( OneByte ){
			pdata[OneByte] = rdata;
			OneByte++;
		}
		if( rdata == '*' ){
			CheckByte = OneByte;
		}
		if( CheckByte ){
			if( OneByte-CheckByte == 2 ){
				OneByte = 0;
				CheckByte = 0;
				OneFrameRe++;
				OneFrameRe = OneFrameRe%FRAMENUMBER;
			}
		}
	}
	if(USART_GetFlagStatus(USART1,USART_FLAG_ORE)==SET)	    	//  发生溢出需先读SR,再读DR
	{
		USART_ClearFlag(USART1,USART_FLAG_ORE);	                //读SR
		USART_ReceiveData(USART1);			       	                //读DR
	}
}


// wakeup lcd
// 右上第一个
// PB12 
void EXTI3_IRQHandler(void)
{
	GPIO_SetBits( GPIOB, GPIO_Pin_12 );
}


void
EXTI0_IRQHandler(void)
{
	EXTI->PR |= 1;           
	CodeStart();
}

/* function : TIM1_TRG_COM_IRQHandler
** parameter: none
** return   : none 
** priority :  */

#if 0
void TIM1_UP_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_Update)!=RESET){
		TIM_ClearITPendingBit(TIM1,TIM_IT_Update);
		GPIO_ResetBits( GPIOB, GPIO_Pin_1 );
  }
}
#endif
u8 Flag1s;
void TIM1_UP_IRQHandler(void)
{
	Flag1s++;
	if(Flag1s>9){
		Flag1s = 0;
		GPIO_ResetBits( GPIOB, GPIO_Pin_12 );
	}
}


void TIM1_CC_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM1,TIM_IT_CC1)!=RESET){
		TIM_ClearITPendingBit(TIM1,TIM_IT_CC1);
  }
	Flag1s = 0;
	
}
