/*
 * io_management.c
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */

#include "io_management.h"

void io_manager_int(void)
{
    // enable GPIOF
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    // check if peripheral access is enabled
    //while(!SysCtlPeripheralReady(SYSCTL_PERIPH_GPIOF))
    //{

    //}
    //q
    // Enable the GPIO pin for the LED (PF3).  Set the direction as output, and
    // enable the GPIO pin for digital function.
    //
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void LED_off(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0X00);
}

void LED_on(void)
{
    GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3);
}

void LED_blink(void)
{
    volatile uint32_t ui32Loop;
    LED_on();
    // silly delay
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++){}
    LED_off();
    // silly delay
    for(ui32Loop = 0; ui32Loop < 200000; ui32Loop++){}
}
