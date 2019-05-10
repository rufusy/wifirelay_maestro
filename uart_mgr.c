/*
 * uart_management.c
 *
 *  Created on: Apr 17, 2019
 *      Author: rufusy
 */

#include "uart_mgr.h"


char read_index,
        read_flag = 0,
        indata[35] = {'\0'},
        outdata[35] = {'\0'};

void
serial_comm_init(void)
{
    /*
     *  UART module 2 receive PD6  U2RX
     *  UART module 2 transmit PD7 U2TX
    *//*
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(),
                          115200,
                          (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)
                          );
    UARTFIFODisable(UART0_BASE);
    IntEnable(INT_UART0);   // enable interrupts on UART0
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_TX);   // enable interrupts for rx and tx only

    UARTCharPut(UART0_BASE,'h');
    UARTCharPut(UART0_BASE,'E');
    UARTCharPut(UART0_BASE,'L');
    UARTCharPut(UART0_BASE,'L');
    UARTCharPut(UART0_BASE,'L');
    UARTCharPut(UART0_BASE,'O');
    UARTCharPut(UART0_BASE,' ');
    */

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    GPIOPinConfigure(GPIO_PB0_U1RX);
    GPIOPinConfigure(GPIO_PB1_U1TX);
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART1_BASE,
                        SysCtlClockGet(),
                        115200,
                        (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE)
                        );
    UARTFIFODisable(UART1_BASE);
    IntEnable(INT_UART1);   // enable interrupts on UART0
    UARTIntEnable(UART1_BASE, UART_INT_RX | UART_INT_TX);   // enable interrupts for rx and tx only

    UARTCharPut(UART1_BASE,'h');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'L');
    UARTCharPut(UART1_BASE,'L');
    UARTCharPut(UART1_BASE,'L');
    UARTCharPut(UART1_BASE,'O');
    UARTCharPut(UART1_BASE,' ');
}

/*
 * store input data from  UART channel into indata[]
 * */

void
serial_read(char indata[], char ch)
{
    // sample data received: +red.green.blue*
    if(ch == '+')
    {
        char i;
        for(i =0; i<35; ++i)
        {
            indata[i] = 0;
        }
        read_flag = 0;
        read_index = 0;
    }
    else if(ch != '*')
    {
        indata[read_index] = ch;
        read_index++;
        read_flag = 0;
    }
    else if(ch == '*')
        read_flag = 1;
}


void
serial_print(char outdata[])
{
    char i,j;
    j =  strlen(outdata);
    if(j>0)
    {
        for (i=0; i<j; ++i)
        {
            while(!UARTSpaceAvail(UART1_BASE));
            UARTCharPutNonBlocking(UART1_BASE, outdata[i]);
        }
        while(!UARTSpaceAvail(UART1_BASE));
               UARTCharPutNonBlocking(UART1_BASE,'\n');
    }
}



void
UARTIntHandler(void)
{
    uint32_t ui32Status;
    ui32Status = UARTIntStatus(UART1_BASE, true); //get interrupt status
    UARTIntClear(UART1_BASE, ui32Status); //clear the asserted interrupts

    while(UARTCharsAvail(UART1_BASE)) //loop while there are chars
    {
        serial_read(indata, UARTCharGetNonBlocking(UART1_BASE));
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2); //blink LED
        //SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec
        //GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0); //turn off LED
    }
}
