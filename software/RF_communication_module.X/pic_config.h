#ifndef PIC_CONFIG_H
#define	PIC_CONFIG_H

// MCU
#define REG             U1STA
#define DELAY           0xFFFF

// I/O bits
#define BAL             PORTBbits.RB0
#define JOBB            PORTBbits.RB1
#define PIROS           BIT_2
#define ZOLD            BIT_3

void oscconfig();
void pinconfig();
void delaycpu();
void status_reg();

#endif	/* PIC_CONFIG_H */