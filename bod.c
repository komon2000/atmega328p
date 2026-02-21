#include "bod.h"
#include "config.h"
#include <avr/io.h>

void bod_init(void) {
    MCUSR = 0;                    // Clear all reset flags (including BORF)
}

void bod_disable(void) {
    MCUCR |= (1 << BODS) | (1 << BODSE);   // Start disable sequence
    MCUCR &= ~(1 << BODSE);
    MCUCR |= (1 << BODS);                  // BOD off
}

void bod_enable(void) {
    MCUCR |= (1 << BODS) | (1 << BODSE);
    MCUCR &= ~(1 << BODSE);
    MCUCR &= ~(1 << BODS);                 // BOD on
}

uint8_t was_brown_out_reset(void) {
    return (MCUSR & (1 << BORF)) ? 1 : 0;
}