#include "LedPattern_FastLed.h"

#ifdef LED_PATTERN_FADE_UNSUPPORTED
#error This example requires LED_PATTERN_FADE_UNSUPPORTED to be NOT defined! Please change this is LedPattern_config.h
#endif

// Define some RGB colors, to keep pattern definition readable.
#define RED     255,0,0
#define GREEN   0,255,0
#define BLUE    0,0,255
#define WHITE   255,255,255
#define OFF     0,0,0

// The pattern to execute
const uint8_t myPattern0[] = {
  LedPattern::CMD_SET, OFF,
  LedPattern::CMD_REPEAT, LedPattern::repeatForever,
  LedPattern::CMD_FADETO, 100, RED,
  LedPattern::CMD_FADETO, 100, GREEN,
  LedPattern::CMD_FADETO, 100, BLUE,
  LedPattern::CMD_FADETO, 100, OFF,
  LedPattern::CMD_ENDREPEAT,
  /* LedPattern::CMD_FINISHED */
};

const uint8_t myPattern1[] = {
  LedPattern::CMD_SET, OFF,
  LedPattern::CMD_REPEAT, LedPattern::repeatForever,
  LedPattern::CMD_FADETO, 100, WHITE,
  LedPattern::CMD_FADETO, 100, OFF,
  LedPattern::CMD_ENDREPEAT,
  /* LedPattern::CMD_FINISHED */
};
 

// IO Pin definition.
#define LED_PIN    6

// This example uses two NeoPixels, chainned together
#define LED_COUNT  2    // Total number of NeoPixels

// Create the Led pattern handling instances; one for each led
static LedPattern_FastLed pattern0(FastLED, 0);
static LedPattern_FastLed pattern1(FastLED, 1);

static CRGB leds[LED_COUNT];

void setup() {
  // Initialize the NeoPixel chain
  FastLED.addLeds<NEOPIXEL, LED_PIN>(leds, LED_COUNT);

  // Start the patterns
  pattern0.start(myPattern0);
  pattern1.start(myPattern1);
}

void loop()
{
  // Update both patterns (setting leds)
  pattern0.update();
  pattern1.update();
  // Explicitly instruct the FastLed controller to update its pixels
  FastLED.show();
  // Wait 1 time cycle before updating again.
  delay(10);
}

