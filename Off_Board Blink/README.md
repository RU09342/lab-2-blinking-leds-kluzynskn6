# Lab 2-4: Off board blink

Nick Kluzynski

# Introduction
The purpose of this lab is to control the LEDs on various MSP430 devices. In this iteration, LEDs blink symettrically on a breadboard, without using the development board. The MSP430G2553 is the only board available that can be removed, so this was the only one tested for this iteration.  Before starting this, a pin had to be continously set to power, so that the processor would not continously reset. To get the LEDs blinking, the ports corresponding to the button must be configured as an I/O and then as an input. Then, the ports corresponding to the LEDs must be configured to an output; and then that port must be controlled to turn on and off. There are several ways to do this, from for loops to timers. 

## Implementation
### LEDs
The way done here is to utilize timer interrupts to switch the LED. First, the port is configured as an output by selecting it as an I/O, then as an output.

### Breadboard
On the breadboard, 5V were supplied to the rails. While the power was disconeccted, the chip was placed in the board with Vcc and Vss being supplied by the rails. Before the LEDs could be connected, a pull-down resistor was placed before the LED, which would then lead to the negative rail.


### Timers
Before configuring the timer, global interrupts were enabled. Once that was done, 2 timers were then initialized to match SM clock operating at 1 MHz, then divided by 8. From there, the first interrupt was enabled and set to a value of 10,000. This makes it so that the timer increments until reaching 10,000. Upon reaching 10,000 it triggers the interrupt and restarts.  The second timer's first inttrupt was enabled, but was set to a different number. There are 2 seperate interrupt functions for each timer, and each one flips different LEDs

### Picture
To showcase how the circuity is wired, here is a gif of the chip working in the breadboard.
![Off board blinking](https://github.com/RU09342/lab-2-blinking-leds-kluzynskn6/blob/master/Off_Board%20Blink/offBoardBlink.gif)
<p><a href="https://giphy.com/gifs/embedded-l4EoOMzO4fd3qxuaA">via GIPHY</a></p>
