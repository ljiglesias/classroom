/***************************************************
 * Ayudantia 4: SPI
 * SPI - Card SD
 *
 * Author: Camila Turrieta :)
 * Reference: LAB 8 - 2019-1
 ****************************************************/

#define F_CPU	16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "USART/USART_implement_me.h"
#include "PetitFatFilesystem/PetitFS.h"
#include "SPI/SPI_implement_me.h"

void errorHalt(char* msg);
int Menu(void);
void text_read(void);
void read_all(void);
void write(void);
void init_syst(void);

/* The main function */
int main(void)
{
// Configuration 
	
	// UART
	struct USART_configuration config_57600_8N1 = {57600,8,0,1};
	USART_Init(config_57600_8N1);


	// SPI
	SPI_Master_Init();
	
	// CS SS: Slave Selector
	DDRB |= (1 << PORTB1);	
	
	// Initialize SD and system.
			// Card SD
			FATFS fs;     		/* File system structure */

			// Welcome message
			USART_Transmit_String("-------------------------- SD Card Test -------------------------- \r\n");
			USART_Transmit_String("Hello! This is the SD card test.\n");
			
			// Initialize SD and file system.
			USART_Transmit_String("\r\n Trying to mount the SD card's file system: ");
			
			if (pf_mount(&fs))
			{
				errorHalt("pf_mount");
			}
			USART_Transmit_String("success.\n");

	int opcion;

	while(1)
	{
		// Program
		opcion = Menu();

		switch (opcion)
		{
			// Only read
			case 1:
				text_read();
				break;

			// Only write
			case 2:
				write();
				break;

			// Read
			case 3:
				read_all();
				break;

			// Bye bye
			case 4:
				USART_Transmit_String("\n\n<---- The SD card test is done ! ---->\n\n");
				USART_Transmit_String("Bye bye...");
				while(1);
				break;

			// Default
			default:
				USART_Transmit_String("Error... :( \r\n");
				USART_Transmit_String("Please try again! \r\n");
				_delay_ms(1000);
			break;
		}
	}
}

// Funciones
void errorHalt(char* msg) {
	FATFS fs;
	USART_Transmit_String("Error: ");
	USART_Transmit_String(msg);
	USART_Transmit_String("...\r\n");
	int j = 0;
	
	while(j < 10){
		pf_mount(&fs);
		j = j + 1;
	}
	
	if (j == 10){
		USART_Transmit_String("Please try again!");
		while(1);
	}
}

int Menu(void)
{
		char buf_menu;
		int  output_menu;
		USART_Transmit_String("  \r\n \r\n");
		USART_Transmit_String("-------------------------- MENU -------------------------- \r\n");
		USART_Transmit_String("  \r\n");
		USART_Transmit_String("1: Reading a text file! \r\n");
		USART_Transmit_String("2: Write somethings on a file \r\n");
		USART_Transmit_String("3: Reading all! \r\n");
		USART_Transmit_String("4: Escape \r\n");
		USART_Transmit_String("  \r\n");
		USART_Transmit_String("---------------------------------------------------------- \r\n");
		USART_Transmit_String("Option: ");
		buf_menu = USART_Receive_char();
		USART_Transmit_char(buf_menu);
		USART_Transmit_String("\r\n");
		USART_Transmit_String("---------------------------------------------------------- \r\n");
		output_menu = buf_menu - '0';
		return output_menu;
}

void text_read(void)
{
	// Card SD
	uint8_t buf[32];	/* Buffer for card access */
	UINT nr;			/* Used for various file access functions. */

	USART_Transmit_String("\r\n -----------------------------------------------\n\n\n");
	// Open read test file.
	USART_Transmit_String("\r\n Trying to open a text file for reading: \r\n");
	if (pf_open("SEPtest.txt"))
	{
		errorHalt("pf_open");
	}
	USART_Transmit_String("\r\n success.\n");
	
	// Print test file to the serial interface.
	USART_Transmit_String("\r\n Here is the file content:\r\n");
	USART_Transmit_String("\r\n -----------------------------------------------\r\n");
	while (1)
	{
		if (pf_read(buf, sizeof(buf), &nr))
		{
			errorHalt("pf_read");
		}
		if (nr == 0)
		{
			break;
		}

		for(uint8_t i=0; i<nr; i++)
		{
			USART_Transmit_char(buf[i]);
		}
	}
	
	USART_Transmit_String("\r\n -----------------------------------------------\n\n\n");
}

