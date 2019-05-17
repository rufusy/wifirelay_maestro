/*
 * relay_management.h
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#ifndef RELAY_MGR_H_
#define RELAY_MGR_H_

#include "WIFIRelayBoard.h"

char relay_no[10];

void relay_select(void);
void relay_nit(void);
void relay_1(char relay_action[]);
void relay_2(char relay_action[]);
void relay_3(char relay_action[]);
void relay_4(char relay_action[]);
void relay_5(char relay_action[]);



#endif /* RELAY_MGR_H_ */
