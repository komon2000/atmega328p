#include "temp.h"
#include "adc.h"
#include "config.h"
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void temp_init(void)
{
    adc_init();        // Ensure ADC is enabled + prescaler set
}

float temp_read_celsius(void)
{
    uint8_t saved_admux = ADMUX;
    uint8_t sreg = SREG;

    // === Switch to temperature sensor configuration ===
    cli();
    ADMUX = (1 << REFS1) | (1 << REFS0) | 8;   // 1.1 V ref + channel 8
    SREG = sreg;                               // allow interrupts during delay

    _delay_us(120);                            // Reference stabilization (datasheet)

    ADCSRA |= (1 << ADSC);                     // Start conversion
    while (ADCSRA & (1 << ADSC));              // Wait for completion

    uint16_t adc = ADC;

    // === Restore previous ADC settings (critical!) ===
    sreg = SREG;
    cli();
    ADMUX = saved_admux;
    SREG = sreg;

    return (adc - TEMP_CAL_OFFSET) / TEMP_CAL_SLOPE;
}

int8_t temp_read_int(void)
{
    float t = temp_read_celsius();
    return (int8_t)(t + (t >= 0.0f ? 0.5f : -0.5f));   // proper rounding
}