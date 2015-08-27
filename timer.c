/*
** All timer in this file
** Author Moonyong
** Date 9/22/2013 */

#include "stm32f10x.h"

/* FUNCTION: TIMER1 1s
** PARAMETER: 
** RETURN: */

TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

void Timer1Init( void )
{
	/* TIM1 Peripheral Configuration ----------------------------------------*/
  /* Time Base configuration */	
	TIM_DeInit(TIM1);
	TIM_TimeBaseStructure.TIM_Period=2000;		 //ARR的值
	TIM_TimeBaseStructure.TIM_Prescaler=36000;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1; //采样分频
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up; //向上计数模式
  //TIM_TimeBaseStructure.TIM_RepetitionCounter = 4;
	TIM_ClearFlag(TIM1, TIM_FLAG_Update);
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);
	TIM_ITConfig(TIM1,TIM_IT_Update,ENABLE);
	//TIM_ITConfig(TIM1,TIM_IT_Trigger,ENABLE);
	/* TIM1 counter enable */
	TIM_Cmd(TIM1, ENABLE);
	
}


 

