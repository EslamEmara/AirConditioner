/*
 * ADC_interface.h
 *
 * Created: 9/18/2021 9:28:11 PM
 *  Author: Overflow
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_



/* voltage reference for ADC */
typedef enum
{
	AREF_VoltRef=0x00,
	AVCC_VoltRef=0x40,
	_2_56V_VoltREF=0xC0,
}ADC_VoltRef;

/* Data Format in ADC data register */
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
	ADC7_Channel
}ADC_Ch_Select;


/* Operation Mode in ADC */
typedef enum
{
	SingleConvertion    = 0x0000,
	AutoTrig_FreeRun    = 0x0020,
	AutoTrig_AnalogComp = 0x2020,
	AutoTrig_INT0_Req   = 0x4020
// the last two digits for SFIOR & the others for polling or trigger
	
}ADC_Mode;


/* Interrupt or polling based Operation */
typedef enum
{
	ADC_Polling=0x00,
	ADC_InterruptEnable=0x08,
}ADC_TrigMode;

/* ADC clk source */
typedef enum
{
	ADC_Div_2 = 1,
	ADC_Div_4,
	ADC_Div_8,
	ADC_Div_16,
	ADC_Div_32,
	ADC_Div_64,
	ADC_Div_128, // conversion starts every almost 1 ms
}ADC_Prescale;


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
               ADC_VoltRef ref_volt);


/*****
 * Description: Enable a channel to operate
 * Paramerters: uint8 channel_ID
 * Return: none
 * Ex: ADC_EnableChannel(ADC0_Channel);
 */
void ADC_EnableChannel(ADC_Ch_Select channel);


/*****
 * Description: Enable all preset channels
 * Paramerters: none
 * Return: none
 * Ex: ADC_StartConversion();
 */
void ADC_StartConversion(void);


/*****
 * Description: Read the value of ADC data register 
 * Paramerters: none
 * Return: uint16_t sensor reading
 * Ex: uint16_t result = Adc_getReading();
 * NOTE: We Only use one channel so we don't pass any argument here (implemented at the next update ISA)
 */
uint16_t ADC_GetReading(void);

// Not used
void ADC_Set_Callback(void(*pf)(void));

/******* Sequence of configuring ADC
 * 
 * ADC_Init(AutoTrig_FreeRun,ADC_Div_128,ADC_Polling,_2_56V_VoltREF) (recommended config for our App)
 * ADC_EnableChannel(ADCn_Channel);
 * ADC_StartConversion();
 *
 */
#endif