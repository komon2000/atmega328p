#ifndef I2C_H
#define I2C_H
#include <avr/io.h>
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * Hardware TWI (I2C) Master
 * - 100 kHz or 400 kHz (configurable in config.h)
 * - Timeout protection on every operation
 * - High-level register helpers for 95% of sensors/devices
 */
void i2c_init(void);

uint8_t i2c_start(uint8_t addr);        // addr = (device << 1) | R/W bit
void    i2c_stop(void);
uint8_t i2c_write(uint8_t data);        // 0 = ACK received
uint8_t i2c_read_ack(void);             // master sends ACK
uint8_t i2c_read_nack(void);            // master sends NACK (last byte)

// High-level helpers (most common usage)
uint8_t i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data);
uint8_t i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr);   // returns 0xFF on error

#ifdef __cplusplus
}
#endif
#endif