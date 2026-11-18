/**
  ******************************************************************************
  * @file    stm32f446xx_gpio_mort.c 
  * @author  mortamar@andrew.cmu.edu
  * @version 2.0
  * @date    June-2026
  * @brief   Controls STM32F446ze GPIO
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "stm32f446xx_gpio_mort.h"
#include "stm32f446xx_rcc_mort.h"



/* MACRO definitions----------------------------------------------------------*/
//Port A addresses:



//Port B addresses: //Fill the table of Port B addresses
//#define PORTB_BASE_ADDRESS ((uint32_t)0x40020400)
#define PORTB_BASE_ADDRESS    GPIOB_BASE_MORT
#define PORTB_MODER_REGISTER (PORTB_BASE_ADDRESS + 0x00)
#define PORTB_OTYPER_REGISTER (PORTB_BASE_ADDRESS + 0x04)
#define PORTB_OSPEEDR_REGISTER (PORTB_BASE_ADDRESS + 0x08)
#define PORTB_PUPDR_REGISTER (PORTB_BASE_ADDRESS + 0x0C)
#define PORTB_IDR_REGISTER (PORTB_BASE_ADDRESS + 0x10)
#define PORTB_ODR_REGISTER (PORTB_BASE_ADDRESS + 0x14)
#define PORTB_BSRRL_REGISTER (PORTB_BASE_ADDRESS + 0x18)
#define PORTB_BSRR_REGISTER (PORTB_BASE_ADDRESS + 0x18)
#define PORTB_BSRRH_REGISTER (PORTB_BASE_ADDRESS + 0x1A)
#define PORTB_LCKR_REGISTER (PORTB_BASE_ADDRESS + 0x1C)
#define PORTB_AFR1_REGISTER (PORTB_BASE_ADDRESS + 0x20)
#define PORTB_AFR2_REGISTER (PORTB_BASE_ADDRESS + 0x24)


//Port C addresses: //Fill the table of Port C addresses
//#define PORTC_BASE_ADDRESS ((uint32_t)0x40020800)
#define PORTC_BASE_ADDRESS    GPIOC_BASE_MORT
#define PORTC_MODER_REGISTER (PORTC_BASE_ADDRESS + 0x00)
#define PORTC_OTYPER_REGISTER (PORTC_BASE_ADDRESS + 0x04)
#define PORTC_OSPEEDR_REGISTER (PORTC_BASE_ADDRESS + 0x08)
#define PORTC_PUPDR_REGISTER (PORTC_BASE_ADDRESS + 0x0C)
#define PORTC_IDR_REGISTER (PORTC_BASE_ADDRESS + 0x10)
#define PORTC_ODR_REGISTER (PORTC_BASE_ADDRESS + 0x14)
#define PORTC_BSRRL_REGISTER (PORTC_BASE_ADDRESS + 0x18)
#define PORTC_BSRR_REGISTER (PORTC_BASE_ADDRESS + 0x18)
#define PORTC_BSRRH_REGISTER (PORTC_BASE_ADDRESS + 0x1A)
#define PORTC_LCKR_REGISTER (PORTC_BASE_ADDRESS + 0x1C)
#define PORTC_AFR1_REGISTER (PORTC_BASE_ADDRESS + 0x20)
#define PORTC_AFR2_REGISTER (PORTC_BASE_ADDRESS + 0x24)
#define PORTC_OSPEEDR_REGISTER (PORTC_BASE_ADDRESS + 0x08)


//Port D addresses: //These are needed for communication do not edit
//#define PORTD_BASE_ADDRESS ((uint32_t)0x40020C00U)
#define PORTD_BASE_ADDRESS		GPIOD_BASE_MORT
#define PORTD_MODER_REGISTER (PORTD_BASE_ADDRESS + 0x00)
#define PORTD_OTYPER_REGISTER (PORTD_BASE_ADDRESS + 0x04)
#define PORTD_OSPEEDR_REGISTER (PORTD_BASE_ADDRESS + 0x08)
#define PORTD_PUPDR_REGISTER (PORTD_BASE_ADDRESS + 0x0C)
#define PORTD_IDR_REGISTER (PORTD_BASE_ADDRESS + 0x10)
#define PORTD_ODR_REGISTER (PORTD_BASE_ADDRESS + 0x14)
#define PORTD_BSRRL_REGISTER (PORTD_BASE_ADDRESS + 0x18)
#define PORTD_BSRR_REGISTER (PORTD_BASE_ADDRESS + 0x18)
#define PORTD_BSRRH_REGISTER (PORTD_BASE_ADDRESS + 0x1A)
#define PORTD_LCKR_REGISTER (PORTD_BASE_ADDRESS + 0x1C)
#define PORTD_AFR1_REGISTER (PORTD_BASE_ADDRESS + 0x20)
#define PORTD_AFR2_REGISTER (PORTD_BASE_ADDRESS + 0x24)
#define PORTD_OSPEEDR_REGISTER (PORTD_BASE_ADDRESS + 0x08)

