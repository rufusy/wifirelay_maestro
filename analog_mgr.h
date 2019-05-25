/*
 * analog_management.h
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */



#ifndef ANALOG_MGR_H_
#define ANALOG_MGR_H_

#include "WIFIRelayBoard.h"

extern uint32_t adc_value[4],
                an1_lower_threshold,
                an1_upper_threshold,

                an2_lower_threshold,
                an2_upper_threshold,

                an3_lower_threshold,
                an3_upper_threshold,

                an4_lower_threshold,
                an4_upper_threshold;


extern char an1_out1[7],    // analog channel 1
            an1_out2[7],
            an1_out1_action[5],
            an1_out2_action[5],
            an1_out1_counter_action[5],
            an1_out2_counter_action[5],
            // analog channel 2
            an2_out1[7],
            an2_out2[7],
            an2_out1_action[5],
            an2_out2_action[5],
            an2_out1_counter_action[5],
            an2_out2_counter_action[5],
            // analog channel 3
            an3_out1[7],
            an3_out2[7],
            an3_out1_action[5],
            an3_out2_action[5],
            an3_out1_counter_action[5],
            an3_out2_counter_action[5],
            // analog channel 4
            an4_out1[7],
            an4_out2[7],
            an4_out1_action[5],
            an4_out2_action[5],
            an4_out1_counter_action[5],
            an4_out2_counter_action[5];


void analog_init(void);
void analog_read(void);
void analog_select(void);
void analog_1(void);
void analog_2(void);
void analog_3(void);
void analog_4(void);
void analog_channel_relay(char analog_hw_interface[], char analog_hw_action[]);
void copy_command(char dest[], char src[]);

#endif

