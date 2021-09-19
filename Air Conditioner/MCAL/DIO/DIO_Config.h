/*
 * DIO_INT.h
 *
 * Created: 30/06/2021 
 *  Author: Mahmoud Ayoub
 */ 


#ifndef DIO_INT_H_
#define DIO_INT_H_

#include "Std_Types.h"
#include "Regs_map.h"
#include "DIO_REG.h"

#define portA 0
#define portB 1
#define portC 2
#define portD 3

#define OUTPUT 1
#define INPUT 0



void DIO_SetPinDirection (uint8_t PortNumber , uint8_t PinNumber , uint8_t Direction) ;
void DIO_SetPinValue (uint8_t PortNumber , uint8_t PinNumber , uint8_t Value) ; 
void DIO_TogglePinValue (uint8_t PortNumber , uint8_t PinNumber) ;

void DIO_SetPortDirection (uint8_t PortNumber , uint8_t Direction) ;
void DIO_SetPortValue (uint8_t PortNumber , uint8_t Value) ;
void DIO_SetUpperHalfPortValue (uint8_t PortNumber , uint8_t Value);
 
void DIO_SetLowerHalfPortValue (uint8_t PortNumber , uint8_t Value);
 
uint8_t DIO_GetPinValue (uint8_t PortNumber , uint8_t PinNumber) ; 
uint8_t DIO_GetPortValue (uint8_t PortNumber) ; 

#endif /* DIO_INT_H_ */