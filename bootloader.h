#ifndef BOOTLOADER_H
#define BOOTLOADER_H

#include "config.h"

#ifdef __cplusplus
extern "C" {
#endif

void bootloader_jump(void);           // Restart into bootloader for new sketch upload
void bootloader_print_info(void);

#ifdef __cplusplus
}
#endif

#endif