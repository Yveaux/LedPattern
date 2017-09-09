#include "LedPattern_Mono.h"
#include <Arduino.h>

#define NODEBUG
#ifndef NODEBUG
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x); Serial.flush();
#else
#define debug(x)
#define debugln(x)
#endif 

LedPattern_Mono::LedPattern_Mono( const uint8_t ledPin )
    : m_ledPin(ledPin)
{
    pinMode(ledPin, OUTPUT);
    ledOff();
}

void LedPattern_Mono::ledWrite( const uint8_t intensity )
{
    if (0 == intensity) {
        digitalWrite(m_ledPin, LOW);
    } else if (255 == intensity) {
        digitalWrite(m_ledPin, HIGH);
    } else {
        analogWrite(m_ledPin, intensity);
    }  
#ifndef LED_PATTERN_FADE_UNSUPPORTED
    m_state = intensity<<7;
#endif
}
        
void LedPattern_Mono::ledOff( void )
{
    const uint8_t patternOff[] = { 0};
    pattern off = patternOff;
    ledSet(off);
}

void LedPattern_Mono::ledSet(pattern& p)
{
    ledWrite(*p++);
#ifndef LED_PATTERN_FADE_UNSUPPORTED
    m_step = 0;
#endif
}

#ifndef LED_PATTERN_FADE_UNSUPPORTED
void LedPattern_Mono::ledFadeTo(pattern& p, const uint8_t steps)
{
    uint8_t target = *p++;
    m_step = ((int16_t(target)<<7) - m_state)/steps;
    debug("FADE "); debug(m_state); debug("->"); debug(target); debug(", step "); debugln(m_step);
    ledUpdate();
}

void LedPattern_Mono::ledUpdate(void)
{
    if (m_step)
    {
        ledWrite((m_state + m_step)>>7);
        debug("STATE "); debugln(m_state);
    }
}
#endif
