#ifndef TIMER00_H
#define TIMER00_H
#include <stdint.h>
#ifdef __cplusplus
extern "C" {
#endif

void timer0_init(void);          // PWM only

void timer0_pwmA(uint8_t duty);  // Pin 6
void timer0_pwmB(uint8_t duty);  // Pin 5

#ifdef __cplusplus
}
#endif
#endif