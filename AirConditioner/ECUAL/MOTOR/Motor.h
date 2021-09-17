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

#define		LOW			0
#define		HIGH		1

typedef struct motor {
	uint8 DIR1_PORT;
	uint8 DIR1_PIN;
	uint8 DIR2_PORT;
	uint8 DIR2_PIN;
	uint8 PWM_ID;
	}ST_MOTORconfig_t;

void Motor_init(ST_MOTORconfig_t config);
void Motor_moveForward(ST_MOTORconfig_t config,uint8 speed);
void Motor_moveBackwards(ST_MOTORconfig_t config,uint8 speed);


#endif /* MOTOR_H_ */