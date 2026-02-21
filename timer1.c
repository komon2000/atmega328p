#include "timer1.h"
#include "gpio.h"
#include "config.h"
#include <avr/io.h>

void timer1_init(void)
{
    // Set PWM pins as outputs using gpio.h (full library consistency)
    gpio_pin_mode(9,  OUTPUT);   // OC1A
    gpio_pin_mode(10, OUTPUT);   // OC1B

    // Fast PWM 10-bit (mode 7), non-inverting on both channels
    TCCR1A = (1 << WGM11) | (1 << WGM10) | (1 << COM1A1) | (1 << COM1B1);
    TCCR1B = (1 << WGM12);

    // Prescaler from config.h (exactly matches timer00 style)
#if defined(TIMER1_PRESCALER_1)
    TCCR1B |= (1 << CS10);
#elif defined(TIMER1_PRESCALER_8)
    TCCR1B |= (1 << CS11);
#elif defined(TIMER1_PRESCALER_64)
    TCCR1B |= (1 << CS11) | (1 << CS10);
#elif defined(TIMER1_PRESCALER_256)
    TCCR1B |= (1 << CS12);
#elif defined(TIMER1_PRESCALER_1024)
    TCCR1B |= (1 << CS12) | (1 << CS10);
#else
    TCCR1B |= (1 << CS11) | (1 << CS10);   // default /64
#endif

    OCR1A = 0;
    OCR1B = 0;
}

void timer1_pwmA(uint16_t duty)
{
    if (duty > 1023) duty = 1023;

    if (duty == 0) {
        TCCR1A &= ~(1 << COM1A1);          // disable output
    } else {
        TCCR1A = (TCCR1A & ~(1 << COM1A0)) | (1 << COM1A1);  // non-inverting
        OCR1A = duty;
    }
}

void timer1_pwmB(uint16_t duty)
{
    if (duty > 1023) duty = 1023;

    if (duty == 0) {
        TCCR1A &= ~(1 << COM1B1);
    } else {
        TCCR1A = (TCCR1A & ~(1 << COM1B0)) | (1 << COM1B1);  // non-inverting
        OCR1B = duty;
    }
}

void timer1_disable_pwm(void)
{
    TCCR1A &= ~((1 << COM1A1) | (1 << COM1B1));
}

uint16_t timer1_get_count(void)
{
    return TCNT1;
}