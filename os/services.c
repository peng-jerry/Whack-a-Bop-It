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
                insertBopTimerToList(currentevent.type, currentevent.name, getTime_ms());
            break;
            case TIMEOUT:
                WABIStateMachine(TIMEOUT, currentevent.name, currentevent.value);
            break;
            case BUTTON_PRESS:
                WABIStateMachine(BUTTON_PRESS, currentevent.name, currentevent.value);
            break;
        }
    }
}