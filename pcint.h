#ifndef PCINT_H
#define PCINT_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Pin Change Interrupts (PCINT)
 * - Any edge on pins 0-19 (Arduino Uno/Nano numbering)
 * - Only the specific pin that changed triggers its callback
 * - Works on PORTB, PORTC, PORTD
 */
void pcint_init(void);
void pcint_attach(uint8_t pin, void (*callback)(void));
void pcint_detach(uint8_t pin);

#ifdef __cplusplus
}
#endif
#endif