/*
 * LM35.h
 *
 * Created: 9/17/2021 1:22:43 PM
 *  Author: OverFlow
 */ 


#ifndef LM35_H_
#define LM35_H_

#include "../../MCAL/ADC/ADC_interface.h"

typedef enum{
	LM35_ID0,
	LM35_ID1,
	LM35_ID2,
	LM35_ID3,
	LM35_ID4,
	LM35_ID5,
	LM35_ID6,
	LM35_ID7,
	}EN_SensorID_t;

/*****
 * Description: this function initiates LM35 which enables ADC channel and start converting the reading of LM35 
 * Parameters: none
 * Return: none
 */
void Lm35_init();		/*initialize lm35 */

/*****
 * Description: this function gets the current temperature
 * Parameters: SensorID: selects the channel of LM35 to read the its value after conversion 
 * Return: Reading of LM35
 */
uint8_t Lm35_GetTemp(EN_SensorID_t SensorID); /*Get reading from lm35*/





#endif /* LM35_H_ */