/*
 * analog_management.c
 *
 *  Created on: Mar 30, 2019
 *      Author: rufusy
 */


#include "analog_mgr.h"
#include "sanitize_cfg.h"
#include "uart_mgr.h"


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