void read_all(void)
{
	// Card SD
	uint8_t buf[32];	/* Buffer for card access */
	uint8_t buf1[32];	/* Buffer for card access */
	uint8_t buf2[32];	/* Buffer for card access */
	UINT nr;			/* Used for various file access functions. */
	
	USART_Transmit_String("\r\n -----------------------------------------------\n\n\n");
	// Open read test file.
	USART_Transmit_String("\r\n Trying to open a text file for reading: \r\n");
	if (pf_open("SEPtest.txt"))
	{
		errorHalt("pf_open");
	}
	USART_Transmit_String("\r\n success.\n");
	
	// Print test file to the serial interface.
	USART_Transmit_String("\r\n Here is the file content:\n");
	USART_Transmit_String("\r\n -----------------------------------------------\r\n");
	while (1)
	{
		if (pf_read(buf, sizeof(buf), &nr))
		{
			errorHalt("pf_read");
		}
		if (nr == 0)
		{
			break;
		}

		for(uint8_t i=0; i<nr; i++)
		{
			USART_Transmit_char(buf[i]);
		}
	}
	
	USART_Transmit_String("\r\n-----------------------------------------------\n\r\n");
	USART_Transmit_String("\r\n-----------------------------------------------\n\r\n");
	// Open read test file.
	USART_Transmit_String("\r\n Trying to open a text file for reading: ");
	if (pf_open("writeMe.txt"))
	{
		errorHalt("pf_open");
	}
	USART_Transmit_String("\r\n success.\n");
	
	// Print test file to the serial interface.
	USART_Transmit_String("\r\n Here is the file content:\n");
	USART_Transmit_String("\r\n-----------------------------------------------\r\n");
	while (1)
	{
		if (pf_read(buf1, sizeof(buf1), &nr))
		{
			errorHalt("pf_read");
		}
		if (nr == 0)
		{
			break;
		}

		for(uint8_t i=0; i<nr; i++)
		{
			USART_Transmit_char(buf1[i]);
		}
	}
	
	USART_Transmit_String("\r\n-----------------------------------------------\n\r\n");
	USART_Transmit_String("\r\n-----------------------------------------------\n\r\n");
	// Open read test file.
	USART_Transmit_String("\r\n Trying to open a text file for reading: \r\n");
	if (pf_open("writeMe2.txt"))
	{
		errorHalt("pf_open");
	}
	USART_Transmit_String("success.\n");
	
	// Print test file to the serial interface.
	USART_Transmit_String("\r\nHere is the file content:\n");
	USART_Transmit_String("\r\n-----------------------------------------------\r\n");
	while (1)
	{
		if (pf_read(buf2, sizeof(buf2), &nr))
		{
			errorHalt("pf_read");
		}
		if (nr == 0)
		{
			break;
		}

		for(uint8_t i=0; i<nr; i++)
		{
			USART_Transmit_char(buf2[i]);
		}
	}
	
	USART_Transmit_String("\r\n-----------------------------------------------\n\r\n");
	USART_Transmit_String("\r\n-----------------------------------------------\n\r\n");
}

void write(void)
{
	// Card SD
	UINT nr;			/* Used for various file access functions. */

	// Open write test file.
	USART_Transmit_String("\r\n Trying to open a text file for writing: ");
	if (pf_open("writeMe.txt"))
	{
		errorHalt("pf_open");
	}
	USART_Transmit_String("success.\n");
	
	// Set read/write pointer to beginning of file.
	USART_Transmit_String("\r\n Going to beginning of file: ");
	if (pf_lseek(0))
	{
		errorHalt("pf_lseek");
	}
	USART_Transmit_String("success.\n");
	
	// Write data and finish the transaction.
	USART_Transmit_String("\r\n Writing some data to the file: ");

	char message[] = "If this message does not appear in your text file, you failed to read the PFF documentation. Read about the use of pf_write() there!";
	
	if (pf_write(message, strlen(message), &nr))
	{
		errorHalt("pf_write while writing the file content");
	}
	if (pf_write(0, 0, &nr))
	{
		errorHalt("pf_write while closing the file.");
	}
	USART_Transmit_String("\r\n success.\n");
	
	// Open write test file.
	USART_Transmit_String("\r\n Trying to open another text file for writing more: ");
	if (pf_open("writeMe2.txt"))
	{
		errorHalt("pf_open");
	}
	USART_Transmit_String("success.\r\n");
	
	// Set read/write pointer to beginning of file.
	USART_Transmit_String("\r\n Going to beginning of file: ");
	if (pf_lseek(0))
	{
		errorHalt("pf_lseek");
	}
	USART_Transmit_String("success.\n");
	
	// Receive a message over USART
	USART_Transmit_String("\r\n Please type a short message and to finish type '$':\r\n");
	USART_Receive_String(message, strlen(message));
	USART_Transmit_String("\r\n Please press any key! \r\n");
	char any = USART_Receive_char();
	USART_Transmit_String("\r\n success.\n ");

	// Write it to the file and finish the transaction.
	USART_Transmit_String("\r\n Writing message to the file...");
	if (pf_write(message, strlen(message), &nr))
	{
		errorHalt("pf_write while writing the file content");
	}
	if (pf_write(0, 0, &nr))
	{
		errorHalt("pf_write while closing the file.");
	}
	USART_Transmit_String("\n\r Success.\n");
	USART_Transmit_String("\r\n Message: \r\n ");
	USART_Transmit_String(message);
	USART_Transmit_String("\r\n success.\r\n ");
}