#ifndef TIMER0_H
#define TIMER0_H

#include <stdint.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void     timer0_init(void);
uint32_t millis(void);
uint32_t micros(void);
void     delay_ms(uint32_t ms);
void timer0_pwmA(uint8_t duty);   // Pin 6  (OC0A)
void timer0_pwmB(uint8_t duty);   // Pin 5  (OC0B)

#ifdef __cplusplus
}
#endif

#endif