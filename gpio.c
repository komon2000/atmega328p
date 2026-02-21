#include "gpio.h"

// ====================== GPIO (Arduino-style pin mapping) ======================

void gpio_init(void)
{
    // AVR resets all pins to INPUT (no pull-up) — nothing required here.
    // This function exists for API consistency with the rest of the library.
}

void gpio_pin_mode(uint8_t pin, uint8_t mode)
{
    if (pin < 8) {                              // PORTD: pins 0-7
        uint8_t mask = (1 << pin);
        if (mode == OUTPUT) {
            DDRD |= mask;
        } else {
            DDRD &= ~mask;
            if (mode == INPUT_PULLUP) PORTD |= mask;
            else                      PORTD &= ~mask;
        }
    }
    else if (pin < 14) {                        // PORTB: pins 8-13
        uint8_t mask = (1 << (pin - 8));
        if (mode == OUTPUT) {
            DDRB |= mask;
        } else {
            DDRB &= ~mask;
            if (mode == INPUT_PULLUP) PORTB |= mask;
            else                      PORTB &= ~mask;
        }
    }
    else if (pin < 20) {                        // PORTC: pins 14-19 (A0-A5)
        uint8_t mask = (1 << (pin - 14));
        if (mode == OUTPUT) {
            DDRC |= mask;
        } else {
            DDRC &= ~mask;
            if (mode == INPUT_PULLUP) PORTC |= mask;
            else                      PORTC &= ~mask;
        }
    }
}

void gpio_write(uint8_t pin, uint8_t val)
{
    if (pin < 8) {                              // PORTD
        if (val) PORTD |=  (1 << pin);
        else     PORTD &= ~(1 << pin);
    }
    else if (pin < 14) {                        // PORTB
        uint8_t bit = pin - 8;
        if (val) PORTB |=  (1 << bit);
        else     PORTB &= ~(1 << bit);
    }
    else if (pin < 20) {                        // PORTC
        uint8_t bit = pin - 14;
        if (val) PORTC |=  (1 << bit);
        else     PORTC &= ~(1 << bit);
    }
}

uint8_t gpio_read(uint8_t pin)
{
    if (pin < 8) {
        return (PIND & (1 << pin)) ? HIGH : LOW;
    }
    else if (pin < 14) {
        uint8_t bit = pin - 8;
        return (PINB & (1 << bit)) ? HIGH : LOW;
    }
    else if (pin < 20) {
        uint8_t bit = pin - 14;
        return (PINC & (1 << bit)) ? HIGH : LOW;
    }
    return LOW;                                 // invalid pin
}

void gpio_toggle(uint8_t pin)
{
    // Atomic toggle: writing 1 to the corresponding bit in PINx register toggles PORTx
    // (single instruction, no read-modify-write, fully interrupt-safe)
    if (pin < 8) {
        PIND = (1 << pin);
    }
    else if (pin < 14) {
        PINB = (1 << (pin - 8));
    }
    else if (pin < 20) {
        PINC = (1 << (pin - 14));
    }
}