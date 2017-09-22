#include <msp430.h> 
#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0x61;
    P1DIR  |=0x61;
    P1OUT  |=0x61;

    TA0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TA0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TA0CCR0 =  10000;                  //Sets to 12 Hz

    int count=0;


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
       if(count>5000)
        {
            P1OUT^=0x40;
            count=0;
        }
        else
        {
            count++;
        }

    }

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
{
    P1OUT^=0x01;
}
