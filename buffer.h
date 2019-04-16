/*
 * buffer.h
 *
 *  Created on: Apr 16, 2019
 *      Author: rufusy
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "WIFIRelayBoard.h"

typedef struct
{
    uint8_t data[];
    uint16_t head;
    uint16_t tail;
    uint16_t size;
}circular_buffer;


void buf_reset(circular_buffer *buf, uint16_t size);
uint16_t buf_len(const circular_buffer *buf);
uint16_t buf_isfull(const circular_buffer *buf);
uint16_t buf_isempty(const circular_buffer *buf);
uint8_t buf_get_byte(circular_buffer *buf);
void buf_put_byte(circular_buffer *buf, uint8_t val);




#endif /* BUFFER_H_ */
