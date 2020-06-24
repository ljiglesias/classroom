/****************************************************************
 * Derechos de Autor (2020) Fernando Huanca <fjhuanca@uc.cl>
 * 
 * Desarrollado con fines educacionales en IEE2463-PUC de Chile.
 * 
 * Este archivo no puede ser copiado/distribuido sin la
 * autorización expresa de su autor.
 ****************************************************************/

#define F_CPU 16000000UL			// Definimos la frecuencia del clock.

#include <avr/io.h>
#include "uart_header.h"			//Incluímos el header con las funciones uart.

int main(void){
	struct uart_settings configuracion = {9600, 8, 0, 1};
		
	uart_init(configuracion);		//Iniciamos con la configuracion
	DDRB |= (1 << DDB1);			//Puerto LED (Función no relacionada a UART)
	
	uart_send('B');					//Enviamos caracter a caracter
	uart_send('i');
	uart_send('e');
	uart_send('n');
	uart_send('v');
	uart_send('e');
	uart_send('n');
	uart_send('i');
	uart_send('d');
	uart_send('o');
	uart_send('s');
	uart_send(' ');
	uart_send('a');
	uart_send(' ');
	uart_send('S');
	uart_send('E');
	uart_send('P');
	uart_send('!');
	while(1);
}


