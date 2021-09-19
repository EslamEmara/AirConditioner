 /******************************************************************************
 *
 * Module: KEYPAD
 *
 * File Name: keypad.h
 *
 * Description: Header file for the Keypad driver
 *
 * Author: Mohamed AbdelAzeem
 *
 *******************************************************************************/

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_types.h"
#include "common_macros.h"
#include "Regs_map.h"

/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/

/* Keypad configurations for number of rows and columns */
#define N_col 3
#define N_row 4

/* Keypad Port Configurations */
/*#define KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN  PINA
#define KEYPAD_PORT_DIR DDRA*/
#define KEYPAD_PORT_OUT portA
#define KEYPAD_PORT_IN  portA
#define KEYPAD_PORT_DIR portA


/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/

/*
 * Function responsible for getting the pressed keypad key
 */
uint8_t KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */
