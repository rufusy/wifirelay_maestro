/*
 * uart_management.c
 *
 *  Created on: Apr 17, 2019
 *      Author: rufusy
 */

#include "uart_management.h"


void serial_comm_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //enable GPIO port for LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2); //enable pin for LED PF2
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(),
                        115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)
                        );
    IntMasterEnable();  // enable processor interrupts
    IntEnable(INT_UART0);   // enable interrupts on UART0
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_TX);   // enable interrupts for rx and tx only

    // initialize tx_buffer, rx_buffer
    buf_reset(tx_buffer,BUFLEN);
    buf_reset(rx_buffer,BUFLEN);

    UARTCharPut(UART0_BASE,'E');
    UARTCharPut(UART0_BASE,'n');
    UARTCharPut(UART0_BASE,'t');
    UARTCharPut(UART0_BASE,'e');
    UARTCharPut(UART0_BASE,'r');
    UARTCharPut(UART0_BASE,' ');
    UARTCharPut(UART0_BASE,'t');
    UARTCharPut(UART0_BASE,'e');
    UARTCharPut(UART0_BASE,'x');
    UARTCharPut(UART0_BASE,'t');
    UARTCharPut(UART0_BASE,':');
    UARTCharPut(UART0_BASE,' ');
}

// send single char
void serial_comm_putchar (uint8_t ch)
{
    // wait until space is available in FIFO then send char
    while(!UARTSpaceAvail(UART0_BASE));
    UARTCharPutNonBlocking(UART0_BASE, (uint8_t)ch);
}



uint16_t serial_comm_write(uint8_t *p, uint16_t len)
{
    uint16_t i;
    for (i=0; i<len; ++i)
    {
        while(buf_isfull(tx_buffer)); // spin wait
        buf_put_byte(tx_buffer, *p++);
        UARTIntEnable(UART0_BASE, UART_INT_TX);   // turn on tx interrupt
    }
}


// receive single char
uint16_t serial_comm_read(uint8_t *p, uint16_t len)
{
    uint16_t i = len;
    while(i > 0)
    {
        while(buf_isempty(rx_buffer)); // spin wait
        *p++ = buf_get_byte(rx_buffer);
        UARTIntEnable(UART0_BASE, UART_INT_RX);   // turn on rx interrupt
        i--;
    }
    return len -i;
}



void UARTIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status

    // if data is in tx buffer
    if(!buf_isempty(tx_buffer))
    {
        UARTCharPutNonBlocking(UART0_BASE, buf_get_byte(tx_buffer));
        if(buf_isempty(tx_buffer))  // if tx buffer is empty
            UARTDisable(UART0_BASE, UART_INT_TX);   // disable tx interrupts
    }

    // if the receive buffer is not full
    if(!buf_isfull(rx_buffer))
    {
        while(UARTCharsAvail(UART0_BASE))
        {
            buf_put_byte(rx_buffer,UARTCharGetNonBlocking(UART0_BASE));
        }
        if(buf_isfull(rx_buffer))
            UARTDisable(UART0_BASE, UART_INT_RX);   // disable rx interrupts
    }


    /*
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART0_BASE, true); //get interrupt status
    UARTIntClear(UART0_BASE, ui32Status); //clear the asserted interrupts
    while(UARTCharsAvail(UART0_BASE)) //loop while there are chars
    {
        UARTCharPutNonBlocking(UART0_BASE, UARTCharGetNonBlocking(UART0_BASE)); //echo character
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
        SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); //turn off LED
    }
    */
}
