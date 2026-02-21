#include "clock.h"
#include "config.h"
#include <avr/interrupt.h>   // ← REQUIRED for cli() and SREG

void clock_init(void)
{
    clock_set_prescaler(DEFAULT_CLOCK_DIV);
}

void clock_set_prescaler(uint8_t div)
{
    if (div > 8) div = 8;               // safety clamp

    uint8_t oldSREG = SREG;
    cli();                              // disable interrupts while changing

    CLKPR = (1 << CLKPCE);              // Enable prescaler change
    CLKPR = div;                        // Set new divider

    SREG = oldSREG;                     // restore interrupts
}

uint32_t clock_get_frequency(void)
{
    uint8_t div = CLKPR & 0x0F;
    uint32_t freq = BASE_F_CPU;
    if (div >= 1) {
        freq >>= div;                   // fast divide by 2^div
    }
    return freq;
}