/**
  ******************************************************************************
  * @file    statemachine.c
  * @author  J
  * @version
  * @date
  * @brief   Whack-a-Bop-It State Machine
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "statemachine.h"
#include "events.h"
#include "eventchecker.h"               
#include "stm32f446xx_gpio_mort.h"                 
#include "stm32f446xx_timer_mort.h"     
#include "stm32f446xx_usart3_mort.h"
#include "timerqueue.h"    

/* Module variables----------------------------------------------------------*/
static bopstate_t bopstate = WELCOMING;

/* function definitions-------------------------------------------------------*/

// WABI State Machine
void WABIStateMachine( bopeventtype_t newevent, uint16_t param1, uint32_t param2 )
{
    switch (bopstate)
    {
        
        //WELCOMING
        case WELCOMING:
            printfUSART3("State:Welcoming");
            //if BUTTON_PRESS event
            if (newevent == BUTTON_PRESS)
            {
                clearGPIOB15();
                setGPIOB13();
                insertBopEventToQueue(STARTTIMEOUT, ACTION_TIMER, (uint32_t)5000);
                bopstate = ACTION_STATE;
                //Will become COUNTDOWN
            }
            else if ((newevent == TIMEOUT) && (param1 == ACTION_TIMER))
            {
                break;
            }
            //else 
            else
            {
                clearGPIOB15();
                clearGPIOB13();
                setGPIOB12();
                insertBopEventToQueue(STARTTIMEOUT, ERROR_TIMER, (uint32_t)5000);
                bopstate = ERROR_STATE;
            }
        break;

        //ACTION_STATE
        case ACTION_STATE:
            //if BUTTON PRESS
            printfUSART3("State:Action");
            if (newevent == BUTTON_PRESS)
            {
                clearGPIOB13();
                setGPIOB15();
                bopstate = WELCOMING;
            }
            //else if TIMEOUT
            else if ((newevent == TIMEOUT) && (param1 == ACTION_TIMER))
            {
                clearGPIOB13();
                setGPIOB15();                
                bopstate = WELCOMING;
            }
            else
            {
                clearGPIOB15();
                clearGPIOB13();
                setGPIOB12();
                insertBopEventToQueue(STARTTIMEOUT, ERROR_TIMER, (uint32_t)5000);
                bopstate = ERROR_STATE;
            }
        break;

        //ERROR_STATE
        case ERROR_STATE:
            printfUSART3("State:Error");
            if ((newevent == TIMEOUT) && (param1 == ERROR_TIMER))
            {
                setGPIOB13();
                bopstate = WELCOMING;
            }

        break;
    }
}

//Checks if there is a new event; if so, removes it from the queue 
// and calls the functions and/or state machines that need it


//EOF