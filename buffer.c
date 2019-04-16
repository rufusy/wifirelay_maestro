/*
 * buffer.c
 *
 *  Created on: Apr 16, 2019
 *      Author: rufusy
 */

#include "buffer.h"

/*
*/
void buf_reset(circular_buffer *buf, uint16_t size)
{
    buf->head = buf->tail = 0;
    buf->size = size;
}

/*
*/
uint16_t buf_len(const circular_buffer *buf)
{
    volatile uint16_t len = buf->tail - buf->head;
    if (len < 0)
        len += buf->size;
    return len;
}

/*
*/
uint16_t buf_isfull(const circular_buffer *buf)
{
    return buf->head == ((buf->tail + 1) % buf->size);
}

/*
*/
uint16_t buf_isempty(const circular_buffer *buf)
{
    return buf->head == buf->tail;
}


uint8_t buf_get_byte(circular_buffer *buf)
{
    /*
        start head at 0
        end size at 5
        ........
        item = data[0]
        head = (0+1)%5 = 1
        item = data[1]
        head = (1+1)%5 = 2
        item = data[2]
        ........
    */
    uint8_t item = buf->data[buf->head];
    buf->head = (buf->head + 1) % buf->size;
    return item;
}


void buf_put_byte(circular_buffer *buf, uint8_t val)
{
    /*
        start tail at 0
        end size at 5
        ........
        data[0] = val
        tail = (0+1)%5 = 1
        data[1] = val
        tail = (1+1)%5 = 2
        data[2] = val
        ........
    */
    buf->data[buf->tail] = val;
    buf->tail = (buf->tail + 1) % buf->size;
}










