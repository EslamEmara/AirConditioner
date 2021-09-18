/*
 * ADC_interface.h
 *
 * Created: 9/10/2021 9:28:11 PM
 *  Author: farouk
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_




typedef enum
{
	AREF_VoltRef=0x00,
	AVCC_VoltRef=0x40,
	_2_56V_VoltREF=0xC0,
}ADC_VoltRef;

typedef enum
{
	LEFT_Adjust=0x20,
	RIGHT_Adjust=0x00,
}ADC_DataAdjustment;

typedef enum
{
	ADC0_Channel,
	ADC1_Channel,
	ADC2_Channel,
	ADC3_Channel,
	ADC4_Channel,
	ADC5_Channel,
	ADC6_Channel,
	ADC7_Channel,
	DIFF_PADC0_NADC0_G10x,
	DIFF_PADC1_NADC0_G10x
}ADC_Ch_Select;


typedef enum
{
	SingleConvertion    = 0x0000,
	AutoTrig_FreeRun    = 0x0020,
	AutoTrig_AnalogComp = 0x2020,
	AutoTrig_INT0_Req   = 0x4020
// the last two digits for SFIOR & the others for polling or trigger
	
}ADC_Mode;

typedef enum
{
	ADC_Polling=0x00,
	ADC_InterruptEnable=0x08,
}ADC_TrigMode;

typedef enum
{
	ADC_Div_2 = 1,
	ADC_Div_4,
	ADC_Div_8,
	ADC_Div_16,
	ADC_Div_32,
	ADC_Div_64,
	ADC_Div_128,
}ADC_Prescale;



void ADC_Init(ADC_Mode Mode, ADC_Prescale Prescaler, ADC_TrigMode int_or_pol,
               ADC_VoltRef ref_volt);

void ADC_EnableChannel(ADC_Ch_Select channel);

void ADC_StartConversion(ADC_Ch_Select channel);

ADC_Set_Callback(void(*pf)(void));

#endif