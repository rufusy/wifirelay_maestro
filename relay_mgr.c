/*
 * relay_management.c
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#include "relay_mgr.h"
#include "sanitize_cfg.h"
#include "uart_mgr.h"

void relay_select(void)
{
    // relay manager
         if (strcmp((char*)sanitize_serial_in_cfg[0],"rel1") == 0)    // select relay
             relay_1();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"rel2") == 0)
             relay_2();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"rel3") == 0)
             relay_3();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"rel4") == 0)
             relay_4();
         if (strcmp((char*)sanitize_serial_in_cfg[0],"rel5") == 0)
             relay_5();
}


void
relay_nit(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_0);  // relay 1
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_1);  // relay 2
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_5);  // relay 3
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_4);  // relay 4
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_5);  // relay 5
    // set relays at 0v on startup
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
}


void
relay_1(void)
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, GPIO_PIN_0);
        serial_print("+rel1.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_0, 0);
        serial_print("+rel1.low*");
    }
}


void
relay_2(void)
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, GPIO_PIN_1);
        serial_print("+rel2.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_1, 0);
        serial_print("+rel2.low*");
    }
}


void
relay_3(void)
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
        serial_print("+rel3.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
        serial_print("+rel3.low*");
    }
}


void
relay_4(void)
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4);
        serial_print("+rel4.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
        serial_print("+rel4.low*");
    }
}


void
relay_5(void)
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
        serial_print("+rel5.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
        serial_print("+rel5.low*");
    }
}
