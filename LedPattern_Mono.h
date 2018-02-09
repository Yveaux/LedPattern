#ifndef LEDPATTERN_MONO_H_INCLUDED
#define LEDPATTERN_MONO_H_INCLUDED

#include "LedPattern.h"

class LedPattern_Mono : public LedPattern
{
    public:
        LedPattern_Mono( const uint8_t ledPin );
        
    protected:
        void ledOff( void );
        void ledWrite( const uint8_t intensity );
        void ledSet(pattern& p);
        uint8_t m_ledPin;

#ifndef LED_PATTERN_FADE_UNSUPPORTED
        void ledFadeTo(pattern& p, const uint8_t steps);
        void ledUpdate(void);
        void ledFadeStop(void);
        int16_t m_state;
        int16_t m_step;
#endif
};

#endif    // LEDPATTERN_MONO_H_INCLUDED
