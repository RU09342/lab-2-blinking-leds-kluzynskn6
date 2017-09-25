#include <msp430.h> 
#include <msp430fr5994.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //disables high impedence mode

    P1SEL0 &=0xFC; //Sets port 1.0 and 1.1 as an I/O
    P1DIR  |=0x03; //Sets bits 1 and 2 to outputs
    P1OUT  |=0x01; //Turns on bit 1

    TB0CCTL0 = CCIE;  // CCR0 interrupt enabled
    TB0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TB0CCR0 =  10000;  //Sets to 12 Hz

    int count=0;

    _BIS_SR(GIE);  // Enable interrupt
    while(1)
    {
        if(count>7500)
        {
            P1OUT^=0x02;
            count=0;
        }
        else
        {
            count++;
        }
    }
}

#pragma vector=TIMERB0_VECTOR
__interrupt void Timer_B (void)
{
    P1OUT^=0x01;
}
