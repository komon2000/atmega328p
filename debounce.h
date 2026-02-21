#ifndef DEBOUNCE_H
#define DEBOUNCE_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

void debounce_init(void);
void debounce_add(uint8_t pin, uint8_t active_low); // active_low = 1 if button pulls to GND
void debounce_update(void);                         // Call regularly (e.g. every 1-5 ms)
uint8_t debounce_is_pressed(uint8_t pin);           // Current stable state (level)
uint8_t debounce_was_pressed(uint8_t pin);          // One-shot rising edge (true only once)

#ifdef __cplusplus
}
#endif
#endif