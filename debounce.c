#include "debounce.h"
#include "gpio.h"      // for gpio_read()
#include "timer00.h"   // for millis() — rename to millis.h if you prefer
#include "config.h"

#define MAX_BUTTONS 8

typedef struct {
    uint8_t  pin;
    uint8_t  active_low;
    uint8_t  stable_state;
    uint8_t  prev_state;      // for clean one-shot rising-edge detection
    uint32_t last_change;
} debounce_t;

static debounce_t buttons[MAX_BUTTONS];
static uint8_t button_count = 0;

void debounce_init(void)
{
    button_count = 0;
}

void debounce_add(uint8_t pin, uint8_t active_low)
{
    if (button_count >= MAX_BUTTONS) return;

    debounce_t *b = &buttons[button_count];

    b->pin         = pin;
    b->active_low  = active_low;
    b->last_change = millis();

    // Initial sample to prevent false edge on first update/was_pressed
    uint8_t raw = gpio_read(pin);
    b->stable_state = b->prev_state = active_low ? (raw == LOW) : (raw == HIGH);

    button_count++;
}

void debounce_update(void)
{
    uint32_t now = millis();

    for (uint8_t i = 0; i < button_count; i++)
    {
        debounce_t *b = &buttons[i];

        uint8_t raw     = gpio_read(b->pin);
        uint8_t current = b->active_low ? (raw == LOW) : (raw == HIGH);

        if (current != b->stable_state)
        {
            // Potential bounce — wait full debounce period
            if (now - b->last_change >= DEBOUNCE_TIME_MS)
            {
                b->stable_state = current;
                b->last_change  = now;
            }
        }
        else
        {
            // Stable — keep resetting the timer
            b->last_change = now;
        }
    }
}

uint8_t debounce_is_pressed(uint8_t pin)
{
    for (uint8_t i = 0; i < button_count; i++) {
        if (buttons[i].pin == pin) {
            return buttons[i].stable_state;
        }
    }
    return 0;
}

uint8_t debounce_was_pressed(uint8_t pin)
{
    for (uint8_t i = 0; i < button_count; i++) {
        if (buttons[i].pin == pin) {
            uint8_t was = (buttons[i].prev_state == 0 && buttons[i].stable_state == 1);
            buttons[i].prev_state = buttons[i].stable_state;
            return was;
        }
    }
    return 0;
}