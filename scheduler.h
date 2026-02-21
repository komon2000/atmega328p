#ifndef SCHEDULER_H
#define SCHEDULER_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Simple Cooperative Task Scheduler
 * - Non-preemptive, runs in main loop context
 * - Up to MAX_TASKS (defined in config.h, default 12)
 * - Named tasks for easy debugging
 * - Call scheduler_run() frequently in loop()
 */
void scheduler_init(void);
uint8_t scheduler_add(void (*task)(void), uint32_t interval_ms, const char* name);
void    scheduler_enable(uint8_t id);
void    scheduler_disable(uint8_t id);
void    scheduler_run(void);           // Main dispatcher — call often!

#ifdef __cplusplus
}
#endif
#endif