//Port E addresses:

//Port F addresses:


//flags MODER Register:
#define GPIO_0_MODER                0x03
#define GPIO_0_MODER_OUT            0x01
#define GPIO_0_MODER_AF             0x02
#define GPIO_1_MODER                (uint32_t)(0x03<<2)
#define GPIO_1_MODER_OUT            (uint32_t)(0x01<<2)
#define GPIO_1_MODER_AF             (uint32_t)(0x02<<2)
#define GPIO_2_MODER                (uint32_t)(0x03<<4)
#define GPIO_2_MODER_OUT            (uint32_t)(0x01<<4)
#define GPIO_2_MODER_AF             (uint32_t)(0x02<<4)
#define GPIO_3_MODER                (uint32_t)(0x03<<6)
#define GPIO_3_MODER_OUT            (uint32_t)(0x01<<6)
#define GPIO_3_MODER_AF             (uint32_t)(0x02<<6)
#define GPIO_4_MODER                (uint32_t)(0x03<<8)
#define GPIO_4_MODER_OUT            (uint32_t)(0x01<<8)
#define GPIO_4_MODER_AF             (uint32_t)(0x02<<8)
#define GPIO_5_MODER                (uint32_t)(0x03<<10)
#define GPIO_5_MODER_OUT            (uint32_t)(0x01<<10)
#define GPIO_5_MODER_AF             (uint32_t)(0x02<<10)
#define GPIO_6_MODER                0x3000
#define GPIO_6_MODER_AF             0x2000
#define GPIO_6_MODER_OUT            0x1000
#define GPIO_6_MODER_IN             0x0000
#define GPIO_6_MODER_AN             0x3000
#define GPIO_7_MODER                (((uint32_t)0x03)<<14)
#define GPIO_7_MODER_OUT            (uint32_t)(0x01<<14)
#define GPIO_7_MODER_AF             (uint32_t)(0x02<<14)
#define GPIO_7_MODER_IN             0x0000
#define GPIO_8_MODER                (uint32_t)(0x03<<16)
#define GPIO_8_MODER_OUT            (uint32_t)(0x01<<16)
#define GPIO_8_MODER_AF             (uint32_t)(0x02<<16)
#define GPIO_9_MODER                (uint32_t)(0x03<<18)
#define GPIO_9_MODER_OUT            (uint32_t)(0x01<<18)
#define GPIO_9_MODER_AF             (uint32_t)(0x02<<18)
#define GPIO_10_MODER                (uint32_t)(0x03<<20)
#define GPIO_10_MODER_OUT            (uint32_t)(0x01<<20)
#define GPIO_10_MODER_AF             (uint32_t)(0x02<<20)
#define GPIO_10_MODER                (uint32_t)(0x03<<20)
#define GPIO_10_MODER_OUT            (uint32_t)(0x01<<20)
#define GPIO_10_MODER_AF             (uint32_t)(0x02<<20)
#define GPIO_11_MODER                (uint32_t)(0x03<<22)
#define GPIO_11_MODER_OUT            (uint32_t)(0x01<<22)
#define GPIO_11_MODER_AF             (uint32_t)(0x02<<22)
#define GPIO_11_MODER                (uint32_t)(0x03<<22)
#define GPIO_11_MODER_OUT            (uint32_t)(0x01<<22)
#define GPIO_11_MODER_AF             (uint32_t)(0x02<<22)
#define GPIO_11_MODER_IN             0x0000
#define GPIO_12_MODER               (((uint32_t)0x03)<<24)
#define GPIO_12_MODER_OUT           (((uint32_t)0x01)<<24)
#define GPIO_13_MODER               (((uint32_t)0x03)<<26)
#define GPIO_13_MODER_OUT           (((uint32_t)0x01)<<26)
#define GPIO_14_MODER                (((uint32_t)0x03)<<28)
#define GPIO_14_MODER_OUT            (((uint32_t)0x01)<<28)
#define GPIO_14_MODER_AF             (((uint32_t)0x02)<<28)
#define GPIO_15_MODER                (((uint32_t)0x03)<<30)
#define GPIO_15_MODER_OUT            (((uint32_t)0x01)<<30)
#define GPIO_15_MODER_AF             (((uint32_t)0x02)<<30)
//flags OTYPER Register:
#define GPIO_0_OTYPER               0x01
#define GPIO_0_OTYPER_PP            0x00
#define GPIO_1_OTYPER               (uint32_t)(0x01<<1)
#define GPIO_1_OTYPER_PP            0x00
#define GPIO_2_OTYPER               (uint32_t)(0x01<<2)
#define GPIO_2_OTYPER_PP            0x00
#define GPIO_3_OTYPER               (uint32_t)(0x01<<3)
#define GPIO_3_OTYPER_PP            0x00
#define GPIO_4_OTYPER               (uint32_t)(0x01<<4)
#define GPIO_4_OTYPER_PP            0x00
#define GPIO_5_OTYPER               (uint32_t)(0x01<<5)
#define GPIO_5_OTYPER_PP            0x00
#define GPIO_6_OTYPER               0x40
#define GPIO_6_OTYPER_PP            0x00
#define GPIO_7_OTYPER               (((uint32_t)0x01)<<7)
#define GPIO_7_OTYPER_PP            0x00
#define GPIO_8_OTYPER               (((uint32_t)0x01)<<8)
#define GPIO_8_OTYPER_PP            0x00
#define GPIO_9_OTYPER               (((uint32_t)0x01)<<9)
#define GPIO_9_OTYPER_PP            0x00
#define GPIO_10_OTYPER               (((uint32_t)0x01)<<10)
#define GPIO_10_OTYPER_PP            0x00
#define GPIO_11_OTYPER               (((uint32_t)0x01)<<11)
#define GPIO_11_OTYPER_PP            0x00
#define GPIO_12_OTYPER              (((uint32_t)0x01)<<12)
#define GPIO_12_OTYPER_PP           0x00
#define GPIO_13_OTYPER              (((uint32_t)0x01)<<13)
#define GPIO_13_OTYPER_PP           0x00
#define GPIO_14_OTYPER               (((uint32_t)0x01)<<14)
#define GPIO_14_OTYPER_PP            0x00
#define GPIO_15_OTYPER               (((uint32_t)0x01)<<15)
#define GPIO_15_OTYPER_PP            0x00
//flags OSPEEDR Register:
#define GPIO_0_OSPEEDR_HIGH_SPEED   3 
#define GPIO_6_OSPEEDR              0x3000
#define GPIO_6_OSPEEDR_HIGH_SPEED   0x3000
#define GPIO_8_OSPEEDR              (((uint32_t)0x03)<<16)
#define GPIO_8_OSPEEDR_FAST_SPEED   (((uint32_t)0x02)<<16)
#define GPIO_8_OSPEEDR_HIGH_SPEED   (((uint32_t)0x03)<<16)
#define GPIO_9_OSPEEDR              (((uint32_t)0x03)<<18)
#define GPIO_9_OSPEEDR_FAST_SPEED   (((uint32_t)0x02)<<18)
#define GPIO_9_OSPEEDR_HIGH_SPEED   (((uint32_t)0x03)<<18)

