/*
 * Timer_program.c
 *
 *  Created on: Oct 9, 2022
 *      Author: Kimo Store
 */

#include "Timer_private.h"
#include "Timer_interface.h"
#include "Timer_config.h"


static void (*Timer0_CallBack[2])(void) = {NULL};
static void (*Timer2_CallBack[2])(void) = {NULL};
static void (*Timer1_CallBack[2])(void) = {NULL};

ISR(TIMER0_OVERFLOW_VECTOR)
{
	Timer0_CallBack[0]();
}

ISR(TIMER0_OUTCOMP_VECTOR)
{
	Timer0_CallBack[1]();
}


ISR(TIMER2_OVERFLOW_VECTOR)
{
	Timer2_CallBack[0]();
}

ISR(TIMER2_OUTCOMP_VECTOR)
{
	Timer2_CallBack[1]();
}

ISR(TIMER1_OVERFLOW_VECTOR)
{
	Timer1_CallBack[0]();
}


Timer_State Timer_voidInit(TimerType Copy_EnumTimerType ,TimerMode Copy_EnumTimerMode )
{
	sei();
	u8 state = Timer_ERROR;
	switch(Copy_EnumTimerMode)
	{
	case OVERFLOW_MODE:
		switch(Copy_EnumTimerType)
		{
		case Timer0:

			CLEAR_BIT(TCCR0 ,WGM00 );
			CLEAR_BIT(TCCR0 ,WGM01 );
			SET_BIT(TIMSK , TOIE0);
			state = Timer_OK;

			break;


		case Timer1:
			TCCR1A = (1<<FOC1A)|(1<<FOC1B);
			TCCR1B = 0;
			OCR1A = 0;
			OCR1B = 0;
			ICR1 = 0;
			TIMSK |=(1<<TOIE1);

			/* Initial value of Timer Register _1ms */

			state = Timer_OK;
			break;

		case Timer2:
			CLEAR_BIT(TCCR2 ,WGM20 );
			CLEAR_BIT(TCCR2 ,WGM21 );
			SET_BIT(TIMSK , TOIE2);
			state = Timer_OK;
			break;
		default:
			state = Timer_ERROR;
			break;
		}
		break;


		case OUT_COMPARE_MODE:
			switch(Copy_EnumTimerType)
			{
			case Timer0:
				CLEAR_BIT(TCCR0 ,WGM00 );
				SET_BIT(TCCR0 ,WGM01 );
				SET_BIT(TIMSK , OCIE0);

#if OCO_Response == OC0_Disconnected
				CLEAR_BIT(TCCR0 ,COM00 );
				CLEAR_BIT(TCCR0 ,COM01 );
#elif OCO_Response == toggleOC0
				SET_BIT(TCCR0 ,COM00 );
				CLEAR_BIT(TCCR0 ,COM01 );
#elif OCO_Response == clearOC0
				CLEAR_BIT(TCCR0 ,COM00 );
				SET_BIT(TCCR0 ,COM01 );
#elif OCO_Response == setOC0
				SET_BIT(TCCR0 ,COM00 );
				SET_BIT(TCCR0 ,COM01 );
#endif
				state = Timer_OK;
				break;

			case Timer1:


				break;

			case Timer2:
				CLEAR_BIT(TCCR2 ,WGM20 );
				SET_BIT(TCCR2 ,WGM21 );
				SET_BIT(TIMSK , OCIE2);

#if OC2_Response == OC2_Disconnected
				CLEAR_BIT(TCCR2 ,COM20 );
				CLEAR_BIT(TCCR2 ,COM21 );
#elif OC2_Response == toggleOC2
				SET_BIT(TCCR2 ,COM20 );
				CLEAR_BIT(TCCR2 ,COM21 );
#elif OC2_Response == clearOC2
				CLEAR_BIT(TCCR2 ,COM20 );
				SET_BIT(TCCR2 ,COM21 );
#elif OC2_Response == setOC2
				SET_BIT(TCCR2 ,COM20 );
				SET_BIT(TCCR2 ,COM21 );
#endif

				state = Timer_OK;
				break;
			default:
				state = Timer_ERROR;
				break;
			}


			break;

			case PWM_PHASE_CORRECR:

				switch(Copy_EnumTimerType)
				{
				case Timer0:
					SET_BIT(TCCR0 ,WGM00 );
					CLEAR_BIT(TCCR0 ,WGM01 );
					break;


				case Timer1:


					break;


				case Timer2:

					SET_BIT(TCCR2 ,WGM20 );
					CLEAR_BIT(TCCR2 ,WGM21 );

					break;
				default:
					state = Timer_ERROR;
					break;
				}

				break;

				case FAST_PWM:

					switch(Copy_EnumTimerType)
					{
					case Timer0:
						SET_BIT(TCCR0 ,WGM00 );
						SET_BIT(TCCR0 ,WGM01 );
						break;


					case Timer1:


						break;


					case Timer2:
						SET_BIT(TCCR2 ,WGM20 );
						SET_BIT(TCCR2 ,WGM21 );


						break;
					default:
						state = Timer_ERROR;
						break;
					}

					break;
					default:
						state = Timer_ERROR;
						break;
	}

	return state;
}

