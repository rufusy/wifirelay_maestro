/*
 * sanitze_cfg.c
 *
 *  Created on: Apr 1, 2019
 *      Author: rufusy
 */

#include "sanitize_cfg.h"


void get_serial_in(void)
{
    strcpy(serial_in_cfg,"blink.on.off");
}



void sanitize_serial_in(void)
{
    j=0; cnt=0;
    for(i=0;i<=(strlen(serial_in_cfg));i++)
    {
        // if space or NULL found, assign NULL into splitStrings[cnt]
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
