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
uint32_t lower_threshold,
         upper_threshold;

void adc_init(void);
void adc_sample(void);
void adc_select(void);
void analog_1(void);
void analog_2(void);
void analog_3(void);
void analog_4(void);
void analog_relay(void);

#endif

