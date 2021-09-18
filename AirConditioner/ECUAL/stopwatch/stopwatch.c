/*
 * stopwatch.c
 *
 * Created: 9/18/2021 8:14:30 PM
 *  Author: Omar
 */ 
void set_stopWatch(float delay, void (*function)(void), uint8_t repeating_number)
{
	for(uint8_t iterator=0; iterator < repeating_number; iterator++)
	{
		uint8_t Timer_Schedule_Fun(delay, config, function); // set desired delay and callback function
	}
}