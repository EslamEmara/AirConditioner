 /******************************************************************************
 *
 * Module: LCD
 *
 * File Name: lcd.c
 *
 * Description: Source file for the LCD driver
 *
 * Author: Mohamed AbdelAzeem
 *
 *******************************************************************************/

#include "lcd.h"
#include "../../MCAL/DIO/DIO_Config.h"
#include "../Delay/delay.h"
#include "../../MCAL/DIO/DIO_Config.h"

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void LCD_init(void)
{
//	LCD_CTRL_PORT_DIR |= (1<<E) | (1<<RS) | (1<<RW); /* Configure the control pins(E,RS,RW) as output pins */
	DIO_SetPinDirection(LCD_CTRL_PORT_DIR, E, OUTPUT);
	DIO_SetPinDirection(LCD_CTRL_PORT_DIR, RS, OUTPUT);
	DIO_SetPinDirection(LCD_CTRL_PORT_DIR, RW, OUTPUT);
	
	DIO_SetPortValue(LCD_CTRL_PORT_DIR, 0x00);
	DIO_SetPortValue(LCD_DATA_PORT_DIR, 0x00);

	#if (DATA_BITS_MODE == 4)
		#ifdef UPPER_PORT_PINS
			//LCD_DATA_PORT_DIR |= 0xF0; /* Configure the highest 4 bits of the data port as output pins */
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 4, OUTPUT);
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 5, OUTPUT);
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 6, OUTPUT);
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 7, OUTPUT);
		#else
			//LCD_DATA_PORT_DIR |= 0x0F; /* Configure the lowest 4 bits of the data port as output pins */
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 0, OUTPUT);
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 1, OUTPUT);
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 2, OUTPUT);
			DIO_SetPinDirection(LCD_DATA_PORT_DIR, 3, OUTPUT);
		#endif
		LCD_sendCommand(FOUR_BITS_DATA_MODE); /* initialize LCD in 4-bit mode */
		LCD_sendCommand(TWO_LINE_LCD_Four_BIT_MODE); /* use 2-line lcd + 4-bit Data Mode + 5*7 dot display Mode */
	#elif (DATA_BITS_MODE == 8)
		//LCD_DATA_PORT_DIR = 0xFF; /* Configure the data port as output port */
		DIO_SetPortDirection(LCD_DATA_PORT_DIR, OUTPUT);
		LCD_sendCommand(TWO_LINE_LCD_Eight_BIT_MODE); /* use 2-line lcd + 8-bit Data Mode + 5*7 dot display Mode */
	#endif

	LCD_sendCommand(CURSOR_OFF); /* cursor off */
	LCD_sendCommand(CLEAR_COMMAND); /* clear LCD at the beginning */
}

void LCD_sendCommand(uint8_t command)
{
	//CLEAR_BIT(LCD_CTRL_PORT,RS); /* Instruction Mode RS=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, RS, LOW);
	
	//CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, RW, LOW);
	
	delay_us(1); /* delay for processing Tas = 50ns */
	
	//SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, HIGH);
	
	delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
	
	
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required command to the data bus D4 --> D7 */
	#ifdef UPPER_PORT_PINS
		//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		DIO_SetUpperHalfPortValue(LCD_DATA_PORT, (command & 0xF0));
	#else
	/* out the Lowest 4 bits of the required command to the data bus D0 --> D3 */
		//LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command & 0xF0) >> 4);
		//DIO_SetPortValue(LCD_DATA_PORT, (command & 0xF0) >> 4);
		DIO_SetLowerHalfPortValue(LCD_DATA_PORT, (command & 0xF0) >> 4);
#endif

	delay_us(1); /* delay for processing Tdsw = 100ns */
	
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, LOW);
	
	delay_us(1); /* delay for processing Th = 13ns */
	
//	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, HIGH);
	delay_us(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required command to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command & 0x0F) << 4);
	DIO_SetUpperHalfPortValue(LCD_DATA_PORT, ((command & 0x0F) << 4));
#else
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
	DIO_SetLowerHalfPortValue(LCD_DATA_PORT, (command & 0x0F));
#endif

	delay_us(1); /* delay for processing Tdsw = 100ns */
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, LOW);
	delay_us(1); /* delay for processing Th = 13ns */
	
