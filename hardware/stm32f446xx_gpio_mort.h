/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32F446XX_GPIO_MORT_H_
#define __STM32F446XX_GPIO_MORT_H_


/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "system/stm32f446xx_mort.h"

/* Macros for Everyone--------------------------------------------------------*/
#define PIN_0   0
#define PIN_1   1
#define PIN_2   2
#define PIN_3   3
#define PIN_4   4
#define PIN_5   5
#define PIN_6   6
#define PIN_7   7
#define PIN_8   8
#define PIN_9   9
#define PIN_10  10




/*Function declarations---------------------------------------------------------*/
void initGpioC6C7AsInput( void );
void initGpioD8D9AsAF7( void );
void initGpioB12B13B15AsOutput( void );
void setGPIOB12( void );
void clearGPIOB12( void );
void setGPIOB13( void );
void clearGPIOB13( void );
void setGPIOB15( void );
void clearGPIOB15( void );

uint32_t checkGPIOC7( void );
uint32_t checkGPIOC6(void);



#endif /*__STM32F446XX_GPIO_MORT_H_ */
