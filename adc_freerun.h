#ifndef ADC_FREERUN_H
#define ADC_FREERUN_H

#include "config.h"
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

void adc_freerun_init(void);
void adc_freerun_start(void);
void adc_freerun_stop(void);
uint16_t adc_freerun_get_raw(void);      // instant latest value
uint16_t adc_freerun_get_mV(void);       // instant mV (5V ref)
void adc_freerun_attach(void (*callback)(uint16_t raw, uint16_t mV));

#ifdef __cplusplus
}
#endif

#endif