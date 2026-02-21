#include <avr/interrupt.h>  // For sei()
#include "config.h"
#include "uart.h"
#include "gpio.h"
#include "temp.h"
#include "eeprom.h"
#include "timer0.h"

// Define any missing constants if not in config.h (based on typical values)
#ifndef LED_PIN
#define LED_PIN 13
#endif
#ifndef EEPROM_MAGIC_ADDR
#define EEPROM_MAGIC_ADDR 0x00
#endif
#ifndef EEPROM_MAGIC_VALUE
#define EEPROM_MAGIC_VALUE 0xAA
#endif
#ifndef EEPROM_BOOT_COUNT_ADDR
#define EEPROM_BOOT_COUNT_ADDR 0x01
#endif

int main(void) {
    // Initialize system clock if needed (optional, but good practice)
    clock_init();

    // Initialize UART for serial output (e.g., to monitor via serial console at 9600 baud)
    uart_init();

    // Initialize GPIO for LED
    gpio_pin_mode(LED_PIN, OUTPUT);

    // Initialize temperature sensor
    temp_init();

    // Initialize Timer0 for millis() and delay_ms()
    timer0_init();

    // Enable global interrupts (required for Timer0 ISR)
    sei();

    // Increment and print boot count from EEPROM
    eeprom_increment_boot_count();
    uart_printf("Boot count: %u\n", eeprom_get_boot_count());

    // Main loop: Blink LED, read temperature, print via UART
    while (1) {
        // Toggle LED using GPIO
        gpio_toggle(LED_PIN);

        // Read temperature and print
        int8_t temp = temp_read_int();
        uart_printf("Temperature: %d C\n", temp);

        // Delay 1 second using Timer0
        delay_ms(1000);
    }

    return 0;
}