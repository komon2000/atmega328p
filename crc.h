#ifndef CRC_H
#define CRC_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

/**
 * CRC-16-CCITT (polynomial 0x1021, non-reflected)
 * - Initial value: 0xFFFF
 * - Final XOR: 0x0000
 * - Table-driven, stored in flash (PROGMEM)
 */
uint16_t crc16_init(void);
uint16_t crc16_update(uint16_t crc, uint8_t byte);
uint16_t crc16(const uint8_t* data, uint16_t length); // convenience wrapper

#ifdef __cplusplus
}
#endif
#endif