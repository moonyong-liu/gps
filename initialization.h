#ifndef __INIT_H
#define __INIT_H

#include "stm32f10x.h"

void GPIO_INIT(void);
void NVIC_INIT(void);
void RCC_INIT(void);
void UARTForGPS_INIT(void);
void EXTI_INIT(void);


#endif /*__INIT_H*/
