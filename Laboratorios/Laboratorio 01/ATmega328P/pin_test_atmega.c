#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	// Define los pines del puerto B a SALIDA
	DDRB |= 0x3F;
	// Define los pines del puerto C a SALIDA
	DDRC |= 0x3F;
	// Define los pines del puerto D a SALIDA
	DDRD |= 0xFF;

	//Set pines del puerto B a HIGH
	PORTB |= 0x3F;
	//Set pines del puerto C a HIGH
	PORTC |= 0x3F;
	//Set pines del puerto D a HIGH
	PORTD |= 0xFF;
	//Set pines del puerto D en HIGH
	while (1)
	{
	}
	return 0;
}