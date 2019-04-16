/*
 * uart_management.h
 *
 *  Created on: Apr 17, 2019
 *      Author: rufusy
 */

#ifndef UART_MANAGEMENT_H_
#define UART_MANAGEMENT_H_


#include "sanitize_cfg.h"
#include "buffer.h"

#define BUFLEN 255

circular_buffer _rx_buffer, _tx_buffer;
circular_buffer *const tx_buffer = &_tx_buffer;
circular_buffer *const rx_buffer = &_rx_buffer;

void serial_comm_init(void);
void serial_comm_putchar (uint8_t ch);
uint16_t serial_comm_write(uint8_t *p, uint16_t len);
uint16_t serial_comm_read(uint8_t *p, uint16_t len);



#endif /* UART_MANAGEMENT_H_ */
