﻿/*
 * App.c
 *
 *  Author: Mahmoud Ayoub - Eslam Emara
 */ 

#define CURRENT_TEMP_ROW_COLUMN				1,0
#define DESIRED_TEMP_ROW_COLUMN				1,0
#define WAIT_TIME							5

#define DESIRED_MODE						1
#define ACTUAL_MODE							0

#define LCD_MODE							ACTUAL_MODE

uint8_t desired_temp = 25;

/*
Description : function to initialize ECUAL (LCD , Keypad , Fan , Temp sensor)
inputs		: none
outputs		: none
*/
void App_Init(void) {
	LCD_init () ; 
	Keypad_init () ; 
	Fan_init () ;  
	Temp_sensor_init () ; 
}

/*
Description : function to get desired temperature from user (only 2 digits)
inputs		: none
outputs		: return value of desired temperature	|| 0 >> number entered is out of limits
*/
uint8_t App_GetUserInput() {												/*Get desired temperature from keypad (integer)*/
	uint8_t no_of_digits = 0 ;
	uint8_t single_key = 0 ;  
	uint8_t array_of_keys [3] = {0 , 0 , 0} ; 
	uint8_t counter = 0 ; 
	uint8_t int_keys = 0 ; 

	while (1) {
		single_key = keypad_read () ;                               // get key pressed on keypad
		if (single_key != '=') {									// user doesn't finish entering temperature
			LCD_MODE = DESIRED_MODE;
			if (no_of_digits < 2) {									// no of digits pressed still valid
				array_of_keys [no_of_digits] = single_key ;				// add pressed key into the array of integers
				no_of_digits ++ ;
			}
		}
		else if (single_key == '=') {								// here the user finished entering the temperature
			for (counter = 0 ; counter < 2 ; counter ++) {				// convert array of integers into single integer
				int_keys = 10*int_keys + array_of_keys[counter] ;
			}
			no_of_digits = 0 ;										// assign zero to no_of_digits to start again 
			for (counter = 0 ; counter < 3 ; counter ++) {			// assign zeros to the array after finishing
				array_of_keys [counter] = 0 ;
			}
			// return converted value
			if ((int_keys >= 15) && (int_keys <= 30)) {				//check limits on inputs >= 15 , <= 30
				return int_keys ;
			}
			else {
				return 0 ; 		
			}
		}
	}
}

/*
Description : function to get measured temperature
inputs		: none
outputs		: return value of measured temperature	 
*/
uint8_t App_MeasureCurrentTemp(void) {
	uint8_t current_temp = 0 ; 
	current_temp = Temp_sensor_read () ; 
	return current_temp ; 
}							

/*
Description : function to adjust fan according to desired temperature
inputs		: current temperature , desired temperature
outputs		: none	
*/
void App_AdjustTemp(uint8_t currentTemp ,uint8_t desiredTemp) {
	/*if currentTemp > desired FAN On*/
	/*else Fan OFF*/
	if (currentTemp > desiredTemp) {
		Fan_ON () ; 
	}
	else {
		Fan_OFF () ; 
	}
}			

void convert_2DigitInt_to_str(uint8_t number,uint8_t* arr){
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
}
void App_PrintCurrenTemp(uint8_t current)								/*Print Temp values on LCD*/
{
	uint8_t* Str_number;
	convert_2DigitInt_to_str(current , Str_number);
	LCD_clearScreen();
	Lcd_SendStringXY(CURRENT_TEMP_ROW_COLUMN,Str_number);
}
void App_PrintDesiredMode(uint8_t desired);
{
	uint8_t* Str_number;
	convert_2DigitInt_to_str(desired , Str_number);
	LCD_clearScreen();
	Lcd_SendStringXY(DESIRED_TEMP_ROW_COLUMN,Str_number);
}

void app(){
	
	uint8_t current_temp = App_MeasureCurrentTemp();
	uint8_t stopwatch_started = 0;
	desired_temp = App_GetUserInput();
	
	if (desired_temp !=0){
		Lcd_mode = DESIRED_MODE;
		Stopwatch_start(WAIT_TIME,0);						/*start counting 5 secs (reset counter to zero mode)*/
		stopwatch_started = 1;					
	}
	if (stopwatch_started == 1){							/*if stopwatch started counting*/
		if(Stopwatch_start(WAIT_TIME,1)){					/*if stopwatch finished counting	(check on count mode*/
			Lcd_mode = ACTUAL_MODE;
			App_AdjustTemp(current_temp,desired_temp);
			stopwatch_started = 0;				
		}
	}
	
	if(Lcd_mode == DESIRED_MODE){							/*Desired temprature mode*/
		App_PrintDesiredMode(desired_temp);
	}
	else{													/*Actual temprature mode*/
		App_PrintCurrenTemp(current_temp);
	}
}