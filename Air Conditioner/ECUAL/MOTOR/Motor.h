/*
 * Motor.h
 *
 * Created: 9/5/2021 3:40:22 PM
 *  Author: Eslam Emara
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_


#include "..\..\MCAL\DIO\DIO_Config.h"
#include "..\..\MCAL\PWM\pwm.h"

#define		PRESCALAR	0

#define		MOTOR_LOW			0
#define		MOTOR_HIGH			1

typedef struct motor {
	uint8_t DIR1_PORT;
	uint8_t DIR1_PIN;
	uint8_t DIR2_PORT;
	uint8_t DIR2_PIN;
	uint8_t PWM_ID;
	}ST_MOTORconfig_t;

void Motor_init(ST_MOTORconfig_t config);
void Motor_moveForward(ST_MOTORconfig_t config,uint8_t speed);
void Motor_moveBackwards(ST_MOTORconfig_t config,uint8_t speed);


#endif /* MOTOR_H_ */