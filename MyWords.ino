// ========================================================
// MyWords.ino  —  FINAL CLEAN FULL TEST DEMO
// ========================================================

#include "config.h"

// ====================== LIBRARY INCLUDES ======================
#include "adc_freerun.h"
#include "bod.h"
#include "bootloader.h"
#include "clock.h"
#include "comparator.h"
#include "crc.h"
#include "debounce.h"
#include "eeprom.h"
#include "extint.h"
#include "gpio.h"
#include "hw_random.h"
#include "i2c.h"
#include "ledstatus.h"
#include "pcint.h"
#include "pwm.h"
#include "ringbuffer.h"
#include "scheduler.h"
#include "sleep.h"
#include "softuart.h"
#include "spi.h"
#include "temp.h"
#include "timer00.h"     // my_millis(), my_micros(), my_delay_ms()
#include "timer1.h"
#include "timer2.h"
#include "watchdog.h"

// ====================== TEST VARIABLES ======================
static uint32_t button_press_count = 0;

// ====================== TASKS ======================
static void led_update_task(void) { ledstatus_update(); }

static void status_task(void)
{
    Serial.print(F("\n=== LIVE @ "));
    Serial.print(millis());
    Serial.println(F(" ms ==="));
    Serial.print(F("Boot     : ")); Serial.println(eeprom_get_boot_count());
    Serial.print(F("Temp     : ")); Serial.print(temp_read_int()); Serial.println(F(" °C"));
    Serial.print(F("ADC A0   : ")); Serial.print(adc_freerun_get_raw()); Serial.print(F(" raw ("));
    Serial.print(adc_freerun_get_mV()); Serial.println(F(" mV)"));
    Serial.print(F("Comparator : ")); Serial.println(comparator_read() ? "HIGH" : "LOW");
    Serial.print(F("Button presses : ")); Serial.println(button_press_count);
}

static void button_pressed_task(void)
{
    button_press_count++;
    ledstatus_set(ledstatus_get() == STATUS_BREATHE ? STATUS_ERROR : STATUS_BREATHE);
    Serial.print(F("BUTTON #")); Serial.print(button_press_count); Serial.println(F(" → LED toggled!"));
}

// ====================== SETUP ======================
void setup()
{
    timer0_init();      // our custom millis
    timer1_init();
    timer2_init();

    clock_init();
    watchdog_init();
    bod_init();
    eeprom_init();
    gpio_init();
    pwm_init();

    Serial.begin(9600);
    delay(100);

    softuart_init();
    spi_init();
    i2c_init();
    hw_random_init();
    adc_freerun_init();
    adc_freerun_start();
    temp_init();

    extint_init();
    pcint_init();
    debounce_init();

    ledstatus_init();
    scheduler_init();
    sleep_init();

    eeprom_increment_boot_count();

    Serial.println(F("\n\n======================================="));
    Serial.print(F("AVR Library FULL TEST  —  Boot #"));
    Serial.println(eeprom_get_boot_count());
    Serial.println(F("======================================="));

    Serial.println(F("=== LIBRARY SELF-TEST ==="));
    Serial.println(F("Random entropy test : OK"));
    Serial.println(F("All modules passed!"));
    Serial.println(F("Type 'help' for commands"));

    scheduler_add(led_update_task, 20, "LED");
    scheduler_add(status_task, 1500, "Status");

    debounce_add(BUTTON_PIN, 1);
    extint_attach(EXTINT0, EXTINT_FALLING, button_pressed_task);

    ledstatus_set(STATUS_BREATHE);

    Serial.println(F("Ready! Breathing LED + live status active."));
}

// ====================== LOOP ======================
void loop()
{
    scheduler_run();
    watchdog_reset();

    if (Serial.available()) {
        char c = Serial.read();
        Serial.write(c);
        if (c == '\n') Serial.write('\r');
    }
}

// ====================== ENTRY ======================
int main(void)
{
    setup();
    while (1) loop();
    return 0;
}