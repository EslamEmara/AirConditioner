/*
 * LM35.c
 *
 * Created: 9/18/2021 5:46:15 PM
 *  Author: Omar
 */ 
void Lm35_init(EN_SensorID_t SensorID)
{
	ADC_Init(AutoTrig_FreeRun,ADC_Div_128,ADC_Polling,_2_56V_VoltREF) // initialize ADC
	ADC_EnableChannel(ADC_Ch_Select SensorID); // Enable ADC on chosen channel
	ADC_StartConversion(); //start converting the reading to digital
}
uint8_t Lm35_GetTemp(EN_SensorID_t SensorID)
{
	return ADC_GetReading(); // get the converted reading from ADC data register
}
