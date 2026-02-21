#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"          // <-- from your library

// ===============================================
// Simple map function
// ===============================================
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max,
             uint16_t out_min, uint16_t out_max)
{
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

// ===============================================
// SERVO CONTROL (125 = 0°, 655 = 180°)
// ===============================================
void servo_init(void)
{
    // Timer1: 16-bit Fast PWM, TOP = ICR1, Prescaler 64 → 50 Hz
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);

    ICR1 = 4999;                    // 20 ms period
    DDRB |= (1 << PB1);             // PB1 (D9) as output
}

void servo_write(uint16_t pos)
{
    if (pos < 125) pos = 125;
    if (pos > 655) pos = 655;
    OCR1A = pos;                    // This is the value your servo expects
}

// ===============================================
// MAIN
// ===============================================
int main(void)
{
    adc_init();          // Library ADC init (with DIDR0 = 0xFF already added)
    servo_init();

    uint16_t current_pos = 390;      // Start at ~90° (middle)

    while (1)
    {
        uint16_t pot = adc_read(0);                     // Read potentiometer on A0
        uint16_t target = map(pot, 0, 1023, 125, 655);  // Map 0-1023 → 125-655

        // ===== GRADUAL MOVEMENT (prevents servo stopping on big jumps) =====
        if (target > current_pos) {
            current_pos += 6;       // Change this number for faster/slower response
        }
        else if (target < current_pos) {
            current_pos -= 6;
        }

        servo_write(current_pos);

        _delay_ms(15);   // 15 ms update rate = very smooth (about 67 updates/sec)
    }
}