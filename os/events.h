#ifndef __EVENTS_H_
#define __EVENTS_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>


/* Macros --------------------------------------------------------------------*/
#define MAX_EVENT_QUEUE_SIZE   10

/* Event types ---------------------------------------------------------------*/
typedef enum
{
    STARTTIMEOUT,
    NO_EVENT,
    BUTTON_PRESS,
    WAVE_IT_CUE,
    BOP_IT_CUE,
    SLIDE_IT_CUE,
    WHACK_IT_CUE,
    SPIN_IT_CUE,
    CORRECT_ACTION,
    INCORRECT_ACTION,
    TIMEOUT
} bopeventtype_t;

/* Event object --------------------------------------------------------------*/
typedef struct bopevent_o
{
    bopeventtype_t type;
    uint16_t         name;     
    uint32_t         value;     
} bopevent_o;

/* Event queue object --------------------------------------------------------*/
typedef struct bopeventqueue_o
{
    bopevent_o queue[MAX_EVENT_QUEUE_SIZE];
    uint8_t     sizeofq;
    uint8_t     startofq;
    uint8_t     endofq;
} bopeventqueue_o;

/* Function declarations -----------------------------------------------------*/
void         initBopEventQueue( void );
void         insertBopEventToQueue( bopeventtype_t type, uint16_t name, uint32_t value );
void         deleteBopEventFromQueue( void );
uint16_t     getBopEventQueueSize( void );
bopevent_o   getBopEventFromQueue( void );

#endif /*__EVENTS_H_ */