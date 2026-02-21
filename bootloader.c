#include "bootloader.h"
#include "uart.h"
#include <avr/wdt.h>
#include <avr/interrupt.h>   // ← REQUIRED for cli()
#include <util/delay.h>
#include "config.h"

void bootloader_jump(void)
{
    uart_puts_P(PSTR("\n\n>>> JUMPING TO BOOTLOADER <<<\n"));
    uart_puts_P(PSTR("Please start firmware upload now in Arduino IDE...\n"));
    _delay_ms(200);

    cli();                                   // Disable all interrupts
    wdt_enable(BOOTLOADER_TRIGGER_TIME);     // Short watchdog timeout
    while(1);                                // Wait for watchdog reset
}

void bootloader_print_info(void)
{
    uart_puts_P(PSTR("Bootloader Control active (Optiboot 512-byte compatible)\n"));
    uart_puts_P(PSTR("Call bootloader_jump() anytime to enter programming mode.\n"));
}