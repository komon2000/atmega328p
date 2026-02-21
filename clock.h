#ifndef CLOCK_H
#define CLOCK_H

#include <avr/io.h>
#include <stdint.h>
#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void clock_init(void);                    // Call VERY early in setup()
void clock_set_prescaler(uint8_t div);    // Change speed on the fly
uint32_t clock_get_frequency(void);       // Returns current CPU frequency in Hz

// Prescaler options (safe & common)
#define CLK_DIV_1     0
#define CLK_DIV_2     1
#define CLK_DIV_4     2
#define CLK_DIV_8     3
#define CLK_DIV_16    4
#define CLK_DIV_32    5
#define CLK_DIV_64    6
#define CLK_DIV_128   7
#define CLK_DIV_256   8

#ifdef __cplusplus
}
#endif

#endif