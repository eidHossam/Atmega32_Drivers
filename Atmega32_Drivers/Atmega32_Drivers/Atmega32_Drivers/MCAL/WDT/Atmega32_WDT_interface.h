/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the watchdog module.
* Author    : Hossam Eid
* Created on: 4/12/2023
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the watchdog driver.
**************************************************************************************************************************
*/


#ifndef ATMEGA32_WDT_INTERFACE_H_
#define ATMEGA32_WDT_INTERFACE_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32.h"
#include "../../Lib/Bit_Math.h"

/**************************************************************************************************************************
*===============================================
*         Enum Configuration References
*===============================================
*/

enum eWDT_Prescaler{
    WDT_PRESCALER_16,   /*Default prescaler*/
    WDT_PRESCALER_32,
    WDT_PRESCALER_64,
    WDT_PRESCALER_128,
    WDT_PRESCALER_256,
    WDT_PRESCALER_512,
    WDT_PRESCALER_1024,
    WDT_PRESCALER_2048
};
#define ASSERT_WDT_PRESCALER(PRE) ((PRE == WDT_PRESCALER_16)    || (PRE == WDT_PRESCALER_32)   ||  \
                                   (PRE == WDT_PRESCALER_64)    || (PRE == WDT_PRESCALER_128)  || \
                                   (PRE == WDT_PRESCALER_256)   || (PRE == WDT_PRESCALER_512)  || \
                                   (PRE == WDT_PRESCALER_1024)  || (PRE == WDT_PRESCALER_2048))

enum eReset_Status{
    WDT_Reset,
    WDT_NoReset
};

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL WDT DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_Enable
* @brief		:   This function enables the watchdog timer peripheral.
* @param [in]	:   prescaler: Defines the timeout period for the watchdog timer.
======================================================================================================================
*/
void MCAL_WDT_Enable(enum eWDT_Prescaler prescaler);

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_Disable
* @brief		:   This function Disables the watchdog timer peripheral.
======================================================================================================================
*/
void MCAL_WDT_Disable();

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_Reset
* @brief		:   This function Reset the watchdog timer timeout period.
======================================================================================================================
*/
void MCAL_WDT_Reset();

/**
======================================================================================================================
* @Func_name	:   MCAL_WDT_ResetStatus
* @brief		:   This function checks if a reset was made by the watchdog timer.
* @return       :   WDT_Reset if the reset was made, WDT_NoReset if the reset wasn't made.
======================================================================================================================
*/
enum eReset_Status MCAL_WDT_ResetStatus();


#endif /* ATMEGA32_WDT_INTERFACE_H_ */