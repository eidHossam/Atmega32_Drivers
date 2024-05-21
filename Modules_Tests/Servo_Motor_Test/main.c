/*
 * Atmega32_Drivers.c
 * @brief : This file is a test for the timer0 module which is acheived by increasing the counter showed on the 
 * 7seg display by one every 1 second, and also toggeling the GPIOB_3 pin to see the wave and make sure we have the right
 * timing.
 * Created: 9/11/2023 4:23:15 PM
 * Author : Hossam Eid
 */

#define F_CPU  8000000UL 
#include "Atmega32_Drivers/MCAL/Timer2/Atmega32_Timer2.h"
#include "Atmega32_Drivers/MCAL/Timer0/Atmega32_Timer0.h"
#include "Atmega32_Drivers/HAL/Servo_Motor_Driver/Servo_Motor_Interface.h"

eServoMotorDegree_t degrees[3] = {ServoMotor_0Degree, ServoMotor_90Degree, ServoMotor_180Degree};
void callback(void)
{
    static uint8_t i = 0;
    
    MCAL_GPIO_TogglePin(GPIOD, GPIO_PIN1);
    
    HAL_ServoMotorTurn(degrees[i]);
    i++;
    
    if(i >= 3)
    {
        i = 0;
    }

    MCAL_TIMER0_SingleIntervalDelayms(1000, callback);
}

int main(void)
{   
    GPIO_Pin_Config_t GPIO_cfg;

    GPIO_cfg.pinNumber = GPIO_PIN1;
    GPIO_cfg.pinMode = GPIO_MODE_OUTPUT;
    MCAL_GPIO_Init(GPIOD, &GPIO_cfg);
    
    HAL_ServoMotorInit();
    HAL_ServoMotorTurn(ServoMotor_0Degree);

    MCAL_TIMER0_SingleIntervalDelayms(1000, callback);

    while (1) 
    {
	}
}
