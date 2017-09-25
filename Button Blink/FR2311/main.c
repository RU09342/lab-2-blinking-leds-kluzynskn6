#include <msp430.h> 
#include<msp430fr2311.h>

int count=0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    PM5CTL0 &= ~LOCKLPM5; //Disables high impedence mode

    P1SEL0 &0x01;
    P1DIR |=0x01;
    P1OUT |=0x01;

    P2SEL0 &0x01;
    P2DIR |=0x01;
    P2OUT |=0x01;

    P1DIR &= 0xFD;  //Sets button 1 to an input
    P1REN |= 0x02;  //Enables resistor
    P1OUT |= 0x02;  // Sets resistor to pull up
    P1IE  |= 0x02;  // interrupt enabled
    P1IES |= 0x02;  // Hi/lo edge
    P1IFG &= 0xFD;  // IFG cleared


    TB0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TB0CTL = TBSSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TB0CCR0 =  10000;                  //Sets to 12 Hz

    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
        if(count==1||count==4)
        {
            TB0CCR0 = 2500; //Sets to 3 Hz
        }
        if(count==2||count==5)
        {
            TB0CCR0 = 5000; //Sets to 6 Hz
        }
        if(count==3||count==6)
        {
            TB0CCR0 = 10000;//Sets to 12 Hz
        }
    }

 }

     #pragma vector=TIMER0_B0_VECTOR
     __interrupt void Timer_A (void)
     {
         if(count==0)
         {
             P1OUT&=0xFE; //Clears 1.0
             P1OUT&=0xFE;//Clears 2.0
         }
         else if(count<=3)
         {
             P1OUT^=0x01;//Invert P1.0
             P2OUT&=0xFE;//Clears 2.0
         }
         else
         {
             P2OUT^=0x01;//Inverts P2.0
             P1OUT &=0xFE;//Clears P1.0
         }
     }

     // Button interrupt function
     #pragma vector=PORT1_VECTOR
     __interrupt void Port_1(void)
     {
            if(count==6)
                count=0;
            else
                count++;
            P1IFG &=0xFD;// IFG cleared
     }

