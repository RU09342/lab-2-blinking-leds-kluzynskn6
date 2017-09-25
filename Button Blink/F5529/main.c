#include <msp430.h> 
#include<msp430f5529.h>

int count =0;
int color =0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer

    P1SEL &=0x01;
    P1DIR |=0x01;
    P4SEL &=0x80;
    P4DIR |=0x80;


    TB0CCTL0 = CCIE;                   // CCR0 interrupt enabled
    TB0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
    TB0CCR0 =  10000;                  //Sets to 12 Hz

    P1SEL &= 0xFD;
    P1DIR &= 0xFD;  //Sets button 1 and 2 (5.5, 5.6) to an input
    P1REN |= 0x02;  //Enables resistors for button 1 and 2
    P1OUT |= 0x02;  // Sets resistor to pull up for button 1 and 2
    P1IE  |= 0x02;  // interrupt enabled for button 1 and 2
    P1IES |= 0x02;  // Hi/lo edge for button 1 and 2
    P1IFG &= 0xFD;  // IFG cleared for button 1 and 2

    P2SEL &= 0xFD;
    P2DIR &= 0xFD;  //Sets button 1 and 2 (5.5, 5.6) to an input
    P2REN |= 0x02;  //Enables resistors for button 1 and 2
    P2OUT |= 0x02;  // Sets resistor to pull up for button 1 and 2
    P2IE  |= 0x02;  // interrupt enabled for button 1 and 2
    P2IES |= 0x02;  // Hi/lo edge for button 1 and 2
    P2IFG &= 0xFD;  // IFG cleared for button 1 and 2


    _BIS_SR(GIE);             // Enable interrupt
    while(1)
    {
    	if(count==1)
    	{
    		TB0CCR0 =  2500; //Sets to 3 Hz
    	}
    	    if(count==2)
    	{
    	    TB0CCR0 =  5000;//Sets to 6 Hz
    	}
    	    if(count==3)
    	{
    	    TB0CCR0 =  10000;//Sets to 12 Hz
    	}
    }

   }

   #pragma vector=TIMERB0_VECTOR
   __interrupt void Timer_B (void)
   {
       if(count==0)
       {
           P1OUT&=0xFE;
           P4OUT&=0x7F;
       }
       else if (color==0)
       {
           P1OUT^=0x01;
           P4OUT&=0x7F;
       }
       else
       {
           P4OUT^=0x80;
           P1OUT&=0xFE;
       }
   }

	#pragma vector=PORT1_VECTOR
   __interrupt void Port_1(void)
   {
	   if(color==0)
	   {
		   color=1;
	   }
	   else
	   {
		   color=0;
	   }
	   P1IFG &=0xFD;// IFG cleared
	   return;
   }
#pragma vector=PORT2_VECTOR
__interrupt void Port_2(void)
{
    if(count==3)
    {
        count=0;
    }
    else
    {
        count++;
    }
    P2IFG &=0xFD;                        // IFG cleared
}
