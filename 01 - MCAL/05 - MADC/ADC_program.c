/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** ADC_PROGRAM.c			                ****************/
/*** Date    : 9/7/2020                    ****************/
/*** Version :  02                          ****************/
/***********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_config.h"
#include "ADC_private.h"


static u16 * GstaticDataConverted = NULL;
static void (*GStaticCallBackFunc)(void) ;


void ADC_voidInit( ADC_Cnfg_type * Add_pstrADC )
{
	/*
	(1)ADC Sample Time
	*/
	u8 Local_u8Channel = (Add_pstrADC -> ADC_strChannel) ; 
	u8 Local_u8SampleTime =  (Add_pstrADC -> ADC_strSample_Time);
	//u8 Local_u8Prescaller = (Add_pstrADC -> ADC_strADCPrescaller);
	
	if ( Local_u8Channel <=  9  )
	{
		ADC_SMPR2 &= ~ ( 0b111  << (Local_u8Channel*3)); // Bit Masking
		ADC_SMPR2 |=  ( Local_u8SampleTime<< (Local_u8Channel*3)); // Set the value of sampling time
	}
	else if ( Local_u8Channel <= ADC_MAX_NUMBER_CHANNELS  ) 
	{
		Local_u8Channel -= 10;
		ADC_SMPR1 &= ~ ( 0b111  << (Local_u8Channel*3)); // Bit Masking
		ADC_SMPR1 |=  ( Local_u8SampleTime<< (Local_u8Channel*3)); // Set the value of sampling time
	}
	else
	{
		/*Error*/
	}
	
	/*
	(2)Select the alignment Converted data
	*/
	 if ((Add_pstrADC -> ADC_strAlignment) == ADC_DATA_LEFT_ALIGNMENT)
	 {
		 SET_BIT(ADC_CR2 , 11);// ALIGN Bit ( 0 : Right Aligned , 1 : Left Aligned)
	 }
	 else
	 {
		 CLR_BIT(ADC_CR2 , 11);
 	 }
	/*
	(3)select the external event used to trigger the start of conversion of a regular group
	*/
	ADC_CR2 &=~ 0x000E0000; //Bit Masking for bits (17,18,19)
	ADC_CR2 |=  0x000E0000; //to select SWSTART bit as a trigger source to start the conversion
	
	
	/* (4) Set the Clock of ADC */
	ADC_CCR &=~ (0b11 << 16 );
	ADC_CCR |=  (ADC_PRESCALLER << 16 );
	
	/*
	(5)Power On the ADC peripheral
	*/
	SET_BIT(ADC_CR2 , 0); //Setting ADON bit 
	
		
}




ADC_enuErrorStatus ADC_enuStartConversionSynch( u8 ADC_u8ChannelNumber , u16 * ADC_pu16ConvertedData ,u8 ADC_u8ModeConversion )
{
	ADC_enuErrorStatus Loacl_enuErrorStatus = ADC_enuOk;
	u16 Local_u16TimeOut = 500;
	u8 Local_u8EndOfConversionFlag ;

	
	/* (0) Validation of inputs */
	if ((ADC_pu16ConvertedData != NULL) && (ADC_u8ChannelNumber < ADC_MAX_NO_OF_CHANNELS))
	{	
		/*
		(1) Setting the channel
		*/
		// L[3:0]: Regular channel sequence length (No_OF_Conversions)
		ADC_SQR1 &=~ 0x00F00000; //Bit masking for bits (20,21,22,23)
		ADC_SQR1 |=  (ADC_REGULAR_CONVERSIONS << 20) ;
		
		ADC_SQR3 &=~ ( 0b11111  << (0)); //As we usually use single conversion ,// for multi channels "Scan mode" ( 0b11111  << (Copy_u8Channel*5));
		ADC_SQR3 |= ADC_u8ChannelNumber;
		/*
		(2)According to the mode we will start the conversion
		*/
		
		if (ADC_u8ModeConversion== ADC_SINGLE_MODE_CONVERSION)
		{
			SET_BIT(ADC_CR2 , 1); // CONT: Continuous conversion
		}
		else
		{
			CLR_BIT(ADC_CR2 , 1);	//Clearing CONT bit
		}
	//	GstaticDataConverted = (Add_strChannel ->ADC_pu16ConvertedData);
		/* Enable the interrupt*/
	//	SET_BIT(ADC_CR1 , 5);  // Set [EOCIE ,Bit 5]
		SET_BIT(ADC_CR2 , 0); //Setting ADON bit
		SET_BIT(ADC_CR2 , 30);//SWSTART: Start conversion of regular channels
		
		/* Checking for the End of Conversion */

		Local_u8EndOfConversionFlag =  GET_BIT(ADC_SR , 1);
		while ( (Local_u8EndOfConversionFlag == 0 ) && Local_u16TimeOut )//EOC flag
		{
			Local_u16TimeOut -- ;
			Local_u8EndOfConversionFlag =  GET_BIT(ADC_SR , 1);

		}
		Local_u8EndOfConversionFlag =  GET_BIT(ADC_SR , 1);

		if (Local_u8EndOfConversionFlag == 1)
		{
			if ( (GET_BIT(ADC_CR2 , 11)) == 1)
			{
				/* Hence it is left Aligned */
				*ADC_pu16ConvertedData = (u16)(ADC_DR >> 4);
			}
			else
			{
				/* Hence it is Right Aligned */
				*ADC_pu16ConvertedData = (u16) ADC_DR ;
			}

			/*  (2)>>>(3)clearing the flag  */
			CLR_BIT(ADC_SR , 1);//EOC bit

		}
		else
		{
			Loacl_enuErrorStatus = ADC_enuNOK;
		}

		
	}
	else 
	{
		Loacl_enuErrorStatus = ADC_enuNULLPointer;
	}
	return Loacl_enuErrorStatus;
}




