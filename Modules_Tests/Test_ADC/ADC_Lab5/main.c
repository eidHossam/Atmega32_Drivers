/*
 * Atmega32_Drivers.c
 * @brief : Lab_5 for the ADC, Display the input voltage a percentage on the LCD.
 *                              POT ===> ADC ====> 7-segment display , LCD.
 * Created: 1/31/2024 
 * Author : Hossam Eid
 */

#define F_CPU  1000000UL
#include "Atmega32_Drivers/MCAL/ADC/Atmega32_ADC.h"
#include "Atmega32_Drivers/HAL/LCD_Driver/LCD_interface.h"
#include <stdio.h>
uint16_t buffer = 0;
uint16_t prec = 0;
uint16_t max = 0;
uint16_t oldBuffer = 0xFFFF;
char string[10];

void callback(void)
{
    MCAL_ADC_GetResult(&buffer);

    GPIOC->PORT = (uint8_t)(buffer >> 8);
    GPIOD->PORT = (uint8_t)(buffer);

    
    if(buffer != oldBuffer)
    {
        LCD_Clear_Screen();
        LCD_Send_String("Perc: ");

        prec = (((uint32_t)buffer * 100)/ 1024);
        LCD_Cursor_XY(0, 8);
        sprintf(string, "%u", prec);
        LCD_Send_String(string);
        
        LCD_Cursor_XY(0, 10);
        LCD_Send_Char('%');

        uint8_t i;
        max = (prec * 17) / 100;
        LCD_Cursor_XY(1, 0);
        for(i = 0; i < max; i++)
        {
            LCD_Send_Char(0xFF);
        }
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
    cfg.ADC_ReferenceSelect = ADC_Internal_AVCC;
    cfg.ADC_AutoTrigger = ADC_AutoTrigger_Disabled;
    
    MCAL_ADC_Init(&cfg);
    MCAL_ADC_Set_EOC_Callback(callback);
    LCD_Send_Command(LCD_CURSOR_OFF);
    MCAL_ADC_StartConversion();

    while (1) 
    {
       
	}
}
