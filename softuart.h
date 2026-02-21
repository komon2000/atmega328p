#ifndef SOFTUART_H
#define SOFTUART_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Software (bit-banged) UART
 * - TX: Fully functional, blocking, reliable at SOFTUART_BAUD
 * - RX: Placeholder (easy to upgrade later with RingBuffer + PCINT)
 * - Uses gpio.h for full library consistency
 * - Ideal for debug output when hardware UART is busy
 */
void softuart_init(void);

void softuart_putc(char c);
void softuart_puts(const char* str);
void softuart_puts_P(const char* str);     // PROGMEM version (PSTR)
int  softuart_printf(const char* format, ...);

uint8_t softuart_available(void);   // TODO: upgrade with ringbuffer + interrupt
char    softuart_read(void);

#ifdef __cplusplus
}
#endif
#endif