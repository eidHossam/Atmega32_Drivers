/*
 * Atmega32_Drivers.c
 * @brief : Lab_2 for the ADC, Display the reading of the ADC module on 4 7-seg displays using interrupts
 * Created: 1/31/2024 
 * Author : Hossam Eid
 */

#define F_CPU  1000000UL
#include "Atmega32_Drivers/MCAL/ADC/Atmega32_ADC.h"

void callback(void)
{
    uint16_t buffer = 0;
    MCAL_ADC_GetResult(&buffer);

    GPIOC->PORT = (uint8_t)(buffer >> 8);
    GPIOD->PORT = (uint8_t)(buffer);

}

int main(void)
{   
    
    GPIOC->DDR = 0xff;  /*Make GPIOC output*/
    GPIOD->DDR = 0xff;  /*Make GPIOD output*/

    GPIOA->DDR = 0x00;  /*Make GPIOA input*/

    sADC_Config_t cfg;
    cfg.ADC_channelSelection = ADC_Channel_0;
    cfg.ADC_Prescaler = ADC_Prescale_128;
    cfg.ADC_ResultAlignment = ADC_RightAlignmet;
    cfg.ADC_ReferenceSelect = ADC_Internal_256V;
    cfg.ADC_AutoTrigger = ADC_AutoTrigger_FreeRunning;

    MCAL_ADC_Init(&cfg);
    MCAL_ADC_Set_EOC_Callback(callback);
    MCAL_ADC_StartConversion();

    while (1) 
    {

	}
}
