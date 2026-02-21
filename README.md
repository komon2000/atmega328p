# Bare-Metal ATmega328P Driver Library

![ATmega328P](https://img.shields.io/badge/Microcontroller-ATmega328P-blue.svg)
![License](https://img.shields.io/badge/License-MIT-green.svg)
![Language](https://img.shields.io/badge/Language-C%20(Avr-GCC)-orange.svg)

A complete, lightweight, **bare-metal** peripheral driver collection for the **ATmega328P** (and compatible) in pure AVR-GCC C.  
**No Arduino core, no frameworks** — maximum performance and control.

## ✨ Features

- **Full peripheral coverage**:
  | Peripheral       | Files                  | Status |
  |------------------|------------------------|--------|
  | GPIO             | `gpio.c/h`             | ✅     |
  | UART             | `uart.c/h`             | ✅     |
  | ADC              | `adc.c/h`, `adc_freerun.c/h` | ✅ |
  | PWM              | `pwm.c/h`              | ✅     |
  | Timers           | `timer0/1/2.c/h`       | ✅     |
  | I²C              | `i2c.c/h`              | ✅     |
  | SPI              | `spi.c/h`              | ✅     |
  | External/PCINT   | `extint.c/h`, `pcint.c/h` | ✅  |
  | Watchdog + Sleep | `watchdog.c/h`, `sleep.c/h` | ✅ |
  | EEPROM           | `eeprom.c/h`           | ✅     |
  | Clock + BOD      | `clock.c/h`, `bod.c/h` | ✅     |
  | Comparator       | `comparator.c/h`       | ✅     |
  | CRC + HW Random  | `crc.c/h`, `hw_random.c/h` | ✅ |
  | Ring Buffer      | `ringbuffer.c/h`       | ✅     |
  | Scheduler        | `scheduler.c/h`        | ✅     |
  | Debounce         | `debounce.c/h`         | ✅     |
  | Soft UART        | `softuart.c/h`         | ✅     |
  | Temperature      | `temp.c/h`             | ✅     |
  | Bootloader       | `bootloader.c/h`       | ✅     |

- Zero dependencies  
- Interrupt-driven where it makes sense  
- Small footprint (optimized for 328P’s 32 KB flash)  
- Easy to extend or port

## 📁 Project Structure
All drivers live in the root (flat structure for simplicity).  
Future: `src/`, `include/`, `examples/` coming soon.

## 🚀 Getting Started

### 1. Prerequisites
```bash
brew install avr-gcc avrdude  # on macOS
# or use your package manager on Linux/Windows
