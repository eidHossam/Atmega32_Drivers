/*
 * Atmega32_Drivers.c
 *
 * Created: 9/11/2023 4:23:15 PM
 * Author : hp
 */
#define F_CPU  8000000UL 
#include "Atmega32.h"
#include "GPIO/Atmega32_GPIO.h"
#include "SPI/Atmega32_SPI.h"
#include "Atmega32_Drivers/HAL/LCD_Driver/LCD_interface.h"

/*------------Select device--------------*/
#define SPI_AS_MASTER
//#define SPI_AS_SLAVE

void SPI_Init();

int main(void)
{
    char name[] = "Eng.Hossam Eid", faculty[] = "Engineering Co";
    uint8_t rec, temp;
    volatile uint32_t i;

	LCD_Init();
    SPI_Init();
	
    while (1) 
    {
		for(i = 0; i < 15; i++)
        {
#ifdef SPI_AS_MASTER
            temp = name[i];
            MCAL_GPIO_WritePin(GPIOB, GPIO_PIN4, GPIO_PIN_LOW);
            MCAL_SPI_ExchangeData(&temp);
            MCAL_GPIO_WritePin(GPIOB, GPIO_PIN4, GPIO_PIN_HIGH);
            LCD_Send_Char(temp);
            name[i] = temp;
#endif
#ifdef SPI_AS_SLAVE
            temp = faculty[i];
            MCAL_SPI_ExchangeData(&temp);
            LCD_Send_Char(temp);
            faculty[i] = temp;
#endif
        }

        for(i = 0; i < 10000; i++);
        LCD_Clear_Screen();
    }
}


void SPI_Init()
{
    SPI_Config_t config;
    config.SPI_CPHA = SPI_SAMPLE_SECOND_EDGE;
    config.SPI_CPOL = SPI_IDLE_HIGH;
    config.SPI_DataOrder = SPI_FIRST_BIT_LSB;
    config.SPI_DoubleSpeed_EN = SPI_2XSPEED_DISABLE;
    config.SPI_IRQ_EN = SPI_IRQ_DISABLE;
    config.SPI_BaudRate = SPI_BAUD_RATE_PRESCALER_4;
    
#ifdef SPI_AS_MASTER
    config.SPI_Mode = SPI_MODE_MASTER;
#endif
#ifdef SPI_AS_SLAVE
     config.SPI_Mode = SPI_MODE_SLAVE;
#endif

    MCAL_SPI_Init(&config);
}