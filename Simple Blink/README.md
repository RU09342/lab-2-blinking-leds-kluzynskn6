# Lab 2-1: Simple Blink

Nick Kluzynski

# Introduction
The purpose of this lab is to control the LEDs on various MSP430 devices. In this iteration, a single LED blinks symettrically at a preset rate. To do this, the ports corresponding to the LED must be configured to an output; and then that port must be controlled to turn on and off. There are several ways to do this, from for loops to timers.

## Implications
### Ports
The way done here is to utilize timer interrupts to switch the LED. First, the port is configured as an output by selecting it as an I/O, then as an output.

### Timers
Before configuring the timer, global interrupts were enabled. Once that was done, the timer was then initialized to match SM clock operating at 1 MHz, then divided by 8. From there, the first interrupt was enabled and set to a value of 10,000. This makes it so that the timer increments until reaching 10,000. Upon reaching 10,000 it triggers the interrupt and restarts. During the trigger, the port is XORed with 1, which will alternate that port. 
