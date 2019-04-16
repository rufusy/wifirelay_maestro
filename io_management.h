/*
 * io_management.h
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#ifndef IO_MANAGEMENT_H_
#define IO_MANAGEMENT_H_

#include "WIFIRelayBoard.h"

/*
 *  below   configuration  command maps    to:
 *  0   ->  i/o management
 *  1   ->  GPIO1
 *  1   ->  output
 *  1  ->  wake up status (high)
 * */




char* manager;  // in this case i/o management
char* pin_number;   // gpio pin on PORTB
char* pin_direction;    // output/input
char* startup_state;    // pin state when board is operating high/low
char* operating_state;  // pin state when board wakes up high/low


char* sanitize_command;
char* serial_command[3];
int state;
char* command;

void io_manager_int(void);
void serial_config_sanitize(void);
void LED_blink(void);
void LED_off(void);
void LED_on(void);

#endif /* IO_MANAGEMENT_H_ */
