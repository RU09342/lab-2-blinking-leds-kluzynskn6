#include <msp430.h> 
#include<msp430g2553.h>

/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

        P1SEL &=0x01;
        P1DIR  |=0x01;
        P1OUT  |=0x01;


        TA0CCTL0 = CCIE;                   // CCR0 interrupt enabled
        TA0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
        TA0CCR0 =  10000;                  //Sets to 12 Hz


        _BIS_SR(GIE);             // Enable interrupt
        while(1)
        {
        }

       }

       #pragma vector=TIMER0_A0_VECTOR
       __interrupt void Timer_A (void)
       {
           P1OUT^=0x01;
       }
