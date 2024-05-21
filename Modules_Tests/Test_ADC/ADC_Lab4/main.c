/*
 * Atmega32_Drivers.c
 * @brief : Lab_4 for the ADC, Display the temperature we get from the LM35 sensor onto the 7-segment display and LCD.
 *                              LM35 ===> ADC ====> 7-segment display , LCD
 * Created: 1/31/2024 
 * Author : Hossam Eid
 */

#define F_CPU  1000000UL
#include "Atmega32_Drivers/MCAL/ADC/Atmega32_ADC.h"
#include "Atmega32_Drivers/HAL/LCD_Driver/LCD_interface.h"
#include <stdio.h>
uint16_t buffer = 0;
uint16_t oldBuffer = 0;
char string[10];

void callback(void)
{
    MCAL_ADC_GetResult(&buffer);

    buffer >>= 2;
    GPIOC->PORT = (uint8_t)(buffer >> 8);
    GPIOD->PORT = (uint8_t)(buffer);

    if(buffer != oldBuffer)
    {
        LCD_Cursor_XY(0, 12);
        sprintf(string, "%u", buffer);
        LCD_Send_String(string);
    }

    oldBuffer = buffer;

    MCAL_ADC_StartConversion();

}

int main(void)
{    
    GPIOA->DDR = 0x00;  /*Make GPIOA input*/
    GPIOC->DDR = 0xff;  /*Make GPIOC output*/
    GPIOD->DDR = 0xff;  /*Make GPIOC output*/
    
    LCD_Init();

    sADC_Config_t cfg;
    cfg.ADC_channelSelection = ADC_Channel_0;
    cfg.ADC_Prescaler = ADC_Prescale_128;
    cfg.ADC_ResultAlignment = ADC_RightAlignmet;
    cfg.ADC_ReferenceSelect = ADC_Internal_256V;
    cfg.ADC_AutoTrigger = ADC_AutoTrigger_Disabled;
    
    MCAL_ADC_Init(&cfg);
    MCAL_ADC_Set_EOC_Callback(callback);
    LCD_Send_String("Temperature: ");
    MCAL_ADC_StartConversion();

    while (1) 
    {
       
	}
}
