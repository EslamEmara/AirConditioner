/*
 * App.c
 *
 *  Author: Mahmoud Ayoub - Eslam Emara
 */ 



#include "App.h"

#define CURRENT_TEMP_ROW_COLUMN				1,0
#define DESIRED_TEMP_ROW_COLUMN				1,0

#define WAIT_TIME							5

#define DESIRED_MODE						1
#define ACTUAL_MODE							0
#define DEFAULT_TEMP						25

#define MAX_TEMP							30
#define MIN_TEMP							15

/*global variables*/
uint8_t gLcd_mode;					/*Lcd display mode*/
uint8_t gDesired_temp;				/*user input*/

uint8_t number[3] ={0};				/*array of characters contain user inputs*/
uint8_t digit_count;				/*number of digits entered*/
uint8_t num_int;					/*number in integer format*/

ST_MOTORconfig_t MOTOR_1_config = {portA,1,portA,2,PWM1};      // FAN configuration


/*
Description : function to initialize ECUAL (LCD , Keypad , Fan , Temp sensor,global variables)
inputs		: none
outputs		: none
*/


void App_Init(void) {
	
	LCD_init () ;
	Keypad_init(); 
	Lm35_init (LM35_ID0) ;
	Motor_init(	MOTOR_1_config );; 
	gLcd_mode = ACTUAL_MODE;
	gDesired_temp = DEFAULT_TEMP;
	digit_count = 0;	
	num_int =0;
}

/*
*Function to get user input from the user
*inputs: none
*return: 0 if user input is not in range , 1 otherwise
*This function is periodic , if no key is pressed it will return 255
*Expected output: it displays the desired temprature on the connected lcd
*				put the desired value on the global num_int;
*/

uint8_t App_GetUserInput(){
		uint8_t keypad_reading = 0;
		keypad_reading = Keypad_read(ONE_PRESS);					/*read from keypad in ONE_PRESS mode*/
		
		if (keypad_reading != NO_KEY_PRESSED){						/*check if button is pressed*/
			if(keypad_reading >= '0' && keypad_reading <= '9'){
				gLcd_mode = DESIRED_MODE;
				if (digit_count <= 1){			/*check if input digits is less than maximum digits*/
					number[digit_count] = keypad_reading;
					number[digit_count+1] = '\0';					/*terminate string after input character*/
					digit_count++;
					LCD_clearScreen();
					LCD_displayStringRowColumn(0,0,"Desired Temp");
					LCD_displayStringRowColumn(1,0,(char*)number);
				}
			}
			if(keypad_reading == '='){
				num_int = Char_Arr_ToInt(number);					/*get integer number from array*/

				digit_count = 0;
				number[0] = '\0';
				number[1]='\0';
				number[2]='\0';
				if (num_int > MAX_TEMP || num_int <MIN_TEMP){
					return 0;
				}
				else return 1;

			}
		}
	return 255;
}

/*
Description : function to get measured temperature
inputs		: none
outputs		: return value of measured temperature	 
*/
uint8_t App_MeasureCurrentTemp(void) {
	uint8_t current_temp = 0 ; 
	current_temp = Lm35_GetTemp (LM35_ID0) ; 
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
		if ((currentTemp - desiredTemp) <= 10)
		Motor_moveForward(MOTOR_1_config , 10*(currentTemp - desiredTemp)) ;     // FAN ON 
		else{
		Motor_moveForward(MOTOR_1_config , 100) ;     // FAN ON
		}
	}
	else {
		Motor_moveForward(MOTOR_1_config , 0) ;     // FAN OFF 
	}
}	


/*
*Function to print the current temperature on the LCD
*inputs: current temperature
*void return.
*
*/
void App_PrintCurrenTemp(uint8_t current)								/*Print Temp values on LCD*/
{
	char Str_number[3];
	convert_2DigitInt_to_str(current,(char*)Str_number);
	LCD_displayStringRowColumn(0,0,"Current Temp");
	LCD_displayStringRowColumn(CURRENT_TEMP_ROW_COLUMN,Str_number);
}

/*
*Function to print the global desired temperature on the LCD
*inputs: none
*void return.
*
*/
void App_PrintDesiredMode()
{
	char Str_number[3];
	convert_2DigitInt_to_str(gDesired_temp,Str_number);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Desired Temp");
	LCD_displayStringRowColumn(DESIRED_TEMP_ROW_COLUMN,Str_number);
}
/*application logic*/

void app(){
	uint8_t current_temp = App_MeasureCurrentTemp();;
	uint8_t fun_return=0;
	fun_return = App_GetUserInput();
	if (fun_return != 255){
		
		 if (fun_return == 1){
			 gDesired_temp = num_int;
			 gLcd_mode = ACTUAL_MODE;

		}
		else{
			gDesired_temp = DEFAULT_TEMP;
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Not Valid!");
			
		}
		
	}
		if(gLcd_mode == ACTUAL_MODE){							/*Desired temperature mode*/
			App_PrintCurrenTemp(current_temp);
		}
		App_AdjustTemp(current_temp,gDesired_temp);

	
}

/*
*Function to convert 2 digit integer into string
*inputs: uint8 number
*i/o paramter: char* string
*/

void convert_2DigitInt_to_str(uint8_t number,char* arr){
	if (number < 10){
		arr[0] = number + '0';
		arr[1] = '\0';
		
	}
	else{
		arr[0] = (number / 10) + '0';
		arr[1]= (number - ((number / 10) * 10)) + '0';
		arr[2] = '\0';

	}

}

/*
*Function to convert character array to integer
*i/o: character array uint8*
*return: converted integer
*
*/
uint8_t Char_Arr_ToInt(uint8_t* arr){

	if (arr[1] == 0){
		return (arr[0] - '0');
	}
	else{
		return (arr[0]-'0')*10 + (arr[1]-'0');
	}
}