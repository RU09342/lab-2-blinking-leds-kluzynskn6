#include <msp430.h> 
#include <msp430fr6989.h>

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //Disables high impedence mode

    P1SEL0 &=0x01;
    P9SEL0 &=0x80;
    P1DIR  |=0x01;
    P9DIR  |=0x80;
    P1OUT  |=0x01;
    P9OUT  |=0x80;

    TB0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TB0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TB0CCR0 =  10000;                  //Sets to 12 Hz
    TB0IV=0x01;

    int count=0;


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
       if(count>5000)
        {
            P9OUT^=0x80;
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
