/*
 * Motor.c
 *
 * Created: 9/5/2021 3:40:07 PM
 *  Author: Eslam Emara
 */ 

#include "Motor.h"

/*
 *Function to initialize motor 
 *Inputs ST_MOTORconfig_t config (see Motor.h for definition)
 *ST_MOTORconfig_t Members:: {uint8_t DIR_PORT,uint8_t DIR_PIN,uint8_t PWM_ID}
 *direction pin is the pin connected to the direction pin in the motor driver.
 *PWM pin the pin connected to speed pin in the motor driver.
 *void return.
 *EXAMPLE:
 *  ST_MOTORconfig_t MOTOR_1_config = {PORTA,0,PORTB,3};
	Motor_init(	MOTOR_1_config );
 * Expected OUTPUT: Setting Pins of PWM and Direction as output.
					Initializing PWM.
 */

void Motor_init(ST_MOTORconfig_t config)
{
	if(config.PWM_ID == PWM1)
		pwm_init(PWM1,NON_INVERTING_MODE,PRESCALAR);
		
	if(config.PWM_ID == PWM2)
		pwm_init(PWM2,NON_INVERTING_MODE,PRESCALAR);
			
	if (config.DIR1_PIN <= 7 && config.DIR2_PIN <= 7 ){
		DIO_SetPinDirection(config.DIR1_PORT,config.DIR1_PIN,OUTPUT);
		DIO_SetPinDirection(config.DIR2_PORT,config.DIR2_PIN,OUTPUT);

	}

	
}
/*
 *	Function to move the motor clockwise 
 *	Inputs ST_MOTORconfig_t motor ID config , uint8_t speed percentage from 0 to 100
 *	void return. 
 *	Expected output: Motor rotate clockwise if inputs are valid 
 */
void Motor_moveForward(ST_MOTORconfig_t config,uint8 speed)
{
	DIO_SetPinValue(config.DIR1_PORT,config.DIR1_PIN,LOW);
	DIO_SetPinValue(config.DIR2_PORT,config.DIR2_PIN,HIGH);

	if (speed>=0 && speed <=100)
		pwm_SetSpeed(config.PWM_ID,speed);
}

/*
 *	Function to move the motor anti-clockwise 
 *	Inputs ST_MOTORconfig_t motor ID config , uint8_t speed percentage from 0 to 100
 *	void return. 
 *	Expected output: Motor rotate anti-clockwise if inputs are valid 
 */

void Motor_moveBackwards(ST_MOTORconfig_t config,uint8 speed)
{
		DIO_SetPinValue(config.DIR2_PORT,config.DIR2_PIN,LOW);
		DIO_SetPinValue(config.DIR1_PORT,config.DIR1_PIN,HIGH);
		if (speed>=0 && speed <=100)
			pwm_SetSpeed(config.PWM_ID,speed);
}