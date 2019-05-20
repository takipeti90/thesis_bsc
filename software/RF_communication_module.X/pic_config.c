#include <plib.h>
#include "pic_config.h"
#include "uart.h"
#include "spi.h"

void oscconfig()
{
    OSCConfig(OSC_FRC,0,0,0);       // FRC=8MHz, SYSCLK=PBCLK=8MHz
    OSCSetPBDIV(OSC_PB_DIV_1);
    mOSCDisableSOSC();              // Sosc disable
    CFGCON = 0x0;                   // JTAG disable
    WDTCON = 0x00000000;            // Watchdog timer disable
}

void pinconfig()
{
    PORTSetPinsDigitalIn(IOPORT_B,BIT_0|BIT_1|BIT_7);   // BIT_0: bal gomb, BIT_1: jobb gomb, BIT_7: nIRQ
    PORTSetPinsDigitalOut(IOPORT_B,BIT_2|BIT_3|BIT_9);  // BIT_2: piros LED, BIT_3: zöld LED, BIT_9: nSEL
    PORTClearBits(IOPORT_B, PIROS|ZOLD);
}

void delaycpu()
{
    T2CON = 0x0;                // 1MHz/8 timer osc
    T2CONSET = 0x00000030;
    TMR2 = 0;
    PR2 = 0xFFFF;
    T2CONSET = 0x8000;

    while(DELAY > TMR2) {}
    T2CONSET = 0x0;
}

void status_reg()                   // kolvassa a PIC beállított regsizterének értékét
{
    unsigned int content=0;
    unsigned char i=3;

    content = REG;
    writeuart(content);
    while(i)
    {
        content = content >> 8;
        writeuart(content);
        i--;
    }
}