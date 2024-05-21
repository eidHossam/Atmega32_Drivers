/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the ADC module.
* Author    : Hossam Eid
* Created on: 1/31/2024 9:54:49 AM
**************************************************************************************************************************
* Description: This file contains the functions definitions for the ADC driver.
**************************************************************************************************************************
*/

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32_ADC.h"

/** @defgroup Private Macros and defines
  * @{
  */

/**
  * @}
  */

/** @defgroup Global variables
  * @{
  */
sADC_Config_t ADC_CFG;

Ptr_Func endOfConversionCallback = NULL;
/**
  * @}
  */

/** @defgroup Local functions
  * @{
  */


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
* @Func_name	:   MCAL_ADC_Init
* @brief		:   Intializes the ADC module with the parameters passed to it.
* @param [in]	:   cfg: Configuration structure.
* @return       :   eStatus_t: Status of the function call.
* @Note         :   This function won't start the conversion process it only initializes the ADC module.
======================================================================================================================
*/
eStatus_t MCAL_ADC_Init(sADC_Config_t* cfg)
{
    eStatus_t status = E_OK;
    uint8_t tempReg = 0;

    if(NULL == cfg)
    {
        status = E_NOK;
    }else if(!ASSERT_ADC_CHANNEL(cfg->ADC_channelSelection) || !ASSERT_ADC_ALIGNMENT(cfg->ADC_ResultAlignment) ||
             !ASSERT_ADC_REFERENCE(cfg->ADC_ReferenceSelect)|| !ASSERT_ADC_PRESCALER(cfg->ADC_Prescaler) || 
             !ASSERT_ADC_AUTO_TRIGGER(cfg->ADC_AutoTrigger)){
        
        status = E_NOK;
    }else{
        ADC_CFG = *cfg;

        /*Setting the ADMUX register*/
        ADC->ADMUX = 0x00;
        tempReg |= (cfg->ADC_channelSelection | cfg->ADC_ResultAlignment | cfg->ADC_ReferenceSelect);
        ADC->ADMUX = tempReg;

        /*Setting the ADCSRA register*/
        ADC->ADCSRA = 0x00;
        tempReg = 0;
        tempReg |=  cfg->ADC_Prescaler;

        if(cfg->ADC_AutoTrigger != ADC_AutoTrigger_Disabled)
        {   
            tempReg |= ADC_ADCSRA_ADATE_MASK;
            
            SFIOR &= ~(SFIOR_ADTS_MASK);
            SFIOR |= cfg->ADC_AutoTrigger;
        }

        ADC->ADCSRA |= tempReg;

        /*Enable the ADC module*/
        ADC->ADCSRA |= ADC_ADCSRA_ADEN_MASK;
    }

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_Reset
* @brief		:   This function reset the ADC module to its intial state.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_Reset()
{
    eStatus_t status = E_OK;

    ADC->ADMUX  = 0x00;
    ADC->ADCSRA = 0x00;

    SFIOR &= ~(SFIOR_ADTS_MASK);

    return status; 
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_StartConversion
* @brief		:   Starts the conversion process.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_StartConversion()
{
    eStatus_t status = E_OK;

    /*In-case of auto trigger conversion mode*/
    if(ADC_CFG.ADC_AutoTrigger != ADC_AutoTrigger_Disabled && !READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADATE_POS))
    {
        SET_BIT(ADC->ADCSRA, ADC_ADCSRA_ADATE_POS);
    }

    SET_BIT(ADC->ADCSRA, ADC_ADCSRA_ADSC_POS);
        
    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_StopConversion
* @brief		:   Stops the conversion process.
* @return       :   eStatus_t: Status of the function call.
* @Note         :   This function is only needed in case of the auto-trigger mode.
======================================================================================================================
*/
eStatus_t MCAL_ADC_StopConversion()
{
    eStatus_t status = E_OK;

    /*Wait for current conversion process.*/
    while(READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADSC_POS) && !READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADIF_POS));

    CLEAR_BIT(ADC->ADCSRA, ADC_ADCSRA_ADATE_POS);

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_SwitchChannel
* @brief		:   Changes the channel to read from.
* @param [in]	:   channel: The new channel to be read from.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_SwitchChannel(eADC_Channel_t channel)
{
    eStatus_t status = E_OK;
    if(!ASSERT_ADC_CHANNEL(channel))
    {
        status = E_NOK;
    }else{
        
        /*Wait for any ongoing conversion to be done*/
        while(READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADSC_POS));
    
        MCAL_ADC_StopConversion();

        ADC->ADMUX = ((ADC->ADMUX & ~(ADC_ADMUX_MUX_MASK)) | channel);
        ADC_CFG.ADC_channelSelection = channel;
        
        MCAL_ADC_StartConversion();
    }

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_GetResult
* @brief		:   Returns the result of the conversion.
* @param [out]	:   pBuffer: Buffer to store the result in
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_GetResult(uint16_t* pBuffer)
{
    eStatus_t status = E_OK;
    
    if(NULL == pBuffer)
    {
        status = E_NOK;
    }else{
        
        /*Wait for the ADC interrupt flag to be set*/
        while(!READ_BIT(ADC->ADCSRA, ADC_ADCSRA_ADIF_POS));

        *(pBuffer)  = ADC->ADCL;
        *(pBuffer) |= (ADC->ADCH << 8);

        SET_BIT(ADC->ADCSRA, ADC_ADCSRA_ADIF_POS);
    }

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_ConvertData
* @brief		:   Returns the result of the conversion.
* @param [out]	:   pBuffer: Buffer to store the result in
* @return       :   eStatus_t: Status of the function call.
* @note         :   This function works with a busy and wait mechanism
======================================================================================================================
*/
eStatus_t MCAL_ADC_ConvertData(uint16_t* pBuffer, eADC_Channel_t channel)
{
    eStatus_t status = E_OK;
    if(NULL == pBuffer || !ASSERT_ADC_CHANNEL(channel))
    {
        status = E_NOK;
    }else{
        
        MCAL_ADC_SwitchChannel(channel);
        
        status = MCAL_ADC_GetResult(pBuffer);
    }

    return status;
}

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_SetCallback
* @brief		:   Enables the end of conversion interrupt and sets the callback function for it.
* @param [in]	:   Ptr_Func: The callback function.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_Set_EOC_Callback(Ptr_Func callback)
{
    eStatus_t status = E_OK;
    if(NULL == callback)
    {
        status = E_NOK;
    }else{
        endOfConversionCallback = callback;

        G_INTERRUPT_ENABLE;
        ADC->ADCSRA |= ADC_ADCSRA_ADIE_MASK;
    }

    return status;
}

/**************************************************************************************************************************
===============================================
*               ADC ISR functions
*===============================================
*/

void __vector_16 (void) __attribute__((signal));
void __vector_16 (void){
    
    if(endOfConversionCallback)
    {
        endOfConversionCallback();
    }
}
