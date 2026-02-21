#include "eeprom.h"
#include <avr/io.h>
#include <avr/interrupt.h>
#include "config.h"

// ====================== INTERNAL LOW-LEVEL (no name conflict) ======================
static void eeprom_write_byte(uint16_t addr, uint8_t data)
{
    while (EECR & (1 << EEPE));
    uint8_t sreg = SREG;
    cli();
    EEAR = addr;
    EEDR = data;
    EECR = (1 << EEMPE);
    EECR |= (1 << EEPE);
    SREG = sreg;
}

static uint8_t eeprom_read_byte(uint16_t addr)
{
    while (EECR & (1 << EEPE));
    EEAR = addr;
    EECR |= (1 << EERE);
    return EEDR;
}

static void eeprom_write_word(uint16_t addr, uint16_t data)
{
    eeprom_write_byte(addr, (uint8_t)data);
    eeprom_write_byte(addr + 1, (uint8_t)(data >> 8));
}

static uint16_t eeprom_read_word(uint16_t addr)
{
    return ((uint16_t)eeprom_read_byte(addr + 1) << 8) | eeprom_read_byte(addr);
}

// ====================== PUBLIC HIGH-LEVEL API ======================
void eeprom_init(void)
{
    if (eeprom_read_byte(EEPROM_MAGIC_ADDR) != EEPROM_MAGIC_VALUE) {
        eeprom_write_word(EEPROM_BOOT_COUNT_ADDR, 0);
        eeprom_write_byte(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_VALUE);
    }
}

uint16_t eeprom_get_boot_count(void)
{
    if (eeprom_read_byte(EEPROM_MAGIC_ADDR) != EEPROM_MAGIC_VALUE) return 0;
    return eeprom_read_word(EEPROM_BOOT_COUNT_ADDR);
}

void eeprom_increment_boot_count(void)
{
    uint16_t count = eeprom_get_boot_count() + 1;
    eeprom_write_word(EEPROM_BOOT_COUNT_ADDR, count);
    eeprom_write_byte(EEPROM_MAGIC_ADDR, EEPROM_MAGIC_VALUE);
}