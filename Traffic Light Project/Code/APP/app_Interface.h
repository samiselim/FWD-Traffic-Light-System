/*
 * app.h
 *
 *  Created on: ??þ/??þ/????
 *      Author: Kimo Store
 */

#ifndef APP_H_
#define APP_H_

#include "../HAL/LED_Driver/LED_interface.h"
#include "../HAL/Button_Driver/Btn_interface.h"
#include "../MCAL/Ex_Interrupt_Driver/EXTI_Interface.h"
#include "../MCAL/Timer_Driver/Timer_interface.h"


void App_init();
void App_Start();


#endif /* APP_H_ */