//flags PUPDR Register:
#define GPIO_0_PUPDR                0x03
#define GPIO_0_PUPDR_NOPULL         0x00
#define GPIO_0_PUPDR_PU            0x01
#define GPIO_0_PUPDR_PD            0x02
#define GPIO_1_PUPDR                (uint32_t)(0x03<<2)
#define GPIO_1_PUPDR_NOPULL         0x00
#define GPIO_1_PUPDR_PU            (uint32_t)(0x01<<2)
#define GPIO_1_PUPDR_PD            (uint32_t)(0x02<<2)
#define GPIO_2_PUPDR                (uint32_t)(0x03<<4)
#define GPIO_2_PUPDR_NOPULL         0x00
#define GPIO_2_PUPDR_PU            (uint32_t)(0x01<<4)
#define GPIO_2_PUPDR_PD            (uint32_t)(0x02<<4)
#define GPIO_3_PUPDR                (uint32_t)(0x03<<6)
#define GPIO_3_PUPDR_NOPULL         0x00
#define GPIO_3_PUPDR_PU            (uint32_t)(0x01<<6)
#define GPIO_3_PUPDR_PD            (uint32_t)(0x02<<6)
#define GPIO_4_PUPDR                (uint32_t)(0x03<<8)
#define GPIO_4_PUPDR_NOPULL         0x00
#define GPIO_4_PUPDR_PU            (uint32_t)(0x01<<8)
#define GPIO_4_PUPDR_PD            (uint32_t)(0x02<<8)
#define GPIO_5_PUPDR                (uint32_t)(0x03<<10)
#define GPIO_5_PUPDR_NOPULL         0x00
#define GPIO_5_PUPDR_PU            (uint32_t)(0x01<<10)
#define GPIO_5_PUPDR_PD            (uint32_t)(0x02<<10)
#define GPIO_6_PUPDR                0x3000
#define GPIO_6_PUPDR_NOPULL         0x00
#define GPIO_6_PUPDR_PD             0x2000
#define GPIO_6_PUPDR_PU             0x1000
#define GPIO_7_PUPDR                (((uint32_t)0x03)<<14)
#define GPIO_7_PUPDR_NOPULL         0x00
#define GPIO_7_PUPDR_PU            (uint32_t)(0x01<<14)
#define GPIO_7_PUPDR_PD            (uint32_t)(0x02<<14)
#define GPIO_8_PUPDR                (uint32_t)(0x03<<16)
#define GPIO_8_PUPDR_NOPULL         0x00
#define GPIO_8_PUPDR_PU            (uint32_t)(0x01<<16)
#define GPIO_8_PUPDR_PD            (uint32_t)(0x02<<16)
#define GPIO_9_PUPDR                (uint32_t)(0x03<<18)
#define GPIO_9_PUPDR_NOPULL         0x00
#define GPIO_9_PUPDR_PU            (uint32_t)(0x01<<18)
#define GPIO_9_PUPDR_PD            (uint32_t)(0x02<<18)
#define GPIO_10_PUPDR                (uint32_t)(0x03<<20)
#define GPIO_10_PUPDR_NOPULL         0x00
#define GPIO_10_PUPDR_PU            (uint32_t)(0x01<<20)
#define GPIO_10_PUPDR_PD            (uint32_t)(0x02<<20)
#define GPIO_11_PUPDR                (uint32_t)(0x03<<22)
#define GPIO_11_PUPDR_NOPULL         0x00
#define GPIO_11_PUPDR_PU            (uint32_t)(0x01<<22)
#define GPIO_11_PUPDR_PD            (uint32_t)(0x02<<22)
#define GPIO_12_PUPDR               (((uint32_t)0x03)<<24)
#define GPIO_12_PUPDR_NOPULL        0x00
#define GPIO_13_PUPDR               (((uint32_t)0x03)<<26)
#define GPIO_13_PUPDR_NOPULL        0x00
#define GPIO_14_PUPDR                (((uint32_t)0x03)<<28)
#define GPIO_14_PUPDR_NOPULL         0x00
#define GPIO_14_PUPDR_PU            (((uint32_t)0x01)<<28)
#define GPIO_14_PUPDR_PD            (((uint32_t)0x02)<<28)
#define GPIO_15_PUPDR                (((uint32_t)0x03)<<30)
#define GPIO_15_PUPDR_NOPULL         0x00
#define GPIO_15_PUPDR_PU            (((uint32_t)0x01)<<30)
#define GPIO_15_PUPDR_PD            (((uint32_t)0x02)<<30)
//input data register:
#define GPIO_0_IDR                0x01
#define GPIO_1_IDR               (uint32_t)(0x01<<1)
#define GPIO_2_IDR               (uint32_t)(0x01<<2)
#define GPIO_3_IDR               (uint32_t)(0x01<<3)
#define GPIO_4_IDR               (uint32_t)(0x01<<4)
#define GPIO_5_IDR               (uint32_t)(0x01<<5)
#define GPIO_6_IDR               0x40
#define GPIO_7_IDR               (uint32_t)(0x01<<7)
#define GPIO_8_IDR               (uint32_t)(0x01<<8)
#define GPIO_9_IDR               (uint32_t)(0x01<<9)
#define GPIO_10_IDR              (uint32_t)(0x01<<10)
#define GPIO_11_IDR              (uint32_t)(0x01<<11)
#define GPIO_14_IDR              (((uint32_t)0x01)<<14)
#define GPIO_15_IDR              (((uint32_t)0x01)<<15)
//flags AFR1 Register:
#define GPIO_0_AFR1_AF2             2
#define GPIO_0_AFR1                 0xF
#define GPIO_6_AFR1                 0xF000000
#define GPIO_6_AFR1_AF2             0x2000000
//flags AFR2 or AFRH Register
#define GPIO_8_AFR2_SET_ALL				0xF
#define GPIO_8_AFR2_AF7					0x7
#define GPIO_9_AFR2_SET_ALL				(uint32_t)(0xF<<4)
#define GPIO_9_AFR2_AF7				(uint32_t)(0x7<<4)

