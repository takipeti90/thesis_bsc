#include "si4432_config.h"
#include "spi.h"
#include "uart.h"
#include "pic_config.h"
#include <plib.h>

extern unsigned int itstatus1;
extern unsigned int itstatus2;

void si4432config_gfsk_PER()
{
    writespi(0x07,0x80);                // Software reset
    while(nIRQ == 1);
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    writespi(0x05,0x00);                // disable interrupt
    writespi(0x06,0x00);                // disable interrupt
    writespi(0x07,READY_MODE);          // IC on ready mode
    writespi(0x09,0x78);                // load capacitance = 12 pF
    // GPIO driving capability 0, pullup resistor off
    writespi(0x0B,0x14);                // GPIO0 = RX Data (output)
    writespi(0x0C,0x19);                // GPIO1 = valid preamble (output)           // 0x1B(Sync Word detected)
    writespi(0x0D,0x1A);                // GPIO2 = invalid preamble (output)         // 0x1C(RSSI over treshold)
    writespi(0x27,0x78);                // RSSI treshold = -60 dBm körüli
// Bandwidth
    writespi(0x1C,0xAB);                // IF Filter bandwidth
    writespi(0x1D,0x40);                // enable AFC
    writespi(0x20,0xE2);                // ------
    writespi(0x21,0x80);
    writespi(0x22,0x0D);
    writespi(0x23,0x1B);                // clock recovery
    writespi(0x24,0x00);
    writespi(0x25,0x03);                // -----
// Packet handling
    writespi(0x30,0xAC);                // RX/TX PH, CRC(CCIT) only data, MSB first, no data whitening, no inversion
    writespi(0x32,0x00);                // no Broadcast (FFh) || 0 byte header check
    writespi(0x33,0x06);                // 0 byte header, 4 byte sync, variable packet length in header
    writespi(0x34,0x0A);                // preamble length: 80 bits
    writespi(0x35,0x42);                // preamble check: 32 bits
    writespi(0x36,0xD7);                // 4 byte Sync Word
    writespi(0x37,0x93);
    writespi(0x38,0xC4);
    writespi(0x39,0x61);
    writespi(0x3A,0xFF);                // 4 byte Header
    writespi(0x3B,0xFF);
    writespi(0x3C,0xFF);
    writespi(0x3D,0xFF);
    writespi(0x3F,0xFF);                // 4 byte Header for check
    writespi(0x40,0xFF);
    writespi(0x41,0xFF);
    writespi(0x42,0xFF);
    writespi(0x43,0x00);                // all Header disabled
    writespi(0x44,0x00);
    writespi(0x45,0x00);
    writespi(0x46,0x00);
// TX power, data rate, modulation, frequency settings
    writespi(0x6D,0x00);                // TX Power = 00-11dBm, 01-14dBm, 02-17dBm, 03-20dBm
    writespi(0x6E,0x09);                // data rate = 1,2 kbps
    writespi(0x6F,0xD5);
    writespi(0x70,0x2A);                // manchester enable
    writespi(0x71,0x23);                // FIFO, GFSK modulation
    writespi(0x72,0x50);                // frequency deviation = 50 kHz + AFC bandwidth
    writespi(0x73,0x00);                // frequency offset = 0 Hz
    writespi(0x74,0x00);
    writespi(0x75,0x53);                // carrier frequency = 433 MHz
    writespi(0x76,0x4B);
    writespi(0x77,0x00);
}

