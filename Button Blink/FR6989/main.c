#include <msp430.h>
#include <msp430fr6989.h>

       int count=0;
       int color=0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
       PM5CTL0 &= ~LOCKLPM5; //Disables high impedence mode

       P1SEL0 &=0xFE;
       P9SEL0 &=0x7F;
       P1DIR  |=0x01;
       P9DIR  |=0x80;
       P1OUT  |=0x01;
       P9OUT  &=0x7F;

       P1DIR &= 0xF9;  //Sets button 1 and 2 to an input
       P1REN |=0x06;   //Enables resistor
       P1OUT |=0x06;   // Sets resistor to pull up
       P1IE  |= 0x06;  // interrupt enabled
       P1IES |= 0x06;  // Hi/lo edge
       P1IFG &= 0xF9;  // IFG cleared

       TB0CCTL0 = CCIE;                   // CCR0 interrupt enabled
       TB0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
       TB0CCR0 =  10000;                  //Sets to 12 Hz


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

    //Timer interrupt function
   #pragma vector=TIMERB0_VECTOR
   __interrupt void Timer_B (void)
   {
       if(count==0)
       {
           P1OUT&=0xFE;
           P9OUT&=0x7F;
       }
       else if (color==0)
       {
           P1OUT^=0x01;
           P9OUT&=0x7F;
       }
       else
       {
           P9OUT^=0x80;
           P1OUT&=0xFE;
       }
   }

   // Button interrupt function
   #pragma vector=PORT1_VECTOR
   __interrupt void Port_1(void)
   {
      if(P1IN==0x02)
      {
          if(color==0)
              color=1;
          else
              color=0;
          __delay_cycles(5);
          P1IFG &=0xFB;// IFG cleared
      }
      else
      {
          if(count==3)
          {
              count=0;
          }
          else
          {
              count++;
          }
          P1IFG &=0xFD;                        // IFG cleared
      }
   }

