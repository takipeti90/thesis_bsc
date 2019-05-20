#ifndef SPI_H
#define	SPI_H

// Si4432
#define READY_MODE      0x01
#define TX_MODE         0x09
#define RX_MODE         0x05
#define nSEL            PORTBbits.RB9
#define nIRQ            PORTBbits.RB7           // ha az Si4432 van


void spiconfig();
void writespi(unsigned int addr, unsigned int data);
unsigned int readspi(unsigned int addr);
//------CW jel-------------
void CW();
//-------------------------
//-------PER---------------
void send_data(unsigned int data);
void send_data_PER(unsigned int data, unsigned int packet_number);
void rx_state_PER();
void receive_data_PER();
//-------------------------

#endif	/* SPI_H */