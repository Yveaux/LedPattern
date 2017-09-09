#ifndef LEDPATTERN_RGB_H_INCLUDED
#define LEDPATTERN_RGB_H_INCLUDED

#include "LedPattern.h"

class LedPattern_RGB : public LedPattern
{
    public:
        LedPattern_RGB( const uint8_t ledPinR, const uint8_t ledPinG, const uint8_t ledPinB );
        
    protected:
        void ledOff( void );
        void ledWrite( const uint8_t i, const uint8_t intensity );
        void ledSet(pattern& p);
        uint8_t m_ledPins[3];

        #ifndef LED_PATTERN_FADE_UNSUPPORTED
            void ledFadeTo(pattern& p, const uint8_t steps);
            void ledUpdate(void);
            void ledFadeStop(void);
            int16_t m_state[3];
            int16_t m_step[3];
        #endif
};

#endif    // LEDPATTERN_RGB_H_INCLUDED
