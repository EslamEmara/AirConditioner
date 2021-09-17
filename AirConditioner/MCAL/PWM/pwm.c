/*
 * pwm.c
 *
 *  Author: Mahmoud Ayoub
 */ 
#include "pwm.h"
/*
ID          >> PWM1 , PWM2
pwm mode	>> NON_INVERTING_MODE , INVERTING_MODE
prescalar	>> 0 , 8 , 64 , 256 , 1024
*/

void pwm_init (uint8 ID , uint8 mode , uint16 prescalar) {
	if (ID == PWM1) {
		PORTB_DIR |= (1<<3) ;
		if (mode == NON_INVERTING_MODE) {		// fast pwm - non inverting mode
			switch (prescalar) {
				case 0 :
					T0_Control_REG |= 0x69 ;
					break ;
				case 8 :
					T0_Control_REG |= 0x6A ;
					break ;
				case 64 :
					T0_Control_REG |= 0x6B ;
					break ;
				case 256 :
					T0_Control_REG |= 0x6C ;
					break ;
				case 1024 :
					T0_Control_REG |= 0x6D ;
					break ;
				}
			}
		else if (mode == INVERTING_MODE) {		// fast pwm - inverting mode
			switch (prescalar) {
				case 0 :
					T0_Control_REG |= 0x79 ;
					break ;
				case 8 :
					T0_Control_REG |= 0x7A ;
					break ;
				case 64 :
					T0_Control_REG |= 0x7B ;
					break ;
				case 256 :
					T0_Control_REG |= 0x7C ;
					break ;
				case 1024 :
					T0_Control_REG |= 0x7D ;
					break ;
				}
			}
	}
	else if (ID == PWM2) {
		 PORTD_DIR |= ( 1<< 7 ) ;
		if (mode == NON_INVERTING_MODE) {		// fast pwm - non inverting mode
			switch (prescalar) {
				case 0 :
					T2_Control_REG |= 0x69 ;
					break ;
				case 8 :
					T2_Control_REG |= 0x6A ;
					break ;
				case 64 :
					T2_Control_REG |= 0x6B ;
					break ;
				case 256 :
					T2_Control_REG |= 0x6C ;
					break ;
				case 1024 :
					T2_Control_REG |= 0x6D ;
					break ;
			}
		}
		else if (mode == INVERTING_MODE) {		// fast pwm - inverting mode
			switch (prescalar) {
				case 0 :
					T2_Control_REG |= 0x79 ;
					break ;
				case 8 :
					T2_Control_REG |= 0x7A ;
					break ;
				case 64 :
					T2_Control_REG |= 0x7B ;
					break ;
				case 256 :
					T2_Control_REG |= 0x7C ;
					break ;
				case 1024 :
					T2_Control_REG |= 0x7D ;
					break ;
			}
		}
	}
}
void pwm_SetSpeed (uint8 ID ,uint8 percentage) {
	uint8 duty_cycle = 255 * percentage / 100 ; 
	if (ID == PWM1) {
		T0_OutCmp_REG = duty_cycle ; 
	}
	else if (ID == PWM2) {
		T2_OutCmp_REG = duty_cycle ;
	}
	
}