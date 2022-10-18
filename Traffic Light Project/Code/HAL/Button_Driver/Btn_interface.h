/****************************************************** */
/* Author 		: Sami Selim							*/
/* Version 		: V 00									*/
/* Date 		: 26 DEC 2020							*/
/****************************************************** */

#ifndef BTN_INTERFACE_H_
#define BTN_INTERFACE_H_


#include "../../SERVACE_LAYER/DATA_TYPES.h"
#include "../../MCAL/GPIO_Driver/GPIO_Interface.h"

#define Btn_PULLUP_ON  0
#define Btn_PULLUP_OFF 1

typedef enum
{
	Btn_OK,
	Btn_ERROR
}Btn_State;

Btn_State Btn_voidInit(u8 Copy_u8Reg , u8 Copy_u8Pin  , u8 Copyu8PULLUP);
u8 Btn_voidRead(u8 Copy_u8Reg ,  u8 Copy_u8Pin );

#endif /* BTN_INTERFACE_H_ */
