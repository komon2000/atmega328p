#include "watchdog.h"
#include "config.h"
#include <avr/wdt.h>

void watchdog_init(void)
{
    uint8_t wdt_period;

#if defined(WATCHDOG_TIMEOUT_15MS)
    wdt_period = WDTO_15MS;
#elif defined(WATCHDOG_TIMEOUT_30MS)
    wdt_period = WDTO_30MS;
#elif defined(WATCHDOG_TIMEOUT_60MS)
    wdt_period = WDTO_60MS;
#elif defined(WATCHDOG_TIMEOUT_120MS)
    wdt_period = WDTO_120MS;
#elif defined(WATCHDOG_TIMEOUT_250MS)
    wdt_period = WDTO_250MS;
#elif defined(WATCHDOG_TIMEOUT_500MS)
    wdt_period = WDTO_500MS;
#elif defined(WATCHDOG_TIMEOUT_1S)
    wdt_period = WDTO_1S;
#elif defined(WATCHDOG_TIMEOUT_2S)
    wdt_period = WDTO_2S;
#elif defined(WATCHDOG_TIMEOUT_4S)
    wdt_period = WDTO_4S;
#elif defined(WATCHDOG_TIMEOUT_8S)
    wdt_period = WDTO_8S;
#else
    wdt_period = WDTO_2S;          // safe default
#endif

    wdt_enable(wdt_period);
}

void watchdog_reset(void)
{
    wdt_reset();                   // "pet the dog"
}

void watchdog_disable(void)
{
    wdt_disable();
}