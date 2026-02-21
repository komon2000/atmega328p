#include "i2c.h"
#include "config.h"

#define I2C_TIMEOUT  2000   // ~1 ms @ 16 MHz — safe and fast

static uint8_t i2c_wait_twint(void)
{
    uint16_t timeout = I2C_TIMEOUT;
    while (!(TWCR & (1 << TWINT)) && timeout--)
        ;
    return (timeout == 0) ? 1 : 0;   // 1 = timeout
}

void i2c_init(void)
{
    TWCR = 0;                        // reset TWI

#if defined(I2C_SPEED_400KHZ)
    TWBR = 12;                       // 400 kHz @ 16 MHz, prescaler=1
#else
    TWBR = 72;                       // 100 kHz @ 16 MHz (most reliable)
#endif
    TWSR = 0;                        // prescaler = 1
    TWCR = (1 << TWEN);              // enable TWI
}

uint8_t i2c_start(uint8_t addr)
{
    TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
    if (i2c_wait_twint()) return 1;           // timeout

    if ((TWSR & 0xF8) != 0x08) return 2;      // START condition failed

    TWDR = addr;
    TWCR = (1<<TWINT)|(1<<TWEN);
    if (i2c_wait_twint()) return 3;

    uint8_t status = TWSR & 0xF8;
    if (status != 0x18 && status != 0x40)     // SLA+W ACK or SLA+R ACK
        return 4;

    return 0;
}

void i2c_stop(void)
{
    TWCR = (1<<TWINT)|(1<<TWSTO)|(1<<TWEN);
    while (TWCR & (1 << TWSTO));              // wait for STOP to complete
}

uint8_t i2c_write(uint8_t data)
{
    TWDR = data;
    TWCR = (1<<TWINT)|(1<<TWEN);
    if (i2c_wait_twint()) return 1;
    return ((TWSR & 0xF8) == 0x28) ? 0 : 2;   // 0 = ACK received
}

uint8_t i2c_read_ack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEA)|(1<<TWEN);
    if (i2c_wait_twint()) return 0;
    return TWDR;
}

uint8_t i2c_read_nack(void)
{
    TWCR = (1<<TWINT)|(1<<TWEN);              // no ACK
    if (i2c_wait_twint()) return 0;
    return TWDR;
}

// ====================== High-level helpers ======================

uint8_t i2c_write_reg(uint8_t dev_addr, uint8_t reg_addr, uint8_t data)
{
    uint8_t err;
    if ((err = i2c_start(dev_addr << 1))) return err;
    if (i2c_write(reg_addr)) { i2c_stop(); return 10; }
    if (i2c_write(data))     { i2c_stop(); return 11; }
    i2c_stop();
    return 0;
}

uint8_t i2c_read_reg(uint8_t dev_addr, uint8_t reg_addr)
{
    uint8_t data = 0xFF;

    if (i2c_start(dev_addr << 1)) goto error;
    if (i2c_write(reg_addr))      goto error;
    if (i2c_start((dev_addr << 1) | 1)) goto error;   // repeated start + read

    data = i2c_read_nack();
    i2c_stop();
    return data;

error:
    i2c_stop();
    return 0xFF;
}