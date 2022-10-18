/*
 * Timer_interface.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Kimo Store
 */

#ifndef MCAL_TIMER_DRIVER_TIMER_INTERFACE_H_
#define MCAL_TIMER_DRIVER_TIMER_INTERFACE_H_

#include "../../SERVACE_LAYER/DATA_TYPES.h"

typedef enum
{
	Timer0,
	Timer1,
	Timer2
}TimerType;

typedef enum
{
	Timer_OK,
	Timer_ERROR
}Timer_State;

typedef enum
{
	OVERFLOW_MODE,
	PWM_PHASE_CORRECR,
	OUT_COMPARE_MODE,
	FAST_PWM

}TimerMode;


#define toggleOC0 0
#define clearOC0  1
#define setOC0    2
#define OC0_Disconnected 3

#define toggleOC2 0
#define clearOC2  1
#define setOC2    2
#define OC2_Disconnected 3

#define _1ms_Period		(1000UL)
#define _10ms_Period	(10000UL)
#define _100ms_Period	(100000UL)


Timer_State Timer_voidInit(TimerType Copy_EnumTimerType ,TimerMode Copy_EnumTimerMode );

Timer_State Timer_voidStart(TimerType Copy_EnumTimerType , u8 Copy_IntialValue);

Timer_State Timer_voidStop(TimerType Copy_EnumTimerType);

void Timer_voidSetCallBack(void (*copy_ISR)(void) ,TimerType Copy_enumTimerType ,  TimerMode Copy_enumTimerMode);


#endif /* MCAL_TIMER_DRIVER_TIMER_INTERFACE_H_ */
