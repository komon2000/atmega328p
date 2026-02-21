#ifndef COMPARATOR_H
#define COMPARATOR_H

#include <avr/io.h>
#include <stdint.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void comparator_init(void);
uint8_t comparator_read(void);   // Returns 1 when positive input > negative input

#ifdef __cplusplus
}
#endif

#endif