#include "adc_freerun.h"
#include "config.h"
#include <avr/interrupt.h>

static void (*adc_callback)(uint16_t, uint16_t) = 0;
volatile uint16_t adc_freerun_latest = 0;

ISR(ADC_vect)
{
    adc_freerun_latest = ADC;               // auto-clears ADIF

    if (adc_callback)
    {
        uint16_t mv;
#if defined(ADC_REF_AVCC)
        mv = (uint32_t)adc_freerun_latest * 5000UL / 1024UL;
#elif defined(ADC_REF_1V1)
        mv = (uint32_t)adc_freerun_latest * 1100UL / 1024UL;
#else
        mv = 0;
#endif
        adc_callback(adc_freerun_latest, mv);
    }
}

void adc_freerun_init(void)
{
    // Disable ADC first → safe to change reference/prescaler/ADATE/ADIE
    ADCSRA &= ~(1 << ADEN);

    // Reference + channel (exactly mirrors adc.c logic)
#if defined(ADC_REF_AVCC)
    ADMUX = (1 << REFS0) | (FREERUN_CHANNEL & 0x0F);
#elif defined(ADC_REF_1V1)
    ADMUX = (1 << REFS1) | (1 << REFS0) | (FREERUN_CHANNEL & 0x0F);
#else
    ADMUX = (FREERUN_CHANNEL & 0x0F);
#endif

    // Full ADCSRA in one write (ADEN + ADATE + ADIE + chosen prescaler)
#if defined(FREERUN_PRESCALER_32)
    ADCSRA = (1<<ADPS2) | (1<<ADPS0) | (1<<ADEN) | (1<<ADATE) | (1<<ADIE);  // /32
#elif defined(FREERUN_PRESCALER_16)
    ADCSRA = (1<<ADPS2)               | (1<<ADEN) | (1<<ADATE) | (1<<ADIE);  // /16
#else
    ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0) | (1<<ADEN)|(1<<ADATE)|(1<<ADIE); // /128 (fallback)
#endif

    ADCSRB = 0;   // Free-running mode (ADTS = 000)
}

void adc_freerun_start(void)
{
    ADCSRA |= (1 << ADSC);   // kick off the first conversion → free-runs
}

void adc_freerun_stop(void)
{
    ADCSRA &= ~(1 << ADIE);  // stop interrupts (conversions can continue quietly)
}

uint16_t adc_freerun_get_raw(void)
{
    uint16_t val;
    uint8_t sreg = SREG;
    cli();
    val = adc_freerun_latest;
    SREG = sreg;
    return val;
}

uint16_t adc_freerun_get_mV(void)
{
#if defined(ADC_REF_AVCC)
    return (uint32_t)adc_freerun_get_raw() * 5000UL / 1024UL;
#elif defined(ADC_REF_1V1)
    return (uint32_t)adc_freerun_get_raw() * 1100UL / 1024UL;
#else
    return 0;
#endif
}

void adc_freerun_attach(void (*callback)(uint16_t raw, uint16_t mV))
{
    adc_callback = callback;
}