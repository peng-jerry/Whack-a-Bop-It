/**
  ******************************************************************************
  * @file    eventchecker.c
  * @author
  * @version
  * @date
  * @brief   Event checkers: timer timeouts and the start button
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "eventchecker.h"
#include "events.h"
#include "timerqueue.h"
#include "stm32f446xx_timer_mort.h"     // getTime_ms()
#include "stm32f446xx_gpio_mort.h"      // checkGPIOC7()
#include "stm32f446xx_usart3_mort.h"


/* Module variables----------------------------------------------------------*/

/* function definitions-------------------------------------------------------*/

//if a timer has expired, removes it from the list and inserts a TIMEOUT event
void timeoutEventCheck( void )
{
    uint16_t i;
    uint32_t currenttime;
    currenttime = getTime_ms();

    for (i = 0; i < boptimerlist.sizeoflist; i++)
    {
        if ((currenttime - boptimerlist.list[i].timestarttime) >= boptimerlist.list[i].timeouttime)
        {
            insertBopEventToQueue(TIMEOUT,
                                    boptimerlist.list[i].timername,
                                    boptimerlist.list[i].timeouttime);
            deleteBopTimerFromList(i);
            return;
        }
    }
}

//inserts PRESSED_START on a falling edge of PC7
void ButtonPressEventCheck( void )
{
    static uint8_t lastButtonState = 1;     // idles high
    uint8_t currentButtonState;

    if (checkGPIOC6() != 0)
    {
        currentButtonState = 1;
    }
    else
    {
        currentButtonState = 0;
    }

    if ((currentButtonState == 0) && (lastButtonState == 1))
    {
        insertBopEventToQueue(BUTTON_PRESS, 0, 0);
    }

    lastButtonState = currentButtonState;
}
//EOF