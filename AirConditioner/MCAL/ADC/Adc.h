/*
 * Adc.h
 *
 * Created: 9/17/2021 1:15:32 PM
 *  Author: OverFlow
 */


#ifndef ADC_H_
#define ADC_H_


void Adc_init(uint8_t channel , uint8_t prescalar);
/*set mode ,prescaler,channel*/

void Adc_getReading(uint8_t channel);
  /*get adc reading from equivalent channel*/



#endif /* ADC_H_ */
