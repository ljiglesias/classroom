#include <msp430.h> 

#define a 0b00000001
#define b 0b00000100
#define c 0b00001000
#define d 0b00010000
#define e 0b00100000
#define f 0b01000000
#define g 0b10000000

#define ZERO a + b + c + d + e + f
#define ONE b + c
#define TWO a + b + d + e + g
#define THREE a + b + c + d + g
#define FOUR b + c + f + g
#define FIVE a + c + d + f + g
#define SIX a + c + d + e + f + g
#define SEVEN a + b + c
#define EIGHT a + b + c + d + e + f + g
#define NINE a + b + c + d + f + g
#define ALL a + b + c + d + e + f + g

void Timer_A0_Configuration (void);
void Timer_A1_Configuration (void);
void Pin_Configuration(void);

unsigned int lista[10] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
unsigned int contador = 0;                    // Contador de 0 a 999
int          contador_2 = 0;                  // Contador de 0 a 2 que selecciona que digito vamos a prender
volatile int unidad;
volatile int decena;
volatile int centena;                         

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	              // Parar el watchdog timer

    Timer_A0_Configuration();                 // Configuración funcionamiento Timer 0
    Timer_A1_Configuration();                 // Configuración funcionamiento Timer 1
    Pin_Configuration();                      // Configuración de los pines a utilizar

	__bis_SR_register(GIE);                   // Activa las interrupciones generales

	while(1){}
}

void Pin_Configuration(void)
{
	P2DIR = ALL;
	P1DIR = b + d + e + f;
	P2OUT = ALL;
}

void Timer_A0_Configuration (void)
{
    TA0CCTL0 = CCIE;                          // Interrupción de comparación activada.
	TA0CCR0 = 200;                            // Valor al que debe llegar el contador para activar la interrupción.
	TA0CTL = TASSEL_1 + MC_1 + TACLR;         

    /**
     * TASSEL_1 -> ACLK - 2^16 Hz
     * MC_1 -> Up mode: Timer cuenta hasta TA0CCR0
     * TACLR -> Cuando este bit se declara en 1, el contador se resetea a 0. Este bit vuelve automáticamente a 0 después de esto.
    */
}

void Timer_A1_Configuration (void)
{
    TA1CCTL0 = CCIE;                          // Interrupción de comparación activada. 
	TA1CCR0 = 6554;                           // Valor al que debe llegar el contador para activar la interrupción.
	TA1CTL = TASSEL_1 + MC_1 + TACLR;         

    /**
     * TASSEL_1 -> ACLK - 2^16 Hz
     * MC_1 -> Up mode: Timer cuenta hasta TA1CCR0
     * TACLR -> Cuando este bit se declara en 1, el contador se resetea a 0. Este bit vuelve automáticamente a 0 después de esto.
    */
}


/** Esta interrupción se encarga del switcheo de 
 *  los distintos digitos del display a una frecuencia
 *  imperceptible al ojo humano
*/
#pragma vector=TIMER0_A0_VECTOR
__interrupt void TIMER0_A0_ISR(void){ 
    switch(contador_2){
        case 2:
            centena = (contador/100)%10;
            P1OUT = e;
            P1OUT |= f;
            P2OUT |= ALL;
            P2OUT &= ~lista[centena];
            break;
        case 1:
            decena = (contador/10)%10;
            P1OUT = d + f ;
            P1OUT &= ~(f);
            P2OUT |= ALL;
            P2OUT &= ~lista[decena];
            break;
        case 0:
            unidad = contador%10;
            P1OUT = b;
            P1OUT |= f;
            P2OUT |= ALL;
            P2OUT &= ~lista[unidad];
            break;
    }
    contador_2++;
    if(contador_2 == 3){
        contador_2 = 0;
    }
}

/** 
 * Esta interrupción se encarga de llevar la cuenta de 0
 * a 999 con incrementos cada 100 ms aprox.
*/
#pragma vector=TIMER1_A0_VECTOR
__interrupt void TIMER1_A0_ISR(void){
    contador++;
    if (contador == 999){
        contador = 0;
    }
}