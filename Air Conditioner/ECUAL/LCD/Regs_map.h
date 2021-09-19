/******************************************************************************
 *
 * Module: Timer
 *
 * File Name: Regs_map.h
 *
 * Description: registers map for atmega32
 *
 * Author: Mohamed AbdelAzeem
 *
 * Date : SEP,2021
 *
 *******************************************************************************/


#ifndef REGS_MAP_H_
#define REGS_MAP_H_

/* PORTD */
#define PD7     7
#define PD6     6
#define PD5     5
#define PD4     4
#define PD3     3
#define PD2     2
#define PD1     1
#define PD0     0

/* PORTC */
#define PC7     7
#define PC6     6
#define PC5     5
#define PC4     4
#define PC3     3
#define PC2     2
#define PC1     1
#define PC0     0


/* PORTB */
#define PB7     7
#define PB6     6
#define PB5     5
#define PB4     4
#define PB3     3
#define PB2     2
#define PB1     1
#define PB0     0


#define OC0 PB3
#define OC1A PD5
#define OC1B PD4

#define REG(n) (*((volatile uint8_t*)(n)))

/* Port D */
#define PIND    REG(0x10)  
#define DDRD    REG(0x31)
#define PORTD   REG(0x32)

/* Port C */
#define PINC    REG(0x13)
#define DDRC    REG(0x34)
#define PORTC   REG(0x35)

/* Port B */
#define PINB    REG(0x16)
#define DDRB    REG(0x17)
#define PORTB   REG(0x18)

/* Port A */
#define PINA    REG(0x39)
#define DDRA    REG(0x03A)
#define PORTA   REG(0x3B)



#define TCCR0				REG(0x53)
#define TCNT0				REG(0x52)
#define OCR0				REG(0x5C)

#define TCCR1A				REG(0x4F)
#define TCCR1B				REG(0x4E)
#define TCNT1				REG(0x2C)
#define TCNT1H				REG(0x4D)
#define TCNT1L				REG(0x4C)

#define OCR1A				REG(0x2A)
#define OCR1B				REG(0x28)
#define	OCR1AL				REG(0x4A)
#define	OCR1AH				REG(0x4B)
#define OCR1BH				REG(0x49)
#define OCR1BL				REG(0x48)

#define TCCR2				REG(0x45)
#define TCNT2				REG(0x44)
#define OCR2				REG(0x43)
#define TIMSK				REG(0x59)
#define TIFR				REG(0x58)
#define ASSR				REG(0x42)
#define STATUS_REG			REG(0x5F)

#define PORTB_DIR			REG(0x37)
#define PORTD_DIR			REG(0x31)
#define  DDRC				REG(0x34)
#define  PORTC				REG(0x35)
#define  SREG				REG(0x5F)



/* TIMSK */
#define OCIE2   7
#define TOIE2   6
#define TICIE1  5
#define OCIE1A  4
#define OCIE1B  3
#define TOIE1   2
#define OCIE0   1
#define TOIE0   0


/* TCCR1A */
#define COM1A1  7
#define COM1A0  6
#define COM1B1  5
#define COM1B0  4
#define FOC1A   3
#define FOC1B   2
#define WGM11   1
#define WGM10   0

/* TCCR1B */
#define ICNC1   7
#define ICES1   6
/* bit 5 reserved */
#define WGM13   4
#define WGM12   3
#define CS12    2
#define CS11    1
#define CS10    0

/* TIFR */
#define OCF2    7
#define TOV2    6
#define ICF1    5
#define OCF1A   4
#define OCF1B   3
#define TOV1    2
#define OCF0    1
#define TOV0    0




#define WGM01_BIT   3
#define WGM21_BIT   3
#define OCIE0_BIT   1
#define TOIE0_BIT   0
#define OCIE2_BIT   7
#define TOIE2_BIT   6
#define I_BIT		7
#define OCIE_BIT      1


#endif /* REGS_MAP_H_ */