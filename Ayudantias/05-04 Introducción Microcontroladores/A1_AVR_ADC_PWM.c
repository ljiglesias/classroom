/*
 * name: Ayudantia #1 ADC y PWM
 *
 * author: 
 *      Camila Turrieta
 *
 * Microcontroller:
 * 		ATMEGA328P
 */

#define F_CPU 16000000 //16MHz
#include <avr/io.h>
#include <util/delay.h>

void Config_ADC(void);
void Config_Timer(void);
void ADC_conversion(void);

int main(void)
{
    Config_ADC();
	Config_Timer();
	
	//Configuracion pines: output pwm
	DDRD   |=  (1 << DDD6); 
	
	//Pin para debuguear 
	DDRD   |=  (1 << DDD5); 
	PORTD  |=  (1 << PORTD5); 
	
	//Variables auxiliares
	int duty = 0;
	float ADC_value = 0.0;
	float aux = 0.0;

	
    while (1) 
    {
		ADC_conversion();
		
		// Valor del ADC a float
		ADC_value = (float) ADC;
		
		//Linealizacion
		aux = ADC_value*255/671;
		
		//Conversion del valor a numero entero
		duty = (int) aux;
		
		//Debuguear
		if (duty > 255)
		{
			PORTD  &=  ~(1 << PORTD5); 
		}
		
		//Valor para comparar con el timer
		OCR0A = duty;
		
    }
}

// Funciones



// Configuracion del ADC de 10 bits
void Config_ADC(void)
{
	//  Voltage de referencia interno 
	// y pin de lectura PC0 (MUX3:0 = 0)
	ADMUX |= (1 << REFS0);
	//Deshabilitar funcion I/0 PC0
	DIDR0 |= (1 << ADC0D);
	// Prescaler: 128
	ADCSRA |= (1 << ADPS2)|(1 << ADPS1)|(1 << ADPS0);

	//Modo de operacion: single conversion
		//Enable
		//ADCSRA |= (1 << ADEN);
		//Start conversion
		//ADCSRA |= (1 << ADSC);
}

void ADC_conversion(void)
{
	//Habilitar conversion e iniciar
	ADCSRA |= (1 << ADSC)|(1 << ADEN);
	
	//Esperar a que la conversion este lista
	while((ADCSRA & (1<< ADSC)));
	
	//Deshabilitar
	ADCSRA &= ~(1 << ADEN);
}

// Configuracion de TIMER para PWM
void Config_Timer(void)
{
	//Modo de operacion: Fast PWM Mode
	TCCR0A |= (1 << COM0A1)|(1 <<WGM01)|(1 <<WGM00);
	
	//Comparar TCNT0 con OCR0A
	TIMSK0 |= (1 << OCIE0A);
	
	//Prescaler: 1024
	TCCR0B |= (1 << CS02)|(1 << CS00);
	
	//Comparador con TCNT0
	OCR0A = 255;
}

