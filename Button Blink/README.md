# Lab 2-3: Button Blink

Nick Kluzynski

# Introduction
The purpose of this lab is to control the LEDs on various MSP430 devices. In this iteration, LEDs blink symettrically using a button to control them. To do this, the ports corresponding to the button must be configured as an I/O and then as an input. Then, the ports corresponding to the LEDs must be configured to an output; and then that port must be controlled to turn on and off. There are several ways to do this, from for loops to timers. 

## Implications
### LEDs
The way done here is to utilize timer interrupts to switch the LED. First, the port is configured as an output by selecting it as an I/O, then as an output.


### Buttons
The buttons work using interrupts, similiar to timers. So after configuring the port to an input with a pull up resistor, the interrupt needs to be set up. To do this, several registers need to be enabled/disabled on that port.  The intterupt is also set up using registers. Once configured correctly, the interrupt triggers on every button press, and executes a predefined function. 


### Controller
The button here does not only turn it on and off, but can also change the speed and color of the LED. To do this, there are several functions that are continously executed. 

The first one is a while(1) loop in the main function that detects what number the speed variable is set to, and then changes the timer interrupt value to different speeds. 

The second is within the timer interrupt service routine; where it detects to see if the speed variable is on as well as the value of the color bit. From there, it determines LED to blink, if any.

 The third activates on a button press, which first determines which button was pressed and then changes either the speed vaiable or the color variable depending on the button. Depending on the board, there was only one button avaiable. For these boards, whenever the button was pressed, the speed was increased; but instead of reseting, it would change the color.


### Timers
Before configuring the timer, global interrupts were enabled. Once that was done, 2 timers were then initialized to match SM clock operating at 1 MHz, then divided by 8. From there, the first interrupt was enabled and set to a value of 10,000. This makes it so that the timer increments until reaching 10,000. Upon reaching 10,000 it triggers the interrupt and restarts.  The second timer's first inttrupt was enabled, but was set to a different number. There are 2 seperate interrupt functions for each timer, and each one flips different LEDs
