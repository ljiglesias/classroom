/***************************************************
 * Ayudantia 4: SPI
 * SPI - Card SD
 *
 * Author: Camila Turrieta :)
 * Reference: LAB 8 - 2019-1
 ****************************************************/

#ifndef _SPI_IMPLEMENT_ME_H_
#define _SPI_IMPLEMENT_ME_H_

#include <stdint.h>
#include <stdbool.h>

// The initialisation function. Call it once from your main() program before
// issuing any SPI commands with the functions below!
void SPI_Master_Init(void);

// The transmit function. Takes one character and transmits it over SPI.
// Note that it does NOT control the Chip Select (CS) line!
void SPI_Master_transmit_char(uint8_t data);

// This function receives a single byte over the SPI bus.
char SPI_Master_receive_char(void);


#endif // _SPI_IMPLEMENT_ME_H_