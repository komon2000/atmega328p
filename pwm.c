#include "pwm.h"
#include "gpio.h"
#include "timer00.h"   // Timer0 PWM channels
#include "timer1.h"    // Timer1 PWM channels (10-bit)
#include "timer2.h"    // Timer2 PWM channels
#include "config.h"

static const uint8_t pwm_supported_pins[6] = {3, 5, 6, 9, 10, 11};

void pwm_init(void)
{
    // Set all hardware PWM pins to OUTPUT by default (safe & convenient)
    for (uint8_t i = 0; i < 6; i++) {
        gpio_pin_mode(pwm_supported_pins[i], OUTPUT);
    }

    // Underlying timers are initialized by their own *_init() calls
    // (timer00_init, timer1_init, timer2_init) — called earlier in setup()
}

void pwm_write(uint8_t pin, uint8_t duty)
{
    if (duty > 255) duty = 255;

    switch (pin)
    {
        case 3:  timer2_pwmB(duty);                         break; // OC2B  (PD3)
        case 5:  timer0_pwmB(duty);                         break; // OC0B  (PD5)
        case 6:  timer0_pwmA(duty);                         break; // OC0A  (PD6)
        case 9:  timer1_pwmA((uint16_t)duty << 2);          break; // OC1A  (PB1) — 10-bit
        case 10: timer1_pwmB((uint16_t)duty << 2);          break; // OC1B  (PB2) — 10-bit
        case 11: timer2_pwmA(duty);                         break; // OC2A  (PB3)
        default: /* not a PWM pin — ignore silently */      break;
    }
}

void pwm_disable(uint8_t pin)
{
    pwm_write(pin, 0);   // turns output off cleanly
}