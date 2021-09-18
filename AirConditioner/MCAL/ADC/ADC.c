/*
 * ADC.c
 *
 * Created: 9/10/2021 9:28:11 PM
 *  Author: farouk
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"



void ADC_Init(ADC_Mode Mode, ADC_Prescale Prescaler, ADC_TrigMode int_or_pol,
               ADC_VoltRef ref_volt)
{
	// reset registers
	ADMUX  = 0x00;
	ADCSRA = 0x00;
 
	// enable channel & define the refrence voltage
	ADMUX |= ADC_VoltageReferPin;  //0b11000010
	// set preescaler & trigger mode & int_or_polling
	ADCSRA |=  (Prescaler | (Mode<<8) | int_or_pol); //0b00011011;
	// clear SFIOR (last 4 bits)
	SFIOR &= ~(0xE0);
	// set auto-trigger mode
	SFIOR |= (Mode>>8);

}

void ADC_EnableChannel(ADC_Ch_Select channel)
{
	ADMUX |=  channel;
}

void ADC_StartConversion(ADC_Ch_Select channel)
{
	// set ADEN in ADCSRA (ADC Enable)
	ADCSRA |= (1<<8);
	// set ADSC in ADCSRA ADC (start conversion)
	ADCSRA |= (1<<7);
}

extern "C" {
	ISR(ADC_vect){
		if(ADC_Callback != NULL)
		ADC_Callback();
	}
}
			