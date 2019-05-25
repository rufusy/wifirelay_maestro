/*
 * analog_management.c
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */


#include "analog_mgr.h"
#include "sanitize_cfg.h"
#include "uart_mgr.h"
#include "relay_mgr.h"
#include "io_mgr.h"


uint32_t adc_value[4]= {'\0'},
         an1_lower_threshold = 0,
         an1_upper_threshold = 0,
         an2_upper_threshold = 0,
         an2_lower_threshold = 0,
         an3_upper_threshold = 0,
         an3_lower_threshold = 0,
         an4_upper_threshold = 0,
         an4_lower_threshold = 0;

char    an1_out1[7] = {'\0'},   // analog channel 1
        an1_out2[7] = {'\0'},
        an1_out1_action[5] = {'\0'},
        an1_out2_action[5] = {'\0'},
        an1_out1_counter_action[5] = {'\0'},
        an1_out2_counter_action[5] = {'\0'},
        // analog channel 2
        an2_out1[7] = {'\0'},
        an2_out2[7] = {'\0'},
        an2_out1_action[5] = {'\0'},
        an2_out2_action[5] = {'\0'},
        an2_out1_counter_action[5] = {'\0'},
        an2_out2_counter_action[5] = {'\0'},
        // analog channel 3
        an3_out1[7] = {'\0'},
        an3_out2[7] = {'\0'},
        an3_out1_action[5] = {'\0'},
        an3_out2_action[5] = {'\0'},
        an3_out1_counter_action[5] = {'\0'},
        an3_out2_counter_action[5] = {'\0'},
        // analog channel 4
        an4_out1[7] = {'\0'},
        an4_out2[7] = {'\0'},
        an4_out1_action[5] = {'\0'},
        an4_out2_action[5] = {'\0'},
        an4_out1_counter_action[5] = {'\0'},
        an4_out2_counter_action[5] = {'\0'};


void
analog_init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    GPIOPinTypeADC(GPIO_PORTE_BASE, GPIO_PIN_3 | GPIO_PIN_2 |GPIO_PIN_1);
    GPIOPinTypeADC(GPIO_PORTB_BASE, GPIO_PIN_4);
    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0); // PE3
    ADCSequenceStepConfigure(ADC0_BASE, 1, 1, ADC_CTL_CH1); // PE2
    ADCSequenceStepConfigure(ADC0_BASE, 1, 2, ADC_CTL_CH2); // PE1
    ADCSequenceStepConfigure(ADC0_BASE, 1, 3, ADC_CTL_CH10 | ADC_CTL_IE | ADC_CTL_END);  // PB4
    ADCSequenceEnable(ADC0_BASE,1);
}


void
analog_select(void)
{   // +an1.1000.700.relay1.relay2.high.high*
    if (strcmp((char*)sanitize_serial_in_cfg[0],"an1") == 0)
        analog_1();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"an2") == 0)
        analog_2();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"an3") == 0)
        analog_3();
    if (strcmp((char*)sanitize_serial_in_cfg[0],"an4") == 0)
        analog_4();
}

void
analog_1(void)
{ // save configuration
    an1_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]); // 1000
    an1_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]); // 700
    memset(an1_out1, '\0', sizeof(an1_out1));
    strcpy(an1_out1, sanitize_serial_in_cfg[3]); // relay1

    memset(an1_out2, '\0', sizeof(an1_out2));
    strcpy(an1_out2, sanitize_serial_in_cfg[4]); // relay2

    memset(an1_out1_action, '\0', sizeof(an1_out1_action));
    strcpy(an1_out1_action, sanitize_serial_in_cfg[5]); // high

    memset(an1_out2_action, '\0', sizeof(an1_out2_action));
    strcpy(an1_out2_action, sanitize_serial_in_cfg[6]); // high

    if(strcmp(an1_out1_action,"high") == 0)
        copy_command(an1_out1_counter_action, "low");
    else if(strcmp(an1_out1_action,"low") == 0)
        copy_command(an1_out1_counter_action, "high");

    if(strcmp(an1_out2_action,"high") == 0)
        copy_command(an1_out2_counter_action, "low");
    else if(strcmp(an1_out2_action,"low") == 0)
        copy_command(an1_out2_counter_action, "high");
}

void
analog_2(void)
{
    an2_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]);
    an2_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]);
    memset(an2_out1, '\0', sizeof(an2_out1));
    strcpy(an2_out1, sanitize_serial_in_cfg[3]);

    memset(an2_out2, '\0', sizeof(an2_out2));
    strcpy(an2_out2, sanitize_serial_in_cfg[4]);

    memset(an2_out1_action, '\0', sizeof(an2_out1_action));
    strcpy(an2_out1_action, sanitize_serial_in_cfg[5]);

    memset(an2_out2_action, '\0', sizeof(an2_out2_action));
    strcpy(an2_out2_action, sanitize_serial_in_cfg[6]);

    if(strcmp(an2_out1_action,"high") == 0)
        copy_command(an2_out1_counter_action, "low");
    else if(strcmp(an2_out1_action,"low") == 0)
        copy_command(an2_out1_counter_action, "high");

    if(strcmp(an2_out2_action,"high") == 0)
        copy_command(an2_out2_counter_action, "low");
    else if(strcmp(an2_out2_action,"low") == 0)
        copy_command(an2_out2_counter_action, "high");
}