void si4432config_fsk_PER()
{
    writespi(0x07,0x80);                // Software reset
    while(nIRQ == 1);
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    writespi(0x05,0x00);                // disable interrupt
    writespi(0x06,0x00);                // disable interrupt
    writespi(0x07,READY_MODE);          // IC on ready mode
    writespi(0x09,0x78);                // load capacitance = 12 pF
    // GPIO driving capability 0, pullup resistor off
    writespi(0x0B,0x14);                // GPIO0 = RX Data (output)
    writespi(0x0C,0x19);                // GPIO1 = valid preamble (output)           // 0x1B(Sync Word detected)
    writespi(0x0D,0x1A);                // GPIO2 = invalid preamble (output)         // 0x1C(RSSI over treshold)
    writespi(0x27,0x78);                // RSSI treshold = -60 dBm körüli
// Bandwidth
    writespi(0x1C,0xAB);                // IF Filter bandwidth
    writespi(0x1D,0x40);                // enable AFC
    writespi(0x20,0xE2);                // ------
    writespi(0x21,0x80);
    writespi(0x22,0x0D);
    writespi(0x23,0x1B);                // clock recovery
    writespi(0x24,0x00);
    writespi(0x25,0x03);                // -----
// Packet handling
    writespi(0x30,0xAC);                // RX/TX PH, CRC(CCIT) only data, MSB first, no data whitening, no inversion
    writespi(0x32,0x00);                // no Broadcast (FFh) || 0 byte header check
    writespi(0x33,0x06);                // 0 byte header, 4 byte sync, variable packet length in header
    writespi(0x34,0x0A);                // preamble length: 80 bits
    writespi(0x35,0x42);                // preamble check: 32 bits
    writespi(0x36,0xD7);                // 4 byte Sync Word
    writespi(0x37,0x93);
    writespi(0x38,0xC4);
    writespi(0x39,0x61);
    writespi(0x3A,0xFF);                // 4 byte Header
    writespi(0x3B,0xFF);
    writespi(0x3C,0xFF);
    writespi(0x3D,0xFF);
    writespi(0x3F,0xFF);                // 4 byte Header for check
    writespi(0x40,0xFF);
    writespi(0x41,0xFF);
    writespi(0x42,0xFF);
    writespi(0x43,0x00);                // all Header disabled
    writespi(0x44,0x00);
    writespi(0x45,0x00);
    writespi(0x46,0x00);
// TX power, data rate, modulation, frequency settings
    writespi(0x6D,0x00);                // TX Power = 00-11dBm, 01-14dBm, 02-17dBm, 03-20dBm
    writespi(0x6E,0x09);                // data rate = 1,2 kbps
    writespi(0x6F,0xD5);
    writespi(0x70,0x2A);                // manchester enable
    writespi(0x71,0x22);                // FIFO, FSK modulation
    writespi(0x72,0x50);                // frequency deviation = 50 kHz + AFC bandwidth
    writespi(0x73,0x00);                // frequency offset = 0 Hz
    writespi(0x74,0x00);
    writespi(0x75,0x53);                // carrier frequency = 433 MHz
    writespi(0x76,0x4B);
    writespi(0x77,0x00);
}

void si4432config_ook_PER()
{
    writespi(0x07,0x80);                // Software reset
    while(nIRQ == 1);
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    writespi(0x05,0x00);                // disable interrupt
    writespi(0x06,0x00);                // disable interrupt
    writespi(0x07,READY_MODE);          // IC on ready mode
    writespi(0x09,0x78);                // load capacitance = 12 pF
    // GPIO driving capability 0, pullup resistor off
    writespi(0x0B,0x14);                // GPIO0 = RX Data (output)
    writespi(0x0C,0x19);                // GPIO1 = valid preamble (output)           // 0x1B(Sync Word detected)
    writespi(0x0D,0x1A);                // GPIO2 = invalid preamble (output)         // 0x1C(RSSI over treshold)
    writespi(0x27,0x78);                // RSSI treshold = -60 dBm körüli
// Bandwidth
    writespi(0x1C,0xC1);                // IF Filter bandwidth
    writespi(0x1D,0x40);                // enable AFC
    writespi(0x20,0x39);                // ------
    writespi(0x21,0x20);
    writespi(0x22,0x34);
    writespi(0x23,0x6E);                // clock recovery
    writespi(0x24,0x00);
    writespi(0x25,0x6B);                // -----
// Packet handling
    writespi(0x30,0xAC);                // RX/TX PH, CRC(CCIT) only data, MSB first, no data whitening, no inversion
    writespi(0x32,0x00);                // no Broadcast (FFh) || 0 byte header check
    writespi(0x33,0x06);                // 0 byte header, 4 byte sync, variable packet length in header
    writespi(0x34,0x0A);                // preamble length: 80 bits
    writespi(0x35,0x42);                // preamble check: 32 bits
    writespi(0x36,0xD7);                // 4 byte Sync Word
    writespi(0x37,0x93);
    writespi(0x38,0xC4);
    writespi(0x39,0x61);
    writespi(0x3A,0xFF);                // 4 byte Header
    writespi(0x3B,0xFF);
    writespi(0x3C,0xFF);
    writespi(0x3D,0xFF);
    writespi(0x3F,0xFF);                // 4 byte Header for check
    writespi(0x40,0xFF);
    writespi(0x41,0xFF);
    writespi(0x42,0xFF);
    writespi(0x43,0x00);                // all Header disabled
    writespi(0x44,0x00);
    writespi(0x45,0x00);
    writespi(0x46,0x00);
// TX power, data rate, modulation, frequency settings
    writespi(0x6D,0x00);                // TX Power = 00-11dBm, 01-14dBm, 02-17dBm, 03-20dBm
    writespi(0x6E,0x09);                // data rate = 1,2 kbps
    writespi(0x6F,0xD5);
    writespi(0x70,0x2A);                // manchester enable
    writespi(0x71,0x21);                // FIFO, OOK modulation
    writespi(0x72,0x50);                // frequency deviation = 50 kHz + AFC bandwidth
    writespi(0x73,0x00);                // frequency offset = 0 Hz
    writespi(0x74,0x00);
    writespi(0x75,0x53);                // carrier frequency = 433 MHz
    writespi(0x76,0x4B);
    writespi(0x77,0x00);
}

