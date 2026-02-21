#include "hw_random.h"
#include "adc.h"           // Uses adc_read() → no conflict with adc_freerun
#include "timer00.h"       // for millis()
#include <util/atomic.h>
#include "config.h"

static uint32_t rand_state = 0xA5A5A5A5UL;

void hw_random_init(void)
{
    uint8_t saved_admux = ADMUX;

    // Ensure ADC is enabled (idempotent if adc_freerun already called it)
    adc_init();

    // Collect high-quality entropy from floating pin + system timing noise
    uint32_t seed = 0xA5A5A5A5UL;
    for (uint8_t i = 0; i < 32; i++)
    {
        uint16_t noise = adc_read(RANDOM_ENTROPY_PIN);   // 10 bits of real analog noise
        seed ^= (uint32_t)noise;
        seed ^= millis();
    }

    rand_state = seed;

    ADMUX = saved_admux;   // Restore original ADC channel/reference (important!)
}

static uint32_t xorshift32(void)
{
    uint32_t x;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        x = rand_state;
        x ^= x << 13;
        x ^= x >> 17;
        x ^= x << 5;
        rand_state = x;
    }
    return x;
}

uint8_t hw_random8(void)
{
    return (uint8_t)xorshift32();
}

uint16_t hw_random16(void)
{
    return (uint16_t)xorshift32();
}

uint32_t hw_random32(void)
{
    return xorshift32();
}

uint32_t hw_random_between(uint32_t min, uint32_t max)
{
    if (min >= max) return min;
    uint32_t range = max - min;
    // Unbiased distribution using 64-bit multiplication (no modulo bias)
    return min + (uint32_t)(((uint64_t)hw_random32() * range) >> 32);
}