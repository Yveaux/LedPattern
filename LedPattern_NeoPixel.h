#ifndef LEDPATTERN_NEOPIXEL_H_INCLUDED
#define LEDPATTERN_NEOPIXEL_H_INCLUDED

#include "LedPattern.h"
#include <Adafruit_NeoPixel.h>

class LedPattern_NeoPixel : public LedPattern
{
    public:
        LedPattern_NeoPixel( Adafruit_NeoPixel& neo, const uint16_t idx );
        
    protected:
        void ledOff( void );
        void ledSet(pattern& p);
        Adafruit_NeoPixel& m_neo;
        const uint16_t m_idx;

        #ifndef LED_PATTERN_FADE_UNSUPPORTED
            void ledFadeTo(pattern& p, const uint8_t steps);
            void ledUpdate(void);
            void ledFadeStop(void);
            int16_t m_state[3];
            int16_t m_step[3];
        #endif
};

#endif    // LEDPATTERN_NEOPIXEL_H_INCLUDED
