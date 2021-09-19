/*
 * App.h
 *
 * Created: 9/17/2021 1:35:42 PM
 *  Author: OverFlow
 */


#ifndef APP_H_
#define APP_H_
/*=================MAHMOUD=============*/

void App_Init(void);														/*Init ECUAL*/

uint8_t App_GetUserInput();												/*Get desired temperature from keypad (integer)*/

/* limits on inputs > 15 , <30*/
/*read from keypad until = is pressed*/

uint8_t App_MeasureCurrentTemp(void);										/*Get current sensor readings*/
/*get sensor readings (current temperature) */

void App_AdjustTemp(uint8_t currentTemp ,uint8_t desiredTemp);				/*Adjust fan according to desired temp*/

/*if currentTemp > desired FAN On*/
/*else Fan OFF*/

static void ConvertIntToStr(uint8_t number);				/*convert integer to string 2 digits*/
/*
void convert_2DigitInt_to_str(unsigned char number,char* arr){
	arr[0] = (number / 10);

	if (arr[0] == 0){
		arr[0] = number + '0';
		arr[1] = '\0';
		return;
	}
	else{
		arr[1]= (number - (arr[0]*10));
		arr[0]+= '0';
		arr[1]+='0';
		arr[2]= '\0';
	}
}*/

/*=============ESLAM==========*/

void App_PrintCurrenTemp(uint8_t current);								/*Print Temp values on LCD*/
/*============ convert to string ==============*/

void App_PrintDesiredMode(uint8_t desired);
/*============ convert to string ==============*/

void app();





#endif /* APP_H_ */
