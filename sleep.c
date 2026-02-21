#include "sleep.h"
#include "bod.h"           // Required for deepest power saving
#include <avr/sleep.h>
#include <avr/power.h>
#include "config.h"

void sleep_init(void)
{
    // Nothing to initialize — ready to use
}

void sleep_enter(void)
{
#ifdef SLEEP_MODE_POWER_DOWN
    bod_disable();                    // Critical: saves ~20–30 µA
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    power_all_disable();              // Turn off ADC, timers, USART, TWI, SPI, etc.
#else
    set_sleep_mode(SLEEP_MODE_IDLE);  // IDLE keeps timers & some peripherals alive
#endif

    sleep_enable();
    sleep_cpu();                      // ← CPU sleeps here
    sleep_disable();

    // === Wake-up path ===
#ifdef SLEEP_MODE_POWER_DOWN
    power_all_enable();               // Restore power to peripherals
    bod_enable();                     // Re-enable Brown-Out Detection
#endif
}