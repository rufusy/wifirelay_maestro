/*
 * analog_management.h
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */



#ifndef ANALOG_MGR_H_
#define ANALOG_MGR_H_

#include "WIFIRelayBoard.h"

extern uint32_t adc_value[4];

void adc_init(void);
void adc_sample(void);

#endif

