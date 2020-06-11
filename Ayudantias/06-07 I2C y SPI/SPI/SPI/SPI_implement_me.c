/***************************************************
 * Ayudantia 4: SPI
 * SPI - Card SD
 *
 * Author: Camila Turrieta :)
 * Reference: LAB 8 - 2019-1
 ****************************************************/
#include <avr/io.h>
#include "SPI_implement_me.h"

void SPI_Master_Init(void)
{
	/* Set MOSI and SCK output, all others input */

	//DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	DDRB |= (1 << PORTB3)|(1 << PORTB5);
	DDRB &= ~(1 << PORTB4);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR |= (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}

// This function transmits a single byte over the SPI bus.
//
// It does *not* control the CS line.
void SPI_Master_transmit_char(uint8_t data)
{
	/* Start transmission */
	SPDR = data;
	/* Wait for transmission complete */
	while(!(SPSR & (1<<SPIF)));
	
}

// This function receives a single byte over the SPI bus.
//
// This is very easy and short if you understood how SPI works.
// Hint: It is a *full duplex* bus!
char SPI_Master_receive_char(void)
{
	SPI_Master_transmit_char(0xFF);
	while(!(SPSR & (1<<SPIF)));
	return SPDR
}