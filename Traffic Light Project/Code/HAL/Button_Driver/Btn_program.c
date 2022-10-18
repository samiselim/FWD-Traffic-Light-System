/****************************************************** */
/* Author 		: Sami Selim							*/
/* Version 		: V 00									*/
/* Date 		: 26 DEC 2020							*/
/****************************************************** */


#include "Btn_interface.h"

/*Skeleton
 * 1) This Function will take Btn DDRx and pin and if you want pull up or not
 * 2) it will make this pin as output
 * 3) it will enable pull up resistor if the user need it
 * 4) it will return OK or NOT OK.
 * */
Btn_State Btn_voidInit(u8 Copy_u8Reg , u8 Copy_u8Pin , u8 Copyu8PULLUP)
{

	if(GPIO_void_Set_Direction(Copy_u8Reg , Copy_u8Pin , INPUT) == GPIO_OK)
	{
		if(Copyu8PULLUP == Btn_PULLUP_ON)
		{
			if(GPIO_void_Set_PULL_UP(Copy_u8Reg , Copy_u8Pin) == GPIO_OK)
			{
				return Btn_OK;
			}
			else
			{
				return Btn_ERROR;
			}
		}
		return Btn_OK;
	}
	else
	{
		return Btn_ERROR;
	}
}


/*Skeleton
 * 1) this function will take wanted port and pin and will return if the button pressed or not
 * 2) it will return state of the button
 * */
u8 Btn_voidRead(u8 Copy_u8Reg ,  u8 Copy_u8Pin )
{
	u8 state;
	GPIO_void_ReadPIN(Copy_u8Reg ,Copy_u8Pin , &state );

	return state;
}
