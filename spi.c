#include "spi.h"
#include "gpio.h"
#include "config.h"

void spi_init(void)
{
    // === Pin setup using gpio.h (consistent with entire library) ===
    gpio_pin_mode(10, OUTPUT);                 // SS (default)
    gpio_pin_mode(11, OUTPUT);                 // SCK  (PB5)
    gpio_pin_mode(12, OUTPUT);                 // MOSI (PB3)  wait — Arduino numbering:
    // Arduino pins: 10=PB2 (SS), 11=PB3 (MOSI), 12=PB4 (MISO), 13=PB5 (SCK)
    gpio_pin_mode(13, OUTPUT);                 // SCK
    gpio_pin_mode(11, OUTPUT);                 // MOSI
    gpio_pin_mode(12, INPUT);                  // MISO

    gpio_write(SPI_SS_PIN, HIGH);              // SS idle HIGH

    // === SPI configuration ===
    uint8_t spcr = (1 << SPE) | (1 << MSTR);   // Enable + Master

    // Mode (0-3)
    if (SPI_MODE & 1) spcr |= (1 << CPHA);
    if (SPI_MODE & 2) spcr |= (1 << CPOL);

    // Speed
#if defined(SPI_SPEED_DIV_2)
    SPSR |= (1 << SPI2X);
#elif defined(SPI_SPEED_DIV_4)
    // nothing — default /4
#elif defined(SPI_SPEED_DIV_8)
    SPSR |= (1 << SPI2X);
    spcr |= (1 << SPR0);
#elif defined(SPI_SPEED_DIV_16)
    spcr |= (1 << SPR0);
#elif defined(SPI_SPEED_DIV_32)
    SPSR |= (1 << SPI2X);
    spcr |= (1 << SPR1);
#elif defined(SPI_SPEED_DIV_64)
    spcr |= (1 << SPR1);
#elif defined(SPI_SPEED_DIV_128)
    spcr |= (1 << SPR1) | (1 << SPR0);
#else
    spcr |= (1 << SPR0);                       // default /16
#endif

    SPCR = spcr;
}

uint8_t spi_transfer(uint8_t data)
{
    SPDR = data;
    while (!(SPSR & (1 << SPIF)));
    return SPDR;
}

void spi_write(uint8_t data)
{
    spi_transfer(data);
}

uint8_t spi_read(void)
{
    return spi_transfer(0xFF);
}

// ====================== Chip Select Helpers ======================

void spi_select(uint8_t ss_pin)
{
    gpio_write(ss_pin, LOW);
}

void spi_deselect(uint8_t ss_pin)
{
    gpio_write(ss_pin, HIGH);
}