//flags ODR Register:
#define GPIO_0_ODR_HIGH                0x01
#define GPIO_1_ODR_HIGH               (uint32_t)(0x01<<1)
#define GPIO_2_ODR_HIGH               (uint32_t)(0x01<<2)
#define GPIO_3_ODR_HIGH               (uint32_t)(0x01<<3)
#define GPIO_4_ODR_HIGH               (uint32_t)(0x01<<4)
#define GPIO_5_ODR_HIGH               (uint32_t)(0x01<<5)
#define GPIO_6_ODR_HIGH                0x40
#define GPIO_7_ODR_HIGH               (uint32_t)(0x01<<7)
#define GPIO_8_ODR_HIGH               (uint32_t)(0x01<<8)
#define GPIO_9_ODR_HIGH               (uint32_t)(0x01<<9)
#define GPIO_10_ODR_HIGH              (uint32_t)(0x01<<10)
#define GPIO_11_ODR_HIGH              (uint32_t)(0x01<<11)
#define GPIO_12_ODR_HIGH              (((uint32_t)0x01)<<12)
#define GPIO_13_ODR_HIGH              (((uint32_t)0x01)<<13)
#define GPIO_15_ODR_HIGH              (((uint32_t)0x01)<<15)

/* function definitions----------------------------------------------------------*/

