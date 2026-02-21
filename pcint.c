#include "pcint.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"

// Callbacks accessed from ISR → must be volatile
static void (*volatile pcint_callbacks[20])(void) = {0};

// Previous port states → detect exactly which pin changed
static uint8_t old_pind = 0;
static uint8_t old_pinb = 0;
static uint8_t old_pinc = 0;

void pcint_init(void)
{
    uint8_t sreg = SREG;
    cli();

    PCICR  = 0;                         // disable all groups
    PCMSK0 = PCMSK1 = PCMSK2 = 0;

    // Clear pending flags
    PCIFR = (1<<PCIF0) | (1<<PCIF1) | (1<<PCIF2);

    // Capture initial states (prevents spurious callbacks on boot)
    old_pind = PIND;
    old_pinb = PINB;
    old_pinc = PINC;

    for (uint8_t i = 0; i < 20; i++) {
        pcint_callbacks[i] = 0;
    }

    SREG = sreg;
}

void pcint_attach(uint8_t pin, void (*callback)(void))
{
    if (pin >= 20) return;

    uint8_t sreg = SREG;
    cli();

    pcint_callbacks[pin] = callback;

    if (pin < 8) {                          // PORTD (pins 0-7)
        PCMSK2 |= (1 << pin);
        PCICR  |= (1 << PCIE2);
    }
    else if (pin < 14) {                    // PORTB (pins 8-13)
        PCMSK0 |= (1 << (pin - 8));
        PCICR  |= (1 << PCIE0);
    }
    else {                                  // PORTC (pins 14-19 / A0-A5)
        PCMSK1 |= (1 << (pin - 14));
        PCICR  |= (1 << PCIE1);
    }

    SREG = sreg;
}

void pcint_detach(uint8_t pin)
{
    if (pin >= 20) return;

    uint8_t sreg = SREG;
    cli();

    pcint_callbacks[pin] = 0;

    // Smart disable: turn off PCIE only when no pins left on that port
    if (pin < 8) {                          // PORTD
        PCMSK2 &= ~(1 << pin);
        if (PCMSK2 == 0) PCICR &= ~(1 << PCIE2);
    }
    else if (pin < 14) {                    // PORTB
        uint8_t bit = pin - 8;
        PCMSK0 &= ~(1 << bit);
        if (PCMSK0 == 0) PCICR &= ~(1 << PCIE0);
    }
    else {                                  // PORTC
        uint8_t bit = pin - 14;
        PCMSK1 &= ~(1 << bit);
        if (PCMSK1 == 0) PCICR &= ~(1 << PCIE1);
    }

    SREG = sreg;
}

// ====================== ISRs ======================

ISR(PCINT0_vect)   // PORTB — pins 8-13
{
    PCIFR |= (1 << PCIF0);                  // acknowledge flag
    uint8_t changed = PINB ^ old_pinb;
    old_pinb = PINB;

    for (uint8_t i = 0; i < 6; i++) {
        if ((changed & (1 << i)) && pcint_callbacks[i + 8]) {
            pcint_callbacks[i + 8]();
        }
    }
}

ISR(PCINT1_vect)   // PORTC — pins 14-19
{
    PCIFR |= (1 << PCIF1);
    uint8_t changed = PINC ^ old_pinc;
    old_pinc = PINC;

    for (uint8_t i = 0; i < 6; i++) {
        if ((changed & (1 << i)) && pcint_callbacks[i + 14]) {
            pcint_callbacks[i + 14]();
        }
    }
}

ISR(PCINT2_vect)   // PORTD — pins 0-7
{
    PCIFR |= (1 << PCIF2);
    uint8_t changed = PIND ^ old_pind;
    old_pind = PIND;

    for (uint8_t i = 0; i < 8; i++) {
        if ((changed & (1 << i)) && pcint_callbacks[i]) {
            pcint_callbacks[i]();
        }
    }
}