/**
**************************************************************************************************************************
* brief     : This module contains functions for configuring and controlling the ADC module.
* Author    : Hossam Eid
* Created on: 1/31/2024 9:55:03 AM
**************************************************************************************************************************
* Description: This file contains the function prototypes and definitions for the ADC driver.
**************************************************************************************************************************
*/
#ifndef ATMEGA32_ADC_H_
#define ATMEGA32_ADC_H_

/*
*===============================================
*                   Includes
*===============================================
*/
#include "Atmega32.h"

/**************************************************************************************************************************
*===============================================
*         Enum Configuration References
*===============================================
*/
/*---------------------------@ref ADC_CHANNEL_DEFINE---------------------------*/
typedef enum{
    ADC_Channel_0,                          /*!<Single ended input channel 0*/
    ADC_Channel_1,                          /*!<Single ended input channel 1*/
    ADC_Channel_2,                          /*!<Single ended input channel 2*/
    ADC_Channel_3,                          /*!<Single ended input channel 3*/
    ADC_Channel_4,                          /*!<Single ended input channel 4*/
    ADC_Channel_5,                          /*!<Single ended input channel 5*/
    ADC_Channel_6,                          /*!<Single ended input channel 6*/
    ADC_Channel_7,                          /*!<Single ended input channel 7*/

    ADC_Channel_POS0_NEG0_10x,              /*!<Differential input channel (0 +ve), (0 -ve), Gain 10x*/
    ADC_Channel_POS1_NEG0_10x,              /*!<Differential input channel (1 +ve), (0 -ve), Gain 10x*/
    ADC_Channel_POS0_NEG0_200x,             /*!<Differential input channel (0 +ve), (0 -ve), Gain 200x*/
    ADC_Channel_POS1_NEG0_200x,             /*!<Differential input channel (1 +ve), (0 -ve), Gain 200x*/
    ADC_Channel_POS2_NEG2_10x,              /*!<Differential input channel (2 +ve), (2 -ve), Gain 10x*/
    ADC_Channel_POS3_NEG2_10x,              /*!<Differential input channel (3 +ve), (2 -ve), Gain 10x*/
    ADC_Channel_POS2_NEG2_200x,             /*!<Differential input channel (2 +ve), (2 -ve), Gain 200x*/
    ADC_Channel_POS3_NEG2_200x,             /*!<Differential input channel (3 +ve), (2 -ve), Gain 200x*/

    ADC_Channel_POS0_NEG1,                  /*!<Differential input channel (0 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS1_NEG1,                  /*!<Differential input channel (1 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS2_NEG1,                  /*!<Differential input channel (2 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS3_NEG1,                  /*!<Differential input channel (3 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS4_NEG1,                  /*!<Differential input channel (4 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS5_NEG1,                  /*!<Differential input channel (5 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS6_NEG1,                  /*!<Differential input channel (6 +ve), (1 -ve), Gain 1x*/
    ADC_Channel_POS7_NEG1,                  /*!<Differential input channel (7 +ve), (1 -ve), Gain 1x*/

    ADC_Channel_POS0_NEG2,                  /*!<Differential input channel (0 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS1_NEG2,                  /*!<Differential input channel (1 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS2_NEG2,                  /*!<Differential input channel (2 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS3_NEG2,                  /*!<Differential input channel (3 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS4_NEG2,                  /*!<Differential input channel (4 +ve), (2 -ve), Gain 1x*/
    ADC_Channel_POS5_NEG2,                  /*!<Differential input channel (5 +ve), (2 -ve), Gain 1x*/
    
    ADC_Channel_VBG,                        /*!<Single ended input channel 1.22V*/
    ADC_Channel_GND,                        /*!<Single ended input channel 0V*/
}eADC_Channel_t;

#define ASSERT_ADC_CHANNEL(CHANNEL) ((CHANNEL >= 0) && (CHANNEL <= 31))

/*---------------------------@ref ADC_DEFINE_ALIGNMENT---------------------------*/
/**
 * The ADLAR bit affects the presentation of the ADC conversion result in the ADC Data Register.
 * Write one to ADLAR to left adjust the result.
 */

typedef enum{
    ADC_RightAlignmet,
    ADC_LeftAlignmet = ADC_ADMUX_ADLAR_MASK
}eADC_Alignment_t;

#define ASSERT_ADC_ALIGNMENT(alignment) ((alignment == ADC_RightAlignmet) || \
                                         (alignment == ADC_LeftAlignmet))

/*---------------------------@ref ADC_REFERENCE_DEFINE---------------------------*/
typedef enum{
    ADC_External_AREF,                          /*!<Use the external voltage applied to AREF pin*/
    ADC_Internal_AVCC = ADC_ADMUX_REFS0_MASK,   /*!<Use the internal voltage of the MCU*/
    ADC_Internal_256V   = ADC_ADMUX_REFS_MASK     /*!<Use an internal voltage of 2.56V*/
}eADC_Refrence_t;

#define ASSERT_ADC_REFERENCE(ref) (ref == ADC_External_AREF || \
                                   ref == ADC_Internal_AVCC || \
                                   ref == ADC_Internal_256V)

/*---------------------------@ref ADC_PRESCALER_DEFINE---------------------------*/
typedef enum{
    ADC_Prescale_2 = 1,
    ADC_Prescale_4,
    ADC_Prescale_8,
    ADC_Prescale_16,
    ADC_Prescale_32,
    ADC_Prescale_64,
    ADC_Prescale_128
}eADC_Prescaler_t;           

