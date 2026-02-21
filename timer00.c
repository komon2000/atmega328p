#include "timer00.h"
#include <avr/io.h>

void timer0_init(void)
{
    // Fast PWM 8-bit, non-inverting on both channels, /64 prescaler
    TCCR0A = (1 << WGM01) | (1 << WGM00) | (1 << COM0A1) | (1 << COM0B1);
    TCCR0B = (1 << CS01) | (1 << CS00);

    OCR0A = 0;
    OCR0B = 0;
}

void timer0_pwmA(uint8_t duty)
{
    if (duty == 0) {
        TCCR0A &= ~(1 << COM0A1);
    } else {
        TCCR0A = (TCCR0A & ~(1 << COM0A0)) | (1 << COM0A1);
        OCR0A = duty;
    }
}

void timer0_pwmB(uint8_t duty)
{
    if (duty == 0) {
        TCCR0A &= ~(1 << COM0B1);
    } else {
        TCCR0A = (TCCR0A & ~(1 << COM0B0)) | (1 << COM0B1);
        OCR0B = duty;
    }
}