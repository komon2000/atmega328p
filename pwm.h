#ifndef PWM_H
#define PWM_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hardware PWM Output (Arduino Uno / Nano compatible)
 * Supported pins: 3 (OC2B), 5 (OC0B), 6 (OC0A), 9 (OC1A), 10 (OC1B), 11 (OC2A)
 * Duty cycle: 0–255 (8-bit resolution)
 * Timer1 uses 10-bit mode internally (0–1020) for higher precision
 */
void pwm_init(void);
void pwm_write(uint8_t pin, uint8_t duty);   // 0–255
void pwm_disable(uint8_t pin);

#ifdef __cplusplus
}
#endif
#endif