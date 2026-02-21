#ifndef EXTINT_H
#define EXTINT_H

#include <stdint.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EXTINT_LOW      0
#define EXTINT_CHANGE   1
#define EXTINT_FALLING  2
#define EXTINT_RISING   3

#define EXTINT0         0   // Pin 2
#define EXTINT1         1   // Pin 3

void extint_init(void);
void extint_attach(uint8_t num, uint8_t mode, void (*callback)(void));
void extint_detach(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif