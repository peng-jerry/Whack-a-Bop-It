/**
  ******************************************************************************
  * @file    timerqueue.c
  * @author
  * @version
  * @date
  * @brief   Event checkers: timer timeouts and the start button
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "eventchecker.h"
#include "events.h"
#include "stm32f446xx_timer_mort.h"     // getTime_ms()
#include "stm32f446xx_gpio_mort.h"      // checkGPIOC7()
#include "timerqueue.h"

/* Module variables----------------------------------------------------------*/
static boptimerlist_o boptimerlist;

//Empties the timer list
void initBopTimerList( void )
{
    boptimerlist.sizeoflist = 0;
}

//Adds a timer to the list
//If a timer with the same number is already running, it is restarted instead of added twice
void insertBopTimerToList( uint16_t timername, uint32_t timeouttime, uint32_t timestarttime )
{
    uint16_t i;

    /* restart an existing timer with the same number */
    for (i = 0; i < boptimerlist.sizeoflist; i++)
    {
        if (boptimerlist.list[i].timername == timername)
        {
            boptimerlist.list[i].timeouttime = timeouttime;
            boptimerlist.list[i].timestarttime = timestarttime;
            return;
        }
    }

    /* otherwise add it to the end */
    if (boptimerlist.sizeoflist < MAX_TIMER_LIST_SIZE)
    {
        boptimerlist.list[boptimerlist.sizeoflist].timername = timername;
        boptimerlist.list[boptimerlist.sizeoflist].timeouttime = timeouttime;
        boptimerlist.list[boptimerlist.sizeoflist].timestarttime = timestarttime;
        boptimerlist.sizeoflist = boptimerlist.sizeoflist + 1;
    }
}

// Removes the timer at position index, shifting the rest down
void deleteBopTimerFromList( uint16_t index )
{
    uint16_t i;

    if (index >= boptimerlist.sizeoflist)
    {
        return;
    }

    for (i = index; i < boptimerlist.sizeoflist - 1; i++)
    {
        boptimerlist.list[i] = boptimerlist.list[i + 1];
    }
    boptimerlist.sizeoflist = boptimerlist.sizeoflist - 1;
}

