#ifndef TEMP_H
#define TEMP_H
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Internal AVR Temperature Sensor (ATmega328P)
 * - ADC channel 8 with 1.1 V internal bandgap reference
 * - Calibration constants from config.h (TEMP_CAL_OFFSET / TEMP_CAL_SLOPE)
 * - Fully compatible with adc_freerun / adc_read() — restores ADMUX after use
 */
void   temp_init(void);
float  temp_read_celsius(void);
int8_t temp_read_int(void);      // rounded to nearest degree

#ifdef __cplusplus
}
#endif
#endif