/*
 * relay_management.c
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#include "relay_mgr.h"
#include "sanitize_cfg.h"
#include "uart_mgr.h"

void
relay_nit(void)
{
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_6);  // relay 1
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_0);  // relay 2
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_5);  // relay 3
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_4);  // relay 4
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE,GPIO_PIN_5);  // relay 5

    // clear relays during booting
    GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0);
    GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
    GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
}


void relay_select(void)
{
    // relay manager
    if (strcmp((char*)sanitize_serial_in_cfg[0],"relay1") == 0)    // select relay
        relay_1();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"relay2") == 0)
        relay_2();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"relay3") == 0)
        relay_3();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"relay4") == 0)
        relay_4();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"relay5") == 0)
        relay_5();
}


void
relay_1(void) // PD6
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, GPIO_PIN_6);
        serial_print("+relay1.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_6, 0);
        serial_print("+relay1.low*");
    }
}


void
relay_2(void) // PE0
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, GPIO_PIN_0);
        serial_print("+relay2.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0, 0);
        serial_print("+relay2.low*");
    }
}


void
relay_3(void) // PB5
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, GPIO_PIN_5);
        serial_print("+relay3.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTB_BASE, GPIO_PIN_5, 0);
        serial_print("+relay3.low*");
    }
}


void
relay_4(void) // PE4
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, GPIO_PIN_4);
        serial_print("+relay4.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_4, 0);
        serial_print("+relay4.low*");
    }
}


void
relay_5(void) // PE5
{
    if (strcmp((char*)sanitize_serial_in_cfg[1],"high") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, GPIO_PIN_5);
        serial_print("+relay5.high*");
    }

    if (strcmp((char*)sanitize_serial_in_cfg[1],"low") == 0)
    {
        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_5, 0);
        serial_print("+relay5.low*");
    }
}
