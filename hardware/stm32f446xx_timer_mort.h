/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F446XX_TIMER_H_
#define __STM32F446XX_TIMER_H_


/* Includes ------------------------------------------------------------------*/
#include "system/stm32f446xx_mort.h"
#include "stm32f446xx_rcc_mort.h"
#include "stm32f446xx_interruptcontroller_mort.h"

/* Macros ------------------------------------------------------------------*/




/* Function Definitions-------------------------------------------------------*/
void initTimer3AsTimeBase1ms( void );
uint32_t getTime_ms( void );
void TIM3_IRQHandler(void);

#endif /*__STM32F446XX_TIMER_H_ */