#include "LedPattern_Mono.h"

#ifdef LED_PATTERN_FADE_UNSUPPORTED
#error This example requires LED_PATTERN_FADE_UNSUPPORTED to be NOT defined! Please change this is LedPattern_config.h
#endif

// Define Led ON/OFF symbolic names
#define LED_ON  (255)
#define LED_OFF (0)

// The pattern to execute
const uint8_t myPattern[] = {
     LedPattern::CMD_SET,    LED_OFF,
     LedPattern::CMD_REPEAT, LedPattern::repeatForever,
         LedPattern::CMD_REPEAT, 4,
             LedPattern::CMD_FADETO, 100, LED_ON,
             LedPattern::CMD_FADETO, 100, LED_OFF,
         LedPattern::CMD_ENDREPEAT,
         LedPattern::CMD_REPEAT, 3,
             LedPattern::CMD_REPEAT, 5,
                 LedPattern::CMD_SET, LED_ON,
                 LedPattern::CMD_WAIT, 50,
                 LedPattern::CMD_SET, LED_OFF,
                 LedPattern::CMD_WAIT, 20,
             LedPattern::CMD_ENDREPEAT,
             LedPattern::CMD_SET, LED_OFF,
             LedPattern::CMD_WAIT, 100,
             LedPattern::CMD_REPEAT, 10,
                 LedPattern::CMD_SET, LED_ON,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, LED_OFF,
                 LedPattern::CMD_WAIT, 10,
             LedPattern::CMD_ENDREPEAT,
         LedPattern::CMD_SET, LED_OFF,
         LedPattern::CMD_WAIT, 100,
         LedPattern::CMD_ENDREPEAT,
     LedPattern::CMD_ENDREPEAT,
     /* LedPattern::CMD_FINISHED */ };

// LED Pin definition.
// Connect a led to pin 11 (supports PWM for fading)
#define LED_PIN (11)

// Or, use the builtin led (no fading supported)
//#define LED_PIN (LED_BUILTIN)

// Create the Led pattern handling class.
static LedPattern_Mono pattern(LED_PIN);

void setup() {
  // Start the pattern.
  pattern.start(myPattern);
}

void loop()
{
  // Update the pattern (setting leds).
  pattern.update();
  // Wait 1 time cycle before updating again.
  delay(10);
}

