/*
 * Atmega32_Drivers.c
 * @brief : This file is a test for the WDT module which is achieved by increasing the counter showed on the 
 * 7seg display by one every half a second but the watchdog timer timeout period is 2.2 seconds.
 * timing.
 * Created: 9/11/2023 4:23:15 PM
 * Author : Hossam Eid
 */

#define F_CPU  8000000UL 
#include "Atmega32_Drivers/MCAL/Timer0/Atmega32_Timer0.h"
#include "Atmega32_Drivers/MCAL/WDT/Atmega32_WDT_interface.h"

void delay()
{
    uint8_t counter;
    uint32_t i;

    for (i = 0; i < 2000; i++)
    {
        MCAL_TIMER0_SetCounter(0);
        MCAL_TIMER0_GetCounter(&counter);
        while(counter <= 250)
        {
            MCAL_TIMER0_GetCounter(&counter);
        }
    }
    
}
int main(void)
{   
    uint8_t i = 0;
    /*Make all the pins of PortA output*/
    GPIOA->DDR = 0xFF;
    
    /*Set the callback function for the CTC mode*/
    sTimer0_Config_t config = { Timer_Prescale_8, Timer_Normal_Mode, Timer_COM_Disconnected,
                                Timer_TOI_Disable, Timer_TOCI_Disable};
    
    MCAL_TIMER0_SetCompare(250);
    
    MCAL_TIMER0_Init(&config);
    
    MCAL_WDT_Enable(WDT_PRESCALER_2048);
    for (i = 0; i < 10; i++)
    {
        GPIOA->PORT = i;
        delay();
    }
    MCAL_WDT_Disable();
    
    while (1) 
    {
	}
}
