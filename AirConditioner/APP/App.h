/*
 * App.h
 *
 * Created: 9/17/2021 1:35:42 PM
 *  Author: OverFlow
 */ 


#ifndef APP_H_
#define APP_H_


void App_Init();														/*Init ECUAL*/

uint8_t App_GetUserInput();												/*Get desired temperature from keypad (integer)*/
uint8_t App_MeasureCurrentTemp();										/*Get current sensor readings*/

void App_AdjustTemp(uint8_t currentTemp ,uint8_t desired);				/*Adjust fan according to desired temp*/

void App_PrintCurrenTemp(uint8_t current);								/*Print Temp values on LCD*/
void App_PrintDesiredMode(uint8_t desired);


			
/*============ convert to string ==============*/

#endif /* APP_H_ */