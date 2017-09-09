#include "LedPattern_RGB.h"
#include <MsTimer2.h>

#ifdef LED_PATTERN_FADE_UNSUPPORTED
#error This example requires LED_PATTERN_FADE_UNSUPPORTED to be NOT defined! Please change this is LedPattern_config.h
#endif

// Define some RGB colors, to keep pattern definition readable.
#define RED     255,0,0
#define YELLOW  255,255,0
#define GREEN   0,255,0
#define CYAN    0,255,255
#define BLUE    0,0,255
#define MAGENTA 255,0,255
#define WHITE   255,255,255
#define OFF     0,0,0

// The pattern to execute
const uint8_t myPattern[] = {
     LedPattern::CMD_SET, OFF,
     LedPattern::CMD_REPEAT, LedPattern::repeatForever,
         LedPattern::CMD_REPEAT, 4,
             LedPattern::CMD_FADETO, 100, RED,
             LedPattern::CMD_FADETO, 100, YELLOW,
             LedPattern::CMD_FADETO, 100, GREEN,
             LedPattern::CMD_FADETO, 100, CYAN,
             LedPattern::CMD_FADETO, 100, BLUE,
             LedPattern::CMD_FADETO, 100, MAGENTA,
             LedPattern::CMD_FADETO, 100, WHITE,
         LedPattern::CMD_ENDREPEAT,
         LedPattern::CMD_REPEAT, 3,
             LedPattern::CMD_REPEAT, 5,
                 LedPattern::CMD_SET, RED,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, YELLOW,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, GREEN,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, CYAN,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, BLUE,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, MAGENTA,
                 LedPattern::CMD_WAIT, 10,
             LedPattern::CMD_ENDREPEAT,
             LedPattern::CMD_SET, OFF,
             LedPattern::CMD_WAIT, 100,
             LedPattern::CMD_REPEAT, 10,
                 LedPattern::CMD_SET, WHITE,
                 LedPattern::CMD_WAIT, 10,
                 LedPattern::CMD_SET, OFF,
                 LedPattern::CMD_WAIT, 10,
              LedPattern::CMD_ENDREPEAT,
              LedPattern::CMD_SET, OFF,
              LedPattern::CMD_WAIT, 100,
         LedPattern::CMD_ENDREPEAT,
     LedPattern::CMD_ENDREPEAT,
     /* LedPattern::CMD_FINISHED */ };

// LED Pin definition.
// Connect red to LED_PIN_R, green to LED_PIN_G and blue to LED_PIN_B.
#define LED_PIN_R (11)
#define LED_PIN_G (10)
#define LED_PIN_B (9)

// Create the Led pattern handling class.
static LedPattern_RGB pattern(LED_PIN_R, LED_PIN_G, LED_PIN_B);

static void updateLedPattern(void)
{
  // Update the pattern (setting leds).
  pattern.update();
}

void setup() {
  // Configure timer interrupt
  MsTimer2::set(10 /*cycle, ms*/, updateLedPattern);
  MsTimer2::start();

  // Start the pattern.
  pattern.start(myPattern);
}

void loop()
{
}

