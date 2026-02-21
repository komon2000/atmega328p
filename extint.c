#include "extint.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"

// Callbacks accessed from ISR → must be volatile
static void (*volatile extint0_callback)(void) = 0;
static void (*volatile extint1_callback)(void) = 0;

void extint_init(void)
{
    uint8_t sreg = SREG;
    cli();

    EIMSK &= ~((1 << INT0) | (1 << INT1));     // disable both
    EIFR  |=  (1 << INTF0) | (1 << INTF1);     // clear any pending flags
    extint0_callback = 0;
    extint1_callback = 0;

    SREG = sreg;
}

void extint_attach(uint8_t num, uint8_t mode, void (*callback)(void))
{
    if (mode > EXTINT_RISING) return;   // invalid mode safety

    uint8_t sreg = SREG;
    cli();

    if (num == EXTINT0)
    {
        extint0_callback = callback;

        // Set ISC01:ISC00 (bits 1:0)
        EICRA = (EICRA & ~0x03) | ((uint8_t)mode << ISC00);

        EIFR |= (1 << INTF0);               // clear pending flag

        if (callback)
            EIMSK |= (1 << INT0);
        else
            EIMSK &= ~(1 << INT0);
    }
    else if (num == EXTINT1)
    {
        extint1_callback = callback;

        // Set ISC11:ISC10 (bits 3:2)
        EICRA = (EICRA & ~0x0C) | ((uint8_t)mode << ISC10);

        EIFR |= (1 << INTF1);               // clear pending flag

        if (callback)
            EIMSK |= (1 << INT1);
        else
            EIMSK &= ~(1 << INT1);
    }

    SREG = sreg;
}

void extint_detach(uint8_t num)
{
    uint8_t sreg = SREG;
    cli();

    if (num == EXTINT0)
    {
        EIMSK &= ~(1 << INT0);
        EIFR  |=  (1 << INTF0);
        extint0_callback = 0;
    }
    else if (num == EXTINT1)
    {
        EIMSK &= ~(1 << INT1);
        EIFR  |=  (1 << INTF1);
        extint1_callback = 0;
    }

    SREG = sreg;
}

// ====================== ISRs ======================

ISR(INT0_vect)
{
    if (extint0_callback) extint0_callback();
}

ISR(INT1_vect)
{
    if (extint1_callback) extint1_callback();
}