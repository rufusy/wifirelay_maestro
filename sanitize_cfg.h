/*
 * sanitze_cfg.h
 *
 *  Created on: Apr 1, 2019
 *      Author: rufusy
 */

#ifndef SANITIZE_CFG_H_
#define SANITIZE_CFG_H_

#include "WIFIRelayBoard.h"

extern uint8_t serial_in_cfg[100];
extern uint8_t sanitize_serial_in_cfg[10][10]; //can store 10 words of 10 characters
extern uint8_t i,j,cnt;


void get_serial_in(uint8_t data_in[]);
void sanitize_serial_in(void);


#endif /* SANITIZE_CFG_H_ */
