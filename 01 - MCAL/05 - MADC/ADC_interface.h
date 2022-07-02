/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** ADC_Private            			    ****************/
/*** Date    : 25/6/2022                     ****************/
/*** Version :  02                          ****************/
/***********************************************************/

#ifndef ADC_INTERFACE_H
#define ADC_INTERFACE_H

/* This struct for Initialization */
typedef struct 
{
	u8 ADC_strChannel;
	u8 ADC_strSample_Time;
	u8 ADC_strAlignment; // Right / Shift 
		
}ADC_Cnfg_type; 

/*this struct for Start Conversion (Asynch)*/
typedef struct 
{
	u8 ADC_strChannelNumber;
	u16 * ADC_pu16ConvertedData;
	void (*Add_pvoidNotification)(void);
	u8 ADC_strModeConversion; 
	
}ADC_strChannel_type; 


typedef enum 
{
	ADC_enuOk,
	ADC_enuNOK,
	ADC_enuNULLPointer,

}ADC_enuErrorStatus; 



/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : to initialize the ADC Channel            ******************/
/*************************************** INPUTS  : (1)ADC_Cnfg_type struct				******************/
/*************************************** Output  : (void)					   *******************************/
void ADC_voidInit( ADC_Cnfg_type * Add_pstrADC );

/*
EX :


				ADC_Cnfg_type -> ADC_strChannel
				ADC_CH0
				ADC_CH1
				ADC_CH2
					.
	            ADC_CH17
				
				ADC_Cnfg_type -> ADC_strSample_Time
				TIME_14_CYCLES
				TIME_20_CYCLES
				TIME_26_CYCLES
				TIME_41_CYCLES
				TIME_54_CYCLES
				TIME_68_CYCLES
				TIME_84_CYCLES
				TIME_252_CYCLES
				
				ADC_Cnfg_type -> ADC_strAlignment 
				ADC_DATA_RIGHT_ALIGNMENT
				ADC_DATA_LEFT_ALIGNMENT 
				
*/

#define ADC_MAX_NO_OF_CHANNELS  18

#define ADC_CH0   0
#define ADC_CH1   1
#define ADC_CH2   2
#define ADC_CH3	  3 
#define ADC_CH4   4
#define ADC_CH5   5
#define ADC_CH6   6
#define ADC_CH7   7
#define ADC_CH8   8 
#define ADC_CH9   9
#define ADC_CH10  10
#define ADC_CH11  11
#define ADC_CH12  12
#define ADC_CH13  13
#define ADC_CH14  14
#define ADC_CH15  15
#define ADC_CH16  16
#define ADC_CH17  17

#define  TIME_14_CYCLES  0
#define  TIME_20_CYCLES	 1				
#define	 TIME_26_CYCLES	 2				
#define	 TIME_41_CYCLES	 3				
#define	 TIME_54_CYCLES	 4				
#define	 TIME_68_CYCLES	 5				
#define	 TIME_84_CYCLES	 6				
#define	 TIME_252_CYCLES 7	

#define ADC_DATA_RIGHT_ALIGNMENT   0
#define ADC_DATA_LEFT_ALIGNMENT    1 



/*		****Note****  : 	ADC1 analog Channel 16 and Channel 17 are internally connected to the temperature 
												sensor and to VREFINT, respectively
*/

/*
(2) Copy_u8Sample_Time
Select the sample time individually for each channel
The total conversion time is calculated as follows:
        ( Tconv = Sampling time + 12.5 cycles)
*/

/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : to start the conversion for passed channel*****************/
/*************************************** INPUTS  : (3) 							 			 *****************/
/*************************************** Output  : (enum)					   	 *****************************/
ADC_enuErrorStatus ADC_enuStartConversionSynch( u8 ADC_u8ChannelNumber , u16 * ADC_pu16ConvertedData ,u8 ADC_u8ModeConversion );

/*
	For Example : 
	ADC_u8ChannelNumber:
	ADC_CH0
	ADC_CH1
	ADC_CH2
	ADC_CH3
	   ..
	ADC_CH17
	
	ADC_pu16ConvertedData:
	u16 * pu16Data
	
	
	ADC_u8ModeConversion:
	ADC_SINGLE_MODE_CONVERSION 	
    ADC_CONTINUOUS_MODE_CONVERSION

*/

#define    ADC_SINGLE_MODE_CONVERSION 		    0
#define    ADC_CONTINUOUS_MODE_CONVERSION       1

/******************************************* Function(3) **********************************************************************/
/*************************************** Purpose : to start the conversion for passed channel Using Interrupt *****************/
/*************************************** INPUTS  : (pointer to struct) 						 	   			 *****************/
/*************************************** Output  : (enum)					   	 				 *****************************/










/******************************************* Function(4) *****************************************************/
/*************************************** Purpose : to start the conversion for passed channel*****************/
/*************************************** INPUTS  : (3) 							 			 *****************/
/*************************************** Output  : (enum)					   	 *****************************/
u16 ADC_u16AnalogWatchdogInterrupt(u8 Copy_u8Channel , u16 Copy_u16HighThresholdValue_mv ,u16 Copy_u16LowThresholdValue_mv );
/*
* Description : By using this function you will goto interrupt if the converted enterred channel's value exceeds the threshold values  
* ------------
* Inputs: (1)  Copy_u8Channel >> Channel to be converted
*		  (2)  Copy_u16HighThresholdValue_mv >>> Maximum value of the converted channel which not cause interrupt
*		  (3)  Copy_u16LowThresholdValue_mv  >>> Minimum value of the converted channel which not cause interrupt
*/


#define ADC_CHANNELS_GROUP   REGULAR_GROUP
/* Choose : 1-REGULAR_GROUP
			2-INJECTED_GROUP
			*/  

/*Choose  the total number of conversions in the regular 
channel conversion sequenc*/

#define ADC_REGULAR_CONVERSIONS  One_Conversion



#endif
