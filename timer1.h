#ifndef TIMER1_H
#define TIMER1_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Timer1 — 16-bit Timer with 10-bit PWM
 * - Fast PWM mode (TOP = 1023, 10-bit resolution)
 * - Pins: 9 (OC1A), 10 (OC1B)
 * - Prescaler from config.h (TIMER1_PRESCALER_xx)
 * - Used by pwm_write() for pins 9 & 10
 */
void timer1_init(void);

void timer1_pwmA(uint16_t duty);   // Pin 9  (OC1A) — 0..1023
void timer1_pwmB(uint16_t duty);   // Pin 10 (OC1B) — 0..1023

void timer1_disable_pwm(void);

uint16_t timer1_get_count(void);   // Read current TCNT1 value

#ifdef __cplusplus
}
#endif
#endif