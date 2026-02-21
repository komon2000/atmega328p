#ifndef HW_RANDOM_H
#define HW_RANDOM_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hardware-assisted random number generator
 * - Seeds from real analog noise on RANDOM_ENTROPY_PIN (leave floating/unconnected)
 * - Fast xorshift32 PRNG after seeding
 * - Fully compatible with adc_freerun and normal ADC usage
 */
void hw_random_init(void);           // Call early in setup(), before adc_freerun_init()

uint8_t  hw_random8(void);
uint16_t hw_random16(void);
uint32_t hw_random32(void);
uint32_t hw_random_between(uint32_t min, uint32_t max);

#ifdef __cplusplus
}
#endif
#endif