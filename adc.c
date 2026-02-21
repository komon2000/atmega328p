#include "adc.h"
#include "config.h"

void adc_init(void)
{
    // Set reference voltage
#if defined(ADC_REF_AVCC)
    ADMUX = (1 << REFS0); // AVCC with external capacitor at AREF
#elif defined(ADC_REF_1V1)
    ADMUX = (1 << REFS1) | (1 << REFS0); // 1.1V internal
#else
    ADMUX = 0; // AREF pin
#endif

    // Prescaler
#if defined(ADC_PRESCALER_128)
    ADCSRA = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0); // /128
#else
    ADCSRA = (1 << ADPS2) | (1 << ADPS1); // /64 default
#endif

    // ====================== ADC FIX (added here) ======================
    DIDR0 = 0xFF;   // Disable digital input buffers on ADC0–ADC7
                    // → cleaner potentiometer readings + lower power

    ADCSRA |= (1 << ADEN); // enable ADC
}

uint16_t adc_read(uint8_t channel)
{
    // Select channel (0-7 on Uno/Nano) and clear high bits
    ADMUX = (ADMUX & 0xF0) | (channel & 0x07);
    ADCSRA |= (1 << ADSC); // start single conversion
    while (ADCSRA & (1 << ADSC)); // wait until done
    return ADC; // 10-bit result (0-1023)
}

uint16_t adc_read_mV(uint8_t channel)
{
    uint16_t raw = adc_read(channel);
#ifdef ADC_REF_AVCC
    return (uint32_t)raw * 5000UL / 1024UL;
#else
    return (uint32_t)raw * 1100UL / 1024UL;
#endif
}