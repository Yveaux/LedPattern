/*
    LedPattern - A library to run set-and-forget LED blink patterns.

    Created by Ivo Pullens, Emmission, 2017

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef LEDPATTERN_H_INCLUDED
#define LEDPATTERN_H_INCLUDED

#include "LedPattern_config.h"
#include <stdint.h>

#ifndef LED_PATTERN_NO_CRITICAL_SECTIONS
#define LED_PATTERN_CRITICAL_SECTION_START   noInterrupts();
#define LED_PATTERN_CRITICAL_SECTION_END     interrupts();
#else
#define LED_PATTERN_CRITICAL_SECTION_START
#define LED_PATTERN_CRITICAL_SECTION_END
#endif

class LedPattern
{
  public:
    /**
     * Constructor.
     */
    LedPattern(void);

    /**
     * Destructor.
     */
    virtual ~LedPattern(void);

    /**
      * Led pattern type.
      */
    typedef uint8_t const* pattern;

    /**
      * Start a Led pattern.
      */
    virtual void start(const pattern p);

    /**
      * Stop a running Led pattern. Led keeps current state.
      */
    virtual void stop(void);

    /**
      * Switch Led off and stop a running Led pattern.
      */
    virtual void off(void);

    /**
     * Test is Led pattern is currently running.
     * @return true when pattern has finished.
     */
    virtual bool finished(void);

    typedef enum {
        CMD_SET,           /**< Set Led to certain state. */
        #ifndef LED_PATTERN_FADE_UNSUPPORTED
            CMD_FADETO,    /**< Fade Led from current state to new state. */
        #endif
        CMD_WAIT,          /**< Wait some time. */
        CMD_REPEAT,        /**< Repeat following pattern a number of times. */
        CMD_ENDREPEAT,     /**< End marker for repeat sequence. */
        CMD_FINISHED       /**< Mark pattern as finished. */
    } CMD;

    const static uint8_t repeatForever = 255;   /**< Symbolic value, indicating pattern should repeat forever. */
    
    /**
      * Update the pattern.
      * This function is to be called on a regular interval to update Led state.
      * The time elapsed between successive calls determines the unit of time
      * measurement for the WAIT-command.
      */
    virtual void update(void);

  protected:
    virtual void intStop(void);

    /**
      * Turn the Led off.
      */
    virtual void ledOff(void) = 0;

    /**
      * Set the Led to a certain state.
      * The derived class determines the states supported by the Led.
      */
    virtual void ledSet(pattern& p) = 0;

    #ifndef LED_PATTERN_FADE_UNSUPPORTED
        /**
          * Fade the Led to a certain state.
          * The derived class determines the states supported by the Led.
          */
        virtual void ledFadeTo(pattern& p, const uint8_t steps) = 0;

        /**
          * Stop fading the Led.
          */
        virtual void ledFadeStop(void) = 0;

        /**
          * Update the Led state.
          * Used to calculate inbetween state when e.g. fading.
          */
        virtual void ledUpdate(void) = 0;
    #endif

    pattern  m_pattern;     /**< Current position in the pattern. */

    /**
      * Storage type for repetitions.
      */
    typedef struct {
        pattern m_pc;       /**< Location in pattern where repetation should start. */
        uint8_t m_repeat;   /**< Number of repetitions remaining, or LED_PATTERN_REPEAT_FOREVER. */
    } repeat;
    
    uint8_t  m_wait;                                        /**< Number of remaining cycles to wait. */
    repeat   m_repeatStack[LED_PATTERN_REPEAT_STACK_SIZE];  /**< Stack keeping track of active repetitions. */
    int8_t   m_repeatStackIdx;                              /**< Current index in repetition stack. */
};

#endif    // LEDPATTERN_H_INCLUDED
