/*********************************************************************************************************
**--------------File Info---------------------------------------------------------------------------------
** File name:           IRQ_timer.c
** Last modified Date:  2014-09-25
** Last Version:        V1.00
** Descriptions:        functions to manage T0 and T1 interrupts
** Correlated files:    timer.h
**--------------------------------------------------------------------------------------------------------
*********************************************************************************************************/
#include <string.h>
#include <stdio.h>
#include "lpc17xx.h"
#include "timer.h"
#include "../GLCD/GLCD.h" 
#include "../TouchPanel/TouchPanel.h"

//my headers
#include "../render/textures.h"
#include "../logic/logic.h"

//my vars
uint8_t decrCount = 0;
//uint8_t animation;
//uint8_t canReplay;
/******************************************************************************
** Function name:		Timer0_IRQHandler
**
** Descriptions:		Timer/Counter 0 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/

void TIMER0_IRQHandler (void) {
	NVIC_DisableIRQ(TIMER1_IRQn);
	increaseTime();
	drawTime();
	decrCount++;
	if(decrCount == 5) {
		decrCount = 0;
		decreaseStat(0);	//decrease happiness
		decreaseStat(1);	//decrease satiety
		
		if(isDead()){
			disable_timer(0);
			disable_timer(1);
			reset_timer(0);
			reset_timer(1);
			canReplay = 1;
			drawGameOver();
		}
	}
	//idle();
	LPC_TIM0->IR = 1;			// clear interrupt flag
	NVIC_EnableIRQ(TIMER1_IRQn);
	return;
}
/*void TIMER0_IRQHandler (void)
{
	static int clear = 0;
	char time_in_char[5] = "";
	
  if(getDisplayPoint(&display, Read_Ads7846(), &matrix )){
		if(display.y < 280){
			TP_DrawPoint(display.x,display.y);
			GUI_Text(200, 0, (uint8_t *) "     ", Blue, Blue);
			clear = 0;
		}
		else{			
			if(display.y <= 0x13E){			
				clear++;
				if(clear%20 == 0){
					sprintf(time_in_char,"%4d",clear/20);
					GUI_Text(200, 0, (uint8_t *) time_in_char, White, Blue);
					if(clear == 200){	// 1 seconds = 200 times * 500 us
						LCD_Clear(Blue);
						GUI_Text(0, 280, (uint8_t *) " touch here : 1 sec to clear ", Blue, White);			
						clear = 0;
					}
				}
			}
		}
	}
	else{
		//do nothing if touch returns values out of bounds
	}
  LPC_TIM0->IR = 1;			// clear interrupt flag
  return;
}
*/


/******************************************************************************
** Function name:		Timer1_IRQHandler
**
** Descriptions:		Timer/Counter 1 interrupt handler
**
** parameters:			None
** Returned value:		None
**
******************************************************************************/
void TIMER1_IRQHandler (void)
{
	uint8_t frameCounter = 0;
	//idle
	if(animation == 0){
		idle();
	}
	//walk and eat
	else if(animation > 0) {
		while(frameCounter<13){
			walkAndEat(frameCounter);
			frameCounter++;
		}
		animation = 0;
	}
		
  LPC_TIM1->IR = 1;			/* clear interrupt flag */
  return;
}

/******************************************************************************
**                            End Of File
******************************************************************************/
