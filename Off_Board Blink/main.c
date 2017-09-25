#include <msp430.h> 
#include <msp430g2553.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0x41;
    P1DIR |=0x41;
    P1OUT |=0x41;

    TA0CCTL0= CCIE;                   // CCR0 interrupt enabled
    TA0CTL  = TASSEL_2 + MC_2 + ID_3;   // SMCLK/8, upmode
    TA0CCR0 = 50000;                  //Sets to 4 Hz

    TA1CCTL0= CCIE;                   // CCR0 interrupt enabled
    TA1CTL  = TASSEL_2 + MC_2 + ID_3;   // SMCLK/8, upmode
    TA1CCR0 = 65535;                  //Sets to 6 Hz

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

#pragma vector=TIMER1_A0_VECTOR
__interrupt void Timer_A1 (void)
{
    P1OUT^=0x40;
}
