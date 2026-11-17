#ifndef __TIMERQUEUE_H_
#define __TIMERQUEUE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>

/* Macros --------------------------------------------------------------------*/
#define MAX_TIMER_LIST_SIZE 10
#define ACTION_TIMER 1
#define ERROR_TIMER 2

/* Timer object --------------------------------------------------------------*/
typedef struct boptimer_o
{
    uint16_t timername;
    uint32_t timeouttime;     // duration in ms
    uint32_t timestarttime;   // getTime_ms() when started
} boptimer_o;

/* Timer list object ---------------------------------------------------------*/
typedef struct boptimerlist_o
{
    boptimer_o list[MAX_TIMER_LIST_SIZE];
    uint8_t     sizeoflist;
} boptimerlist_o;

/* Function declarations -----------------------------------------------------*/
void initBopTimerList( void );
void insertBopTimerToList( uint16_t timername, uint32_t timeouttime, uint32_t timestarttime );
void deleteBopTimerFromList( uint16_t index );

#endif /*__TIMERQUEUE_H_ */

