/*
 * LM35.h
 *
 * Created: 9/17/2021 1:22:43 PM
 *  Author: OverFlow
 */ 


#ifndef LM35_H_
#define LM35_H_

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

void Lm35_init(EN_SensorID_t SensorID);		/*init lm35 according to channel*/

uint8_t Lm35_GetTemp(EN_SensorID_t SensorID); /*Get reading from lm35*/




#endif /* LM35_H_ */