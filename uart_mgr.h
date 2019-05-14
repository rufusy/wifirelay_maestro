/*
 * uart_management.h
 *
 *  Created on: Apr 17, 2019
 *      Author: rufusy
 */

#ifndef UART_MGR_H_
#define UART_MGR_H_

#include "WIFIRelayBoard.h"


extern char outdata[35];
extern char indata[35];
extern char read_flag;

void serial_comm_init(void);
void serial_read(char indata[], char ch);
void serial_print(char outdata[]);


#endif /* UART_MANAGEMENT_H_ */
