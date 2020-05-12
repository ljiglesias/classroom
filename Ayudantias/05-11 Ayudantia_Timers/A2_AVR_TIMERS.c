/*
 * Ayudantía Timers
 *
 * Created: 09-05-2020 22:08:55
 * Authors : Javier Diaz - Pablo Orellana
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>

// Se definen puertos para display
#define COM_3 (1 << 0)
#define COM_2 (1 << 1)
#define COM_1 (1 << 2)
#define DP (1 << 7)
#define F (1 << 6)
#define A (1 << 5)
#define B (1 << 4)
#define G (1 << 3)
#define E (1 << 2)
#define C (1 << 1)
#define D (1 << 0)

// Se definen números para mostrar en display

#define cero A | B | C | D | E | F
#define uno B | C
#define dos A | B | D | E | G
#define tres A | B | C | D | G
#define cuatro B | C | F | G
#define cinco A | F | G | C | D
#define seis A | F | E | D | C | G
#define siete A | B | C
#define ocho A | B | C | D | E | F | G
#define nueve A | F | B | D | C | G

char numeros[10] = {cero, uno, dos, tres, cuatro, cinco, seis, siete, ocho, nueve};

// Enteros que permiten llevar cuenta del cronometro

volatile int unidad = 0; 
volatile int decena = 0; 
volatile int centena = 0; 
volatile int display = 0; 

// Determinar Velocidad de Cuenta Cronómetro

void Timer_1_Configuration(uint8_t freq){
	TCCR1B |= (1 << CS12) | (1 << WGM12); // Modo CTC, prescaler 256
	TIMSK1 |= (1 << OCIE1A); // Interrupcion de comparacion con registro OCR1A
	OCR1A |= (F_CPU/(freq*256)-1); //Definir frecuencia para velocidad del contador
}

// Determinar Frecuencia de Display

void Timer_0_Configuration(uint8_t freq){
	TCCR0A |= (1 << WGM01); // Modo CTC
	TCCR0B |= (1 << CS02); // prescaler 256
	TIMSK0 |= (1 << OCIE0A); // Interrupcion de comparacion con registro OCR1A
	OCR0A |= (F_CPU/(freq*256)-1); //Definir frecuencia para velocidad de pantalla display
}


int main(void)
{

    // Puerto D - Leds de cada Display

    DDRD |= 0xFF;
	PORTD |= 0xFF;

    // Puerto B - Compuertas de cada Display
	
	DDRB |= 0xFF;
	PORTB |= COM_2;
	PORTB |= COM_3;
	PORTB |= COM_1;
	
	sei(); //activar interrupciones 
	
	Timer_0_Configuration(500); // Display 500 Hz
	Timer_1_Configuration(10); // Cronómetro 10 Hz
	
	while (1){
    }
}

//Rutina de interrupcion para aumentar cuenta en cronómetro

ISR(TIMER1_COMPA_vect){
	
	unidad ++;
	if(unidad==10){
		unidad = 0;
		decena ++;
	}
	if (decena==10){
		unidad = 0;
		centena ++;
	}	
	if (centena == 10){
		centena = 0;
	}
	
}

//Rutina de interrupcion para mostrar numero en pantalla

ISR(TIMER0_COMPA_vect){
	if (display == 0){
		PORTB = (COM_3);
		PORTD = ~(numeros[unidad]) | (DP);
	}
	
	else if (display == 1){	
		PORTB = COM_2;
		PORTD = ~(numeros[decena]);
		PORTD &= ~(DP);
	}
		
	else if (display == 2){	
		PORTB = COM_1;
		PORTD = ~(numeros[centena]) | (DP);
	}
	display++;
	if(display==3){
		display = 0;
	}
}