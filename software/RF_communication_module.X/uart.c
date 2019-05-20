#include "uart.h"
#include "pic_config.h"
#include <plib.h>

void uartconfig()           //1 START, 8 DATA, NO PARITY, 1 STOP, 9615 BAUD
{
    U1RXR = 0b0010;         // RPA4 12.láb
    RPB4R = 0b0001;         // U1TX (RPB4) 11.láb

    IEC1CLR=0x00000380;     // disable UART1 interrupts
    IFS1CLR=0x00000380;     // clear any existing events
    OpenUART1(UART_EN|UART_NO_PAR_8BIT|UART_1STOPBIT,UART_TX_ENABLE|UART_RX_ENABLE,51); //BaudRate = Fpb/(16*(U1BRG+1) ~= 9600 (9615)  BRG=51
}

void writeuart(unsigned int data)
{
    while(U1STAbits.TRMT == 0);
    U1TXREG = data;
}

unsigned int readuart()
{
    unsigned int data;

    if(U1STAbits.RIDLE == 1)
    {
        data = ReadUART1();
        U1STAbits.OERR = 0;
    }
    return data;
}