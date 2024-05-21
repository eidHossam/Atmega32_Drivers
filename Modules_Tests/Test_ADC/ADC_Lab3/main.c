/*
 * Atmega32_Drivers.c
 * @brief : Lab_3 for the ADC, Display the temperature we get from the LM35 sensor onto the 7-segment display.
 *                              LM35 ===> ADC ====> 7-segment display
 * Created: 1/31/2024 
 * Author : Hossam Eid
 */

#define F_CPU  1000000UL
#include "Atmega32_Drivers/MCAL/ADC/Atmega32_ADC.h"
#include "Atmega32_Drivers/MCAL/Timer0/Atmega32_Timer0.h"

void callback(void)
{
    uint16_t buffer = 0;
    MCAL_ADC_GetResult(&buffer);

    buffer >>= 2;
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
