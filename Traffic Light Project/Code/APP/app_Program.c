/*
 * app.c
 *
 *  Created on: ??þ/??þ/????
 *      Author: Kimo Store
 */

#include "app_Interface.h"

volatile u16 vT0 = 0 , vT2 =0 , ExIEvent = 0;

void Normal_Function()
{
	vT0 ++;
	if(vT0 < 152)
	{
		LED_voidOn(GPIOA , PIN0);
		LED_voidOff(GPIOA , PIN1);
		LED_voidOff(GPIOA , PIN2);
		LED_voidOff(GPIOB , PIN0);
		LED_voidOff(GPIOB , PIN1);
		LED_voidOn(GPIOB , PIN2);

	}
	else if(vT0 > 152  && vT0 < 304)
	{

		if(vT0 % 15)
		{
			LED_voidToggle(GPIOA , PIN1);
			LED_voidToggle(GPIOB , PIN1);
		}
	}else if(vT0 >304 && vT0 < 456)
	{
		LED_voidOff(GPIOA , PIN0);
		LED_voidOff(GPIOA , PIN1);
		LED_voidOff(GPIOB , PIN1);
		LED_voidOff(GPIOB , PIN2);

		LED_voidOn(GPIOA , PIN2);
		LED_voidOn(GPIOB , PIN0);

	}
	else if(vT0 > 456 && vT0 < 608)
	{
		if(vT0 % 15)
		{
			LED_voidToggle(GPIOA , PIN1);
			LED_voidToggle(GPIOB , PIN1);
		}
	}
	else if(vT0 > 608)
	{
		vT0 = 0;
	}
}

void Ped_Function1()
{
	vT0 ++;
	if(vT0 >0 && vT0 <152)
	{
		LED_voidOn(GPIOA , PIN2);
		LED_voidOn(GPIOB , PIN0);
	}
	else if(vT0 > 152 && vT0 <304)
	{
		LED_voidOff(GPIOA , PIN2);
		if(vT0 % 15)
		{
			LED_voidToggle(GPIOA , PIN1);
			LED_voidToggle(GPIOB , PIN1);
		}
	}
	else if(vT0 > 304 && vT0 < 456)
	{
		LED_voidOff(GPIOB , PIN0);
		LED_voidOff(GPIOA , PIN1);
		LED_voidOff(GPIOB , PIN1);

		LED_voidOff(GPIOA , PIN2);

		LED_voidOn(GPIOA , PIN0);
		LED_voidOn(GPIOB , PIN2);
	}
	else if(vT0 > 456 && vT0 <608)
	{
		LED_voidOff(GPIOB , PIN2);

		Timer_voidSetCallBack(Normal_Function, Timer0 , OVERFLOW_MODE );
		vT0 = -1 ;
	}
}
void Ped_Function2()
{
	vT0 ++;
	if(vT0 > 0 && vT0 < 152)
	{
		LED_voidOn(GPIOB , PIN2);
		LED_voidOff(GPIOA , PIN0);
		if(vT0 % 15)
		{
			LED_voidToggle(GPIOA , PIN1);
			LED_voidToggle(GPIOB , PIN1);
		}
	}
	else if(vT0 > 152  && vT0 <304)
	{
		LED_voidOff(GPIOB , PIN2);
		LED_voidOff(GPIOA , PIN1);
		LED_voidOff(GPIOB , PIN1);
		LED_voidOn(GPIOA , PIN2);
		LED_voidOn(GPIOB , PIN0);
	}
	else if(vT0 > 304 && vT0 < 456)
	{
		LED_voidOff(GPIOA , PIN2);
		if(vT0 % 15)
		{
			LED_voidToggle(GPIOA , PIN1);
			LED_voidToggle(GPIOB , PIN1);
		}
	}
	else if(vT0 > 456 && vT0 <608)
	{
		LED_voidOff(GPIOA , PIN1);
		LED_voidOff(GPIOB , PIN1);
		LED_voidOff(GPIOB , PIN0);
		LED_voidOn(GPIOA , PIN0);
		LED_voidOn(GPIOB , PIN2);


	}
	else if(vT0 > 608)
	{
		LED_voidOff(GPIOA , PIN0);
		LED_voidOff(GPIOB , PIN2);
		vT0 = 0 ;
		Timer_voidSetCallBack(Normal_Function, Timer0 , OVERFLOW_MODE );
	}


}
void Timer2_Function()
{
	vT2 ++;
}

void ExInterruptFunction()
{

	ExIEvent = 1;


}



void App_init()
{

	/************** Initial of LEDs *****************/

	/* Cars LEDs */
	LED_voidInit(GPIOA , PIN0);  // Green
	LED_voidInit(GPIOA , PIN1);  // Red
	LED_voidInit(GPIOA , PIN2);  // Yellow

	/* Pedestrain LEDs*/
	LED_voidInit(GPIOB , PIN0);  // Green
	LED_voidInit(GPIOB , PIN1);  // Red
	LED_voidInit(GPIOB , PIN2);  // Yellow

	/* . . . in start of program . . . */


	/* . . . Init of Switch . . . */
	Btn_voidInit(GPIOD , PIN2 , Btn_PULLUP_OFF);
	/************** Initial of Timers *****************/

	sei();	/*  Global Interrupt Enable */

	Timer_voidInit(Timer0 , OVERFLOW_MODE);
	Timer_voidInit(Timer2 , OVERFLOW_MODE);

	Timer_voidSetCallBack(Normal_Function , Timer0 , OVERFLOW_MODE );
	Timer_voidSetCallBack(Timer2_Function , Timer2 , OVERFLOW_MODE );




	/************** Initial of External Interrupt 0  *****************/

	EXTI_voidSET_CallBack(ExInterruptFunction , EXTI_0);
	EXTI_voidEnable_EXTI(EXTI_0 , EXTI_FALLING);

}
void App_Start()
{
	Timer_voidStart(Timer0 , 0);

	while(1)
	{
		if(ExIEvent > 0 && (vT0 > 304 && vT0 < 456))
		{

			Timer_voidStop(Timer0);
			Timer_voidSetCallBack(Ped_Function1 , Timer0 , OVERFLOW_MODE );
			Timer_voidStart(Timer0 , 0);
			vT0 = 0;
			ExIEvent = 0;
		}
		if(ExIEvent > 0 && ((vT0 > 0  && vT0 < 304) || (vT0 > 456 && vT0 < 608)))
		{

			Timer_voidStop(Timer0);
			Timer_voidSetCallBack(Ped_Function2, Timer0 , OVERFLOW_MODE );
			Timer_voidStart(Timer0 , 0);
			vT0 = 0;
			ExIEvent = 0;
		}
	}
}
