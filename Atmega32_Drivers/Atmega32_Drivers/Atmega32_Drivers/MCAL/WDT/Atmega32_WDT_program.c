/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the watchdog module.
* Author    : Hossam Eid
* Created on: 4/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the watchdog driver.
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_WDT_interface.h"

/** @defgroup Local macros
  * @{
  */
#define MCUCSR_WDRF_MASK  (1 << 3) /*Watchdog Reset Flag*/
/**
  * @}
  */

/** @defgroup Global variables
  * @{
  */
enum eWDT_Prescaler localPrescaler;
/**
  * @}
  */

/**************************************************************************************************************************
*===============================================
*  			APIs functions definitions
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_Enable
* @brief		:   This function enables the watchdog timer peripheral.
* @param [in]	:   prescaler: Defines the timeout period for the watchdog timer.
======================================================================================================================
*/
void MCAL_WDT_Enable(enum eWDT_Prescaler prescaler)
{
    /**
     * Bit 3 – WDE: Watchdog Enable
     * When the WDE is written to logic one, the Watchdog Timer is enabled
     */

    /*Check the validity of the input parameter if it isn't valid set to the default prescaler*/
    if(!ASSERT_WDT_PRESCALER(prescaler))
    {
        localPrescaler = WDT_PRESCALER_16;
    }else{
        localPrescaler = prescaler;
    }

    /*Acknowledge any previous reset made by the WDT*/
    if(MCAL_WDT_ResetStatus() == WDT_Reset)
    {
      MCUCSR &= ~(MCUCSR_WDRF_MASK);
    }

    WDTCR &= ~(WDTCR_WDP_MASK);         /*Clear the prescaler bits*/
    WDTCR |= (0x07 & localPrescaler);

    SET_BIT(WDTCR, WDTCR_WDE_POS);
}

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_Disable
* @brief		:   This function Disables the watchdog timer peripheral.
======================================================================================================================
*/
void MCAL_WDT_Disable()
{
    /**
     * To disable an enabled Watchdog Timer, the following procedure must be followed:
     *  1. In the same operation, write a logic one to WDTOE and WDE. A logic one must be written to WDE
     *  even though it is set to one before the disable operation starts.
     *  2. Within the next four clock cycles, write a logic 0 to WDE. This disables the Watchdog.
     */

    WDTCR |= ((WDTCR_WDTOE_MASK) | (WDTCR_WDE_MASK));

    WDTCR &= ~(WDTCR_WDE_MASK); 
}

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_Reset
* @brief		:   This function Reset the watchdog timer timeout period.
======================================================================================================================
*/
void MCAL_WDT_Reset()
{
    /*The Watchdog Timer is also reset when it is disabled*/
    MCAL_WDT_Disable();

    MCAL_WDT_Enable(localPrescaler);
}

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_ResetStatus
* @brief		:   This function checks if a reset was made by the watchdog timer.
* @return       :   WDT_Reset if the reset was made, WDT_NoReset if the reset wasn't made.
======================================================================================================================
*/
enum eReset_Status MCAL_WDT_ResetStatus()
{
    enum eReset_Status status = WDT_NoReset;
    
    if((MCUCSR & (MCUCSR_WDRF_MASK)))
    {
        status = WDT_Reset;
    }

    return status;
}

