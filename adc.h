#ifndef ADC_H
#define ADC_H

#include <avr/io.h>
#include <stdint.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void     adc_init(void);                    // call once in setup()
uint16_t adc_read(uint8_t channel);         // returns 0-1023
uint16_t adc_read_mV(uint8_t channel);      // returns voltage in millivolts (0-5000)

#ifdef __cplusplus
}
#endif

#endif