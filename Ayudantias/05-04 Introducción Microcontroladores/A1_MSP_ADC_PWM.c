/*
 * name: Ayudantia #1 ADC y PWM
 * Author:
 *     Camila Turrieta
 *     Felipe Sánchez
 *
 * Microcontroller:
 * 		MSP430F5529     
 * Copyright (c) 2012, Texas Instruments Incorporated
 *
 */

#include<msp430.h>
#include<stdlib.h>

void timer_A(void);
void config_adc(void);
int start_conversion(void);

void main (void)
{
    // WatchDog timer
    WDTCTL = WDTPW | WDTHOLD;

    config_adc();
    timer_A();

    // Debugueo
    P1DIR |= BIT3;
    P1OUT &= ~(BIT3);

    // PWM
    P1DIR |= BIT2;
    P1SEL |= BIT2;

    // ADC
    P6DIR &= ~(BIT0);
    P6SEL |= BIT0;

    // Auxiliaries
    int duty;
    int ADC;
    float ADC_value;
    float aux;



    while(1)
    {
        //Get ADC value
        ADC = start_conversion();

        // Valor del ADC a float
        ADC_value = (float) ADC;

        
        // LED DEBUG
        if (ADC_value > 1023)
        {
            P1OUT |= (BIT3);
        }
        
        //Linealizacion
        aux = ADC_value*255/4095;

        //Conversion del valor a numero entero
        duty = (int) aux;

        TA0CCR1 = duty;
    }
}

void config_adc(void)
{
    // Turn on ADC
    ADC12CTL0 = ADC12ON;

    // ClK = SMLK  SHP = Use sampling timer+ Prescaler
    ADC12CTL1 |= ADC12SSEL_3 + ADC12SHP + ADC12DIV_7;

    // Reference Voltage (3.3) + PIN P6.0 
    ADC12MCTL0 |= ADC12SREF_0 + ADC12INCH_0;

    // Enable conversion
    ADC12CTL0 |= ADC12ENC;
}

int start_conversion(void)
{
    // Star conversion
    ADC12CTL0 |= ADC12SC;

    // Wait conversion
    while (!(ADC12IFG & BIT0));
    
    // Return ADC value
    return ADC12MEM0;
}

void timer_A(void)
{
    // TA0CTL control register:
    // SMCLK = 1.048 MHz - Prescaler = 8 - UPMODE
    TA0CTL |= TASSEL_2 + ID_3 + MC_1;

    // Output mode PIN 1.2
    TA0CCTL1 |= OUTMOD_7;

    // Flags
    TA0CCR0 = 255;          //Top
    TA0CCR1 = 10;           //Flag to toggle
}