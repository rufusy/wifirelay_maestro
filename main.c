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
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2); // rx indicator LED
    serial_comm_init();
    relay_nit();
    adc_init();
    IntMasterEnable();  // enable processor interrupts
    for (;;)
    {
        get_serial_in(indata);
        sanitize_serial_in();
        adc_sample();
    }
}