void initGpioC6C7AsInput( void )
{
      volatile uint32_t  * reg_pointer; 
      // GPIOC Peripheral clock enable
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE);

    // GPIOC Pin 6&7 as input
    reg_pointer = (uint32_t *)PORTC_MODER_REGISTER;
    //clear bit 
    *reg_pointer = *reg_pointer & (~(GPIO_6_MODER | GPIO_7_MODER));
    //set as input
    *reg_pointer = *reg_pointer | GPIO_6_MODER_IN | GPIO_7_MODER_IN;

    //PUSH-PULL Pin
    reg_pointer = (uint32_t *)PORTC_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_OTYPER | (uint32_t)GPIO_7_OTYPER));
    *reg_pointer = *reg_pointer | GPIO_6_OTYPER_PP | GPIO_7_OTYPER_PP;
    
    //Configure floating
    reg_pointer = (uint32_t *)PORTC_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_6_PUPDR | (uint32_t)GPIO_7_PUPDR));
}

void initGpioB12B13B15AsOutput( void )
{
    volatile uint32_t * reg_pointer;
    /* GPIOB Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

    /* GPIOB12,13,15 configured as output */
    reg_pointer = (volatile uint32_t *)PORTB_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~(GPIO_12_MODER | GPIO_13_MODER | GPIO_15_MODER));
    *reg_pointer = *reg_pointer | GPIO_12_MODER_OUT | GPIO_13_MODER_OUT | GPIO_15_MODER_OUT;

    /*GPIOB12,13,15 configured as push-pull */
    reg_pointer = (volatile uint32_t *)PORTB_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~(GPIO_12_OTYPER | GPIO_13_OTYPER | GPIO_15_OTYPER));

    /*GPIOB12,13,15 configured floating */
    reg_pointer = (volatile uint32_t *)PORTB_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~(GPIO_12_PUPDR | GPIO_13_PUPDR | GPIO_15_PUPDR));

    /* start with all three low (emitters off) */
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer & (~(GPIO_12_ODR_HIGH | GPIO_13_ODR_HIGH | GPIO_15_ODR_HIGH));
}

/**
  * @brief  Initializes GPIO D8 and D9 as alternative function to be used by USART3 to communicate to the computer
  * @note   Do NOT EDIT!
  * @param  None
  * @retval None
  */
