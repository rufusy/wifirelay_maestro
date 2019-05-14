/*
 * sanitze_cfg.c
 *
 *  Created on: Apr 1, 2019
 *      Author: rufusy
 */

#include "sanitize_cfg.h"
#include "uart_mgr.h"

char serial_in_cfg[100] = {'\0'},
     sanitize_serial_in_cfg[10][10] = {'\0'};    //can store 10 words of 10 characters
char i,j,cnt;

void
get_serial_in(char data_in[])
{
    if(read_flag == 1)
        strcpy(serial_in_cfg,data_in);
    SysCtlDelay(SysCtlClockGet() / (1000 * 3)); //delay ~1 msec for copy operation to finish
}



void
sanitize_serial_in(void)
{
    j=0; cnt=0;
    for(i=0;i<=(strlen(serial_in_cfg));i++)
    {
        // if period or NULL found, assign NULL into splitStrings[cnt]
        if(serial_in_cfg[i]=='.'||serial_in_cfg[i]=='\0')
        {
            sanitize_serial_in_cfg[cnt][j]='\0';
            cnt++;  //for next word
            j=0;    //for next word, init index to 0
        }
        else
        {
            sanitize_serial_in_cfg[cnt][j]=serial_in_cfg[i];
            j++;
        }
    }
}

