#ifndef SLEEP_H
#define SLEEP_H
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Low-Power Sleep Modes
 * - Default (recommended): SLEEP_MODE_POWER_DOWN (deepest sleep, ~0.1 µA)
 * - Alternative: SLEEP_MODE_IDLE (defined in config.h)
 * 
 * In POWER_DOWN mode BOD is automatically disabled during sleep.
 * Wake-up sources: external interrupt (extint), pin-change (pcint), watchdog, etc.
 */
void sleep_init(void);
void sleep_enter(void);     // Put CPU to sleep — call when idle

#ifdef __cplusplus
}
#endif
#endif