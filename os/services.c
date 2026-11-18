/**
  ******************************************************************************
  * @file    services.c
  * @author  J
  * @version
  * @date
  * @brief   Whack-a-Bop-It Servicer
  ******************************************************************************
  */

/* Includes----------------------------------------------------------*/
#include "statemachine.h"
#include "events.h"
#include "eventchecker.h"                              
#include "stm32f446xx_timer_mort.h"     
#include "stm32f446xx_usart3_mort.h"  
#include "timerqueue.h"
#include "services.h"

void serviceBopEventQueue( void )
{
    bopevent_o currentevent;
    //if no Event, return no Event
    if (getBopEventQueueSize() == 0)
    {
        currentevent.type = NO_EVENT;
    }
    else
    {
        //get current event
        currentevent = getBopEventFromQueue();
        deleteBopEventFromQueue();
        //Given input state perform correct event in State Machine
        switch (currentevent.type)
        {
            case NO_EVENT:
            break;
            case STARTTIMEOUT:
                printfUSART3("starttimer \n");
                insertBopTimerToList(currentevent.name, currentevent.value, getTime_ms());
            break;
            case TIMEOUT:
                printfUSART3("timeout \n");
                WABIStateMachine(TIMEOUT, currentevent.name, currentevent.value);
            break;
            case BUTTON_PRESS:
                printfUSART3("Button Pressed \n");
                WABIStateMachine(BUTTON_PRESS, currentevent.name, currentevent.value);
            break;
        }
    }
}