#include "stm32f10x.h"

GPIO_InitTypeDef  GPIO_InitStructure;
NVIC_InitTypeDef  NVIC_InitStructure;
USART_InitTypeDef USART_InitStructure;
EXTI_InitTypeDef  EXTI_InitStructure;
USART_ClockInitTypeDef USART_ClockInitStructure;

ErrorStatus HSEStartUpStatus;


void UARTForGPS_INIT(void)
{
	USART_InitStructure.USART_BaudRate = 38400;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
	USART_ClockInitStructure.USART_Clock = USART_Clock_Disable;
	USART_ClockInitStructure.USART_CPOL = USART_CPOL_Low;
	USART_ClockInitStructure.USART_CPHA = USART_CPHA_2Edge;
	USART_ClockInitStructure.USART_LastBit = USART_LastBit_Disable;

	USART_ClockInit(USART1, &USART_ClockInitStructure);
    USART_Init(USART1, &USART_InitStructure);

    USART_Cmd(USART1, ENABLE);
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);		
}

// config GPIO  
void GPIO_INIT(void)
{
	/******************液晶管脚定义*************/
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOD, &GPIO_InitStructure);


    //   UART 2 config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		  //推挽输出-TX
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入-RX
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	    //   UART 1 config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		  //推挽输出-TX
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  //浮空输入-RX
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// EXTI0 GPIO Config
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;
	GPIO_Init( GPIOA, &GPIO_InitStructure );
	
	 //  PB12 for LCD power on/off
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Init( GPIOB, &GPIO_InitStructure);
}

// config Interrupt
void NVIC_INIT(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);	

	// USART2 NVIC
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// USART1 NVIC 
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// NVIC Of EXTI B10 in line10
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );
	
	// NVIC Of EXTI A0 in line0
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );
	
	// NVIC of TIME1 intterupt for off the LCD
  NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
		// NVIC of EXTI XX in linex for wakeup lcd
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 7;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init( &NVIC_InitStructure );

  NVIC_Init(&NVIC_InitStructure);
	
}

// config EXTI 
void EXTI_INIT(void)
{
	// EXTI B10 Of line10
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOB, GPIO_PinSource10 );
	EXTI_InitStructure.EXTI_Line = EXTI_Line10;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );
	
	// EXTI A0 Of line0
	GPIO_EXTILineConfig( GPIO_PortSourceGPIOA, GPIO_PinSource0 );	
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init( &EXTI_InitStructure );
	
	
}

// config RCC & AFIO 
void RCC_INIT(void)
{
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();										//时钟控制寄存器全部恢复默认值
	
	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);						//外部高速时钟源开启（8M晶振）
	
	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();		//等待外部时钟就绪

	if(HSEStartUpStatus == SUCCESS){
	    /* HCLK = SYSCLK */
	    RCC_HCLKConfig(RCC_SYSCLK_Div1);				//定义AHB设备时钟为系统时钟1分频 	
	    /* PCLK2 = HCLK */
	    RCC_PCLK2Config(RCC_HCLK_Div1);					//定义ApB2设备时钟为HCLK时钟1分频	
	    /* PCLK1 = HCLK/2 */
	    RCC_PCLK1Config(RCC_HCLK_Div2);					//定义ApB1设备时钟为HCLK时钟2分频	
	    /* Flash 2 wait state */
	    FLASH_SetLatency(FLASH_Latency_2);				//设定内部FLASH的的延时周期为2周期
	    /* Enable Prefetch Buffer */
	    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);	 //使能FLASH预存取缓冲区	
	    /* PLLCLK = 8MHz * 9 = 72 MHz */
	    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);	 //配置PLL时钟为外部高速时钟的9倍频，8MHz * 9 = 72 MHz	
	    /* Enable PLL */
	    RCC_PLLCmd(ENABLE);										 //使能PLL时钟	
	    /* Wait till PLL is ready */
	    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET){
	    }
		/* Select PLL as system clock source */
	    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);				 //使用PLL时钟作为系统时钟源	
	    /* Wait till PLL is used as system clock source */
	    while(RCC_GetSYSCLKSource() != 0x08)					 //返回系统所用时钟源确认为外部高速晶振，8M晶振
	    {
	    }
	}

	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO  | 
													RCC_APB2Periph_GPIOA |
													RCC_APB2Periph_GPIOB |
													RCC_APB2Periph_GPIOC |
													RCC_APB2Periph_USART1|
													RCC_APB2Periph_GPIOD |
													RCC_APB2Periph_TIM1, ENABLE );
							
	RCC_APB1PeriphClockCmd( RCC_APB1Periph_USART2 |
													RCC_APB1Periph_TIM2, ENABLE );

}

