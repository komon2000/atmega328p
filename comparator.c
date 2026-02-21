#include "comparator.h"
#include "config.h"

void comparator_init(void)
{
    // Disable digital input buffers on AIN0/AIN1 (power saving + cleaner analog signal)
    DIDR1 |= (1 << AIN0D) | (1 << AIN1D);

    // Disable comparator and clear any pending interrupt flag while configuring
    uint8_t acsr = (1 << ACD) | (1 << ACI);

#ifdef COMPARATOR_MODE_AIN0_VS_BANDGAP
    acsr |= (1 << ACBG);              // Negative input = 1.1V internal bandgap
    // Positive input = AIN0
#else
    // Default mode (COMPARATOR_MODE_AIN0_VS_AIN1 defined):
    // Positive input = AIN0, Negative input = AIN1
    // ACBG stays cleared
#endif

    ACSR = acsr;          // Write configuration (still disabled)
    ACSR &= ~(1 << ACD);  // Enable the comparator
}

uint8_t comparator_read(void)
{
    return (ACSR & (1 << ACO)) ? 1 : 0;  // ACO = 1 when (+) > (-)
}