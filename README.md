# Arduino Nano LFO

LFO on an Arduino Nano

 
 
## Objective

Create an Arduino Based LFO that can be used in a modular or modularish system.  Originally I was hoping to create a full blown modular with the arduino, but soon realized that it would take a bit more work than I thought.  Not impossible, but I was hoping to use the PWN pins that were available versus needing DAC/ADC stuff.
I wanted simple pots to pins, and pins to LPF for analog outs.

And Blinky lights.

The biggest limitation for arduino is that you get 6 PWM. Since the arduino controls those 6 pwms across its 3 timers, if you want to do interrupts using timers, you kinda have to balance that.
I am using Timer 1, so pins 9, 10 just did not work.

https://forum.arduino.cc/index.php?topic=426773.0

You certainly can get around this.  For example, use a CD40106 for the LFO timer and run entirely on external interrupts.  You actually might get better resolution doing this.  But again, my goal was low part count.

So, with just 4 pwms, I settled for a pure LFO.  With room for features.  If you were so inclined, this could be used for a unit with very few parts.  Pots, buttons, Leds, Resistors and a few Caps at most.

## Features

TWO LFOs with 3 waveforms per channel.
 - Waveform 1 (Selectable)
   - Sine
   - Triangle
   - Ramp up/down
   - Psycho LFO 1 and 2
 - Square wave 50% duty
 - Waveform 2 ( Triangle)
 
 Button to select wavefor
 




## Interface


## Improvements

Square wave 25% duty
Square Wave Random duty
Square wave Bursty
Trapaziod waveform
Folded triangle

Shift button
