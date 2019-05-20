#ifndef SI4432_CONFIG_H
#define	SI4432_CONFIG_H

void si4432config_gfsk_PER();               // 1,2 kbps, packet handler, GFSK
void si4432config_fsk_PER();
void si4432config_ook_PER();
void si4432config_ook_CW();
void si4432config_fsk_CW();
void si4432config_unmodulated_carrier();

#endif