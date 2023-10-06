/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_RIT.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    RIT.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include "lpc17xx.h"
#include "RIT.h"
#include "../render/textures.h"
#include "../logic/logic.h"
//#include "../led/led.h"
#include "../timer/timer.h"

/******************************************************************************
** Function name:		RIT_IRQHandler
**
** Descriptions:		REPETITIVE INTERRUPT TIMER handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

volatile int down=0;
extern char led_value;
uint8_t animation;
uint8_t canReplay;

void RIT_IRQHandler (void)
{					
	static int8_t last_key_pressed = 0;			// 0-> select, 1-> left, 2-> right
	
	if((LPC_GPIO1->FIOPIN & (1<<25)) == 0){ // SELECT
		if(canReplay == 1){
			logicInit();
			textureInit();
			enable_timer(0);
			enable_timer(1);
		}else{
			if(last_key_pressed == 1){						//Snack
				disable_RIT();
				increaseStat(0);
				hoverSnack(0);
				animation = 1;
				enable_RIT();
				
			}
				
			if(last_key_pressed == 2){						//Meal
				disable_RIT();
				increaseStat(1);
				hoverMeal(0);
				animation = 2;
				enable_RIT();
			}
		}
		reset_RIT();
  }
	
	// <----------------------------------------------------->
	
	if((LPC_GPIO1->FIOPIN & (1<<27)) == 0){ // LEFT (SNACK)
		hoverSnack(1);
		hoverMeal(0);
		last_key_pressed = 1;
		reset_RIT();
  }
	
	// <----------------------------------------------------->
	
	if((LPC_GPIO1->FIOPIN & (1<<28)) == 0){ // RIGHT (MEAL)
		hoverMeal(1);
		hoverSnack(0);
		last_key_pressed = 2;
		reset_RIT();
  }
	
	// <----------------------------------------------------->
	
	disable_RIT();
	reset_RIT();
	enable_RIT();
	
  LPC_RIT->RICTRL |= 0x1;	/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
