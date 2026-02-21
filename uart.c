#include "uart.h"
#include "gpio.h"
#include "ringbuffer.h"
#include "clock.h"          // ← new: uses real runtime frequency
#include "config.h"
#include <stdarg.h>
#include <stdio.h>

static RingBuffer uart_rx_buf;

void uart_init(void)
{
    // Pin setup
    gpio_pin_mode(0, INPUT);      // RXD0
    gpio_pin_mode(1, OUTPUT);     // TXD0

    // Dynamic baud rate based on ACTUAL CPU frequency after clock_init()
    uint32_t f_cpu = clock_get_frequency();
    uint16_t ubrr = f_cpu / 16UL / BAUD_RATE - 1;

    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;

    rb_init(&uart_rx_buf);

    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);   // RX + TX + RX interrupt
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);                 // 8N1
}

void uart_putchar(char c)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_puts(const char* str)
{
    while (*str) uart_putchar(*str++);
}

void uart_puts_P(const char* str)
{
    char c;
    while ((c = pgm_read_byte(str++)) != 0) uart_putchar(c);
}

int uart_printf(const char* format, ...)
{
    char buffer[64];
    va_list args;
    va_start(args, format);
    int len = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    uart_puts(buffer);
    return len;
}

uint8_t uart_available(void)
{
    return rb_available(&uart_rx_buf);
}

char uart_read(void)
{
    char c = 0;
    rb_read(&uart_rx_buf, (uint8_t*)&c);
    return c;
}

ISR(USART_RX_vect)
{
    uint8_t data = UDR0;
    rb_write(&uart_rx_buf, data);
}