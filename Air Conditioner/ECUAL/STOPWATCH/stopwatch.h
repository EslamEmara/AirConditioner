/*
 * stopwatch.h
 *
 * Created: 9/18/2021 8:15:03 PM
 *  Author: Omar
 */ 


#ifndef STOPWATCH_H_
#define STOPWATCH_H_

#include "../../MCAL/TIMER/Timer.h"

/****************************************************** GLOBAL VARIABLES *****************************************************/
	
/***************************************************** FUNCTIONS PROTOTYPES **************************************************/
/*****
 * Description: funThisction execute a specific function every determined period of time with repeating option
 * Parameters: delay: waiting timer until executing the function 
			   function: pointer to function that will be executed after delay time
			   repeating_number: specify repeating times of the function
 * Return: uint16_t sensor reading
 */
void set_stopWatch(float delay, void (*function)(void), uint8_t repeating_number);



#endif /* STOPWATCH_H_ */