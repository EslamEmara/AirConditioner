/*
 * App.h
 *
 * Created: 9/17/2021 1:35:42 PM
 *  Author: OverFlow
 */


#ifndef APP_H_
#define APP_H_

#include "../ECUAL/KEYPAD/keypad.h"
#include "../ECUAL/LCD/lcd.h"
#include "../ECUAL/LM35/LM35.h"
#include "../ECUAL/MOTOR/Motor.h"
#include "../ECUAL/STOPWATCH/stopwatch.h"

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

/*=============ESLAM==========*/

void App_PrintCurrenTemp(uint8_t current);								/*Print Temp values on LCD*/
/*============ convert to string ==============*/

void App_PrintDesiredMode();
/*============ convert to string ==============*/

void app();

uint8_t Char_Arr_ToInt(uint8_t* arr);
void convert_2DigitInt_to_str(uint8_t number,char* arr);



#endif /* APP_H_ */
