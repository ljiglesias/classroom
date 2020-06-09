/***************************************************
 * This is an example program to demonstrate the
 * successful implementation of the USART's
 * interrupt functions.
 *
 * Connect your developer board to a PC and configure
 * a terminal emulator with the appropriate baud rate.
 *
 * Hint: You can not connect your terminal to this board
 * and avrdude at the same time. Disconnect your terminal
 * software when loading a new program into the flash!
 *
 * This code is in the public domain.
 *
 ****************************************************/


// MCU Clock Speed - needed for delay.h


#include <msp430.h>
#include <string.h>


// Have a look at both the .h and the .c file, there is code missing.
#include "USART/USART_implement_me.h"



/* The main function */
int main(void)
{
	// You already lerned how to configure that button, remember?
	
	// Initialise the serial communication interface. Note that this now also sets up the interrupts!
	/* struct USART_configuration config_57600_8N1 = {57600, 8, 0, 1}; */ // You can use it

	USART_Init(/* Fill here*/);
	
	// This time you should also configure and enable(!) some interrupts.
	
	
	// Print a welcome message
	USART_Transmit_String("Please send some characters from your terminal.\r\n");
	
	
	while(1)
	{			
		// Your program will only ask *if* a string was received. If yes, it will display this string.
		// If not, it will just skip and do other stuff until it is time to ask again.		
		// Here you could do all kinds of other cool things. Remember, the step above
		// will be skipped in most iterations, so you have plenty of processing time here....
	}
}



// Add a ISR for a button here!