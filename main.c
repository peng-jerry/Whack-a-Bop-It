
/**
  ******************************************************************************
  * @file    main.c 
  * @author  YOU
  * @version 
  * @date    
  * @brief   after the system functions, main is the next function that gets called.
  *             You should modify main and call other functions from here.
  ******************************************************************************
  */
#include <stdint.h>

#include "system/stm32f446xx_system_mort.h"
#include "stm32f446xx_gpio_mort.h"
#include "stm32f446xx_usart3_mort.h" //always include usart where you want to do communications
#include "stm32f446xx_timer_mort.h"
#include "nucleo_led.h"
#include "os/events.h"
#include "os/eventchecker.h"
#include "os/statemachine.h"
#include "os/services.h"
#include "os/timerqueue.h"
#include "stm32f446xx_interruptcontroller_mort.h"


// Simple delay function using software loops, not very good.
// you should implement your own eventually using timers once
// you learn about them.
void delay(volatile int count) {
    while (count--) {
        __asm__("nop");
    }
}


int main (void)
{
    initUSART3();
    initGpioC6C7AsInput();
    initGpioB12B13B15AsOutput();
    initTimer3AsTimeBase1ms();
    setGPIOB15();
    clearGPIOB12();
    printfUSART3("State:Welcoming \n");
    
    while(1)
    {
    	timeoutEventCheck();
        ButtonPressEventCheck();

        serviceBopEventQueue();
    }
}





