/****************************************************************
 * Derechos de Autor (2020) Fernando Huanca <fjhuanca@uc.cl>
 * 
 * Desarrollado con fines educacionales en IEE2463-PUC de Chile.
 * 
 * Este archivo no puede ser copiado/distribuido sin la
 * autorización expresa de su autor.
 ****************************************************************/


#define F_CPU 16000000UL
#include <avr/io.h>
#include "uart_header.h"

void uart_init(struct uart_settings settings){
	uint16_t UBRR = (F_CPU/16/settings.baudrate - 1);	//Definimos el valor para el registro de baud rate.
	UBRR0L = UBRR;										//Asignamos los 8 bits menos significativos.
	UBRR0H = (UBRR >> 8);								//Asignamos los 8 bits más significativos.
	
	switch(settings.databits){
		case 8:
			UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);		//0b011 -> Tamaño data frame (8-bit)
			break;
			
		default:
			break;
	}
	
	switch(settings.stopbits){
		case 1:
			UCSR0C &= ~(1 << USBS0);					//1 stop bit
			break;
			
		default:
			break;
	}

	switch(settings.parity){
		case 0:
			UCSR0C &= ~(1 << UPM01) & ~(1 << UPM00);	//0b00 -> Sin bit de paridad
			break;
		
		default:
			break;
	}
	
	
	UCSR0C &= ~(1 << UMSEL01) & ~(1 << UMSEL00);		//0b00 -> Modo asíncrono (UART)
	
	UCSR0B = (1 << TXEN0);								//Se habilita la transmisión
}

void uart_send(uint8_t character){
	PORTB |= (1 << PORTB1);
	
	while (!(UCSR0A && (1 << TXC0)));			//Se espera mientras haya alguna transmisión en curso.
	UDR0 = character;							//Se asigna el caracter a enviar en el registro
												//de transmisión.	
	PORTB &= ~(1 << PORTB1);
}
