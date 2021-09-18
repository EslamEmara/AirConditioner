/*
 * ADC.c
 *
 * Created: 9/18/2021 9:28:11 PM
 *  Author: Overflow
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"


/*****
 * Description: set global initialization to all channels [prescalar,voltage ref,int or poll,operation mode]
 * Paramerters: uint8 mode (single conversion, free running, ..)
 * 				uint8 prescalar ()
 *				uint8 trig_mode (INt, polling)
 *				uint8 reference volt ()
 * Return: none
 * Ex: ADC_Init(AutoTrig_FreeRun,ADC_Div_128,ADC_Polling,_2_56V_VoltREF);
 */
void ADC_Init(ADC_Mode Mode, ADC_Prescale Prescaler, ADC_TrigMode int_or_pol,
               ADC_VoltRef ref_volt)
{
	// reset registers
	ADMUX  = 0x00;
	ADCSRA = 0x00;
 
	// enable channel & define the refrence voltage
	ADMUX |= ref_volt;  //0b11000010
	// set preescaler & trigger mode & int_or_polling
	ADCSRA |=  (Prescaler | (Mode<<8) | int_or_pol); //0b00011011;
	// clear SFIOR (last 4 bits)
	SFIOR &= ~(0xE0);
	// set auto-trigger mode
	SFIOR |= (Mode>>8);

}


/*****
 * Description: Enable a channel to operate
 * Paramerters: uint8 channel_ID
 * Return: none
 * Ex: ADC_EnableChannel(ADC0_Channel);
 */
void ADC_EnableChannel(ADC_Ch_Select channel)
{
	ADMUX |=  channel;
}


/*****
 * Description: Enable all preset channels
 * Paramerters: none
 * Return: none
 * Ex: ADC_StartConversion();
 */
void ADC_StartConversion(void)
{
	// set ADEN in ADCSRA (ADC Enable)
	SET_BIT(ADCSRA,7);
	// set ADSC in ADCSRA ADC (start conversion)
	SET_BIT(ADCSRA,6);
}


/*****
 * Description: Read the value of ADC data register 
 * Paramerters: none
 * Return: uint16_t sensor reading
 * Ex: uint16_t result = Adc_getReading();
 * NOTE: We Only use one channel so we don't pass any argument here (implemented at the next update ISA)
 */
uint16_t ADC_GetReading(void)
{
	// wait until flag is set (conversion completed)
	while(!GET_BIT(ADCSRA,4));
	// should access ADCL first to prevent ADC access to it
	uint8_t buffer = ADCL;
	// ADC access restored
	uint16_t result = ADCH;
	result = (result<<8) | buffer;
	SET_BIT(ADCSRA,4); // chear the flag
	return result;
}

#if KEY == LOCKED
void ADC_Set_Callback(void(*pf)(void))
{
	ADC_Callback = pf;
}
#endif