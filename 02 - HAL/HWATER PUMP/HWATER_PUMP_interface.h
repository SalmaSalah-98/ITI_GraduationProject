/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  WATER_PUMP.c     * **************************/
/***********************  Date : 23-6-2022    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/


#ifndef HWATER_PUMP_INTERFACE_H_
#define HWATER_PUMP_INTERFACE_H_


typedef enum 
{
	HWATER_PUMP_OK = 0,
	
	HWATER_PUMP_Wrong_Pin,
	
	HWATER_PUMP_Wrong_Port,
	
	HWATER_PUMP_NOK,
	
}HWATER_PUMP_Error_status;


typedef struct
{
	u8 HWATER_PUMP_Port;
	u8 HWATER_PUMP_Pin;
	
}HWATER_PUMP_Pin_t;



/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : to start running Water pump            	******************/
/*************************************** INPUTS  : (void) 									******************/
/*************************************** Output  : (enu)					   *******************************/
HWATER_PUMP_Error_status  HWATER_PUMP_enuOpenPump(void);
/*
We Should choose Configurations the Config.h file
EX: 
				HWATER_PUMP_PORT
				HWATER_PUMP_PIN 

*/



/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : to Stop running Water pump            	******************/
/*************************************** INPUTS  : (void) 									******************/
/*************************************** Output  : (enu)					   *******************************/
HWATER_PUMP_Error_status  HWATER_PUMP_enuStopPump(void);
/*
We Should choose Configurations the Config.h file
EX: 
				HWATER_PUMP_PORT
				HWATER_PUMP_PIN 

*/








#endif