void
analog_3(void)
{
    an3_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]);
    an3_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]);
    memset(an3_out1, '\0', sizeof(an3_out1));
    strcpy(an3_out1, sanitize_serial_in_cfg[3]);

    memset(an3_out2, '\0', sizeof(an3_out2));
    strcpy(an3_out2, sanitize_serial_in_cfg[4]);

    memset(an3_out1_action, '\0', sizeof(an3_out1_action));
    strcpy(an3_out1_action, sanitize_serial_in_cfg[5]);

    memset(an3_out2_action, '\0', sizeof(an3_out2_action));
    strcpy(an3_out2_action, sanitize_serial_in_cfg[6]);

    if(strcmp(an3_out1_action,"high") == 0)
        copy_command(an3_out1_counter_action, "low");
    else if(strcmp(an3_out1_action,"low") == 0)
        copy_command(an3_out1_counter_action, "high");

    if(strcmp(an3_out2_action,"high") == 0)
        copy_command(an3_out2_counter_action, "low");
    else if(strcmp(an3_out2_action,"low") == 0)
        copy_command(an3_out2_counter_action, "high");
}

void
analog_4(void)
{
    an4_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]);
    an4_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]);
    memset(an4_out1, '\0', sizeof(an4_out1));
    strcpy(an4_out1, sanitize_serial_in_cfg[3]);

    memset(an4_out2, '\0', sizeof(an4_out2));
    strcpy(an4_out2, sanitize_serial_in_cfg[4]);

    memset(an4_out1_action, '\0', sizeof(an4_out1_action));
    strcpy(an4_out1_action, sanitize_serial_in_cfg[5]);

    memset(an4_out2_action, '\0', sizeof(an4_out2_action));
    strcpy(an4_out2_action, sanitize_serial_in_cfg[6]);

    if(strcmp(an4_out1_action,"high") == 0)
        copy_command(an4_out1_counter_action, "low");
    else if(strcmp(an4_out1_action,"low") == 0)
        copy_command(an4_out1_counter_action, "high");

    if(strcmp(an4_out2_action,"high") == 0)
        copy_command(an4_out2_counter_action, "low");
    else if(strcmp(an4_out2_action,"low") == 0)
        copy_command(an4_out2_counter_action, "high");
}



void
copy_command(char dest[], char src[])
{
    memset(dest, '\0', sizeof(dest));
    strcpy(dest, src);
}


void
analog_read(void)
{
    ADCIntClear(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1);
    while(!ADCIntStatus(ADC0_BASE, 1, false));
    ADCSequenceDataGet(ADC0_BASE, 1, adc_value);

    // Analog channel 1
    if(adc_value[0] > an1_upper_threshold)
        analog_channel_relay(an1_out1,an1_out1_action);
    else
        analog_channel_relay(an1_out1,an1_out1_counter_action);


    if(adc_value[0] < an1_lower_threshold)
        analog_channel_relay(an1_out2,an1_out2_action);
    else
        analog_channel_relay(an1_out2,an1_out2_counter_action);


    // Analog channel 2
     if(adc_value[1] > an2_upper_threshold)
         analog_channel_relay(an2_out1,an2_out1_action);
     else
         analog_channel_relay(an2_out1,an2_out1_counter_action);


     if(adc_value[1] < an2_lower_threshold)
         analog_channel_relay(an2_out2,an2_out2_action);
     else
         analog_channel_relay(an2_out2,an2_out2_counter_action);


     // Analog channel 3
      if(adc_value[2] > an3_upper_threshold)
          analog_channel_relay(an3_out1,an3_out1_action);
      else
          analog_channel_relay(an3_out1,an3_out1_counter_action);

      if(adc_value[2] < an3_lower_threshold)
           analog_channel_relay(an3_out2,an3_out2_action);
      else
          analog_channel_relay(an3_out2,an3_out2_counter_action);


      // Analog channel 4
      if(adc_value[3] > an4_upper_threshold)
          analog_channel_relay(an4_out1,an4_out1_action);
      else
          analog_channel_relay(an4_out1,an4_out1_counter_action);

      if(adc_value[3] < an4_lower_threshold)
          analog_channel_relay(an4_out2,an4_out2_action);
      else
          analog_channel_relay(an4_out2,an4_out2_counter_action);

}

void
analog_channel_relay(char analog_hw_interface[], char analog_hw_action[])
{
    if(strcmp(analog_hw_interface,"relay1") == 0)
        relay_1(analog_hw_action);

    if (strcmp(analog_hw_interface,"relay2") == 0)
        relay_2(analog_hw_action);

    if (strcmp(analog_hw_interface,"relay3") == 0)
        relay_3(analog_hw_action);

    if (strcmp(analog_hw_interface,"relay4") == 0)
        relay_4(analog_hw_action);

    if (strcmp(analog_hw_interface,"relay5") == 0)
        relay_5(analog_hw_action);

    if (strcmp(analog_hw_interface,"chan1") == 0)
        channel_1(analog_hw_action);

    if (strcmp(analog_hw_interface,"chan2") == 0)
        channel_2(analog_hw_action);

    if (strcmp(analog_hw_interface,"chan3") == 0)
        channel_3(analog_hw_action);

    if (strcmp(analog_hw_interface,"chan4") == 0)
        channel_4(analog_hw_action);

    if (strcmp(analog_hw_interface,"chan5") == 0)
        channel_5(analog_hw_action);
}

