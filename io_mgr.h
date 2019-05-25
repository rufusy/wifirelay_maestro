/*
 * io_management.h
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#ifndef IO_MGR_H_
#define IO_MGR_H_

#include "WIFIRelayBoard.h"

void io_init(void);
void channel_select(void);
void channel_1(char channel_action[]);
void channel_2(char channel_action[]);
void channel_3(char channel_action[]);
void channel_4(char channel_action[]);
void channel_5(char channel_action[]);

#endif /* IO_MGR_H_ */
