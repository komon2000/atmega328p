#ifndef GPIO_H
#define GPIO_H
#include <avr/io.h>
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

// Arduino Uno / Nano compatible pin numbers
// 0-7   → PORTD (PD0-PD7)
// 8-13  → PORTB (PB0-PB5)
// 14-19 → PORTC (PC0-PC5 / A0-A5)

#define INPUT        0
#define OUTPUT       1
#define INPUT_PULLUP 2

#define LOW          0
#define HIGH         1

void gpio_init(void);                  // Call early in setup()
void gpio_pin_mode(uint8_t pin, uint8_t mode);
void gpio_write(uint8_t pin, uint8_t val);
uint8_t gpio_read(uint8_t pin);
void gpio_toggle(uint8_t pin);

#ifdef __cplusplus
}
#endif
#endif