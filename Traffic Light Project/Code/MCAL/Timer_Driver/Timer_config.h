/*
 * Timer_config.h
 *
 *  Created on: Oct 9, 2022
 *      Author: Kimo Store
 */

#ifndef MCAL_TIMER_DRIVER_TIMER_CONFIG_H_
#define MCAL_TIMER_DRIVER_TIMER_CONFIG_H_

#include "Timer_interface.h"

/* PreScaller Options
 * 1)    (Timer stopped )
 * 2)    1 no Prescaller  (Fcpu)
 * 3)    8     Prescaler  (Fcpu / 8)
 * 4)    64    Prescaller (Fcpu / 64)
 * 5)    256   Preescaller  (Fcpu / 256)
 * 6)    1024  Prescaller  (Fcpu / 1024)
 * 6)   */

#define Timer0_Prescaler  1024

#define Timer1_Prescaler   2

#define Timer2_Prescaler   1024


#define TimerPeriod (_1ms_Period) /* For Timer 1 */

/* For Out Compare without PWM  .. OC0 Toggle , Clear , Set */

/* Options
 * 1) toggleOC0
 * 2) clearOC0
 * 3) setOC0
 * 4) OC0_Disconnected

 */
#define OCO_Response toggleOC0

/* Options
 * 1) toggleOC2
 * 2) clearOC2
 * 3) setOC2
 * 4) OC2_Disconnected

 */
#define OC2_Response toggleOC2


#endif /* MCAL_TIMER_DRIVER_TIMER_CONFIG_H_ */
