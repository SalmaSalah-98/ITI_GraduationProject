/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  Soil_Moisture      * **************************/
/***********************  Date : 18-8-2021    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/


#ifndef WATER_LEVEL_INTERFACE_H_
#define WATER_LEVEL_INTERFACE_H_

#define WATER_LEVEL_V_REF_mv   3300UL
#define WATER_LEVEL_V_CC_mv    3300

/* Enum for Error States of function  */
typedef enum
{
	WATER_LEVEL_enuOK,	
	WATER_LEVEL_enuNOK,
	WATER_LEVEL_enuNullPointer,
	
}WATER_LEVEL_enuErrorStatus;


/* type of input data to the functions */
typedef struct 
{
	u8 WATER_LEVEL_strChannel;
	u16 * WATER_LEVEL_pu16strConvertedData;
	
}WATER_LEVEL_Channel_type;



/*************************** Function(1) **************************************************************************************/
/************** Purpose : represent the value of voltage of out Analog pin of Water Level sensor in voltage******************/
/************** INPUTS  : (pointer to struct ) 													*******************************/
/************** Output  : (enu to check)					   									*******************************/
WATER_LEVEL_enuErrorStatus    WATER_LEVELRead_mvSynch(WATER_LEVEL_Channel_type * Add_strCnfgWaterLevel );

/*
				Add_strCnfgSoil ->  WATER_LEVEL_strChannel :
				ADC_CH0
				ADC_CH1
				.
				.
				
				Add_strCnfgSoil -> WATER_LEVEL_pu16strConvertedData:
				
				&Local_u16Data_mv
				
*/



/*************************** Function(2) *****************************************************************************************/
/************** Purpose : represent the value of voltage of out Analog pin of Water Level sensor in percentage	******************/
/************** INPUTS  : (pointer to struct ) 																		******************/
/************** Output  : (enu)					   													*******************************/
WATER_LEVEL_enuErrorStatus WATER_LEVEL_enuReadpercentageSynch(WATER_LEVEL_Channel_type * Add_strCnfgWaterLevel );

/*
				Add_strCnfgSoil ->  WATER_LEVEL_strChannel :
				ADC_CH0
				ADC_CH1
				.
				.
				
				Add_strCnfgSoil -> WATER_LEVEL_pu16strConvertedData:
				
				&Local_u16Data_in_Percentage
				
*/


#endif
