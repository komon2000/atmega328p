#ifndef EEPROM_H
#define EEPROM_H
#include <stdint.h>
#include "config.h"
#ifdef __cplusplus
extern "C" {
#endif

void     eeprom_init(void);

uint16_t eeprom_get_boot_count(void);
void     eeprom_increment_boot_count(void);

#ifdef __cplusplus
}
#endif
#endif