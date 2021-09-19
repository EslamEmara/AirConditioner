/*
 * pwm.h
 *
 *  Author: Mahmoud Ayoub
 */ 


#ifndef PWM_H_
#define PWM_H_

#include "..\..\MCAL\DIO\Std_Types.h"

#define T0_Control_REG			(*((volatile uint8_t*)0x53))
#define T0_Data_REG			(*((volatile uint8_t*)0x52))
#define T0_OutCmp_REG			(*((volatile uint8_t*)0x5C))
#define T2_Control_REG			(*((volatile uint8_t*)0x45))
#define T2_Data_REG			(*((volatile uint8_t*)0x44))
#define T2_OutCmp_REG			(*((volatile uint8_t*)0x43))
#define T_INTMask_REG			(*((volatile uint8_t*)0x59))
#define T_Status_REG			(*((volatile uint8_t*)0x58))
#define portb_DIR				(*((volatile uint8_t*)0x37))
#define portd_DIR				(*((volatile uint8_t*)0x31))


#define NON_INVERTING_MODE 0
#define INVERTING_MODE 1

#define PWM1 0
#define PWM2 1

void pwm_init (uint8_t ID , uint8_t mode , uint16_t prescalar) ; 
void pwm_SetSpeed (uint8_t ID ,uint8_t percentage) ; 



#endif /* PWM_H_ */