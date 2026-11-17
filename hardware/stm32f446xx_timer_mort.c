/**
  ******************************************************************************
  * @file    stm32f446xx_timer_mort.c 
  * @author  YOURNAME
  * @version 
  * @date    
  * @brief   Controls STM32F446ze timers
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "stm32f446xx_timer_mort.h"
#include "stm32f446xx_usart3_mort.h"

/* MACRO definitions----------------------------------------------------------*/

//REGISTER ADDRESSES:
#define TIMER3_BASE_ADDRESS     ((uint32_t)0x40000400)
#define TIM3_CR1_REGISTER       (TIMER3_BASE_ADDRESS + 0x00)
#define TIM3_SR_REGISTER       (TIMER3_BASE_ADDRESS + 0x10)
#define TIM3_EGR_REGISTER       (TIMER3_BASE_ADDRESS + 0x14)
#define TIM3_PSC_REGISTER       (TIMER3_BASE_ADDRESS + 0x28)
#define TIM3_ARR_REGISTER       (TIMER3_BASE_ADDRESS + 0x2C)
#define TIM3_CAPTURE_COMPARE_MODE_1_REGISTER (TIMER3_BASE_ADDRESS + 0x18)
#define TIM3_CAPTURE_COMPARE_MODE_2_REGISTER (TIMER3_BASE_ADDRESS + 0x1C)

#define TIM3_CCER_REGISTER      (TIMER3_BASE_ADDRESS + 0x20)
#define TIM3_CCR1_REGISTER      (TIMER3_BASE_ADDRESS + 0x34)
#define TIM3_CCR3_REGISTER      (TIMER3_BASE_ADDRESS + 0x3C)
#define TIM3_CCR4_REGISTER      (TIMER3_BASE_ADDRESS + 0x40)
#define TIM_CCMR13_IC1F_N8 (0x00F0)

#define TIM_CCMR13_OC1M_0 (0b00010000)
#define TIM_CCMR13_OC1M_1 (0b00100000)
#define TIM_CCMR13_OC1M_2 (0b01000000)
#define TIM_CCMR13_OCPE (0b00001000)
#define TIM_CCMR13_OUTPUT 0x00
#define TIM_CCMR13_CC1S_INPUT_TI1 (0x0001)
#define TIM_CCMR13_CC3S           (0x0003)
#define TIM_CCMR24_CC4S           (0x0300)

//flags for CR1 register:
#define COUNTER_ENABLE_BIT (uint16_t)0x01

//flags for Status register:
#define TIM_UIF 0x01 //timer 3 overflow flag
#define TIM_CH1_CC1IF 0x02 //timer channel 1 capture/compare event
#define TIM_CH3_CC3IF 0x8 //timer channel 3 capture/compare event
//timer 3 interrupt enable register
# define TIM3_INTERRUPT_ENABLE_REGISTER (TIMER3_BASE_ADDRESS + 0x0C)
//flags for interrupt enable register:
#define TIM_CH3_CC_INTERRUPT_ENABLE 0x8 //timer channel 3 capture/compare interrupt
#define TIM_UPDATE_INTERRUPT_ENABLE 0x1 //timer overflow or event interrupt
//Capture compare enable register
#define TIM3_CAPTURE_COMPARE_ENABLE_REGISTER (TIMER3_BASE_ADDRESS + 0x20)
//flags for TIM3_CCER registers for output:
#define TIM3_CCER_CC3E (0x0100)
#define TIM3_CCER_CC4E (0x1000)
//Capture compare mode registers
#define TIM3_CAPTURE_COMPARE_MODE_1_REGISTER (TIMER3_BASE_ADDRESS + 0x18)
#define TIM3_CAPTURE_COMPARE_MODE_2_REGISTER (TIMER3_BASE_ADDRESS + 0x1C)
//flags for Capture compare mode register
#define TIM_CCMR13_OCPE (0b00001000) // enable preload register channels 1 and 3
// Compare, autoreload and Prescaler registers
#define TIM3_COMPARE_1_REGISTER (TIMER3_BASE_ADDRESS + 0x34)
#define TIM3_COMPARE_2_REGISTER (TIMER3_BASE_ADDRESS + 0x38)
#define TIM3_COMPARE_3_REGISTER (TIMER3_BASE_ADDRESS + 0x3C)
#define TIM3_COMPARE_4_REGISTER (TIMER3_BASE_ADDRESS + 0x40)
#define TIM3_PRESCALER_REGISTER (TIMER3_BASE_ADDRESS + 0x28)
#define TIM3_AUTORELOAD_REGISTER (TIMER3_BASE_ADDRESS + 0X2C)

//SR Flags
#define TIM_SR_CC1IF            ((uint32_t)0x0002)

//CR1 Register flags
#define TIM_CR1_CEN             ((uint16_t)0x01)

//CCER register flags:
#define TIM_CCER_CC1E           ((uint32_t)0x0001)
#define TIM_CCER_CC3E           ((uint32_t)0x0100)


static volatile uint32_t timer3_ms = 0; 


// FLAGS:

/* function definitions-------------------------------------------------------*/
void initTimer3AsTimeBase1ms( void )
{
    volatile uint16_t * reg_pointer_16;

    /* Timer 3 APB clock enable */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);

    /* Enable NVIC timer 3 */
    enableNVIC_Timer3();

    /* Clear any pending flags in the status register */
    reg_pointer_16 = (volatile uint16_t *)TIM3_SR_REGISTER;
    *reg_pointer_16 = 0;

    /* Set Prescale and Autoreload: 1 MHz tick, 1 ms period */
    reg_pointer_16 = (volatile uint16_t *)TIM3_PSC_REGISTER;
    *reg_pointer_16 = 89;
    reg_pointer_16 = (volatile uint16_t *)TIM3_ARR_REGISTER;
    *reg_pointer_16 = 999;

    /* Enable interrupt on overflow only */
    reg_pointer_16 = (volatile uint16_t *)TIM3_INTERRUPT_ENABLE_REGISTER;
    *reg_pointer_16 = TIM_UPDATE_INTERRUPT_ENABLE;

    /* Enable timer 3 */
    reg_pointer_16 = (volatile uint16_t *)TIM3_CR1_REGISTER;
    *reg_pointer_16 = *reg_pointer_16 | TIM_CR1_CEN;
}

uint32_t getTime_ms( void )
{
    //get function for timer3_ms
    return timer3_ms;
}


void TIM3_IRQHandler(void)
{
    volatile uint16_t * reg_pointer_16_sr;
    volatile uint16_t * reg_pointer_16_dier;
    reg_pointer_16_sr = (volatile uint16_t *)TIM3_SR_REGISTER;
    reg_pointer_16_dier = (volatile uint16_t *)TIM3_INTERRUPT_ENABLE_REGISTER;
    //check if Overflow triggered the interrupt
    if (( (*reg_pointer_16_sr & TIM_UIF) >0) && ( (*reg_pointer_16_dier & TIM_UPDATE_INTERRUPT_ENABLE) >0))
    {
        //clear interrupt
        *reg_pointer_16_sr = ~((uint16_t)TIM_UIF);
        //perform action: count one millisecond
        timer3_ms++;
    }
}


/* Interrupt Handler----------------------------------------------------------*/


//EOF