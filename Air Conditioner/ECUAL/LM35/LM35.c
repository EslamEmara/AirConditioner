/*
 * LM35.c
 *
 * Created: 9/18/2021 5:46:15 PM
 *  Author: Omar
 */ 

#include "LM35.h"
void Lm35_init(EN_SensorID_t SensorID) // No need to this parameter
{
	ADC_Init(SingleConversion, ADC_Div_128, ADC_Polling, _2_56V_VoltREF); // initialize ADC
}
float32_t Lm35_GetTemp(EN_SensorID_t SensorID)
{
	// get the converted reading from ADC data register
	uint8_t digital_reading = ADC_GetReading(SensorID); 
	// conert digital value to temprature in c
	float32_t temprature = (digital_reading * 100 * 2.56)/(1024);
	return temprature;
}


//---- Updates -----------------
// change ADC mode to SingleConversion (line 11)
// rewrite Lm35_GetTemp 