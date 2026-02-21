#ifndef BOD_H
#define BOD_H

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void bod_init(void);
void bod_disable(void);           // Use before deep sleep for extra power saving
void bod_enable(void);
uint8_t was_brown_out_reset(void);

#ifdef __cplusplus
}
#endif

#endif