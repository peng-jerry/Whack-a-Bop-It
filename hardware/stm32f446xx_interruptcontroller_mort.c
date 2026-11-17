/**
  ******************************************************************************
  * @file    stm32f446xx_interruptcontroller_mort.c 
  * @author  YOURNAME
  * @version 
  * @date    
  * @brief   Controls STM32F446ze NVIC access and interrupt control
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "stm32f446xx_interruptcontroller_mort.h"


/* MACRO definitions----------------------------------------------------------*/

//REGISTER ADDRESSES:
#define SYSTEM_CONTROL_BASE_ADDRESS (0xE000E000)
#define NVIC_BASE_ADDRESS (SYSTEM_CONTROL_BASE_ADDRESS + 0x100)
#define NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31 (NVIC_BASE_ADDRESS)
#define TIM3_INTERRUPT_BIT (0x20000000)


// FLAGS:

/* function definitions-------------------------------------------------------*/
void enableNVIC_Timer3(void)
{
    volatile uint32_t * reg_pointer_32;
    reg_pointer_32 = (volatile uint32_t *)NVIC_INTERRUPT_SET_ENABLE_REGISTER_0_31;
    *reg_pointer_32 = TIM3_INTERRUPT_BIT;
}


/* Interrupt Handler----------------------------------------------------------*/


//EOF