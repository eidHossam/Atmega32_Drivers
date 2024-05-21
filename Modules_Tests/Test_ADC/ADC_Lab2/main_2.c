/*
 * Atmega32_Drivers.c
 * @brief : Lab_2 for the ADC, Display the reading of the ADC module on 4 7-seg displays using interrupts
 * Created: 1/31/2024 
 * Author : Hossam Eid
 */

#define F_CPU  1000000UL
#include "Atmega32_Drivers/MCAL/ADC/Atmega32_ADC.h"
#include "Atmega32_Drivers/MCAL/Timer0/Atmega32_Timer0.h"

void TCallback()
{
    static uint32_t counter;

	if(counter == 20)
    {
        MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN3);
        counter = 0;
    }

    counter++;
}

void callback(void)
{
    uint16_t buffer = 0;
    MCAL_ADC_GetResult(&buffer);

    GPIOC->PORT = (uint8_t)(buffer >> 8);
    GPIOD->PORT = (uint8_t)(buffer);
}

int main(void)
{   
    /*Enable GPIOB_PIN3 to be in output mode*/
    MCAL_GPIO_Init(GPIOB, &(GPIO_Pin_Config_t){GPIO_PIN3, GPIO_MODE_OUTPUT});
    
    
    GPIOC->DDR = 0xff;  /*Make GPIOC output*/
    GPIOD->DDR = 0xff;  /*Make GPIOD output*/

    GPIOA->DDR = 0x00;  /*Make GPIOA input*/
    
    MCAL_TIMER0_CALLBACK_Overflow_INTERRUPT(TCallback);
    sTimer0_Config_t config = {Timer_Prescale_1024, Timer_Normal_Mode, Timer_COM_Disconnected,
                                Timer_TOI_Enable, Timer_TOCI_Disable};
    
    MCAL_TIMER0_Init(&config);

    sADC_Config_t cfg;
    cfg.ADC_channelSelection = ADC_Channel_0;
    cfg.ADC_Prescaler = ADC_Prescale_128;
    cfg.ADC_ResultAlignment = ADC_RightAlignmet;
    cfg.ADC_ReferenceSelect = ADC_Internal_256V;
    cfg.ADC_AutoTrigger = ADC_AutoTrigger_Timer0_OVF;

    MCAL_ADC_Init(&cfg);
    MCAL_ADC_Set_EOC_Callback(callback);
    MCAL_ADC_StartConversion();
    
    while (1) 
    {

	}
}
