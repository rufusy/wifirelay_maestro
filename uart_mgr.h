/*
 * uart_management.h
 *
 *  Created on: Apr 17, 2019
 *      Author: rufusy
 */

#ifndef UART_MGR_H_
#define UART_MGR_H_

#include "WIFIRelayBoard.h"


extern uint8_t outdata[35];
extern uint8_t indata[35];
extern uint8_t read_flag;

void serial_comm_init(void);
void serial_read(uint8_t indata[], uint8_t ch);
void serial_print(uint8_t outdata[]);

#endif /* UART_MANAGEMENT_H_ */
