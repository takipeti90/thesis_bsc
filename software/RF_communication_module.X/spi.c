#include "spi.h"
#include "uart.h"
#include "pic_config.h"
#include <plib.h>

extern unsigned int itstatus1;
extern unsigned int itstatus2;
extern unsigned int packet_received;
extern unsigned int CRC_error;

void spiconfig()
{
    unsigned int data;

    SDI1R = 0b0100;                     // RPB8 (SDI1) 17.láb
    RPB13R = 0b0011;                    // SDO1 (RPB13) 24.láb

    IEC1CLR=0x00000070;                 // disable SPI1 interrupts
    SPI1CON = 0;                        // stops and resets SPI1
    data = SPI1BUF;                     // clear the receive buffer
    IFS1CLR=0x00000070;                 // clear any existing events
    SPI1BRG = 0;                        // Fsck = Fpbclk/(2*(SPIxBRG+1)) = 1 MHz     //199 = 20 kHz
    SPI1STATCLR = 0x40;                 // clear the overflow
    SPI1CON = 0x00008120;               // not frame mode, PBCLK, not enhanced buffer mode, sample at middle of input data, 8bit, master,SMP=0,CKE=1,CKP=0
}

void writespi(unsigned int addr, unsigned int data)
{
    unsigned int temp;

    nSEL = 0;
    putcSPI1(addr|0x80);
    temp = getcSPI1();
    SPI1STATCLR = 0x40;                 // clear the overflow
    putcSPI1(data);
    temp = getcSPI1();
    SPI1STATCLR = 0x40;                 // clear the overflow
    nSEL = 1;
}

unsigned int readspi(unsigned int addr)
{
    unsigned int data;

    nSEL = 0;
    putcSPI1(addr);
    data = getcSPI1();
    SPI1STATCLR = 0x40;                 // clear the overflow
    putcSPI1(0x00);
    data = getcSPI1();
    SPI1STATCLR = 0x40;                 // clear the overflow
    nSEL = 1;
    return data;
}

void CW()
{
    unsigned char i;
    
    writespi(0x08,0x08);                // auto TX

    while(1)
    {
        PORTToggleBits(IOPORT_B, ZOLD);
        for(i=0;i<64;i++)
        {
            writespi(0x7F,0xFF);
        }
        writespi(0x07,TX_MODE);         // enter TX mode
        if(BAL == 0)
            break;
    }
}

void send_data(unsigned int data)
{
    writespi(0x08,0x10);                // RX multi packet
//    writespi(0x72,0x50);                // frequency deviation = 50 kHz = AFC bandwidth

    writespi(0x3E,0x02);                // payload = 2 byte

    writespi(0x7F,data);                // FIFO = data
    writespi(0x7F,0xAA);                // FIFO = 0xAA

    writespi(0x05,0x04);                // enable packet sent interrupt only
    writespi(0x06,0x00);
    writespi(0x07,TX_MODE);             // enter TX mode        ~2ms míg feléled
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    while(nIRQ == 1);                   // wait until packet sent interrupt
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
}

void send_data_PER(unsigned int data, unsigned int packet_number)
{
    unsigned int i;

    for(i=0;i<packet_number;i++)
    {
        send_data(data);                // adat küldése rádión
        PORTToggleBits(IOPORT_B, ZOLD);
        writeuart(i);                   // kiírja, hogy hányadik csomagot küldi
        if(BAL == 0)
            return;
    }
}

void rx_state_PER()
{
//    writespi(0x08,0x12);                // RX multi packet
    writespi(0x08,0x10);                // RX multi packet
//    writespi(0x72,0xA0);                // frequency deviation = 150 kHz = AFC bandwidth

    writespi(0x07,RX_MODE);             // enter RX mode        ~2ms míg feléled

    writespi(0x05,0x03);                // CRC check & Received packet interrupt enable
    writespi(0x06,0x00);
    itstatus1 = readspi(0x03);          // clear interrupts
    itstatus2 = readspi(0x04);
}

void receive_data_PER()
{
    unsigned char i;
    unsigned char length = 0;
    unsigned int payload[64];

    itstatus1 = readspi(0x03);          // interrupt kiolvasása
    itstatus2 = readspi(0x04);

    if ((itstatus1 & 0x01) == 0x01)     // CRC error detected
    {
        writespi(0x07,READY_MODE);
        PORTToggleBits(IOPORT_B, PIROS);
        CRC_error++;
    }

    if ((itstatus1 & 0x02) == 0x02)     // valid packet received
    {
        writespi(0x07,READY_MODE);
        length = readspi(0x4B);         // Packet length beolvasása
        if(length == 2)                 // ha egy byte (ennyit küldünk)
        {
            for(i=0;i<length+1;i++)       // több byte kiolvasása
            {
                payload[i] = readspi(0x7F);
                if(i>0)
                    writeuart(payload[i]);
                PORTToggleBits(IOPORT_B, ZOLD);
            }
            packet_received++;
        }
    }
    rx_state_PER();
}