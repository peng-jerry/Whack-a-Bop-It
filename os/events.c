/**
  ******************************************************************************
  * @file    events.c
  * @author
  * @version
  * @date
  * @brief   Event queue for Whack-a-Bop-It
  ******************************************************************************
  */
    
/* Includes----------------------------------------------------------*/
#include "events.h"

/* Module variables----------------------------------------------------------*/
static bopeventqueue_o bopeventqueue;

/* function definitions-------------------------------------------------------*/

//Empties the event queue
void initBopEventQueue( void )
{
    bopeventqueue.sizeofq  = 0;
    bopeventqueue.startofq = 0;
    bopeventqueue.endofq   = 0;
}

// Adds an event to the end of the queue
//If the queue is full, the event is dropped
void insertBopEventToQueue( bopeventtype_t type, uint16_t name, uint32_t value )
{
    if (bopeventqueue.sizeofq < MAX_EVENT_QUEUE_SIZE)
    {
        bopeventqueue.queue[bopeventqueue.endofq].type   = type;
        bopeventqueue.queue[bopeventqueue.endofq].name = name;
        bopeventqueue.queue[bopeventqueue.endofq].value = value;

        bopeventqueue.endofq = bopeventqueue.endofq + 1;
        if (bopeventqueue.endofq == MAX_EVENT_QUEUE_SIZE)
        {
            bopeventqueue.endofq = 0;      // wrap around
        }
        bopeventqueue.sizeofq = bopeventqueue.sizeofq + 1;
    }
}

//Removes the event at the front of the queue
void deleteBopEventFromQueue( void )
{
    if (bopeventqueue.sizeofq > 0)
    {
        bopeventqueue.startofq = bopeventqueue.startofq + 1;
        if (bopeventqueue.startofq == MAX_EVENT_QUEUE_SIZE)
        {
            bopeventqueue.startofq = 0;    // wrap around
        }
        bopeventqueue.sizeofq = bopeventqueue.sizeofq - 1;
    }
}

//get number of events
uint16_t getBopEventQueueSize( void )
{
    return bopeventqueue.sizeofq;
}

//get the event at the front of the queue
bopevent_o getBopEventFromQueue( void )
{
    return bopeventqueue.queue[bopeventqueue.startofq];
}
//EOF