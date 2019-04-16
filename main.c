#include "WIFIRelayBoard.h"
#include "io_management.h"
#include "uart_management.h"

//#include "sanitize_cfg.h"
//#include "buffer.h"



int main(void)
{
    // command
    /**
     * category
     * gpio number
     * direction
     * startup status
     * i/o.p3.output.high
     */

    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);



    //io_manager_int();

    for (;;)
    {
        //get_serial_in();
        //sanitize_serial_in();
        //if (strcmp(sanitize_serial_in_cfg[2],"off") == 0)
         //   LED_on();



    }
}

