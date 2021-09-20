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

uint8_t gLcd_mode;
uint8_t gDesired_temp;
uint8_t gTimeOut;

uint8_t keypad_reading ;			/*return of keypad press*/
uint8_t number[3] ={0};				/*array of characters contain user inputs*/
uint8_t digit_count;				/*number of digits entered*/
uint8_t num_int;					/*number in integer format*/

ST_MOTORconfig_t MOTOR_1_config = {portA,1,portA,2,PWM1};      // FAN configuration

/*
Description : function to initialize ECUAL (LCD , Keypad , Fan , Temp sensor)
inputs		: none
outputs		: none
*/

void TimerCounter (void);

void App_Init(void) {
	
	LCD_init () ;
	Keypad_init(); 
	Lm35_init (LM35_ID0) ;
	Motor_init(	MOTOR_1_config );; 
	gLcd_mode = ACTUAL_MODE;
	gDesired_temp = 25;
	gTimeOut = 0;
	digit_count = 0;	
	num_int =0;
	keypad_reading =0;
}

/*
Description : function to get desired temperature from user (only 2 digits)
inputs		: none
outputs		: return value of desired temperature	|| 0 >> number entered is out of limits
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

uint8_t Char_Arr_ToInt(uint8_t* arr){

	if (arr[1] == 0){
		return (arr[0] - '0');
	}
	else{
		return (arr[0]-'0')*10 + (arr[1]-'0');
	}
}
uint8_t App_GetUserInput(){
	
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
				if (num_int > 30 || num_int <15){
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
		Motor_moveForward(MOTOR_1_config , 80) ;     // FAN ON 
	}
	else {
		Motor_moveForward(MOTOR_1_config , 0) ;     // FAN OFF 
	}
}			


void App_PrintCurrenTemp(uint8_t current)								/*Print Temp values on LCD*/
{
	char Str_number[3];
	convert_2DigitInt_to_str(current,(char*)Str_number);
	LCD_displayStringRowColumn(0,0,"Current Temp");
	LCD_displayStringRowColumn(CURRENT_TEMP_ROW_COLUMN,Str_number);
}

void App_PrintDesiredMode()
{
	char Str_number[3];
	convert_2DigitInt_to_str(gDesired_temp,Str_number);
	LCD_clearScreen();
	LCD_displayStringRowColumn(0,0,"Desired Temp");
	LCD_displayStringRowColumn(DESIRED_TEMP_ROW_COLUMN,Str_number);
}

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
			gDesired_temp = 25;
			LCD_clearScreen();
			LCD_displayStringRowColumn(0,0,"Not Valid!");
			
		}
		
	}
		if(gLcd_mode == ACTUAL_MODE){							/*Desired temprature mode*/
			App_PrintCurrenTemp(current_temp);
			App_AdjustTemp(current_temp,gDesired_temp);
		}
	
}