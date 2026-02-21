#include "ringbuffer.h"
#include <util/atomic.h>
#include "config.h"

// Fast wrap-around (RINGBUFFER_SIZE must be power of 2)
#define RB_MASK (RINGBUFFER_SIZE - 1)

void rb_init(RingBuffer* rb)
{
    rb->head  = 0;
    rb->tail  = 0;
    rb->count = 0;
}

uint8_t rb_write(RingBuffer* rb, uint8_t data)
{
    uint8_t success = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if (rb->count < RINGBUFFER_SIZE)
        {
            rb->buffer[rb->head] = data;
            rb->head = (rb->head + 1) & RB_MASK;
            rb->count++;
            success = 1;
        }
    }
    return success;
}

uint8_t rb_read(RingBuffer* rb, uint8_t* data)
{
    uint8_t success = 0;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        if (rb->count > 0)
        {
            *data = rb->buffer[rb->tail];
            rb->tail = (rb->tail + 1) & RB_MASK;
            rb->count--;
            success = 1;
        }
    }
    return success;
}

uint16_t rb_available(RingBuffer* rb)
{
    uint16_t c;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { c = rb->count; }
    return c;
}

uint16_t rb_free(RingBuffer* rb)
{
    return RINGBUFFER_SIZE - rb_available(rb);
}

void rb_clear(RingBuffer* rb)
{
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE)
    {
        rb->head  = 0;
        rb->tail  = 0;
        rb->count = 0;
    }
}

uint8_t rb_is_full(RingBuffer* rb)
{
    uint16_t c;
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) { c = rb->count; }
    return (c == RINGBUFFER_SIZE);
}