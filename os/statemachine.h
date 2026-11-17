#ifndef __STATEMACHINE_H_
#define __STATEMACHINE_H_

/* Includes ------------------------------------------------------------------*/
#include <stdint.h>
#include "events.h"

/* States --------------------------------------------------------------------*/
typedef enum
{
    WELCOMING,
    COUNTDOWN,
    RANDOMIZER,
    ACTION_STATE,
    END_GAME_SEQUENCE,
    ERROR_STATE
} bopstate_t;

/* Function declarations -----------------------------------------------------*/
void WABIStateMachine( bopeventtype_t newevent, uint16_t name, uint32_t value );

#endif /*__STATEMACHINE_H_ */