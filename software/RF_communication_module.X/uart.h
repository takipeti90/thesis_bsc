#ifndef UART_H
#define	UART_H

void uartconfig();           //1 START, 8 DATA, NO PARITY, 1 STOP, 9615 BAUD
void writeuart(unsigned int data);
unsigned int readuart();

#endif	/* UART_H */