/************************************************************************/
/************************************************************************/
/***********************  Author:Salma Salah  ***************************/
/***********************  Layer:HAL           ***************************/
/***********************  WATER_PUMP.c     * **************************/
/***********************  Date : 23-6-2022    ***************************/
/***********************  Version :1.00       ***************************/
/************************************************************************/
/************************************************************************/


#ifndef HWATER_PUMP_CONFIG_H_
#define HWATER_PUMP_CONFIG_H_


/* Define the normally closed pin for water pump */
#define HWATER_PUMP_NC_RELAY_PIN   HWATER_PUMP_NC_GROUND // Hence the second pin should be connected by GND
/*
Choose Between :
HWATER_PUMP_NC_GROUND
HWATER_PUMP_NC_VCC   
*/


 /* Connection Between Water pump and MC */
#define 	HWATER_PUMP_PORT	  GPIO_PORTB
#define 	HWATER_PUMP_PIN       GPIO_PIN0 // which is connected with the transistor that controls the Relay









#endif