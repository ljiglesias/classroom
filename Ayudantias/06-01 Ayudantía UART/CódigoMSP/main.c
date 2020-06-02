/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * receive functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate
 * in order to see the test message below.
 *
 * Hint: Disconnect your terminal software when loading
 * a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************
 * Codigo base Laboratorio 5 SEP
 * Codigo modificado por: Jose Gutierrez Molina
 * Fecha 28-05-2020
 ****************************************************/

#include <msp430.h>

//Incluimos la libreria UART. *Formalidad: crear librerias para funciones que utilicen perifericos en especifico.
#include "USART_implement_me.h"


/* The main function */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD;               //Detiene el watchdog

    // Initialise the serial communication interface
    //Configuracion de ejemplo UART - 9600baudrate-8bits de datos-parity bit deshabilitado-1 stop bit
    struct USART_configuration config_9600_8N1 = {9600, 8, 0, 1};
    USART_Init(config_9600_8N1);           //llamamos a la funcion de inicializacion y le entregamos como argumento una
                                            //configuracion deseada.

    //Welcome message
    //USART_Transmit_String("Ayudantia UART - MSP430.\r\n");    //Esta funcion haria mas eficiente la transmision
                                                                //de strings
    USART_Transmit_char('A');
    USART_Transmit_char('y');
    USART_Transmit_char('u');
    USART_Transmit_char('d');
    USART_Transmit_char('a');
    USART_Transmit_char('n');
    USART_Transmit_char('t');
    USART_Transmit_char('i');
    USART_Transmit_char('a');
    USART_Transmit_char(' ');
    USART_Transmit_char('U');
    USART_Transmit_char('A');
    USART_Transmit_char('R');
    USART_Transmit_char('T');
    USART_Transmit_char('-');
    USART_Transmit_char('M');
    USART_Transmit_char('S');
    USART_Transmit_char('P');
    USART_Transmit_char('4');
    USART_Transmit_char('3');
    USART_Transmit_char('0');
    USART_Transmit_char('.');
    USART_Transmit_char('\r');
    USART_Transmit_char('\n');


    while(1)
    {
        //Show the received character
        //El programa espera a que enviemos un caracter por el terminal, que luego es recibido por UART.
        //Luego, se transmite por UART el siguiente mensaje: "Received an: 'caracter recibido'."
        //Y dado que estamos en un ciclo while, se repite el ciclo a medida que se envia caracteres por el terminal.
        char c = USART_Receive_char();
        USART_Transmit_char('R');
        USART_Transmit_char('e');
        USART_Transmit_char('c');
        USART_Transmit_char('e');
        USART_Transmit_char('i');
        USART_Transmit_char('v');
        USART_Transmit_char('e');
        USART_Transmit_char('d');
        USART_Transmit_char(' ');
        USART_Transmit_char('a');
        USART_Transmit_char('n');
        USART_Transmit_char(':');
        USART_Transmit_char(' ');

        USART_Transmit_char(c);

        USART_Transmit_char('.');
        USART_Transmit_char('\r');
        USART_Transmit_char('\n');
    }
}


