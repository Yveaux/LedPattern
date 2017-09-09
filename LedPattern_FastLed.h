#ifndef LEDPATTERN_FASTLED_H_INCLUDED
#define LEDPATTERN_FASTLED_H_INCLUDED

#include "LedPattern.h"
#include <FastLED.h>

class LedPattern_FastLed : public LedPattern
{
    public:
        LedPattern_FastLed( CFastLED& fastled, const uint16_t idx );
        
    protected:
        void ledOff( void );
        void ledSet(pattern& p);
        CFastLED& m_fastled;
        const uint16_t m_idx;

        #ifndef LED_PATTERN_FADE_UNSUPPORTED
            void ledFadeTo(pattern& p, const uint8_t steps);
            void ledUpdate(void);
            void ledFadeStop(void);
            int16_t m_state[3];
            int16_t m_step[3];
        #endif
};

#endif    // LEDPATTERN_FASTLED_H_INCLUDED
