/*
 * App.c
 *
 *  Author: Mahmoud Ayoub - Eslam Emara
 */ 

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