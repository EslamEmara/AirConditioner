/*
 * delay.c
 *
 * Created: 9/18/2021 4:36:12 PM
 *  Author: Mohamed AbdelAZeem
 */ 


#include "delay.h"
#include "../../MCAL/timer/timer.h"

/* if you want delay more than 250us use delay_ms  */


/* Enter delay in Milliseconds */
void delay_ms(uint16_t delay)
{
	uint16_t counter=  0;
	/* configure timer to count to  100usec  */
	St_Config_Timer_t timer0_config1 = {TIMER1, COMPARE_MODE_toggel , INTERNAL_CLK_PRESCALAR0_1 , DEFAULT_INITIAL_VALUE,100,CHANNEL_A};

	Timer_start(&timer0_config1);
	 while(1)
		{
			if(Timer1A_CTC_flag())
			{
				 counter++;
				if(counter == delay * 10  )
				{
					break;
					counter=0;
				}
		
			}
		
		}
}



void delay_us(uint16_t delay)
{
	
		uint16_t counter=  0;
		/* configure timer to count to  100usec  */
		St_Config_Timer_t timer0_config1 = {TIMER1, COMPARE_MODE_toggel , INTERNAL_CLK_PRESCALAR0_1 , DEFAULT_INITIAL_VALUE,0,CHANNEL_A};

		timer0_config1.compare_value = delay;
		Timer_start(&timer0_config1);
		while(1)
		{
			if(Timer1A_CTC_flag())
			{
				counter++;
				if(counter == delay * 10  )
				{
					break;
					counter=0;
				}
				
			}
			
		}
}