void si4432config_ook_CW()
{
    writespi(0x07,0x80);                // Software reset
    while(nIRQ == 1);
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    writespi(0x05,0x00);                // disable interrupt
    writespi(0x06,0x00);                // disable interrupt
    writespi(0x07,READY_MODE);          // IC on ready mode
    writespi(0x09,0x78);                // load capacitance = 12 pF
    writespi(0x27,0x78);                // RSSI treshold = -60 dBm körüli
// Bandwidth
    writespi(0x1C,0xD1);                // RX bandwidth = 200 kHz
    writespi(0x1D,0x40);                // enable AFC
    writespi(0x20,0x39);                // ------
    writespi(0x21,0x20);
    writespi(0x22,0x68);
    writespi(0x23,0xDc);                // clock recovery
    writespi(0x24,0x00);
    writespi(0x25,0x6B);                // -----
// Packet handling
    writespi(0x30,0x00);                // no packet handler, no inversion, MSB first
    writespi(0x33,0x0E);                // 4 byte sync
    writespi(0x34,0x00);                // preamble length: 0 bits
    writespi(0x35,0x02);                // preamble check: 0 bits
    writespi(0x36,0xFF);                // the 4 byte Sync Word
    writespi(0x37,0xFF);
    writespi(0x38,0xFF);
    writespi(0x39,0xFF);
// TX power, data rate, modulation, frequency settings
    writespi(0x6D,0x00);                // TX Power = 00-11dBm, 01-14dBm, 02-17dBm, 03-20dBm                                                                                                          dBm
    writespi(0x6E,0x09);                // data rate = 1,2 kbps
    writespi(0x6F,0xD5);
    writespi(0x70,0x28);                // manchester disable
    writespi(0x71,0x21);                // FIFO, OOK modulation
    writespi(0x72,0x50);                // frequency deviation = 10 kHz + AFC bandwidth
    writespi(0x73,0x00);                // frequency offset = 0 Hz
    writespi(0x74,0x00);
    writespi(0x75,0x53);                // carrier frequency = 500 MHz
    writespi(0x76,0x4B);
    writespi(0x77,0x00);
}