void initGpioD8D9AsAF7( void )
{
      volatile uint32_t  * reg_pointer;
      
      /* GPIOD Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
    
    /* GPIO D 8 and 9 as alternative function */ 
    reg_pointer = (volatile uint32_t *)PORTD_MODER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_8_MODER + (uint32_t)GPIO_9_MODER));
    *reg_pointer = *reg_pointer | GPIO_8_MODER_AF | GPIO_9_MODER_AF;
    //to test that the clock is working:
    //*reg_pointer = *reg_pointer | (uint32_t)GPIO_8_MODER_OUT | (uint32_t)GPIO_9_MODER_OUT;
    
    /* GPIOD pin 8 and 9 push pull -> no, open drain-> No another thing says yes to push pull!*/
    reg_pointer = (volatile uint32_t *)PORTD_OTYPER_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_8_OTYPER + (uint32_t)GPIO_9_OTYPER));
    *reg_pointer = *reg_pointer | GPIO_8_OTYPER_PP | GPIO_9_OTYPER_PP;
    
    /* GPIOD pin 8 and 9 as high speed */
    reg_pointer = (volatile uint32_t *)PORTD_OSPEEDR_REGISTER;
    *reg_pointer = *reg_pointer | (uint32_t)GPIO_8_OSPEEDR_HIGH_SPEED | (uint32_t)GPIO_9_OSPEEDR_HIGH_SPEED;
    
    /* GPIOD pin 8 and 9 pulled up */
    reg_pointer = (volatile uint32_t *)PORTD_PUPDR_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_8_PUPDR + (uint32_t)GPIO_9_PUPDR));
    *reg_pointer = *reg_pointer | (uint32_t)GPIO_8_PUPDR_PU | (uint32_t)GPIO_9_PUPDR_PU;
    
     /*GPIO D 8 and 9 as alternative function 7*/   
     reg_pointer = (volatile uint32_t *)PORTD_AFR2_REGISTER;
    *reg_pointer = *reg_pointer & (~((uint32_t)GPIO_8_AFR2_SET_ALL	+ (uint32_t)GPIO_9_AFR2_SET_ALL));
    *reg_pointer = *reg_pointer | (uint32_t)GPIO_8_AFR2_AF7 | (uint32_t)GPIO_9_AFR2_AF7;    
	
	//Drive them high to test: (this was just to test that the clock was turning on, it is)
	 /* GPIOD 8 and 9 driven high to start out with */
    //reg_pointer = (volatile uint32_t *)PORTD_ODR_REGISTER;
    //*reg_pointer = *reg_pointer | GPIO_8_ODR_HIGH | GPIO_9_ODR_HIGH;

}

/* hardware actions */
uint32_t checkGPIOC6(void)
{
    uint32_t value;
    volatile uint32_t  * reg_pointer;
    //get the current value of the pin 
  reg_pointer = (volatile uint32_t *)PORTC_IDR_REGISTER;
  value = *reg_pointer & GPIO_6_IDR;

  return value;
}

uint32_t checkGPIOC7(void)
{
    uint32_t value;
    volatile uint32_t  * reg_pointer;
    //get the current value of the pin 
  reg_pointer = (volatile uint32_t *)PORTC_IDR_REGISTER;
  value = *reg_pointer & GPIO_7_IDR;

  return value;
}

void setGPIOB12( void )
{
    //Set B12 High
    volatile uint32_t * reg_pointer;
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_12_ODR_HIGH;
}

void clearGPIOB12( void )
{
    //Set B12 Low
    volatile uint32_t * reg_pointer;
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer & (~GPIO_12_ODR_HIGH);
}

void setGPIOB13( void )
{
    //set B13 High
    volatile uint32_t * reg_pointer;
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_13_ODR_HIGH;
}

void clearGPIOB13( void )
{
    //Set B13 Low
    volatile uint32_t * reg_pointer;
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer & (~GPIO_13_ODR_HIGH);
}

void setGPIOB15( void )
{
    //set B15 High
    volatile uint32_t * reg_pointer;
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer | GPIO_15_ODR_HIGH;
}

void clearGPIOB15( void )
{
    //Set B15 Low
    volatile uint32_t * reg_pointer;
    reg_pointer = (volatile uint32_t *)PORTB_ODR_REGISTER;
    *reg_pointer = *reg_pointer & (~GPIO_15_ODR_HIGH);
}

//EOF
