/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  Soil_Moisture.c     * **************************/
/***********************  Date : 18-8-2021    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"
#include "ADC_interface.h"

#include "SOIL_MOISTURE_interface.h"
#include "SOIL_MOISTURE_config.h"
//#include "SOIL_MOISTURE_private.h"




/*************************** Function(1) **************************************************************************************/
/************** Purpose : represent the value of voltage of out Analog pin of soil moisture sensor in voltage******************/
SOIL_MOISTURE_enuErrorStatus HSOIL_u32ReadSoilMoisture_mvSynch(SOIL_MOISTURE_Channel_type * Add_strCnfgSoil )
{
	SOIL_MOISTURE_enuErrorStatus Local_enuErrorState = SOIL_MOISTURE_enuOK ; 
	u8 Local_u8Channel = (Add_strCnfgSoil -> SOIL_strChannel) ; 
	u16 Local_enuConvertedDigital;
	
	if ( (Add_strCnfgSoil != NULL) && (Local_u8Channel < ADC_MAX_NO_OF_CHANNELS)) // As we have only 10 channels for ADC1 peripheral in stm32 
		{
			if ((Add_strCnfgSoil -> SOIL_pu16strConvertedData) != NULL )
			{
			/* Initialization of pin for GPIO */
				GPIO_Pin_Cnfg 	Local_strSOIL_PIN;
				
				Local_strSOIL_PIN.GPIO_MODE = GPIO_MODE_INPUT_OUTPUT_ANALOG;
				Local_strSOIL_PIN.GPIO_OUT_SPEED = GPIO_SPEED_LOW;
				Local_strSOIL_PIN.GPIO_PIN = Local_u8Channel ; //SOIL_MOISTURE_ANALOG_PIN;
				Local_strSOIL_PIN.GPIO_PORT = GPIO_PORTA; /* As ADC is conected to pins of port A */
				
				GPIO_enuSetPinMode(&Local_strSOIL_PIN);
				
				/* Initialization of pin for ADC */
				ADC_Cnfg_type Local_strSOIL_Channel;
				
				Local_strSOIL_Channel.ADC_strChannel = Local_u8Channel ;
				Local_strSOIL_Channel.ADC_strSample_Time = SOIL_MOISTURE_ANALOG_SAMPLING_TIMT;
				Local_strSOIL_Channel.ADC_strAlignment = ADC_DATA_LEFT_ALIGNMENT;
				ADC_voidInit(&Local_strSOIL_Channel);
	
				/* Starting Conversion */
				ADC_enuStartConversionSynch( Local_u8Channel, &Local_enuConvertedDigital , ADC_SINGLE_MODE_CONVERSION );
	
				//	Local_enuConvertedDigital:  Digital (Out of ADC)
				* (Add_strCnfgSoil -> SOIL_pu16strConvertedData) = ((Local_enuConvertedDigital) * V_REF_mv) / 4096UL ; //3600 in case of Vref = 3600 , 2^12 = 4096
			}
			else
			{
				Local_enuErrorState = SOIL_MOISTURE_enuNullPointer ; 
			}
		}
	else 
	   {
		//printf("You choosed wrong channel");
			Local_enuErrorState = SOIL_MOISTURE_enuNOK ; 
	   }
	return Local_enuErrorState ;
}







//(2)
SOIL_MOISTURE_enuErrorStatus HSOIL_u8ReadSoilMoisture_percentageSynch(SOIL_MOISTURE_Channel_type * Add_strCnfgSoil )
{
	SOIL_MOISTURE_enuErrorStatus Local_enuErrorState = SOIL_MOISTURE_enuOK ; 
	u8 Local_enuChannel = (Add_strCnfgSoil -> SOIL_strChannel) ; 
	u16 Local_enuConvertedDigital;
	if ( (Add_strCnfgSoil != NULL) && (Local_enuChannel < ADC_MAX_NO_OF_CHANNELS)) // As we have only 10 channels for ADC1 peripheral in stm32 
		{
			if ((Add_strCnfgSoil -> SOIL_pu16strConvertedData) != NULL )
			{
			/* Initialization of pin for GPIO */
				GPIO_Pin_Cnfg 	Local_strSOIL_PIN;
				
				Local_strSOIL_PIN.GPIO_MODE = GPIO_MODE_INPUT_OUTPUT_ANALOG;
				Local_strSOIL_PIN.GPIO_OUT_SPEED = GPIO_SPEED_LOW;
				Local_strSOIL_PIN.GPIO_PIN = Local_enuChannel ; //SOIL_MOISTURE_ANALOG_PIN;
				Local_strSOIL_PIN.GPIO_PORT = GPIO_PORTA; /* As ADC is conected to pins of port A */
				
				GPIO_enuSetPinMode(&Local_strSOIL_PIN);
				
				/* Initialization of pin for ADC */
				ADC_Cnfg_type Local_strSOIL_Channel;
				
				Local_strSOIL_Channel.ADC_strChannel = Local_enuChannel ;
				Local_strSOIL_Channel.ADC_strSample_Time = SOIL_MOISTURE_ANALOG_SAMPLING_TIMT;
				Local_strSOIL_Channel.ADC_strAlignment = ADC_DATA_LEFT_ALIGNMENT;
				ADC_voidInit(&Local_strSOIL_Channel);
	
				/* Starting Conversion */
				ADC_enuStartConversionSynch( Local_enuChannel, &Local_enuConvertedDigital , ADC_SINGLE_MODE_CONVERSION );
	
				//	Local_enuConvertedDigital:  Digital (Out of ADC)
				* (Add_strCnfgSoil -> SOIL_pu16strConvertedData) = (u8)((u16)((Local_enuConvertedDigital) - 1500 ) / 25) ;
			}
			else
			{
				Local_enuErrorState = SOIL_MOISTURE_enuNullPointer ; 
			}
		}
	else 
	   {
		//printf("You choosed wrong channel");
			Local_enuErrorState = SOIL_MOISTURE_enuNOK ; 
	   }
	return Local_enuErrorState ;
}
