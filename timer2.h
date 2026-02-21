#ifndef TIMER2_H
#define TIMER2_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Timer2 — 8-bit Timer with PWM + optional async crystal
 * - Fast PWM 8-bit (0–255 resolution)
 * - Pins: 11 (OC2A / PB3), 3 (OC2B / PD3)
 * - Prescaler from config.h (TIMER2_PRESCALER_xx)
 * - Optional TIMER2_USE_ASYNC (32.768 kHz crystal on TOSC1/TOSC2)
 * - Used by pwm.h for pins 3 and 11
 */
void timer2_init(void);

void timer2_pwmA(uint8_t duty);   // Pin 11 (OC2A) — 0..255
void timer2_pwmB(uint8_t duty);   // Pin 3  (OC2B) — 0..255

void timer2_disable_pwm(void);

#ifdef __cplusplus
}
#endif
#endif