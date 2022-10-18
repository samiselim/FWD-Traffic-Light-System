/****************************************************** */
/* Author 		: Sami Selim							*/
/* Version 		: V 00									*/
/* Date 		: 21 DEC 2020							*/
/****************************************************** */




#ifndef _MACRO_FUNCTIONS_H
#define _MACRO_FUNCTIONS_H


#define _MMIO_BYTE(mem_addr) *((volatile u8 *)(mem_addr))

#define SET_BIT(REG , PIN)		REG |= (1<<PIN)
#define CLEAR_BIT(REG , PIN)	REG &=~ (1<<PIN)

#define TOGGLE_BIT(REG , PIN) 	REG ^= (1<<PIN)
#define CHECK_BIT(REG , PIN)	(REG>>PIN)& 1


#define sei()  __asm__ __volatile__ ("sei" ::) // Assembly Instruction to Enable Global Interrupt (Setting  bit 7  in Status Register 'SREG')
#define cli()  __asm__ __volatile__ ("cli" ::) // Assembly Instruction to Disable Global Interrupt (Clearing bit 7  in status Register 'SREG')


#endif



