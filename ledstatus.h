#ifndef LEDSTATUS_H
#define LEDSTATUS_H
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Status LED visual indicator
 * - Uses PWM on STATUS_LED_PIN (pin 13 by default)
 * - Update called regularly by scheduler (~50 Hz)
 */
#define STATUS_OFF        0
#define STATUS_ON         1
#define STATUS_BLINK_SLOW 2
#define STATUS_BLINK_FAST 3
#define STATUS_BREATHE    4
#define STATUS_HEARTBEAT  5
#define STATUS_ERROR      6

void ledstatus_init(void);
void ledstatus_set(uint8_t mode);
uint8_t ledstatus_get(void);
void ledstatus_update(void);   // call from scheduler or main loop (~every 20 ms)

#ifdef __cplusplus
}
#endif
#endif