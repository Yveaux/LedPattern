#include "LedPattern_NeoPixel.h"
#include <Arduino.h>

#define NODEBUG
#ifndef NODEBUG
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x); Serial.flush();
#else
#define debug(x)
#define debugln(x)
#endif 

LedPattern_NeoPixel::LedPattern_NeoPixel( Adafruit_NeoPixel& neo, const uint16_t idx )
    : m_neo(neo),
      m_idx(idx)
{
    ledOff();
}

void LedPattern_NeoPixel::ledOff( void )
{
    const uint8_t patternOff[] = { 0, 0, 0};
    pattern off = patternOff;
    ledSet(off);
}

void LedPattern_NeoPixel::ledSet(pattern& p)
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
    m_neo.setPixelColor( m_idx, rgb[0], rgb[1], rgb[2] );
}

#ifndef LED_PATTERN_FADE_UNSUPPORTED
    void LedPattern_NeoPixel::ledFadeStop(void)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            m_step[i]  = 0;
        }
    }

    void LedPattern_NeoPixel::ledFadeTo(pattern& p, const uint8_t steps)
    {
        for (uint8_t i = 0; i < 3; ++i)
        {
            uint8_t target = *p++;
            m_step[i] = ((int16_t(target)<<7) - m_state[i])/steps;
            debug("FADE "); debug(m_state[i]); debug("->"); debug(target); debug(", step "); debugln(m_step[i]);
        }
        ledUpdate();
    }

    void LedPattern_NeoPixel::ledUpdate(void)
    {
        uint8_t rgb[3];
        for (uint8_t i = 0; i < 3; ++i)
        {
            m_state[i] += m_step[i];
            rgb[i] = int16_t(m_state[i])>>7;
            debug("STATE "); debugln(m_state[i]);
        }
        m_neo.setPixelColor( m_idx, rgb[0], rgb[1], rgb[2] );
    }
#endif