#define ASSERT_ADC_PRESCALER(pre) ((pre >= 0) && (pre <= 7))

/*---------------------------@ref ADC_AUTO_TRIGGER_DEFINE---------------------------*/
typedef enum{
    ADC_AutoTrigger_FreeRunning,
    ADC_AutoTrigger_AnalogComparator    = SFIOR_ADTS0_MASK,
    ADC_AutoTrigger_EXTERN_INT0         = SFIOR_ADTS1_MASK,
    ADC_AutoTrigger_Timer0_CTC          = (SFIOR_ADTS0_MASK | SFIOR_ADTS1_MASK),
    ADC_AutoTrigger_Timer0_OVF          = SFIOR_ADTS2_MASK,
    ADC_AutoTrigger_Timer1_CTC          = (SFIOR_ADTS2_MASK | SFIOR_ADTS0_MASK),
    ADC_AutoTrigger_Timer1_OVF          = (SFIOR_ADTS2_MASK | SFIOR_ADTS1_MASK),
    ADC_AutoTrigger_Timer1_CapEvent     = SFIOR_ADTS_MASK,
    ADC_AutoTrigger_Disabled
}eADC_AutoTriggerEN;

#define ASSERT_ADC_AUTO_TRIGGER(trigger) ((trigger == ADC_AutoTrigger_FreeRunning) || \
                                          (trigger == ADC_AutoTrigger_AnalogComparator) || \
                                          (trigger == ADC_AutoTrigger_EXTERN_INT0) || \
                                          (trigger == ADC_AutoTrigger_Timer0_CTC) || \
                                          (trigger == ADC_AutoTrigger_Timer0_OVF) || \
                                          (trigger == ADC_AutoTrigger_Timer1_CTC) || \
                                          (trigger == ADC_AutoTrigger_Timer1_OVF) || \
                                          (trigger == ADC_AutoTrigger_Timer1_CapEvent) || \
                                          (trigger == ADC_AutoTrigger_Disabled))


/**************************************************************************************************************************
*===============================================
* User type definitions (structures)
*===============================================
*/
typedef struct{
    eADC_Channel_t      ADC_channelSelection;           /*!<Specifies the input to the ADC
                                                        This parameter must be a value of @ref ADC_CHANNEL_DEFINE*/

    eADC_Alignment_t    ADC_ResultAlignment;            /*!<Specifies the alignment of the result in the register
                                                        This parameter must be a value of @ref ADC_DEFINE_ALIGNMENT*/

    eADC_Refrence_t     ADC_ReferenceSelect;            /*!<Specifies the voltage reference of the ADC
                                                        This parameter must be a value of @ref ADC_REFERENCE_DEFINE*/

    eADC_Prescaler_t    ADC_Prescaler;                  /*!<Specifies the ADC clock prescaler value
                                                        This parameter must be a value of @ref ADC_PRESCALER_DEFINE*/

    eADC_AutoTriggerEN  ADC_AutoTrigger;                /*!<Specifies the trigger mood of the ADC
                                                        This parameter must be a value of @ref ADC_AUTO_TRIGGER_DEFINE*/
}sADC_Config_t;

/**************************************************************************************************************************
===============================================
*       APIs Supported by "MCAL Timer0 DRIVER"
*===============================================
*/

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_Init
* @brief		:   Initializes the ADC module with the parameters passed to it.
* @param [in]	:   cfg: Configuration structure.
* @return       :   eStatus_t: Status of the function call.
* @Note         :   This function won't start the conversion process it only initializes the ADC module.
======================================================================================================================
*/
eStatus_t MCAL_ADC_Init(sADC_Config_t* cfg);

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_Reset
* @brief		:   This function reset the ADC module to its initial state.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_Reset();

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_StartConversion
* @brief		:   Starts the conversion process.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_StartConversion();

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_StopConversion
* @brief		:   Stops the conversion process.
* @return       :   eStatus_t: Status of the function call.
* @Note         :   This function is only needed in case of the auto-trigger mode.
======================================================================================================================
*/
eStatus_t MCAL_ADC_StopConversion();

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_SwitchChannel
* @brief		:   Changes the channel to read from.
* @param [in]	:   channel: The new channel to be read from.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_SwitchChannel(eADC_Channel_t channel);

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_GetResult
* @brief		:   Returns the result of the conversion.
* @param [out]	:   pBuffer: Buffer to store the result in
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_GetResult(uint16_t* pBuffer);

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_ConvertData
* @brief		:   Returns the result of the conversion.
* @param [out]	:   pBuffer: Buffer to store the result in
* @return       :   eStatus_t: Status of the function call.
* @Note         :   This function works with a busy and wait mechanism
======================================================================================================================
*/
eStatus_t MCAL_ADC_ConvertData(uint16_t* pBuffer, eADC_Channel_t channel);

/**
======================================================================================================================
* @Func_name	:   MCAL_ADC_SetCallback
* @brief		:   Enables the end of conversion interrupt and sets the callback function for it.
* @param [in]	:   Ptr_Func: The callback function.
* @return       :   eStatus_t: Status of the function call.
======================================================================================================================
*/
eStatus_t MCAL_ADC_Set_EOC_Callback(Ptr_Func callback);
#endif /* ATMEGA32_ADC_H_ */