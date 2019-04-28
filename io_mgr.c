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
channel_select()
{
    //  io manager
         if (strcmp((char*)sanitize_serial_in_cfg[0],"ch1") == 0)    // select channel
             channel_1();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"ch2") == 0)
             channel_2();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"ch3") == 0)
             channel_3();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"ch4") == 0)
             channel_4();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"ch5") == 0)
             channel_5();
}

void
channel_1(void) //PD0
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"output") == 0)
    {
        // channel direction is output
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0 );
        serial_print("+ch1.output*");   // send the new state
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"input") == 0)
    {
        // channel direction is input
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_0);
        serial_print("+ch1.input*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        // channel startup state is high
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, GPIO_PIN_0);
        serial_print("+ch1.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {  // channel startup state low
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_0, 0);
        serial_print("+ch1.low*");
    }
}

void
channel_2(void) // PD1
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"output") == 0)
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_1 );
        serial_print("+ch2.output*");   // send the new state
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"input") == 0)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_1);
        serial_print("+ch2.input*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, GPIO_PIN_1);
        serial_print("+ch2.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_1, 0);
        serial_print("+ch2.low*");
    }
}

void
channel_3(void) // PD2
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"output") == 0)
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_2);
        serial_print("+ch3.output*");   // send the new state
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"input") == 0)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_2);
        serial_print("+ch3.input*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, GPIO_PIN_2);
        serial_print("+ch3.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_2, 0);
        serial_print("+ch3.low*");
    }
}

void
channel_4(void) // PD3
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"output") == 0)
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_3 );
        serial_print("+ch4.output*");   // send the new state
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"input") == 0)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_3);
        serial_print("+ch4.input*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);
        serial_print("+ch4.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, 0);
        serial_print("+ch4.low*");
    }
}

void
channel_5(void) // PA5
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"output") == 0)
    {
        GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,GPIO_PIN_5);
        serial_print("+ch4.output*");   // send the new state
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"input") == 0)
    {
        GPIOPinTypeGPIOInput(GPIO_PORTA_BASE,GPIO_PIN_5);
        serial_print("+ch4.input*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, GPIO_PIN_5);
        serial_print("+ch4.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_5, 0);
        serial_print("+ch4.low*");
    }
}






