/*
 * io_management.c
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#include "io_mgr.h"
#include "sanitize_cfg.h"
#include "uart_mgr.h"

void
io_init()
{
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_3);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);

    // clear during bootup
    GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);
}

void
channel_select()
{
    //  io manager
    if (strcmp((char*)sanitize_serial_in_cfg[0],"ch1") == 0)    // select channel
        channel_1(sanitize_serial_in_cfg[1]);
    if (strcmp((char*)sanitize_serial_in_cfg[0],"ch2") == 0)
        channel_2(sanitize_serial_in_cfg[1]);
    if (strcmp((char*)sanitize_serial_in_cfg[0],"ch3") == 0)
        channel_3(sanitize_serial_in_cfg[1]);
    if (strcmp((char*)sanitize_serial_in_cfg[0],"ch4") == 0)
        channel_4(sanitize_serial_in_cfg[1]);
    if (strcmp((char*)sanitize_serial_in_cfg[0],"ch5") == 0)
        channel_5(sanitize_serial_in_cfg[1]);
}


void
channel_1(char channel_action[]) //PD0
{
    if (strcmp(channel_action,"high") == 0)
    {
        // channel startup state is high
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
        serial_print("+ch1.high*");
    }

    if (strcmp(channel_action,"low") == 0)
    {  // channel startup state low
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
        serial_print("+ch1.low*");
    }
}

void
channel_2(char channel_action[]) // PD1
{
    if (strcmp(channel_action,"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        serial_print("+ch2.high*");
    }

    if (strcmp(channel_action,"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);
        serial_print("+ch2.low*");
    }
}

void
channel_3(char channel_action[]) // PD2
{
    if (strcmp(channel_action,"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
        serial_print("+ch3.high*");
    }

    if (strcmp(channel_action,"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
        serial_print("+ch3.low*");
    }
}

void
channel_4(char channel_action[]) // PD3
{
    if (strcmp(channel_action,"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);
        serial_print("+ch4.high*");
    }

    if (strcmp(channel_action,"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);
        serial_print("+ch4.low*");
    }
}

void
channel_5(char channel_action[]) // PA5
{
    if (strcmp(channel_action,"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
        serial_print("+ch4.high*");
    }

    if (strcmp(channel_action,"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        serial_print("+ch4.low*");
    }
}






