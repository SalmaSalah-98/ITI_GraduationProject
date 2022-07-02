/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  WATER_PUMP.c     * **************************/
/***********************  Date : 23-6-2022    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "RCC_interface.h"
#include "GPIO_interface.h"

#include "HWATER_PUMP_interface.h"
#include "HWATER_PUMP_config.h"
#include "HWATER_PUMP_private.h"







/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : to start running Water pump            ******************/

HWATER_PUMP_Error_status  HWATER_PUMP_enuOpenPump(void)
{
	HWATER_PUMP_Error_status Local_enuErrorState = HWATER_PUMP_OK;
	GPIO_Pin_Cnfg Local_strWaterPumpPin ; 

	
	if (HWATER_PUMP_PORT < 6) //Max number of PORTS
	{
		if (HWATER_PUMP_PIN < 16) // MAX number of pins 
		{
			Local_strWaterPumpPin.GPIO_PORT      =  HWATER_PUMP_PORT;
			Local_strWaterPumpPin.GPIO_PIN       =  HWATER_PUMP_PIN;
			Local_strWaterPumpPin.GPIO_MODE 	   =  GPIO_MODE_GP_OUT_PP; 
			Local_strWaterPumpPin.GPIO_OUT_SPEED =	  GPIO_SPEED_LOW;
			
			if ((GPIO_enuSetPinMode(&Local_strWaterPumpPin)) ==  GPIO_enuOK ) 
			{
				GPIO_enuSetPinValue(HWATER_PUMP_PORT ,HWATER_PUMP_PIN, GPIO_HIGH );
				Local_enuErrorState = HWATER_PUMP_OK;
			}
			else
			{
				Local_enuErrorState = HWATER_PUMP_NOK;
			}

		}
		else
		{
			Local_enuErrorState = HWATER_PUMP_Wrong_Pin;
		}
	}
	else
	{
		Local_enuErrorState = HWATER_PUMP_Wrong_Port;
	}
	return Local_enuErrorState;
}

/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : to Stop running Water pump            	******************/

HWATER_PUMP_Error_status  HWATER_PUMP_enuStopPump(void)
{
	HWATER_PUMP_Error_status Local_enuErrorState = HWATER_PUMP_OK;
	GPIO_Pin_Cnfg Local_strWaterPumpPin ; 

	
	if (HWATER_PUMP_PORT < 6) //Max number of PORTS
	{
		if (HWATER_PUMP_PIN < 16) // MAX number of pins 
		{
			Local_strWaterPumpPin.GPIO_PORT      =  HWATER_PUMP_PORT;
			Local_strWaterPumpPin.GPIO_PIN       =  HWATER_PUMP_PIN;
			Local_strWaterPumpPin.GPIO_MODE 	   =  GPIO_MODE_GP_OUT_PP; 
			Local_strWaterPumpPin.GPIO_OUT_SPEED =	  GPIO_SPEED_LOW;
			
			if ((GPIO_enuSetPinMode(&Local_strWaterPumpPin)) ==  GPIO_enuOK ) 
			{
				GPIO_enuSetPinValue(HWATER_PUMP_PORT ,HWATER_PUMP_PIN, GPIO_LOW );
				Local_enuErrorState = HWATER_PUMP_OK;
			}
			else
			{
				Local_enuErrorState = HWATER_PUMP_NOK;
			}

		}
		else
		{
			Local_enuErrorState = HWATER_PUMP_Wrong_Pin;
		}
	}
	else
	{
		Local_enuErrorState = HWATER_PUMP_Wrong_Port;
	}
	return Local_enuErrorState;
}
