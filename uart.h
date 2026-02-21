#ifndef UART_H
#define UART_H
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <stdint.h>
#include "config.h"
#include "ringbuffer.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hardware USART0 (UART)
 * - 8N1 format, configurable baud in config.h
 * - TX: fast blocking
 * - RX: fully interrupt-driven with RingBuffer (lock-free, ISR-safe)
 * - Consistent API with softuart.h
 */
void uart_init(void);

void uart_putchar(char c);
void uart_puts(const char* str);
void uart_puts_P(const char* str);      // PROGMEM version (PSTR)
int  uart_printf(const char* format, ...);

uint8_t uart_available(void);
char    uart_read(void);                // returns 0 if empty

#ifdef __cplusplus
}
#endif
#endif