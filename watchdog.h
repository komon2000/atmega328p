#ifndef WATCHDOG_H
#define WATCHDOG_H
#include "config.h"
#include <avr/wdt.h>
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Watchdog Timer
 * - Timeout set in config.h (WATCHDOG_TIMEOUT_xx)
 * - Call watchdog_reset() regularly (e.g. in scheduler_run() or main loop)
 * - Automatically used by bootloader_jump() for safe reset
 * - Disable before deep sleep if you want maximum power saving
 */
void watchdog_init(void);      // Arm the watchdog
void watchdog_reset(void);     // Feed the dog ("pet the dog")
void watchdog_disable(void);   // Turn off (safe before sleep or bootloader)

#ifdef __cplusplus
}
#endif
#endif