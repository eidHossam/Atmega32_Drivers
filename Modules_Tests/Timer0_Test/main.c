/*
 * Atmega32_Drivers.c
 * @brief : This file is a test for the timer0 module which is acheived by increasing the counter showed on the 
 * 7seg display by one every 1 second, and also toggeling the GPIOB_3 pin to see the wave and make sure we have the right
 * timing.
 * Created: 9/11/2023 4:23:15 PM
 * Author : Hossam Eid
 */

#define F_CPU  8000000UL 
#include "Atmega32_Drivers/MCAL/Timer0/Atmega32_Timer0.h"

void Callback()
{
    static uint32_t counter;

	if(counter == 4000)
    {
        MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN3);
        GPIOA->PORT += 1;
        counter = 0;
    }

    counter++;
}


int main(void)
{   
    /*Make all the pins of PortA output*/
    GPIOA->DDR = 0xFF;

    /*Enable GPIOB_PIN3 to be in output mode*/
    MCAL_GPIO_Init(GPIOB, &(GPIO_Pin_Config_t){GPIO_PIN3, GPIO_MODE_OUTPUT});
    
    /*Set the callback function for the CTC mode*/
	MCAL_TIMER0_CALLBACK_CompareMatch_INTERRUPT(Callback);
    sTimer0_Config_t config = { Timer_Prescale_8, Timer_CTC_Mode, Timer_COM_Disconnected,
                                Timer_TOI_Disable, Timer_TOCI_Enable};
    
    MCAL_TIMER0_SetCompare(250);
    MCAL_TIMER0_Init(&config);
	
    while (1) 
    {
	}
}
