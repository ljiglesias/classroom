/***************************************************
 * This is an example program on how to use an SD
 * card (with socket) on the the Atmega328P.
 * Use e.g. the 1.8" color TFT LCD display PCB from
 * Adafruit Industries (it has a µSD card socket on
 * its back) with an Atmel ATmega328P Xplained mini
 * developer board.
 *
 * 
 * Note that some parts of this code are inspired by
 * and based on the example programs coming with the
 * PFF library.
 * 
 * This code is in the public domain.
 * 
 ****************************************************/


// MCU Clock Speed - needed for delay.h
#define F_CPU	16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


#include "USART/USART_implement_me.h"
#include "PetitFatFilesystem/PetitFS.h"


// UART configuration
#define BAUD	57600					// serial communication baud rate
#define UBRR_VALUE F_CPU/16/BAUD-1



/* A simple helper function to stop in case of some error */
void errorHalt(char* msg) {
	USART_Transmit_String("Error: ");
	USART_Transmit_String(msg);
	USART_Transmit_String("\n");
	while(1);
}



/* The main function */
int main(void)
{
  
	FATFS fs;     		/* File system structure */
	uint8_t buf[32];	/* Buffer for card access */
	UINT nr;			/* Used for various file access functions. */
	
	
	// Initialises the serial communication interface
	USART_Init(UBRR_VALUE);

	
	// Welcome message
	USART_Transmit_String("Hello! This is the SD card test.\n");
  
	// Initialise SD and file system.
	USART_Transmit_String("Trying to mount the SD card's file system: ");
	if (pf_mount(&fs)) errorHalt("pf_mount");
	USART_Transmit_String("success.\n");
	
	// Open read test file.
	USART_Transmit_String("Trying to open a text file for reading: ");
	if (pf_open("SEPtest.txt")) errorHalt("pf_open");
	USART_Transmit_String("success.\n");
	
	// Print test file to the serial interface.
	USART_Transmit_String("Here is the file content:\n");
	USART_Transmit_String("\n-----------------------------------------------\n");
	while (1) {
	  if (pf_read(buf, sizeof(buf), &nr)) errorHalt("pf_read");
	  if (nr == 0) break;
	  for(uint8_t i=0; i<nr; i++)
	  {
	      USART_Transmit_char(buf[i]);
	  }
	}
	
	USART_Transmit_String("\n-----------------------------------------------\n\n\n");
	
	
	
	// Open write test file.
	USART_Transmit_String("Trying to open a text file for writing: ");
	if (pf_open("writeMe.txt")) errorHalt("pf_open");
	USART_Transmit_String("success.\n");
	
	// Set read/write pointer to beginning of file.
	USART_Transmit_String("Going to beginning of file: ");
	if (pf_lseek(0)) errorHalt("pf_lseek");
	USART_Transmit_String("success.\n");
	
	// Write data and finish the transaction.
	USART_Transmit_String("Writing some data to the file: ");
	char message[] = "If this message does not appear in your text file, you failed to read the PFF documentation. Read about the use of pf_write() there!";
	if (pf_write(message, strlen(message), &nr)) errorHalt("pf_write while writing the file content");
	if (pf_write(0, 0, &nr)) errorHalt("pf_write while closing the file.");
	USART_Transmit_String("success.\n");
	
	
	
	// Open write test file.
	USART_Transmit_String("Trying to open another text file for writing more: ");
	if (pf_open("writeMe2.txt")) errorHalt("pf_open");
	USART_Transmit_String("success.\n");
	
	// Set read/write pointer to beginning of file.
	USART_Transmit_String("Going to beginning of file: ");
	if (pf_lseek(0)) errorHalt("pf_lseek");
	USART_Transmit_String("success.\n");
	
	// Receive a message over USART
	USART_Transmit_String("Please type a short message and press enter. ");
	USART_Receive_String(message, strlen(message));
	
	// Write it to the file and finish the transaction.
	USART_Transmit_String("Writing message to the file: ");
	if (pf_write(message, strlen(message), &nr)) errorHalt("pf_write while writing the file content");
	if (pf_write(0, 0, &nr)) errorHalt("pf_write while closing the file.");
	USART_Transmit_String("success.\n");
	USART_Transmit_String("\n\n<---- The SD card test is done! ---->\n\n");
	
	
	
	// Play dead
	while(1);
}


