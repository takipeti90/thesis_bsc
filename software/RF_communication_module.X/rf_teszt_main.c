#include "spi.h"
#include "uart.h"
#include "pic_config.h"
#include "si4432_config.h"
#include <plib.h>

unsigned int itstatus1=0;
unsigned int itstatus2=0;
unsigned int reg[127];
unsigned int i=0;
unsigned int uartIn = 0;
unsigned int packet_received = 0;
unsigned int CRC_error = 0;

void main()
{
    oscconfig();                                    // alap konfigurációk
    pinconfig();
    spiconfig();
    uartconfig();

////--------------------PACKET ERROR RATE------------------------
//
//    si4432config_gfsk_PER();
////    si4432config_fsk_PER();
////    si4432config_ook_PER();
//
//    nSEL = 1;
////    rx_state_PER();                                 // inicializálás után egyb?l RX módba kerül
//
//    while(1)
//    {
//        if(nIRQ == 0)                               // ha packet received vagy CRC error interrupt van
//        {
//            receive_data_PER();
//        }
//
//        uartIn = readuart();
//
//        if(uartIn == 's'||JOBB == 0)                // JOBB gomb vagy "s" UARTon send állapot, ZÖLD LED villog
//        {
//            uartIn = 0;
//            delaycpu();                             // 50 delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            delaycpu();
//            send_data_PER(0x68, 10000);
//            PORTClearBits(IOPORT_B, ZOLD);
//            rx_state_PER();
//        }
////-------------------------------------------------------------

//-----------------LESUGÁRZOTT TELJESÍTMÉNY------------------

//    si4432config_fsk_CW();
//    si4432config_ook_CW();
    si4432config_unmodulated_carrier();

    nSEL = 1;
    rx_state_PER();

    while(1)
    {
        if(nIRQ == 0)
        {
            receive_data_PER();
        }

        uartIn = readuart();

        if(uartIn == 's'||JOBB == 0)
        {
            uartIn = 0;
            CW();
            PORTClearBits(IOPORT_B, ZOLD);
            rx_state_PER();
        }
//-----------------------------------------------------------

        else if(uartIn == 'r')                      // kiírja UART-on az Si4432 regiszterek értékeit, PIROS villog
        {
            uartIn = 0;
            for(i=0;i<128;i++)
            {
                reg[i] = readspi(i);
                delaycpu(0xFFF);
                writeuart(reg[i]);
                delaycpu(0xFFF);
                PORTToggleBits(IOPORT_B, PIROS);
            }
            writeuart(0x00);writeuart(0x00);writeuart(0x00);writeuart(0x00);        // hogy meglegyen a 3 sor a terminalba
        }

        else if(uartIn == 'p')                      // kiírja UART-on az Si4432 regiszterek értékeit, PIROS villog
        {
            uartIn = 0;
            writeuart(packet_received);
            writeuart(CRC_error);
        }

        else if(uartIn == 'c')                      // config állapot, ZÖLD LED
        {
            uartIn = 0;
            PORTClearBits(IOPORT_B, PIROS|ZOLD);
            PORTSetBits(IOPORT_B, ZOLD);
            while(1)
            {
                uartIn = readuart();
                if(uartIn == 'e')
                    break;                          // ESC (ASCII), kilépés config állapotból
                else if(uartIn == 'g')
                    si4432config_gfsk_PER();       // FSK, no packet handler, 1,2 kbps, 2 byte payload
                else if(uartIn == 'f')
                    si4432config_fsk_CW();          // FSK, no packet handler, 1,2 kbps, CW
                else if(uartIn == 'o')
                    si4432config_ook_CW();          // OOK, no packet handler, 1,2 kbps, CW
            }
            uartIn = 0;                             // null (ASCII)
            PORTClearBits(IOPORT_B, ZOLD);
        }
    }
}