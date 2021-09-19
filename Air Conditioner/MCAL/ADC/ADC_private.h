/*
 * ADC_private.h
 *
 * Created: 9/18/2021 9:28:11 PM
 *  Author: Overflow
 */ 


#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

void (*volatile ADC_Callback) (void);


// Register Definition
#define ADMUX	*((volatile uint8_t *)0x27)
#define ADCSRA	*((volatile uint8_t *)0x26)
#define ADCL	*((volatile uint8_t *)0x24)
#define ADCH	*((volatile uint8_t *)0x25)
#define SFIOR   *((volatile uint8_t *)0x50)
#define ADC_DATA *((volatile uint16_t *)0x24)

#endif 