#elif (DATA_BITS_MODE == 8)
	//LCD_DATA_PORT = command; /* out the required command to the data bus D0 --> D7 */
	DIO_SetPortValue(LCD_DATA_PORT, command);
	delay_us(1); /* delay for processing Tdsw = 100ns */
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, LOW);
	delay_us(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayCharacter(uint8_t data)
{
	//SET_BIT(LCD_CTRL_PORT,RS); /* Data Mode RS=1 */
	DIO_SetPinValue(LCD_CTRL_PORT, RS, HIGH);
	
	//CLEAR_BIT(LCD_CTRL_PORT,RW); /* write data to LCD so RW=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, RW, LOW);
	
	delay_us(1); /* delay for processing Tas = 50ns */
	//SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
    DIO_SetPinValue(LCD_CTRL_PORT, E, HIGH);
	
	delay_us(1); /* delay for processing Tpw - Tdws = 190ns */
#if (DATA_BITS_MODE == 4)
	/* out the highest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
	DIO_SetUpperHalfPortValue(LCD_DATA_PORT, (data & 0xF0));
#else
//	LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data & 0xF0) >> 4);
	DIO_SetLowerHalfPortValue(LCD_DATA_PORT, (data & 0xF0)>>4);
#endif

	delay_us(1); /* delay for processing Tdsw = 100ns */
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, LOW);
	
	delay_us(1); /* delay for processing Th = 13ns */
	
//	SET_BIT(LCD_CTRL_PORT,E); /* Enable LCD E=1 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, HIGH);
	delay_us(1); /* delay for processing Tpw - Tdws = 190ns */

	/* out the lowest 4 bits of the required data to the data bus D4 --> D7 */
#ifdef UPPER_PORT_PINS
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data & 0x0F) << 4);
	DIO_SetUpperHalfPortValue(LCD_DATA_PORT, ((data & 0x0F) << 4));
#else
	//LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
	DIO_SetLowerHalfPortValue(LCD_DATA_PORT, (data & 0x0F));
#endif

	delay_us(1); /* delay for processing Tdsw = 100ns */
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, LOW);
	
	delay_us(1); /* delay for processing Th = 13ns */
#elif (DATA_BITS_MODE == 8)
	//LCD_DATA_PORT = data; /* out the required command to the data bus D0 --> D7 */
	DIO_SetPortValue(LCD_DATA_PORT, data);
	delay_us(1); /* delay for processing Tdsw = 100ns */
	
	//CLEAR_BIT(LCD_CTRL_PORT,E); /* disable LCD E=0 */
	DIO_SetPinValue(LCD_CTRL_PORT, E, LOW);
	delay_us(1); /* delay for processing Th = 13ns */
#endif
}

void LCD_displayString(const char *Str)
{
	uint8_t i = 0;
	while(Str[i] != '\0')
	{
		LCD_displayCharacter(Str[i]);
		i++;
	}
	/***************** Another Method ***********************
	while((*Str) != '\0')
	{
		LCD_displayCharacter(*Str);
		Str++;
	}
	*********************************************************/
}

void LCD_goToRowColumn(uint8_t row,uint8_t col)
	{
	uint8_t Address;

	/* first of all calculate the required address */
	switch(row)
	{
		case 0:
				Address=col;
				break;
		case 1:
				Address=col+0x40;
				break;
		case 2:
				Address=col+0x10;
				break;
		case 3:
				Address=col+0x50;
				break;
	}
	/* to write to a specific address in the LCD
	 * we need to apply the corresponding command 0b10000000+Address */
	LCD_sendCommand(Address | SET_CURSOR_LOCATION);
}

void LCD_displayStringRowColumn(uint8_t row,uint8_t col,const char *Str)
{
	LCD_goToRowColumn(row,col); /* go to to the required LCD position */
	LCD_displayString(Str); /* display the string */
}

void LCD_intgerToString(int data)
{
   char buff[16]; /* String to hold the ascii result */
   tostring(buff,data); /* 10 for decimal */
   LCD_displayString(buff);
}

void LCD_clearScreen(void)
{
	LCD_sendCommand(CLEAR_COMMAND); //clear display
}


void tostring(uint8_t str[], uint8_t number)
{
	uint8_t iterator;
	uint8_t StringLength = 0 ;
	uint8_t IntegerNumber = number ;
	uint8_t remainder = 0;
	/* calculating length of the number */
	while(IntegerNumber != 0 )
	{
		StringLength++;
		IntegerNumber /= 10;
	}
	
	IntegerNumber = number;
	for(iterator = 0; iterator < StringLength; iterator++)
	{
		remainder =  IntegerNumber % 10;
		IntegerNumber = IntegerNumber /10;
		str[StringLength-(iterator+1)] = remainder + '0';   /* + '0' to convert number digit to character */
	}
	str[StringLength] = '\0';
}