#include "ledstatus.h"
#include "pwm.h"
#include "timer00.h"   // millis()
#include "gpio.h"
#include "config.h"

static volatile uint8_t current_mode = STATUS_OFF;
static uint32_t last_update = 0;
static uint16_t phase = 0;

void ledstatus_init(void)
{
    gpio_pin_mode(STATUS_LED_PIN, OUTPUT);
    pwm_write(STATUS_LED_PIN, 0);
}

void ledstatus_set(uint8_t mode)
{
    if (mode > STATUS_ERROR) mode = STATUS_OFF;   // safety clamp

    current_mode = mode;
    phase = 0;
    last_update = millis();
}

uint8_t ledstatus_get(void)
{
    return current_mode;
}

void ledstatus_update(void)
{
    uint32_t now = millis();
    if (now - last_update < 20) return;   // ~50 Hz update rate

    last_update = now;
    phase++;

    uint8_t brightness = 0;

    switch (current_mode)
    {
        case STATUS_OFF:
            brightness = 0;
            break;

        case STATUS_ON:
            brightness = 255;
            break;

        case STATUS_BLINK_SLOW:
            brightness = ((phase % 50) < 25) ? 255 : 0;
            break;

        case STATUS_BLINK_FAST:
            brightness = ((phase % 12) < 6) ? 255 : 0;
            break;

        case STATUS_BREATHE:
            {
                // Fast triangle-wave breathing (0 → 255 → 0), ~10 s period
                uint16_t p = phase & 0x1FF;                 // 0-511
                brightness = (p < 256) ? (uint8_t)p : (uint8_t)(511 - p);
            }
            break;

        case STATUS_HEARTBEAT:
            brightness = ((phase % 80) < 8) ? 255 : 0;   // sharp pulse
            break;

        case STATUS_ERROR:
            {
                // Double-flash error pattern
                uint8_t p = phase % 20;
                brightness = ((p < 4) || (p >= 8 && p < 12)) ? 255 : 0;
            }
            break;
    }

    pwm_write(STATUS_LED_PIN, brightness);
}