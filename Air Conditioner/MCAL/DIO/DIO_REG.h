/*
 * DIO_REG.h
 *
 * Created: 30/06/2021 
 *  Author: Mahmoud Ayoub
 */ 


#ifndef DIO_REG_H_
#define DIO_REG_H_

#include "Std_Types.h"

#define DDRA_REG			(*((volatile uint8_t*)0x3A))
#define PORTA_REG			(*((volatile uint8_t*)0x3B))
#define PINA_REG			(*((volatile uint8_t*)0x39))

#define DDRB_REG			(*((volatile uint8_t*)0x37))
#define PORTB_REG			(*((volatile uint8_t*)0x38))
#define PINB_REG			(*((volatile uint8_t*)0x36))

#define DDRC_REG			(*((volatile uint8_t*)0x34))
#define PORTC_REG			(*((volatile uint8_t*)0x35))
#define PINC_REG			(*((volatile uint8_t*)0x33))

#define DDRD_REG			(*((volatile uint8_t*)0x31))
#define PORTD_REG			(*((volatile uint8_t*)0x32))
#define PIND_REG			(*((volatile uint8_t*)0x30))


#endif /* DIO_REG_H_ */