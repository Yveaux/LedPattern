#include "LedPattern.h"
#include <Arduino.h>    // Only for debugging with Serial
#include <assert.h>

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

#define NODEBUG
#ifndef NODEBUG
#define debug(x)   Serial.print(x)
#define debugln(x) Serial.println(x); Serial.flush();
#else
#define debug(x)
#define debugln(x)
#endif 

LedPattern::LedPattern(void)
{
    stop();
}

LedPattern::~LedPattern(void)
{
}

void LedPattern::start(const pattern p)
{
    LED_PATTERN_CRITICAL_SECTION_START
    m_pattern = p;
    m_repeatStackIdx = -1;
    LED_PATTERN_CRITICAL_SECTION_END
}

void LedPattern::intStop(void)
{
    // Internal stop method, which doesn't use critical section.
    m_pattern = 0;
    m_repeatStackIdx = -1;
}

void LedPattern::stop(void)
{
    LED_PATTERN_CRITICAL_SECTION_START
    intStop();
    LED_PATTERN_CRITICAL_SECTION_END
}

void LedPattern::off(void)
{
    LED_PATTERN_CRITICAL_SECTION_START
    intStop();
    ledOff();
    LED_PATTERN_CRITICAL_SECTION_END
}

bool LedPattern::finished(void)
{
    LED_PATTERN_CRITICAL_SECTION_START
    bool finished = !m_pattern;
    LED_PATTERN_CRITICAL_SECTION_END
    return finished;
}

void LedPattern::update( void )
{
    LED_PATTERN_CRITICAL_SECTION_START
    for(;;)
    {
        // Update the led state.
        if (!m_pattern)
        {
            break;
        }

        if (m_wait > 1)
        {
            #ifndef LED_PATTERN_FADE_UNSUPPORTED
                ledUpdate();
            #endif
            --m_wait;
            break;
        }
        for (;;)
        {    
            CMD cmd = CMD(*m_pattern++);
            if (CMD_SET == cmd)
            {
                ledSet(m_pattern);
                debugln("SET");
            #ifndef LED_PATTERN_FADE_UNSUPPORTED
                } else if (CMD_FADETO == cmd) {
                    m_wait = *m_pattern++;
                    assert(m_wait != 0);
                    ledFadeTo(m_pattern, m_wait);
                    debug("FADETO:"); debugln(m_wait);
                    break;
            #endif
            } else if (CMD_WAIT == cmd) {
                m_wait = *m_pattern++;
                debug("WAIT:"); debugln(m_wait);
                #ifndef LED_PATTERN_FADE_UNSUPPORTED
                    ledFadeStop();
                #endif
                break;
            } else if (CMD_REPEAT == cmd) {
                ++m_repeatStackIdx;
                assert(size_t(m_repeatStackIdx) < ARRAY_SIZE(m_repeatStack));
                m_repeatStack[m_repeatStackIdx].m_repeat = *m_pattern++;
                m_repeatStack[m_repeatStackIdx].m_pc     = m_pattern;
                debug("REPEAT:"); debugln(m_repeatStack[m_repeatStackIdx].m_repeat);
            } else if (CMD_ENDREPEAT == cmd) {
                assert(m_repeatStackIdx >= 0);
                if (m_repeatStack[m_repeatStackIdx].m_repeat <= 1)
                {
                    // Finished repeating
                    --m_repeatStackIdx;
                    debugln("END_REPEAT:DONE");
                } else {
                    // Repeat once more
                    if (m_repeatStack[m_repeatStackIdx].m_repeat != repeatForever) {
                        --m_repeatStack[m_repeatStackIdx].m_repeat;
                    }
                    m_pattern = m_repeatStack[m_repeatStackIdx].m_pc;
                    debug("END_REPEAT:"); debugln(m_repeatStack[m_repeatStackIdx].m_repeat);
                }
            } else if (CMD_FINISHED == cmd) {
                stop();
                debugln("FINISHED");
                break;
            }
        }
        break;
    }
    LED_PATTERN_CRITICAL_SECTION_END
}
