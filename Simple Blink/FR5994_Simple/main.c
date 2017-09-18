#include <msp430.h> 
#include<msp430fr5994.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //Disables high impedence mode

    P1SEL0 &=0x03;
    P1DIR  |=0x03;
    P1OUT  |=0x01;


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
       P1OUT^=0x01;
       P1OUT^=0x02;
   }
