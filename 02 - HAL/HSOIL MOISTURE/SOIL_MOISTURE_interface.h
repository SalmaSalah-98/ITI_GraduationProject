/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  Soil_Moisture      * **************************/
/***********************  Date : 18-8-2021    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/


#ifndef SOIL_MOISTURE_INTERFACE_H_
#define SOIL_MOISTURE_INTERFACE_H_

#define V_REF_mv   3300UL
#define V_CC_mv    3300

/* Enum for Error States of function  */
typedef enum
{
	SOIL_MOISTURE_enuOK,	
	SOIL_MOISTURE_enuNOK,
	SOIL_MOISTURE_enuNullPointer,
	
}SOIL_MOISTURE_enuErrorStatus;


/* type of input data to the functions */
typedef struct 
{
	u8 SOIL_strChannel;
	u16 * SOIL_pu16strConvertedData;
	
}SOIL_MOISTURE_Channel_type;



/*************************** Function(1) **************************************************************************************/
/************** Purpose : represent the value of voltage of out Analog pin of soil moisture sensor in voltage******************/
/************** INPUTS  : (pointer to struct ) 													*******************************/
/************** Output  : (enu to check)					   									*******************************/
SOIL_MOISTURE_enuErrorStatus HSOIL_u32ReadSoilMoisture_mvSynch(SOIL_MOISTURE_Channel_type * Add_strCnfgSoil );

/*
				Add_strCnfgSoil ->  SOIL_strChannel :
				ADC_CH0
				ADC_CH1
				.
				.
				
				Add_strCnfgSoil -> SOIL_pu16strConvertedData:
				
				&Local_u16Data_mv
				
*/



/*************************** Function(2) *****************************************************************************************/
/************** Purpose : represent the value of voltage of out Analog pin of soil moisture sensor in percentage******************/
/************** INPUTS  : (pointer to struct ) 																	******************/
/************** Output  : (enu)					   													*******************************/

SOIL_MOISTURE_enuErrorStatus HSOIL_u8ReadSoilMoisture_percentageSynch(SOIL_MOISTURE_Channel_type * Add_strCnfgSoil );
/*
				Add_strCnfgSoil ->  SOIL_strChannel :
				ADC_CH0
				ADC_CH1
				.
				.
				
				Add_strCnfgSoil -> SOIL_pu16strConvertedData:
				
				&Local_u16Data_in_Percentage
				
*/


#endif
