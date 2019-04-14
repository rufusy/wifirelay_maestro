#ifndef _BUFFER_H
#define _BUFFER_H

// 8 bits
typedef signed char     sint8_t;    // -128 to 127
typedef unsigned char   uint8_t;    // 0 to 255
// 16 bits
typedef signed short    sint16_t;   // 32,768 to 32,767
typedef unsigned short  uint16_t;   // 0 to 65,535
// 32 bits
typedef signed int      sint32_t;   // –2,147,483,648 to 2,147,483,647
typedef unsigned int    uint32_t;   // 0 to 4,294,967,295

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

#endif
