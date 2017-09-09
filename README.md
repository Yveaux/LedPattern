# LedPattern
This library allows you to define complex LED blink & fade patterns and execute them calling a simple update() method at regular intervals.
You no longer have to worry about timing, fading and counting.

It can be used to control regular on/off LEDs, fadeable LEDs connected to PWM pins or RGB LEDs like NeoPixel or WS2812B.

A very basic example will switch a LED on/off at regular intervals:

```
#include "LedPattern_Mono.h" 

```
