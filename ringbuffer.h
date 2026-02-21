#ifndef RINGBUFFER_H
#define RINGBUFFER_H
#include <stdint.h>
#include "config.h"

typedef struct {
    uint8_t          buffer[RINGBUFFER_SIZE];
    volatile uint16_t head;
    volatile uint16_t tail;
    volatile uint16_t count;
} RingBuffer;

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Lock-free Ring Buffer (Circular FIFO)
 * - Fully interrupt-safe (ATOMIC_BLOCK)
 * - Optimized for power-of-two size (128 bytes)
 * - Ideal for UART, SoftUART, sensor queues, command buffers, etc.
 */
void     rb_init(RingBuffer* rb);
uint8_t  rb_write(RingBuffer* rb, uint8_t data);     // 1 = success
uint8_t  rb_read(RingBuffer* rb, uint8_t* data);     // 1 = success
uint16_t rb_available(RingBuffer* rb);               // bytes ready to read
uint16_t rb_free(RingBuffer* rb);                    // free space
void     rb_clear(RingBuffer* rb);
uint8_t  rb_is_full(RingBuffer* rb);

#ifdef __cplusplus
}
#endif
#endif