#ifndef SPI_H
#define SPI_H
#include <avr/io.h>
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hardware SPI Master
 * - Fully compatible with config.h (SPI_MODE, SPI_SPEED_DIV_xx, SPI_SS_PIN)
 * - Uses gpio.h for clean pin control
 * - Supports multiple devices via select/deselect
 */
void spi_init(void);

uint8_t spi_transfer(uint8_t data);   // full duplex
void    spi_write(uint8_t data);      // send only
uint8_t spi_read(void);               // receive only (dummy 0xFF)

void spi_select(uint8_t ss_pin);      // pull SS LOW
void spi_deselect(uint8_t ss_pin);    // pull SS HIGH

#ifdef __cplusplus
}
#endif
#endif