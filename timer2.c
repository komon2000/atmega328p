#include "timer2.h"
#include "gpio.h"
#include "config.h"
#include <avr/io.h>

void timer2_init(void)
{
    // Set PWM pins as outputs using gpio.h (full library consistency)
    gpio_pin_mode(11, OUTPUT);   // OC2A - PB3 (pin 11)
    gpio_pin_mode(3,  OUTPUT);   // OC2B - PD3 (pin 3)

    // Fast PWM 8-bit (mode 3), non-inverting on both channels
    TCCR2A = (1 << WGM21) | (1 << WGM20) | (1 << COM2A1) | (1 << COM2B1);

#ifdef TIMER2_USE_ASYNC
    ASSR |= (1 << AS2);          // Use external 32.768 kHz crystal
    // Wait for async registers to synchronize
    while (ASSR & ((1<<TCN2UB)|(1<<OCR2AUB)|(1<<OCR2BUB)|(1<<TCR2AUB)|(1<<TCR2BUB)));
#endif

    // Prescaler from config.h
#if defined(TIMER2_PRESCALER_1)
    TCCR2B = (1 << CS20);
#elif defined(TIMER2_PRESCALER_8)
    TCCR2B = (1 << CS21);
#elif defined(TIMER2_PRESCALER_32)
    TCCR2B = (1 << CS21) | (1 << CS20);
#elif defined(TIMER2_PRESCALER_64)
    TCCR2B = (1 << CS22);
#elif defined(TIMER2_PRESCALER_128)
    TCCR2B = (1 << CS22) | (1 << CS20);
#elif defined(TIMER2_PRESCALER_256)
    TCCR2B = (1 << CS22) | (1 << CS21);
#else
    TCCR2B = (1 << CS22);        // default /64 (matches config.h)
#endif

    OCR2A = 0;
    OCR2B = 0;
}

void timer2_pwmA(uint8_t duty)
{
    if (duty > 255) duty = 255;

    if (duty == 0) {
        TCCR2A &= ~(1 << COM2A1);           // disconnect pin (clean off)
    } else {
        TCCR2A = (TCCR2A & ~(1 << COM2A0)) | (1 << COM2A1); // non-inverting
        OCR2A = duty;
    }
}

void timer2_pwmB(uint8_t duty)
{
    if (duty > 255) duty = 255;

    if (duty == 0) {
        TCCR2A &= ~(1 << COM2B1);
    } else {
        TCCR2A = (TCCR2A & ~(1 << COM2B0)) | (1 << COM2B1); // non-inverting
        OCR2B = duty;
    }
}

void timer2_disable_pwm(void)
{
    TCCR2A &= ~((1 << COM2A1) | (1 << COM2B1));
}