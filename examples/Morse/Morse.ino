#include "LedPattern_Mono.h"

// The morse alphabet.
const char* alphabet[] = {
                "a.-",    "b-...",  "c-.-.",  "d-..", 
                "e.",     "f..-.",  "g--.",   "h....",
                "i..",    "j.---",  "k-.-",   "l.-..",
                "m--",    "n-.",    "o---",   "p.--.", 
                "q--.-",  "r.-.",   "s...",   "t-", 
                "u..-",   "v...-",  "w.--",   "x-..-", 
                "y-.--",  "z--..",  "0-----", "1.----", 
                "2..---", "3...--", "4....-", "5.....", 
                "6-....", "7--...", "8---..", "9----." };
#define LONGEST_CHARACTER (5)

// Define Led ON/OFF symbolic names
#define LED_ON  (255)
#define LED_OFF (0)

const uint8_t dotPattern[] = {
   LedPattern::CMD_SET, LED_ON,
   LedPattern::CMD_WAIT, 3,
   LedPattern::CMD_SET, LED_OFF,
   LedPattern::CMD_WAIT, 1 };

const uint8_t barPattern[] = {
   LedPattern::CMD_SET, LED_ON,
   LedPattern::CMD_WAIT, 9,
   LedPattern::CMD_SET, LED_OFF,
   LedPattern::CMD_WAIT, 1 };

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

static uint8_t myPattern[LONGEST_CHARACTER*ARRAY_SIZE(dotPattern)+1];

// LED Pin definition.
// Use the builtin led (no fading supported)
#define LED_PIN (LED_BUILTIN)

// Create the Led pattern handling class.
static LedPattern_Mono pattern(LED_PIN);

void setup()
{
  Serial.begin(115200);
}

void loop()
{
  if (pattern.finished() && (Serial.available() > 0))
  {
    // Pattern is not running and serial character available
    char c = tolower(Serial.read());

    // Lookup the character in the morse alphabet
    size_t idx = 0;
    for (size_t i = 0; i < ARRAY_SIZE(alphabet); ++i)
    {
      if (alphabet[i][0] == c)
      {
        // Found the character!
        // Now parse the morse code and create the character's blink pattern on the go.
        const char* p = &(alphabet[i][1]);
        while (*p != 0)
        {
          // Add pattern for dot or bar. Both patterns have identical length, so we use length
          // of dot pattern in calculations.
          (void)memcpy( &myPattern[idx], (*p == '.') ? dotPattern : barPattern, ARRAY_SIZE(dotPattern) );
          idx += ARRAY_SIZE(dotPattern);
          ++p;
        }
      }
    }
    // Add a finished command to the pattern
    myPattern[idx] = LedPattern::CMD_FINISHED;
    // And start execution
    pattern.start(myPattern);
  }
  // Update pattern state. Led gets updated and the pattern gets parsed.
  pattern.update();
  // Wait 1 time cycle before updating again.
  delay(100);
}

