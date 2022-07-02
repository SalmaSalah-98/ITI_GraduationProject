/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  Water_Level.c     * **************************/
/***********************  Date : 18-8-2021    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "ADC_interface.h"

#include "WATER_LEVEL_interface.h"
#include "WATER_LEVEL_config.h"




/*************************** Function(1) **************************************************************************************/
/************** Purpose : represent the value of voltage of out Analog pin of soil moisture sensor in voltage******************/
WATER_LEVEL_enuErrorStatus WATER_LEVELRead_mvSynch(WATER_LEVEL_Channel_type * Add_strCnfgWaterLevel )
{
	WATER_LEVEL_enuErrorStatus Local_enuErrorState = WATER_LEVEL_enuOK ; 
	u8 Local_u8Channel = (Add_strCnfgWaterLevel -> WATER_LEVEL_strChannel) ;
	u16 Local_enuConvertedDigital;
	
	if ( (Add_strCnfgWaterLevel != NULL) && (Local_u8Channel < ADC_MAX_NO_OF_CHANNELS)) // As we have only 10 channels for ADC1 peripheral in stm32 
		{
			if ((Add_strCnfgWaterLevel -> WATER_LEVEL_pu16strConvertedData) != NULL )
			{
			/* Initialization of pin for GPIO */
				GPIO_Pin_Cnfg 	Local_strWater_Level_PIN;
				
				Local_strWater_Level_PIN.GPIO_MODE = GPIO_MODE_INPUT_OUTPUT_ANALOG;
				Local_strWater_Level_PIN.GPIO_OUT_SPEED = GPIO_SPEED_LOW;
				Local_strWater_Level_PIN.GPIO_PIN = Local_u8Channel ; //SOIL_MOISTURE_ANALOG_PIN;
				Local_strWater_Level_PIN.GPIO_PORT = GPIO_PORTA; /* As ADC is conected to pins of port A */
				
				GPIO_enuSetPinMode(&Local_strWater_Level_PIN);
				
				/* Initialization of pin for ADC */
				ADC_Cnfg_type Local_strWater_Level_Channel;
				
				Local_strWater_Level_Channel.ADC_strChannel = Local_u8Channel ;
				Local_strWater_Level_Channel.ADC_strSample_Time = WATER_LEVEL_ANALOG_SAMPLING_TIMT;
				Local_strWater_Level_Channel.ADC_strAlignment = ADC_DATA_LEFT_ALIGNMENT;
				ADC_voidInit(&Local_strWater_Level_Channel);
	
				/* Starting Conversion */
				ADC_enuStartConversionSynch( Local_u8Channel, &Local_enuConvertedDigital , ADC_SINGLE_MODE_CONVERSION );
	
				//	Local_enuConvertedDigital:  Digital (Out of ADC)
				* (Add_strCnfgWaterLevel -> WATER_LEVEL_pu16strConvertedData) = ((Local_enuConvertedDigital) * WATER_LEVEL_V_REF_mv) / 4096UL ; //3600 in case of Vref = 3600 , 2^12 = 4096
			}
			else
			{
				Local_enuErrorState = WATER_LEVEL_enuNullPointer ; 
			}
		}
	else 
	   {
		//printf("You choosed wrong channel");
			Local_enuErrorState = WATER_LEVEL_enuNOK ; 
	   }
	return Local_enuErrorState ;
}







//(2)
WATER_LEVEL_enuErrorStatus WATER_LEVEL_enuReadpercentageSynch(WATER_LEVEL_Channel_type * Add_strCnfgWaterLevel )
{
	WATER_LEVEL_enuErrorStatus   Local_enuErrorState = WATER_LEVEL_enuOK ; 
	u8 Local_enuChannel = (Add_strCnfgWaterLevel -> WATER_LEVEL_strChannel) ; 
	u16 Local_enuConvertedDigital;
	if ( (Add_strCnfgWaterLevel != NULL) && (Local_enuChannel < ADC_MAX_NO_OF_CHANNELS)) // As we have only 10 channels for ADC1 peripheral in stm32 
		{
			if ((Add_strCnfgWaterLevel -> WATER_LEVEL_pu16strConvertedData) != NULL )
			{
			/* Initialization of pin for GPIO */
				GPIO_Pin_Cnfg 	Local_strWATER_LEVEL_PIN;
				
				Local_strWATER_LEVEL_PIN.GPIO_MODE      = GPIO_MODE_INPUT_OUTPUT_ANALOG;
				Local_strWATER_LEVEL_PIN.GPIO_OUT_SPEED = GPIO_SPEED_LOW;
				Local_strWATER_LEVEL_PIN.GPIO_PIN       = Local_enuChannel ; //SOIL_MOISTURE_ANALOG_PIN;
				Local_strWATER_LEVEL_PIN.GPIO_PORT      = GPIO_PORTA; /* As ADC is conected to pins of port A */
				
				GPIO_enuSetPinMode(&Local_strWATER_LEVEL_PIN);
				
				/* Initialization of pin for ADC */
				ADC_Cnfg_type Local_strWATER_LEVEL_Channel;
				
				Local_strWATER_LEVEL_Channel.ADC_strChannel    = Local_enuChannel ;
				Local_strWATER_LEVEL_Channel.ADC_strSample_Time = WATER_LEVEL_ANALOG_SAMPLING_TIMT;
				Local_strWATER_LEVEL_Channel.ADC_strAlignment   = ADC_DATA_LEFT_ALIGNMENT;
				ADC_voidInit(&Local_strWATER_LEVEL_Channel);
	
				/* Starting Conversion */
				ADC_enuStartConversionSynch( Local_enuChannel, &Local_enuConvertedDigital , ADC_SINGLE_MODE_CONVERSION );
	
				//	Local_enuConvertedDigital:  Digital (Out of ADC)
				* (Add_strCnfgWaterLevel -> WATER_LEVEL_pu16strConvertedData) = (u8)(Local_enuConvertedDigital / 21) ; // y= x/40.95
			}
			else
			{
				Local_enuErrorState = WATER_LEVEL_enuNullPointer ; 
			}
		}
	else 
	   {
		//printf("You choosed wrong channel");
			Local_enuErrorState = WATER_LEVEL_enuNOK ; 
	   }
	return Local_enuErrorState ;
}
