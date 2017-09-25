#include <msp430.h> 
#include<msp430f5529.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P4SEL &=0x80;
    P4DIR |=0x80;


    TB0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TB0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TB0CCR0 =  10000;                  //Sets to 12 Hz


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    }

   }

   #pragma vector=TIMERB0_VECTOR
   __interrupt void Timer_B (void)
   {
       P4OUT^=0x80;
   }
