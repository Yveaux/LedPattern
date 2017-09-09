#include "LedPattern_FastLed.h"
#include <Arduino.h>

#define NODEBUG
#ifndef NODEBUG
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x); Serial.flush();
#else
#define debug(x)
#define debugln(x)
#endif 

LedPattern_FastLed::LedPattern_FastLed( CFastLED& fastled, const uint16_t idx )
    : m_fastled(fastled),
      m_idx(idx)
{
    m_fastled.clear(true);
    ledOff();
}

void LedPattern_FastLed::ledOff( void )
{
    const uint8_t patternOff[] = { 0, 0, 0};
    pattern off = patternOff;
    ledSet(off);
}

void LedPattern_FastLed::ledSet(pattern& p)
{
    uint8_t rgb[3];
    for (uint8_t i = 0; i < 3; ++i)
    {
        rgb[i] = *p++;
        #ifndef LED_PATTERN_FADE_UNSUPPORTED
            m_state[i] = rgb[i]<<7;
            m_step[i]  = 0;
        #endif
    }
    m_fastled.leds()[m_idx].setRGB( rgb[0], rgb[1], rgb[2] );
}

#ifndef LED_PATTERN_FADE_UNSUPPORTED
    void LedPattern_FastLed::ledFadeStop(void)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            m_step[i]  = 0;
        }
    }

    void LedPattern_FastLed::ledFadeTo(pattern& p, const uint8_t steps)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            uint8_t target = *p++;
            m_step[i] = ((int16_t(target)<<7) - m_state[i])/steps;
            debug("FADE "); debug(m_state[i]); debug("->"); debug(target); debug(", step "); debugln(m_step[i]);
        }
        ledUpdate();
    }

    void LedPattern_FastLed::ledUpdate(void)
    {
        uint8_t rgb[3];
        for (uint8_t i = 0; i < 3; ++i)
        {
            m_state[i] += m_step[i];
            rgb[i] = int16_t(m_state[i])>>7;
            debug("STATE "); debugln(m_state[i]);
        }
        m_fastled.leds()[m_idx].setRGB( rgb[0], rgb[1], rgb[2] );
    }
#endif
