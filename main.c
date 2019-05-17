#include "uart_mgr.h"
#include "sanitize_cfg.h"
#include "io_mgr.h"
#include "relay_mgr.h"
#include "analog_mgr.h"



int
main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_3 | GPIO_PIN_2 | GPIO_PIN_1 ); //enable pin for LED PF2,1
    io_init();
    serial_comm_init();
    relay_nit();
    analog_init();
    IntMasterEnable();  // enable processor interrupts
    for (;;)
    {
        // filter the incoming data from uart1 for usage
        get_serial_in(indata);
        sanitize_serial_in();

        // manage relays, digital and analog IOs
        relay_select();
        channel_select();
        analog_select();
        analog_read();
    }
}

