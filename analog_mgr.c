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


uint32_t adc_value[4]= {'\0'},
         an1_lower_threshold = 0,
         an1_upper_threshold = 0,
         an2_upper_threshold = 0,
         an2_lower_threshold = 0,
         an3_upper_threshold = 0,
         an3_lower_threshold = 0,
         an4_upper_threshold = 0,
         an4_lower_threshold = 0;

char    an1_relay[7] = {'\0'},
        an1_channel[5] = {'\0'},
        an1_action[5] = {'\0'},
        an1_counter_action[5] = {'\0'},

        an2_relay[7] = {'\0'},
        an2_channel[5] = {'\0'},
        an2_action[5] = {'\0'},
        an2_counter_action[5] = {'\0'},

        an3_relay[7] = {'\0'},
        an3_channel[5] = {'\0'},
        an3_action[5] = {'\0'},
        an3_counter_action[5] = {'\0'},

        an4_relay[7] = {'\0'},
        an4_channel[5] = {'\0'},
        an4_action[5] = {'\0'},
        an4_counter_action[5] = {'\0'};


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
{   // an1.1000.500.none.relay1.high
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
    memset(an1_channel, '\0', sizeof(an1_channel));
    strcpy(an1_channel, sanitize_serial_in_cfg[3]); // none
    memset(an1_relay, '\0', sizeof(an1_relay));
    strcpy(an1_relay, sanitize_serial_in_cfg[4]); // relay1
    memset(an1_action, '\0', sizeof(an1_action));
    strcpy(an1_action, sanitize_serial_in_cfg[5]); // high
}

void
analog_2(void)
{
    an2_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]);
    an2_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]);
    memset(an2_channel, '\0', sizeof(an2_channel));
    strcpy(an2_channel, sanitize_serial_in_cfg[3]);
    memset(an2_relay, '\0', sizeof(an2_relay));
    strcpy(an2_relay, sanitize_serial_in_cfg[4]);
    memset(an2_action, '\0', sizeof(an2_action));
    strcpy(an2_action, sanitize_serial_in_cfg[5]);
}

void
analog_3(void)
{
    an3_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]);
    an3_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]);
    memset(an3_channel, '\0', sizeof(an3_channel));
    strcpy(an3_channel, sanitize_serial_in_cfg[3]);
    memset(an3_relay, '\0', sizeof(an3_relay));
    strcpy(an3_relay, sanitize_serial_in_cfg[4]);
    memset(an3_action, '\0', sizeof(an3_action));
    strcpy(an3_action, sanitize_serial_in_cfg[5]);
}

void
analog_4(void)
{
    an4_upper_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[1]);
    an4_lower_threshold = (uint32_t)atoi(sanitize_serial_in_cfg[2]);
    memset(an4_channel, '\0', sizeof(an4_channel));
    strcpy(an4_channel, sanitize_serial_in_cfg[3]);
    memset(an4_relay, '\0', sizeof(an4_relay));
    strcpy(an4_relay, sanitize_serial_in_cfg[4]);
    memset(an4_action, '\0', sizeof(an4_action));
    strcpy(an4_action, sanitize_serial_in_cfg[5]);
}

uint32_t limit = 2000, limit2 = 3000;


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
    if(adc_value[0] <  an1_lower_threshold  || adc_value[0] >  an1_upper_threshold)
    {
        if(strcmp(an1_action,"high") == 0)
            copy_command(an1_counter_action, "low");
        if(strcmp(an1_action,"low") == 0)
            copy_command(an1_counter_action, "high");
        analog_relay(an1_relay,an1_action);
    }
    else
        analog_relay(an1_relay,an1_counter_action);


    // Analog channel 2
    if(adc_value[1] <  an2_lower_threshold  || adc_value[1] >  an2_upper_threshold)
    {
        analog_relay(an2_relay,an2_action);
        if(strcmp(an2_action,"high") == 0)
            copy_command(an2_counter_action, "low");
        if(strcmp(an2_action,"low") == 0)
            copy_command(an2_counter_action, "high");
    }
    else
        analog_relay(an2_relay,an2_counter_action);


    // Analog channel 3
    if(adc_value[2] <  an3_lower_threshold  || adc_value[2] >  an3_upper_threshold)
    {
        analog_relay(an3_relay,an3_action);
        if(strcmp(an3_action,"high") == 0)
            copy_command(an3_counter_action, "low");
        if(strcmp(an3_action,"low") == 0)
            copy_command(an3_counter_action, "high");
    }
    else
        analog_relay(an3_relay,an3_counter_action);


    // Analog channel 4
    if(adc_value[3] <  an4_lower_threshold  || adc_value[3] >  an4_upper_threshold)
    {
        analog_relay(an4_relay,an4_action);
        if(strcmp(an4_action,"high") == 0)
            copy_command(an4_counter_action, "low");
        if(strcmp(an4_action,"low") == 0)
            copy_command(an4_counter_action, "high");
    }
    else
        analog_relay(an4_relay,an4_counter_action);
}

void
analog_relay(char analog_hw_interface[], char analog_hw_action[])
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
}

