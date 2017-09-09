#include "LedPattern_RGB.h"
#include <Arduino.h>

#define NODEBUG
#ifndef NODEBUG
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x); Serial.flush();
#else
#define debug(x)
#define debugln(x)
#endif 

LedPattern_RGB::LedPattern_RGB( const uint8_t ledPinR, const uint8_t ledPinG, const uint8_t ledPinB )
    : m_ledPins{ledPinR, ledPinG, ledPinB}
{
    for (uint8_t i = 0; i < 3; ++i)
        pinMode(m_ledPins[i], OUTPUT);

    ledOff();
}

void LedPattern_RGB::ledWrite( const uint8_t i, const uint8_t intensity )
{
    if (0 == intensity) {
        digitalWrite(m_ledPins[i], LOW);
    } else if (255 == intensity) {
        digitalWrite(m_ledPins[i], HIGH);
    } else {
        analogWrite(m_ledPins[i], intensity);
    }
}

void LedPattern_RGB::ledOff( void )
{
    const uint8_t patternOff[] = { 0, 0, 0};
    pattern off = patternOff;
    ledSet(off);
}

void LedPattern_RGB::ledSet(pattern& p)
{
    for (uint8_t i = 0; i < 3; ++i)
    {
        const uint8_t intensity = *p++;
        ledWrite(i, intensity);
        #ifndef LED_PATTERN_FADE_UNSUPPORTED
            m_step[i]  = 0;
            m_state[i] = intensity<<7;
        #endif
    }
}

#ifndef LED_PATTERN_FADE_UNSUPPORTED
    void LedPattern_RGB::ledFadeStop(void)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            m_step[i]  = 0;
        }
    }

    void LedPattern_RGB::ledFadeTo(pattern& p, const uint8_t steps)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            uint8_t target = *p++;
            m_step[i] = ((int16_t(target)<<7) - m_state[i])/steps;
            debug("FADE "); debug(m_state[i]); debug("->"); debug(target); debug(", step "); debugln(m_step[i]);
        }
        ledUpdate();
    }

    void LedPattern_RGB::ledUpdate(void)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            if (m_step[i])
            {
                m_state[i] += m_step[i];
                ledWrite(i, uint8_t(m_state[i] >> 7));
                debug("STATE "); debugln(m_state[i]);
            }
        }
    }
#endif
