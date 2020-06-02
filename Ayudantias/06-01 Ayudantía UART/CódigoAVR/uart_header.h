/****************************************************************
 * Derechos de Autor (2020) Fernando Huanca <fjhuanca@uc.cl>
 * 
 * Desarrollado con fines educacionales en IEE2463-PUC de Chile.
 * 
 * Este archivo no puede ser copiado/distribuido sin la
 * autorización expresa de su autor.
 ****************************************************************/

#include <stdint.h>

struct uart_settings{
	uint16_t baudrate;
	uint8_t databits;
	uint8_t parity;
	uint8_t stopbits;
};

void uart_init(struct uart_settings settings);

void uart_send(uint8_t data );
