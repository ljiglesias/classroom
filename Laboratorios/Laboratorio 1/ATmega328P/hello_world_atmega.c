#define F_CPU 16000000UL
#define LED_PIN 5
#include <avr/io.h>
#include <util/delay.h>


int main(void)
{
    // Sets the direction of this pin to output
	DDRB |= (1 << LED_PIN);

    while (1) 
    {
    	// toggles the state of this pin
		PORTB ^= (1 << LED_PIN);
		// nusy waits the specified time
		_delay_ms(500);
    }
	return 1;
}

