/*
**************************************************************************************************************************
* brief     : MCU Device Header for the Atmega32.
* Author    : Hossam Eid
* Created on: 9/11/2023
**************************************************************************************************************************
* Description: This file contains the memory map for the MCU with each peripheral base address and registers and 
* instances of each peripheral
* note: This header file is intended for use with the Atmega32 MCU series, but may be adapted for use with other 
* compatible processors.
**************************************************************************************************************************
*/

#ifndef ATMEGA32_H_
#define ATMEGA32_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Bit_Math.h"
#include "Platform_Types.h"

/*================================================================*/
//-----------------------------
//Base addresses for Memories
//-----------------------------
#define DATA_ADDRESS_SPACE          0x00
#define PERIPHERAL_MEMORY_BASE      0x20
#define SRAM_MEMORY_BASE            0x60

/*
*===============================================
*  Base addresses for data bus registers
*===============================================
*/

/*---------------------------GPIO-----------------------------*/
#define GPIOA_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x19)
#define GPIOB_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x16)
#define GPIOC_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x13)
#define GPIOD_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x10)

/*---------------------------SPI-----------------------------*/
#define SPI_BASE     (uint8_t)(PERIPHERAL_MEMORY_BASE + 0x0D)

/*================================================================
*-*-*-*-*-*-*-*-*-*-*-*-
  System registers:
*-*-*-*-*-*-*-*-*-*-*-*-
*/
#define SREG    *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x3F))  /*The AVR Status Register*/
#define SPH     *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x3E))  /*Stack Pointer High Register*/
#define SPL     *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x3D))  /*Stack Pointer Low Register*/

/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral registers:
//-*-*-*-*-*-*-*-*-*-*-*-

typedef struct{
    vuint8_t PIN;              /*Port Input Pins Register*/
    vuint8_t DDR;              /*Port Data Direction Register*/
    vuint8_t PORT;             /*Port Data Register*/
}GPIO_typedef;

typedef struct{
    vuint8_t SPCR;              /*SPI Control Register*/
    vuint8_t SPSR;              /*SPI Status Register*/
    vuint8_t SPDR;              /*SPI Data Register*/
}SPI_typedef;

#define SFIOR   *((volatile uint8_t *)(PERIPHERAL_MEMORY_BASE + 0x30))  /*Special Function IO Register*/
/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Peripheral Instants:
//-*-*-*-*-*-*-*-*-*-*-*

/*----------------GPIO-----------------------*/
#define GPIOA   ((GPIO_typedef *)(GPIOA_BASE))
#define GPIOB   ((GPIO_typedef *)(GPIOB_BASE))
#define GPIOC   ((GPIO_typedef *)(GPIOC_BASE))
#define GPIOD   ((GPIO_typedef *)(GPIOD_BASE))

/*----------------SPI-----------------------*/
#define SPI     ((SPI_typedef *)(SPI_BASE))


/*================================================================*/
//-*-*-*-*-*-*-*-*-*-*-*-
//Generic Macros:
//-*-*-*-*-*-*-*-*-*-*-*
#define G_INTERRUPT_ENABLE      SREG |= (1 << 7);
#define G_INTERRUPT_DISABLE     SREG &= ~(1 << 7);

#endif /* ATMEGA32_H_ */