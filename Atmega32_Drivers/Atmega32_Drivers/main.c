/*
 * Atmega32_Drivers.c
 * @brief : This file is a test for the timer0 module which is acheived by increasing the counter showed on the 
 * 7seg display by one every 1 second, and also toggeling the GPIOB_3 pin to see the wave and make sure we have the right
 * timing.
 * Created: 9/11/2023 4:23:15 PM
 * Author : Hossam Eid
 */

#define F_CPU  8000000UL 
#include "Atmega32_Drivers/MCAL/GPIO/Atmega32_GPIO.h"
#include "Atmega32_Drivers/HAL/LCD_Driver/LCD_interface.h"
#include "Atmega32_Drivers/HAL/PIR_Sensor_Driver/PIR_Interface.h"

int main(void)
{   
    ePIRStatus_t Last, new;

    HAL_PIR_Init(GPIOB, GPIO_PIN2);
    
    LCD_Init();

    Last = HAL_PIR_ReadStatus(GPIOB, GPIO_PIN2);

    while (1) 
    {
        new = HAL_PIR_ReadStatus(GPIOB, GPIO_PIN2);
        
        if(new != Last)
        {
            LCD_Clear_Screen();

            if(new == PIR_MotionDetected)
            {
                LCD_Send_String(stringfy("Motion Detected"));

            }else{
                LCD_Send_String(stringfy("No Motion"));
            }
        }
        Last = new;
	}
}
