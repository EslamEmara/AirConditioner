/*
 * stopwatch.c
 *
 * Created: 9/18/2021 8:14:30 PM
 *  Author: Omar
 */ 
#include "stopwatch.h"
ST_TIMER_config_t StopWatchConfig = {TIMER1, FREQ_8_MHZ, CTC_MODE}; // configure timer

void set_stopWatch(float delay, void (*function)(void), uint8_t repeating_number)
{
	for(uint8_t iterator=0; iterator < repeating_number; iterator++)
	{
		Timer_Schedule_Fun(delay, StopWatchConfig, function); // set desired delay and callback function
	}
}