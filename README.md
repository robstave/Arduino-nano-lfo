# Arduino Nano LFO

LFO on an Arduino Nano

 
 
## Objective

Create an Arduino Based LFO that can be used in a modular or modularish system.  Originally I was hoping to create a full blown modular with the arduino, but soon realized that it would take a bit more work than I thought.  Not impossible, but I was hoping to use the PWN pins that were available versus needing DAC/ADC stuff.
I wanted simple pots to pins, and pins to LPF for analog outs.

And Blinky lights.

So a basic platform that you can optimize, and build out from, without having to work too hard doing that.

### Challenges

The biggest limitation for arduino is that you get 6 PWM across its 3 timers.  PWM and Timers are tied together. If you want to do interrupts using timers, you kinda have to balance that otherwise things get screwy.
I am using Timer 1, so pins 9, 10 just did not work for PWM.

https://forum.arduino.cc/index.php?topic=426773.0

You certainly can get around this.  For example, use a CD40106 for the LFO timer and run entirely on external interrupts.  You actually might get better resolution doing this.  But again, my goal was low part count.

So, with just 4 pwms, I settled for a pure LFO.  With room for features.  If you were so inclined, this could be used for a unit with very few parts.  Pots, buttons, Leds, Resistors and a few Caps at most.

Also, the Analog inputs for arduino is not super high on resolution.  You could do a Corse/fine...which technically you see in analog circuits too.

## Features

TWO LFOs with 3 waveforms per channel.
 - Waveform 1 (Selectable)
   - Sine
   - Triangle
   - Ramp up/down
   - Psycho LFO 1 and 2
 - Square wave 50% duty
 - Waveform 2 ( Triangle)
 
 Button to select waveform
 

## Interface


## Improvements

There is room for improvement here.

- Fast Read on PWM
- Use DDS instead of timer countdowns
- Timer with countdowns has too fine of a resolution on slow counts and not enough in higher freq.  Perhaps map the values rather than a linear (or exp map)

- Other waveforms
  - Square wave 25% duty
  - Square Wave Random duty
  - Square wave Bursty
  - Trapaziod waveform (pwm)
  - Folded triangle (pwm)

Shift button

- Sync
- EEPROM Setting storage for toggle
  - Do you expect to turn off your patch and have it turn back on the same way?  Store off the toggle state to do this.
