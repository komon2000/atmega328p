#include <avr/io.h>
#include <util/delay.h>
#include "adc.h"
#include <avr/interrupt.h>
#include <stdlib.h>
#include <stdio.h>

// ===============================================
// RING BUFFER (embedded)
// ===============================================
#define RINGBUFFER_SIZE  6

typedef struct {
    uint16_t buffer[RINGBUFFER_SIZE];
    uint8_t  idx;
    uint32_t sum;
} RingBuffer_t;

void ringbuffer_init(RingBuffer_t *rb, uint16_t initial_value) {
    for (uint8_t i = 0; i < RINGBUFFER_SIZE; i++) rb->buffer[i] = initial_value;
    rb->idx = 0;
    rb->sum = (uint32_t)initial_value * RINGBUFFER_SIZE;
}

void ringbuffer_add(RingBuffer_t *rb, uint16_t value) {
    rb->sum -= rb->buffer[rb->idx];
    rb->buffer[rb->idx] = value;
    rb->sum += value;
    rb->idx = (rb->idx + 1) % RINGBUFFER_SIZE;
}

uint16_t ringbuffer_average(RingBuffer_t *rb) {
    return (uint16_t)(rb->sum / RINGBUFFER_SIZE);
}

// ===============================================
// LIVE TUNABLE VALUES
// ===============================================
volatile uint8_t g_max_step     = 1;   // bigger = faster
volatile uint8_t g_reverse_step = 1;    // on direction change
volatile uint8_t g_update_ms    = 1;    // smaller = faster response

// ===============================================
// VARIABLE DELAY (this fixes the error)
// ===============================================
void delay_ms_var(uint8_t ms) {
    while (ms--) {
        _delay_ms(1);   // 1 is constant → works
        
       // _delay_us(800);   // 1 is constant → works
    }
}

// ===============================================
// UART + RX INTERRUPT (9600 baud)
// ===============================================
volatile char rx_buffer[32];
volatile uint8_t rx_idx = 0;
volatile uint8_t rx_ready = 0;

void uart_init(void) {
    uint16_t ubrr = (F_CPU / 16 / 9600 - 1);
    UBRR0H = (uint8_t)(ubrr >> 8);
    UBRR0L = (uint8_t)ubrr;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);   // 8N1
}

void uart_putc(char c) {
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void uart_print(const char *s) {
    while (*s) uart_putc(*s++);
}

ISR(USART_RX_vect) {
    char c = UDR0;
    if (c == '\r' || c == '\n') {
        if (rx_idx > 0) {
            rx_buffer[rx_idx] = '\0';
            rx_ready = 1;
        }
        rx_idx = 0;
    } else if (rx_idx < 31) {
        rx_buffer[rx_idx++] = c;
    }
}

void process_command(void) {
    if (rx_buffer[0] == 'S') g_max_step     = (uint8_t)atoi(&rx_buffer[1]);
    if (rx_buffer[0] == 'R') g_reverse_step = (uint8_t)atoi(&rx_buffer[1]);
    if (rx_buffer[0] == 'U') g_update_ms    = (uint8_t)atoi(&rx_buffer[1]);
    if (rx_buffer[0] == 'P') {
        char buf[64];
        sprintf(buf, "MAX=%d  REV=%d  UPD=%d\r\n", g_max_step, g_reverse_step, g_update_ms);
        uart_print(buf);
    }
    uart_print("OK\r\n");
}

// ===============================================
// MAP + SERVO (HPS-2018)
// ===============================================
uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max,
             uint16_t out_min, uint16_t out_max) {
    return (uint32_t)(x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

void servo_init(void) {
    TCCR1A = (1 << COM1A1) | (1 << WGM11);
    TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS11) | (1 << CS10);
    ICR1 = 4999;
    DDRB |= (1 << PB1);             // D9
}

void servo_write(uint16_t pos) {
    if (pos < 125) pos = 125;
    if (pos > 625) pos = 625;
    OCR1A = pos;
}
int main(void) __attribute__((OS_main));   // no hidden Arduino startup
int main(void) {
    adc_init();
    servo_init();
    uart_init();
    sei();                          // enable interrupts

    RingBuffer_t pot_rb;
    uint16_t first_pot = adc_read(0);
    ringbuffer_init(&pot_rb, first_pot);

    uint16_t current_pos = map(first_pot, 0, 1023, 125, 625);
    int8_t last_dir = 0;

    uart_print("Servo + Serial ready!\r\nCommands: Sxx Rxx Uxx P\r\n");

    while (1) {
        uint16_t pot = adc_read(0);
        ringbuffer_add(&pot_rb, pot);

        uint16_t avg_pot = ringbuffer_average(&pot_rb);
        uint16_t target = map(avg_pot, 0, 1023, 125, 625);

        // ANTI-STALL + MAX SPEED
        int8_t new_dir = (target > current_pos) ? 1 : (target < current_pos) ? -1 : 0;

        uint8_t step = g_max_step;
        if (new_dir != 0 && last_dir != 0 && new_dir != last_dir) {
            step = g_reverse_step;
        }

        if (current_pos < target) {
            current_pos += (target - current_pos > step) ? step : (target - current_pos);
        } else if (current_pos > target) {
            current_pos -= (current_pos - target > step) ? step : (current_pos - target);
        }

        last_dir = new_dir;

        servo_write(current_pos);

        if (rx_ready) {
            process_command();
            rx_ready = 0;
        }
          _delay_us(2600);
       // delay_ms_var(g_update_ms);   // ← FIXED variable delay
    }
}
