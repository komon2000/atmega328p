#include "softuart.h"
#include "gpio.h"
#include "config.h"
#include <util/delay.h>
#include <stdarg.h>
#include <stdio.h>
#include <avr/pgmspace.h>

#define BIT_TIME_US (1000000UL / SOFTUART_BAUD)

static uint8_t tx_pin, rx_pin;

void softuart_init(void)
{
    tx_pin = SOFTUART_TX_PIN;
    rx_pin = SOFTUART_RX_PIN;

    gpio_pin_mode(tx_pin, OUTPUT);
    gpio_write(tx_pin, HIGH);           // UART idle state is HIGH

    gpio_pin_mode(rx_pin, INPUT_PULLUP);
}

void softuart_putc(char c)
{
    // Start bit
    gpio_write(tx_pin, LOW);
    _delay_us(BIT_TIME_US);

    // 8 data bits, LSB first
    for (uint8_t i = 0; i < 8; i++) {
        gpio_write(tx_pin, (c & 1) ? HIGH : LOW);
        c >>= 1;
        _delay_us(BIT_TIME_US);
    }

    // Stop bit + small safety margin
    gpio_write(tx_pin, HIGH);
    _delay_us(BIT_TIME_US + (BIT_TIME_US / 2));
}

void softuart_puts(const char* str)
{
    while (*str) softuart_putc(*str++);
}

void softuart_puts_P(const char* str)
{
    char c;
    while ((c = pgm_read_byte(str++)) != 0) {
        softuart_putc(c);
    }
}

int softuart_printf(const char* format, ...)
{
    char buffer[64];                    // Small to save RAM on AVR
    va_list args;
    va_start(args, format);
    int n = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    softuart_puts(buffer);
    return n;
}

// ====================== RX - Placeholder (easy to upgrade) ======================
// TODO: Upgrade to interrupt-driven (PCINT or Timer) + RingBuffer when needed
uint8_t softuart_available(void)
{
    return 0;
}

char softuart_read(void)
{
    return 0;
}