#include <msp430.h>
#include <stdint.h>

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD ; // Detener el timer de watchdog
    //Define pines del puerto 1 como salida
    P1DIR |= 0x7D; //0111_1101
    //Define pines del puerto 2 como salida
    P2DIR |= 0xFD; //1111_1101
    //Define pines del puerto 3 como salida
    P3DIR |= 0xFF; //1111_1111
    //Define pines del puerto 4 como salida
    P4DIR |= 0x8F; //1000_1111
    //Define pines del puerto 6 como salida
    P6DIR |= 0x7F; //0111_1111
    //Define pines del puerto 7 como salida
    P7DIR |= 0x11; //0001_0001
    //Define pines del puerto 8 como salida
    P8DIR |= 0x06; //0000_0110

    // Set los pines del puerto 1 en HIGH
    P1OUT |= 0x7D;
    // Set los pines del puerto 2 en HIGH
    P2OUT |= 0xFD;
    // Set los pines del puerto 3 en HIGH
    P3OUT |= 0xFF;
    // Set los pines del puerto 4 en HIGH
    P4OUT |= 0x8F;
    // Set los pines del puerto 6 en HIGH
    P6OUT |= 0x7F;
    // Set los pines del puerto 7 en HIGH
    P7OUT |= 0x11;
    // Set los pines del puerto 8 en HIGH
    P8OUT |= 0x06;

while (1) // Infinite loop
{
}
return 0;
}
