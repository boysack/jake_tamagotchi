/****************************************Copyright (c)****************************************************
**                                      
**                                 http://www.powermcu.com
**
**--------------File Info---------------------------------------------------------------------------------
** File name:               main.c
** Descriptions:            The GLCD application function
**
**--------------------------------------------------------------------------------------------------------
** Created by:              AVRman
** Created date:            2010-11-7
** Version:                 v1.0
** Descriptions:            The original version
**
**--------------------------------------------------------------------------------------------------------
** Modified by:             Paolo Bernardi
** Modified date:           03/01/2020
** Version:                 v2.0
** Descriptions:            basic program for LCD and Touch Panel teaching
**
*********************************************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "LPC17xx.h"
#include "GLCD/GLCD.h" 
#include "TouchPanel/TouchPanel.h"
#include "timer/timer.h"
#include "joystick/joystick.h"
#include "RIT/RIT.h"

//my headers
#include "render/textures.h"
#include "logic/logic.h"

#define SIMULATOR 1

#ifdef SIMULATOR
extern uint8_t ScaleFlag; // <- ScaleFlag needs to visible in order for the emulator to find the symbol (can be placed also inside system_LPC17xx.h but since it is RO, it needs more work)
#endif


int main(void)
{
  SystemInit();  												/* System Initialization (i.e., PLL)  */
	
  LCD_Initialization();
	LCD_SetBackground(Red);
		
	logicInit();	//even timer enabling
	textureInit();
	
	//age and stats
	init_timer(0, 0x017D7840);						/* time = const * period => const = time * freq = 1s * 25M = 25M */
	//animations
	init_timer(1, 0x005F5E10);							/* time = const * period => const = time * freq = 0.25s * 25M = 0x5F5E10 */
	
	NVIC_SetPriority(RIT_IRQn, 0);
	NVIC_SetPriority(TIMER0_IRQn, 2);
	NVIC_SetPriority(TIMER1_IRQn, 1);
	
	joystick_init();
	init_RIT(0x4C4B40);										// 50ms, 	100MHz
	
	enable_RIT();									
	
	enable_timer(0);
	enable_timer(1);
	
	LPC_SC->PCON |= 0x1;									/* power-down	mode										*/
	LPC_SC->PCON &= ~(0x2);						
	
  while (1)	
  {
		__ASM("wfi");
  }
}

/*********************************************************************************************************
      END FILE
*********************************************************************************************************/
