#include <msp430.h>
#include <msp430fr5994.h>

       int count=0;
       int color=0;

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
       PM5CTL0 &= ~LOCKLPM5; //Disables high impedence mode

       P1SEL0 &=0xFC;//Sets P1.0 and 1.1 to I/O
       P1DIR  |=0x03;//Sets P1.0 and 1.1 to outputs
       P1OUT  |=0x01;//Turns P1.0 on

       P5SEL0 &= 0x9F;
       P5DIR  &= 0x9F;  //Sets button 1 and 2 (5.5, 5.6) to an input
       P5REN  |= 0x60;  //Enables resistors for button 1 and 2
       P5OUT  |= 0x60;  // Sets resistor to pull up for button 1 and 2
       P5IE   |= 0x60;  // interrupt enabled for button 1 and 2
       P5IES  |= 0x60;  // Hi/lo edge for button 1 and 2
       P5IFG  &= 0x9F;  // IFG cleared for button 1 and 2

       TB0CCTL0 = CCIE;                   // CCR0 interrupt enabled
       TB0CTL = TASSEL_2 + MC_1 + ID_3;   // SMCLK/8, upmode
       TB0CCR0 =  10000;                  //Sets to 12 Hz


       _BIS_SR(GIE); // Enable interrupt
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
           P1OUT&=0xFD;
       }
       else if (color==0)
       {
           P1OUT^=0x01;
           P1OUT&=0xFD;
       }
       else
       {
           P1OUT^=0x02;
           P1OUT&=0xFE;
       }
   }

   // Button interrupt function
   #pragma vector=PORT5_VECTOR
   __interrupt void Port_1(void)
   {
      if(P5IN==0x20)
      {
          if(color==0)
              color=1;
          else
              color=0;
          P5IFG &=0xBF;// IFG cleared
          return;
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
          P5IFG &=0xDF;                        // IFG cleared
      }
   }