u16 ADC_u16AnalogWatchdogInterrupt(u8 Copy_u8Channel , u16 Copy_u16HighThresholdValue_mv ,u16 Copy_u16LowThresholdValue_mv )
{
	/*
	(1) Setting the channel and number of conversios
	*/
	
	// L[3:0]: Regular channel sequence length (No_OF_Conversions)
	ADC_SQR1 &=~ 0x00F00000; //Bit masking for bits (20,21,22,23)
	ADC_SQR1 |=  ADC_REGULAR_CONVERSIONS << 20 ; 
	
	ADC_SQR3 &=~ ( 0b11111  << (0)); //As we usually use single conversion ,// for multi channels "Scan mode" ( 0b11111  << (Copy_u8Channel*5));
	ADC_SQR3 |=  Copy_u8Channel;
	
	
	/*
	(1-2) Enabling Analog Watchdog on all regular channels
	*/
	SET_BIT(ADC_CR1 , 23);  //AWDEN bit (Analog Watch Dog Enable)
	SET_BIT(ADC_CR1 , 6);   //AWDIE bit (Analog Watchdog Interrupt Enable bit)
	//(1-2-1) Enabling Analog Watchdog on one regular channel(Copy_u8Channel)
	SET_BIT(ADC_CR1 , 9); //AWDSGL bit (Analog Watch Dog Enable Signal)
	ADC_CR1 &=~ ( 0b11111  << (0)); //Bit masking for fisrt 5 bits of ADC_CR1
	ADC_CR1 |= Copy_u8Channel;
	
	
	/*
	(2)According to the mode we will start the conversion
	*/
	#if    ADC_CONVERSION_MODE == CONTINUOUS_CONVERSION
	/*ADC_CR2 = 0x000E0000*/ 
		SET_BIT(ADC_CR2 , 1); // CONT: Continuous conversion
		SET_BIT(ADC_CR2 , 22);//SWSTART: Start conversion of regular channels
		
	
	#elif  ADC_CONVERSION_MODE == SINGLE_CONVERSION
	
	/*
	(2)>>>(1) start conversion
	*/
	
	CLR_BIT(ADC_CR2 , 1);	//Clearing CONT bit
	SET_BIT(ADC_CR2 , 0); //Setting ADON bit
	SET_BIT(ADC_CR2 , 2); //Setting CAL bit "Caliperation"
	SET_BIT(ADC_CR2 , 22);//SWSTART: Start conversion of regular channels
	
	
	u16 Digital_High = ((u16)Copy_u16HighThresholdValue_mv*4096)/3300UL ; //Converting from analog to Digital
	ADC_HTR =  Digital_High;
	
	u16 Digital_Low  = ((u16)Copy_u16LowThresholdValue_mv*4096)/3300UL ; //Converting from analog to Digital
	ADC_LTR =  Digital_Low;
	/*
	(2)>>>(2) waiting for the flag
	*/
	while (GET_BIT(ADC_SR , 1) == 0);//EOC flag
	/*
	(2)>>>(3)clearing the flag
	*/
	CLR_BIT(ADC_SR , 1);//EOC bit
	
	#else 
	#error("You chosed wrong Conversion Mode")
	#endif
	/*
	(3) Reading the result
	*/
	 // Local_ADC_Result = ADC_DR ;
	return ( ADC_DR >> 4); //to read the data at first 12 bit of the register
}




void ADC_IRQHandler(void)
{
	/* (1) check for which flag*/
	if ((GET_BIT(ADC_SR , 1)) == 1) //EOC flag
	{
		if (GstaticDataConverted != NULL)
		{
			*GstaticDataConverted = (ADC_DR>>4) ;
			GStaticCallBackFunc();
		}
		CLR_BIT(ADC_SR , 1);//EOC bit
	}
	
	
}






/* ################################################################################################################## */