void si4432config_fsk_CW()
{
    writespi(0x07,0x80);                // Software reset
    while(nIRQ == 1);
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    writespi(0x05,0x00);                // disable interrupt
    writespi(0x06,0x00);                // disable interrupt
    writespi(0x07,READY_MODE);          // IC on ready mode
    writespi(0x08,0x10);                // RX multi packet enable
    writespi(0x09,0x78);                // load capacitance = 12 pF
// GPIO driving capability 0, pullup resistor off
    writespi(0x0B,0x14);                // GPIO0 = RX Data (output)
    writespi(0x0C,0x19);                // GPIO1 = valid preamble (output)           // 0x1B(Sync Word detected)
    writespi(0x0D,0x1A);                // GPIO2 = invalid preamble (output)         // 0x1C(RSSI over treshold)
    writespi(0x27,0x78);                // RSSI treshold = -60 dBm körüli
// Bandwidth
    writespi(0x1C,0x1E);                // IF Filter bandwidth
    writespi(0x1D,0x40);                // enable AFC
    writespi(0x20,0x83);                // ------
    writespi(0x21,0xC0);
    writespi(0x22,0x13);
    writespi(0x23,0xA9);                // clock recovery
    writespi(0x24,0x00);
    writespi(0x25,0x02);                // -----
// Packet handling
    writespi(0x30,0x00);                // no packet handler, no inversion, MSB first
    writespi(0x33,0x0E);                // 4 byte sync
    writespi(0x34,0x00);                // preamble length: 0 bits
    writespi(0x35,0x02);                // preamble check: 0 bits
    writespi(0x36,0xFF);                // the 4 byte Sync Word
    writespi(0x37,0xFF);
    writespi(0x38,0xFF);
    writespi(0x39,0xFF);
// TX power, data rate, modulation, frequency settings
    writespi(0x6D,0x00);                // TX Power = 00-11dBm, 01-14dBm, 02-17dBm, 03-20dBm                                                                                                             dBm
    writespi(0x6E,0x09);                // data rate = 1,2 kbps
    writespi(0x6F,0xD5);
    writespi(0x70,0x28);                // manchester disable
    writespi(0x71,0x22);                // FIFO, FSK modulation
    writespi(0x72,0x50);                // frequency deviation = 50 kHz + AFC bandwidth
    writespi(0x73,0x00);                // frequency offset = 0 Hz
    writespi(0x74,0x00);
    writespi(0x75,0x53);                // carrier frequency = 433 MHz
    writespi(0x76,0x4B);
    writespi(0x77,0x00);
}

void si4432config_unmodulated_carrier()
{
    writespi(0x07,0x80);                // Software reset
    while(nIRQ == 1);
    itstatus1 = readspi(0x03);
    itstatus2 = readspi(0x04);
    writespi(0x05,0x00);                // disable interrupt
    writespi(0x06,0x00);                // disable interrupt
    writespi(0x07,READY_MODE);          // IC on ready mode
    writespi(0x09,0x78);                // load capacitance = 12 pF
    writespi(0x27,0x78);                // RSSI treshold = -60 dBm körüli
// Bandwidth
    writespi(0x1C,0xD1);                // RX bandwidth = 200 kHz
    writespi(0x1D,0x40);                // enable AFC
    writespi(0x20,0x39);                // ------
    writespi(0x21,0x20);
    writespi(0x22,0x68);
    writespi(0x23,0xDc);                // clock recovery
    writespi(0x24,0x00);
    writespi(0x25,0x6B);                // -----
// Packet handling
    writespi(0x30,0x00);                // no packet handler, no inversion, MSB first
    writespi(0x33,0x0E);                // 4 byte sync
    writespi(0x34,0x00);                // preamble length: 0 bits
    writespi(0x35,0x02);                // preamble check: 0 bits
    writespi(0x36,0xFF);                // the 4 byte Sync Word
    writespi(0x37,0xFF);
    writespi(0x38,0xFF);
    writespi(0x39,0xFF);
// TX power, data rate, modulation, frequency settings
    writespi(0x6D,0x00);                // TX Power = 00-11dBm, 01-14dBm, 02-17dBm, 03-20dBm                                                                                                          dBm
    writespi(0x6E,0x09);                // data rate = 1,2 kbps
    writespi(0x6F,0xD5);
    writespi(0x70,0x28);                // manchester disable
    writespi(0x71,0x20);                // FIFO, unmodulated carrier
    writespi(0x72,0x50);                // frequency deviation = 10 kHz + AFC bandwidth
    writespi(0x73,0x00);                // frequency offset = 0 Hz
    writespi(0x74,0x00);
    writespi(0x75,0x53);                // carrier frequency = 500 MHz
    writespi(0x76,0x4B);
    writespi(0x77,0x00);
}