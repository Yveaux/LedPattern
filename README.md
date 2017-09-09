# LedPattern
This library allows you to define complex LED blink & fade patterns and execute them calling a simple update() method at regular intervals.
You no longer have to worry about timing, fading and counting.

It can be used to control regular on/off LEDs, fadeable LEDs connected to PWM pins or RGB LEDs like NeoPixel or WS2812B.

A very basic example will switch a LED on/off at regular intervals:

```
#include "LedPattern_Mono.h" 

// Define Led ON/OFF symbolic names 
#define LED_ON  (255)
#define LED_OFF (0) 

// Define the pattern: A repeating sequence of switching the LED on
// for 50 cycles, then off for 100 cycles.
const uint8_t myPattern[] = {
    LedPattern::CMD_REPEAT, LedPattern::repeatForever, 
        LedPattern::CMD_SET, LED_ON,
        LedPattern::CMD_WAIT, 50,
        LedPattern::CMD_SET, LED_OFF,
        LedPattern::CMD_WAIT, 100,
    LedPattern::CMD_ENDREPEAT
};

// Define the LED pin (pin 6 supports PWM, thus fading is supported)
#define LED_PIN (6)

// Create the Led pattern handling class.
static LedPattern_Mono pattern(LED_PIN);

void setup()
{
  // Start playing the pattern
  pattern.start(myPattern);
}

void loop()
{
  // Update pattern state. LED gets updated and the pattern gets parsed.
  pattern.update();
  
  // Wait 1 time (10ms) cycle before updating again.
  delay(10);
}
```

It's just as easy to fade the LED between on and off (must be a pin supporting PWM!):

```
// Define the pattern: A repeating sequence of fading the LED to on
// in 50 cycles, then fading back to off in 100 cycles.
const uint8_t myPattern[] = {
    LedPattern::CMD_SET, OFF,
    LedPattern::CMD_REPEAT, LedPattern::repeatForever, 
        LedPattern::CMD_FADETO,  50, LED_ON,
        LedPattern::CMD_FADETO, 100, LED_OFF,
    LedPattern::CMD_ENDREPEAT
};
```

Or blink 5 times, followed by a pause (nice to blink error codes or states!)

```
// Define the pattern: A repeating sequence of fading the LED to on
// in 50 cycles, then fading back to off in 100 cycles.
const uint8_t myPattern[] = {
    LedPattern::CMD_SET, OFF,
    LedPattern::CMD_REPEAT, LedPattern::repeatForever, 
         LedPattern::CMD_REPEAT, 5, 
             LedPattern::CMD_SET, LED_ON,
             LedPattern::CMD_WAIT, 50,
             LedPattern::CMD_SET, LED_OFF,
             LedPattern::CMD_WAIT, 100,
         LedPattern::CMD_ENDREPEAT
         LedPattern::CMD_WAIT, 200,
    LedPattern::CMD_ENDREPEAT
};
```

Have a look at the examples for more complex and RGB LED examples!
