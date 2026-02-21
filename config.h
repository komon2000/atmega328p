#ifndef CONFIG_H
/* =============================================================================
 *  PIN USAGE & CONFLICT TABLE  (copy-paste this into config.h)
 * =============================================================================
 *
 *  Arduino | AVR   | Functions                              | Major Conflicts
 *  --------|-------|----------------------------------------|------------------------
 *  D0      | PD0   | UART RX                                | -
 *  D1      | PD1   | UART TX                                | -
 *  D2      | PD2   | INT0, PCINT18                          | -
 *  D3      | PD3   | PWM (OC2B)                             | Timer2 PWM
 *  D4      | PD4   | -                                      | -
 *  D5      | PD5   | PWM (OC0B)                             | Timer0 (breaks millis/scheduler!)
 *  D6      | PD6   | PWM (OC0A)                             | Timer0 (breaks millis/scheduler!)
 *  D7      | PD7   | -                                      | -
 *  D8      | PB0   | PCINT0                                 | -
 *  D9      | PB1   | PWM (OC1A)                             | Timer1 PWM
 *  D10     | PB2   | SPI SS / PWM (OC1B)                    | **SPI + Timer1 PWM**
 *  D11     | PB3   | SPI MOSI / PWM (OC2A)                  | **SPI + Timer2 PWM**
 *  D12     | PB4   | SPI MISO                               | SPI
 *  D13     | PB5   | SPI SCK                                | SPI
 *  A0      | PC0   | ADC0                                   | ADC
 *  A1      | PC1   | ADC1                                   | ADC
 *  A2      | PC2   | ADC2                                   | ADC
 *  A3      | PC3   | ADC3                                   | ADC
 *  A4      | PC4   | ADC4 / I2C SDA                         | **ADC + I2C**
 *  A5      | PC5   | ADC5 / I2C SCL                         | **ADC + I2C**
 *
 *  CRITICAL RULES:
 *   - SPI cannot share pins 10 or 11 with PWM.
 *   - I2C (A4/A5) cannot be used as normal ADC at the same time.
 *   - Timer0 PWM (D5/D6) destroys any millis()/delay()-based code.
 *   - Sleep/power-save turns peripherals off – must re-init after wake.
 *
 *  Feature enable flags (set 1/0) – used for future compile checks:
 */
#define USE_UART          1
#define USE_SPI           0
#define USE_I2C           1
#define USE_ADC           1
#define USE_TIMER0_PWM    0     // set 1 only if you don't use timing functions
#define USE_TIMER1_PWM    1
#define USE_TIMER2_PWM    1
#define USE_SLEEP         0
#define CONFIG_H

// ====================== REQUIRED SYSTEM HEADERS ======================
#include <stdint.h>       // uint8_t, uint16_t, etc.
#include <avr/io.h>
#include <avr/pgmspace.h> // PROGMEM
#include <avr/wdt.h>      // WDTO_15MS etc.

// ====================== SYSTEM CLOCK ======================
#define BASE_F_CPU 16000000UL
#define DEFAULT_CLOCK_DIV CLK_DIV_1
#define F_CPU 16000000UL
#define BAUD_RATE 9600

// ====================== ADC SETTINGS ======================
#define ADC_PRESCALER_128
#define ADC_REF_AVCC

// ====================== GPIO SETTINGS ======================
#define LED_PIN 13
#define BUTTON_PIN 2

// ====================== SPI SETTINGS ======================
#define SPI_SS_PIN 10
#define SPI_MODE 0
#define SPI_SPEED_DIV_16

// ====================== I2C / TWI SETTINGS ======================
#define I2C_SPEED_100KHZ
//#define I2C_SPEED_400KHZ

// ====================== ANALOG COMPARATOR SETTINGS ======================
#define COMPARATOR_MODE_AIN0_VS_AIN1
//#define COMPARATOR_MODE_AIN0_VS_BANDGAP

// ====================== TIMER SETTINGS ======================
#define TIMER1_PRESCALER_64
//#define TIMER1_PRESCALER_8
//#define TIMER1_PRESCALER_1

#define TIMER2_PRESCALER_64
//#define TIMER2_USE_ASYNC

// ====================== EXTERNAL INTERRUPTS ======================
#define BUTTON2_PIN 4

// ====================== EEPROM SETTINGS ======================
#define EEPROM_BOOT_COUNT_ADDR 0x00
#define EEPROM_MAGIC_ADDR 0x02
#define EEPROM_MAGIC_VALUE 0x55

// ====================== WATCHDOG TIMER ======================
#define WATCHDOG_TIMEOUT_2S

// ====================== SLEEP MODES ======================
#define SLEEP_MODE_POWER_DOWN
//#define SLEEP_MODE_IDLE

// ====================== BROWN-OUT DETECTION ======================
#define BOD_2V7

// ====================== FREE-RUNNING ADC ======================
#define FREERUN_CHANNEL 0
#define FREERUN_PRESCALER_32

// ====================== SOFTWARE UART ======================
#define SOFTUART_TX_PIN 7
#define SOFTUART_RX_PIN 8
#define SOFTUART_BAUD 9600

// ====================== BUTTON DEBOUNCER ======================
#define DEBOUNCE_TIME_MS 25

// ====================== TASK SCHEDULER ======================
#define MAX_TASKS 12

// ====================== RING BUFFER ======================
#define RINGBUFFER_SIZE 128

// ====================== BOOTLOADER CONTROL ======================
#define BOOTLOADER_TRIGGER_TIME WDTO_15MS

// ====================== LED STATUS INDICATOR ======================
#define STATUS_LED_PIN LED_PIN        // uses Arduino pin 13

// ====================== HARDWARE RANDOM ======================
#define RANDOM_ENTROPY_PIN 7          // A7 — leave unconnected

// ====================== INTERNAL TEMPERATURE SENSOR ======================
#define TEMP_CAL_OFFSET 324.31f
#define TEMP_CAL_SLOPE 1.22f

#endif
