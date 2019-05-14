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


uint32_t adc_value[4] = {'\0'};

void
adc_init(void)
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
adc_sample(void)
{
    ADCIntClear(ADC0_BASE, 1);
    ADCProcessorTrigger(ADC0_BASE, 1);
    while(!ADCIntStatus(ADC0_BASE, 1, false));
    ADCSequenceDataGet(ADC0_BASE, 1, adc_value);
}

void
adc_select(void)
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
{
    upper_threshold = (uint32_t)sanitize_serial_in_cfg[1];
    lower_threshold = (uint32_t)sanitize_serial_in_cfg[2];
    if(adc_value[0] > upper_threshold || adc_value[0] < lower_threshold)
        analog_relay();
}

void
analog_2(void)
{
    upper_threshold = (uint32_t)sanitize_serial_in_cfg[1];
    lower_threshold = (uint32_t)sanitize_serial_in_cfg[2];
    if(adc_value[1] > upper_threshold || adc_value[1] < lower_threshold)
        analog_relay();
}

void
analog_3(void)
{
    upper_threshold = (uint32_t)sanitize_serial_in_cfg[1];
    lower_threshold = (uint32_t)sanitize_serial_in_cfg[2];
    if(adc_value[2] > upper_threshold || adc_value[2] < lower_threshold)
        analog_relay();
}

void
analog_4(void)
{
    upper_threshold = (uint32_t)sanitize_serial_in_cfg[1];
    lower_threshold = (uint32_t)sanitize_serial_in_cfg[2];
    if(adc_value[3] > upper_threshold || adc_value[3] < lower_threshold)
        analog_relay();
}


void
analog_relay(void)
{
    if (strcmp(sanitize_serial_in_cfg[4],"relay1") == 0)
        relay_1(sanitize_serial_in_cfg[5]);

    if (strcmp(sanitize_serial_in_cfg[4],"relay2") == 0)
        relay_2(sanitize_serial_in_cfg[5]);

    if (strcmp(sanitize_serial_in_cfg[4],"relay3") == 0)
        relay_3(sanitize_serial_in_cfg[5]);

    if (strcmp(sanitize_serial_in_cfg[4],"relay4") == 0)
        relay_4(sanitize_serial_in_cfg[5]);

    if (strcmp(sanitize_serial_in_cfg[4],"relay5") == 0)
        relay_5(sanitize_serial_in_cfg[5]);
}

