/***********************************************************************
* FILENAME :        NOMBRE_PROYECTO.c          
*
* DESCRIPTION :
*       Codigo base que genera una PWM a un con un duty cycle especifico
*
* NOTES :
*       Notas a considerar de su codigo
*
* AUTHOR :   Felipe Sanchez Varas        
* START DATE :    24 Mar 20
*
* CHANGES :
*            Nombre Apellido Alumno
*
* VERSION 1.0
* 	Codigo inicial para SEP, LAB 03
*
* VERSION 2.0
* 	Cambios implementados por el alumno
**/

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int freq = 50; // Hz
int duty = 50;
int count = 0;

int main(void)
{	
  	/* Inicio de configuración de PWM con Timers */ 
  
	cli();

  	// Se habilita interrupccion externa de Falling Edge
	EICRA |= (1 << ISC01); 
  	EIMSK |= (1 << INT0);

  	// Set PWM con timers
  	DDRD |= (1 << DDD0); // Set PD0
  
  	// Modo de operación Timer 1
  	// Rellenar modo de operación : _____________
  	TCCR1A &= ~(1 << WGM10);		
	TCCR1A &=~ (1 << WGM11);
  	// Rellenar modo de operación : _____________
	TCCR1B |= (1 << WGM12);
	TCCR1B &=~ (1 << WGM13);

	// Modo de operacion Timer 2
  	// Rellenar modo de operación : _____________
	TCCR0A &= ~(1<<WGM00);
	TCCR0A |= (1<<WGM01);
	TCCR0B &= ~(1<<WGM02);

  	// Rellenar qué hace este registro
  	// _______________________________  
  	OCR1A = (F_CPU/1024/freq) -1;	

  	// Rellenar qué hace este registro
  	// _______________________________ 
  	OCR0A = ((F_CPU/1024/freq)-1)/100;

  	// Habilitar interrupcion Timer 1
  	TIMSK1 |= (1 << OCIE1A); 

  	// Habilitar interrupcion Timer 2
  	TIMSK0 |= (1 << OCIE0A);

  	// Resetear contadores 
  	TCNT1 = 0x0000;
  	TCNT0 = 0x00;

  	// Habilitar interrupciones 
  	sei();
  	
  	// Se establece frecuencia Timer 1
  	// ¿Que preescaler se designó aqui ? 
  	// ___________________
	TCCR1B |= (1<<CS10);		
	TCCR1B &= ~(1<<CS11);
	TCCR1B |= (1<<CS12);

	// Se estable frecuencia Timer 2
  	// ¿Que preescaler se designó aqui ? 
  	// ___________________
  
	TCCR0B|=(1<<CS02);
	TCCR0B&=~(1<<CS01);
	TCCR0B|=(1<<CS00);

  	/* Agregar configuracion de ADC */ 
  
	while(1){
      /* 
      Agregar control de la informacion obtenida en 
      ADC para así poder variar la intensidad del LED, 
      es decir, cambiar el duty cycle.
      */ 
      
	}

}

// Interrupción que realiza comparación 
/* Lo inferior no debería ser modificado */
ISR (TIMER0_COMPA_vect){
	if (count < 100) count++;
	if (count < duty) PORTD= (1 << PORTD0);
	else PORTD &= ~(1 << PORTD0);
}


ISR (TIMER1_COMPA_vect)
{
  count = 0;
}