Timer_State Timer_voidStart(TimerType Copy_EnumTimerType , u8 Copy_IntialValue)
{
	u8 state = Timer_ERROR;
	switch(Copy_EnumTimerType)
	{
	case Timer0:

		TCNT0 = Copy_IntialValue;
#if Timer0_Prescaler == 1
		SET_BIT(TCCR0 ,CS00 );
		CLEAR_BIT(TCCR0 ,CS01);
		CLEAR_BIT(TCCR0 ,CS02);
#elif Timer0_Prescaler == 8
		CLEAR_BIT(TCCR0 ,CS00 );
		SET_BIT(TCCR0 ,CS01);
		CLEAR_BIT(TCCR0 ,CS02);
#elif Timer0_Prescaler == 64
		SET_BIT(TCCR0 ,CS00 );
		SET_BIT(TCCR0 ,CS01);
		CLEAR_BIT(TCCR0 ,CS02);
#elif Timer0_Prescaler == 256
		CLEAR_BIT(TCCR0 ,CS00 );
		CLEAR_BIT(TCCR0 ,CS01);
		SET_BIT(TCCR0 ,CS02);
#elif Timer0_Prescaler == 1024
		SET_BIT(TCCR0 ,CS00 );
		CLEAR_BIT(TCCR0 ,CS01);
		SET_BIT(TCCR0 ,CS02);
#endif

		state = Timer_OK;

		break;
	case Timer1:
		TCNT1 = (65536ul - (TimerPeriod /8ul) );
		/* 8MHZ/64(prescaller) -> 1_Tic - 8us  */
		TCCR1B = (1<<CS11)|(1<<CS10);
		state = Timer_OK;

		break;

	case Timer2:
		TCNT2 = Copy_IntialValue;
#if Timer2_Prescaler == 1
		SET_BIT(TCCR2 ,CS20 );
		CLEAR_BIT(TCCR2 ,CS21);
		CLEAR_BIT(TCCR2 ,CS22);
#elif Timer2_Prescaler == 8
		CLEAR_BIT(TCCR2 ,CS20 );
		SET_BIT(TCCR2 ,CS21);
		CLEAR_BIT(TCCR2 ,CS22);
#elif Timer2_Prescaler == 64
		SET_BIT(TCCR2 ,CS20 );
		SET_BIT(TCCR2 ,CS21);
		CLEAR_BIT(TCCR2 ,CS22);
#elif Timer2_Prescaler == 256
		CLEAR_BIT(TCCR2 ,CS20 );
		CLEAR_BIT(TCCR2 ,CS21);
		SET_BIT(TCCR2 ,CS22);
#elif Timer2_Prescaler == 1024
		SET_BIT(TCCR2 ,CS20 );
		CLEAR_BIT(TCCR2 ,CS21);
		SET_BIT(TCCR2 ,CS22);
#endif
		state = Timer_OK;
		break;
	default:
		state = Timer_ERROR;
		break;
	}
	return state;

}

Timer_State Timer_voidStop(TimerType Copy_EnumTimerType)
{
	u8 state = Timer_ERROR;
	switch(Copy_EnumTimerType)
	{
	case Timer0:
		TCNT0 = 0;
		CLEAR_BIT(TCCR0 ,CS00 );
		CLEAR_BIT(TCCR0 ,CS01);
		CLEAR_BIT(TCCR0 ,CS02);

		state = Timer_OK;

		break;
	case Timer1:

		TCCR1B = 0;

		break;

	case Timer2:
		TCNT2 = 0;
		CLEAR_BIT(TCCR2 ,CS20 );
		CLEAR_BIT(TCCR2 ,CS21);
		CLEAR_BIT(TCCR2 ,CS22);

		state = Timer_OK;
		break;
	default:
		state = Timer_ERROR;
		break;
	}
	return state;
}

void Timer_voidSetCallBack(void (*copy_ISR)(void) ,TimerType Copy_enumTimerType ,  TimerMode Copy_enumTimerMode)
{
	switch(Copy_enumTimerType)
	{
	case Timer0:

		switch(Copy_enumTimerMode)
		{
		case OVERFLOW_MODE:
			Timer0_CallBack[0] = copy_ISR;
			break;
		case OUT_COMPARE_MODE:
			Timer0_CallBack[1] = copy_ISR;
			break;

		case PWM_PHASE_CORRECR:


			break;


		case FAST_PWM:


			break;
		}
		break;
		case Timer1:
			switch(Copy_enumTimerMode)
			{
			case OVERFLOW_MODE:
				Timer1_CallBack[0] = copy_ISR;
				break;
			case OUT_COMPARE_MODE:
				Timer1_CallBack[1] = copy_ISR;
				break;

			case PWM_PHASE_CORRECR:


				break;


			case FAST_PWM:


				break;
			}

			break;



			case Timer2:
				switch(Copy_enumTimerMode)
				{
				case OVERFLOW_MODE:
					Timer2_CallBack[0] = copy_ISR;
					break;
				case OUT_COMPARE_MODE:
					Timer2_CallBack[1] = copy_ISR;
					break;

				case PWM_PHASE_CORRECR:


					break;


				case FAST_PWM:


					break;
				}

				break;
	}
}
