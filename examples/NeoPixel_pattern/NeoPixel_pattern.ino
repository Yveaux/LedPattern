#include "LedPattern_NeoPixel.h"

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


// NeoPixel IO Pin definition.
#define NEOPIXEL_PIN    6

// This example uses two NeoPixels, chainned together
#define NEOPIXEL_COUNT  2    // Total number of NeoPixels

Adafruit_NeoPixel neopixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

// Create the Led pattern handling instances; one for each neopixel
static LedPattern_NeoPixel pattern0(neopixels, 0);
static LedPattern_NeoPixel pattern1(neopixels, 1);

void setup() {
  // Initialize the NeoPixel chain
  neopixels.begin();

  // Start the patterns
  pattern0.start(myPattern0);
  pattern1.start(myPattern1);
}

void loop()
{
  // Update both patterns (setting leds)
  pattern0.update();
  pattern1.update();
  // Explicitly instruct the NeoPixel controller to update its pixels
  neopixels.show();
  // Wait 1 time cycle before updating again.
  delay(10);
}

