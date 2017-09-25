# Lab 2-2: Multiple Blink

Nick Kluzynski

# Introduction
The purpose of this lab is to control the LEDs on various MSP430 devices. In this iteration, a two or more LEDs blinks symettrically at a 2 different preset rate. To do this, the ports corresponding to the LEDs must be configured to an output; and then that port must be controlled to turn on and off. There are several ways to do this, from for loops to timers.

## Implications
### Ports
The way done here is to utilize timer interrupts to switch the LED. First, the port is configured as an output by selecting it as an I/O, then as an output.


### Timers
Before configuring the timer, global interrupts were enabled. Once that was done, 2 timers were then initialized to match SM clock operating at 1 MHz, then divided by 8. From there, the first interrupt was enabled and set to a value of 10,000. This makes it so that the timer increments until reaching 10,000. Upon reaching 10,000 it triggers the interrupt and restarts.  The second timer's first inttrupt was enabled, but was set to a different number. There are 2 seperate interrupt functions for each timer, and each one flips different LEDs


