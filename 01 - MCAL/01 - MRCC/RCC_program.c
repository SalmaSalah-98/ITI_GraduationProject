#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"RCC_interface.h"
#include"RCC_private.h"

/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : Initialize the System Clock in prebuild Time ***************/
RCC_enuErrorState RCC_enuInitSysClk(void)
{
	RCC_enuErrorState Local_enuErrorStatus = RCC_enuOK;
	u32 Local_RCC_CFGR = RCC_CFGR;
	u32 Local_RCC_CR = RCC_CR;
	u32 Local_RCC_PLLCFGR = RCC_PLLCFGR; 
	u8  Local_ClockFlag = 0;
	u8 Local_u8wait = RCC_RDY_FLAG_TIMEOUT;
	RCC_enuPLLErrorState Local_enuPLLErrorStatus = RCC_enuPLL_OK;
	
	
	#if RCC_SYS_CLK == RCC_HSI
	/*  (1) Setting HSION bit to enable HSI  */
	SET_BIT(RCC_CR,0); 
	
	/*  (2) Checking for HSIRDY flag */
	Local_ClockFlag = GET_BIT(Local_RCC_CR,1);
	while((Local_u8wait) && !(Local_ClockFlag))
	{
		Local_u8wait --;
		Local_ClockFlag = GET_BIT(Local_RCC_CR,1);
	}
	if (Local_ClockFlag)
	{
		/*  (3) Switch as the clock Source */
		Local_RCC_CFGR  &=~ ((0b11)<<(0));  // SW[0,1]
		Local_RCC_CFGR  |=  ((RCC_HSI)<<(0));

		/* (4) Checking for the status of the clock Source SWS[2:3] */
		
		if (((Local_RCC_CFGR >> 2) & 0b11) == RCC_HSI)//Get Bits 2,3
		{
			Local_enuErrorStatus = RCC_enuOK; 
		}
		else //of (((Local_RCC_CFGR >> 2) & 0b11) == RCC_HSI)//Get Bits 2,3
		{
			Local_enuErrorStatus = RCC_enuClockSourceSwitchError; 
		}
	}
	else // of (Local_ClockFlag)
	{
		Local_enuErrorStatus = RCC_enuClockNotReady; 
	}
	
	
	#elif RCC_SYS_CLK== RCC_HSE
	/*  (1) Setting HSEON bit */
	SET_BIT(RCC_CR,16); 
	
	/*  (2) Checking for HSERDY flag */
	Local_ClockFlag = GET_BIT(Local_RCC_CR,17);// 'HSERDY Bit'
	while((Local_u8wait) && (!(Local_ClockFlag)))
	{
		Local_u8wait --;
		Local_ClockFlag = GET_BIT(Local_RCC_CR,17);
	}
	if (Local_ClockFlag)
	{
		/*  (3) Switch as the clock Source */
		Local_RCC_CFGR  &=~ ((0b11)<<(0));
		Local_RCC_CFGR  |=  ((RCC_HSE)<<(0));

		/* (4) Checking for the status of the clock Source SWS[2:3] */
		
		if (((Local_RCC_CFGR >> 2) & 0b11) == RCC_HSE)//Get Bits 2,3
		{
			Local_enuErrorStatus = RCC_enuOK; 
		}
		else //of (((Local_RCC_CFGR >> 2) & 0b11) == RCC_HSE)//Get Bits 2,3
		{
			Local_enuErrorStatus = RCC_enuClockSourceSwitchError; 
		}
	}
	else // of (Local_ClockFlag)
	{
		Local_enuErrorStatus = RCC_enuClockNotReady; 
	}
	
	
	#elif RCC_SYS_CLK == RCC_PLL
/*  (0) Check if we can use PLL or it is already used */
if ((GET_BIT(Local_RCC_PLLCFGR, 24)) == 0)
{ 

/*  (1) Setting Configuration of PLL  */
/*  (1-1) Select PLL Clock Source (HSI / HSE)*/
		#if RCC_PLL_CLK_SOURCE == RCC_HSI_SOURCE
			CLR_BIT(Local_RCC_PLLCFGR , 22);//PLLSRC 
		#else 
			SET_BIT(Local_RCC_PLLCFGR , 22);//PLLSRC 
		#endif	
/*  (1-2) Select PLL Parameters (P - Q - M - N)*/
		Local_RCC_PLLCFGR	&=~ ((0b111111)<<(0));
		Local_RCC_PLLCFGR    |=  ((RCC_PLL_M)<<(0)); //Setting 'M' Parameter
	
		Local_RCC_PLLCFGR	&=~ ((0b111111111)<<(6));
		Local_RCC_PLLCFGR    |=  ((RCC_PLL_N)<<(6)); //Setting 'N' Parameter
		
		Local_RCC_PLLCFGR	&=~ ((0b11)<<(16));
		Local_RCC_PLLCFGR    |=  ((RCC_PLL_P)<<(16)); //Setting 'N' Parameter
	
		RCC_PLLCFGR = Local_RCC_PLLCFGR;
/*  (2) Setting PLLON  bit  to Enable the PLL Clock Source */
	SET_BIT(Local_RCC_CR,24); 
	
/*  (3) Checking for HSIRDY flag */
	Local_ClockFlag = GET_BIT(Local_RCC_CR,25);// 'PLLRDY Bit'
	while((Local_u8wait) && (!(Local_ClockFlag)))
	{
		Local_u8wait --;
		Local_ClockFlag = GET_BIT(Local_RCC_CR,25);
	}
	if (Local_ClockFlag)
	{
		/*  (4) Switch as the clock Source */
		Local_RCC_CFGR  &=~ ((0b11)<<(0));
		Local_RCC_CFGR  |=  ((RCC_PLL)<<(0));

		/* (5) Checking for the status of the clock Source SWS[2:3] */
		
		if (((Local_RCC_CFGR >> 2) & 0b11) == RCC_PLL)//Get Bits 2,3
		{
			Local_enuErrorStatus = RCC_enuOK; 
		}
		else //of (((Local_RCC_CFGR >> 2) & 0b11) == RCC_PLL)//Get Bits 2,3
		{
			Local_enuErrorStatus = RCC_enuClockSourceSwitchError; 
		}
	}
	else // of (Local_ClockFlag)
	{
		Local_enuErrorStatus = RCC_enuClockNotReady; 
	}
}
else
{
	Local_enuPLLErrorStatus = RCC_enuPLL_EnableError
}	
	#else 
	Local_enuErrorStatus = RCC_enuClockSourceError; 
	#endif
	
	/* Assigning in the registers */
	RCC_CR      = Local_RCC_CR ;
	RCC_CFGR    =	Local_RCC_CFGR ;
	RCC_PLLCFGR = Local_RCC_PLLCFGR ;
	return Local_enuErrorStatus;
}
	/****************************************************************************************************/
	/* ----------------------------------------------------------------------------------------------- */


/***************************************** Function (2) **************************************************/
/*************************** purpose :  Initialize the clock system (Post build)  ***********************/
RCC_enuErrorState RCC_enuSetClockSystem(u8 Copy_u8ClockSource)
{
	RCC_enuErrorState Local_enuErrorState = RCC_enuOK;
	u8 Local_u8RdyFlag = 0;
	u8 Local_u8ClockStatus ;
	u8 Local_u8wait = 50;
	if (Copy_u8ClockSource > 2)
	{
		Local_enuErrorState = RCC_enuClockSourceError;
	}
	else
	{
		// Clock Source is right
		
		switch(Copy_u8ClockSource)
		{
			case RCC_HSI : SET_BIT(RCC_CR , 0);//HSION
						  //(2)wait until HSIRY == 1
							Local_u8RdyFlag = GET_BIT(RCC_CR ,1);
							while((Local_u8wait) && !(Local_u8RdyFlag))
							{
								Local_u8wait --;
								Local_u8RdyFlag = GET_BIT(RCC_CR ,1); //1
								if (Local_u8RdyFlag == 1)
								{
									Local_enuErrorState = RCC_enuOK;
								}
								else
								{
									Local_enuErrorState = RCC_enuClockNotReady;
								}
							}
							//(3) Access SW bits[0;1]
							RCC_CFGR &=~ (0b11) ;//BIT_MASKING
							RCC_CFGR |= (RCC_HSI) ;
							
							//(4) Check SWS bits
							  Local_u8ClockStatus = (( RCC_CFGR >> 2 )& 0b11); //SWS [2,3]
							  if(Local_u8ClockStatus == RCC_HSI)
							  {
								  Local_enuErrorState = RCC_enuOK;
							  }
							  else
							  {
								  Local_enuErrorState = RCC_enuClockSourceSwitchError;
							  }
			break;
			case RCC_HSE :SET_BIT(RCC_CR , 16);//HSEON
						  //(2)wait until HSERY == 1
							Local_u8RdyFlag = GET_BIT(RCC_CR ,17);
							while((Local_u8wait) && !(Local_u8RdyFlag))
							{
								Local_u8wait --;
								Local_u8RdyFlag = GET_BIT(RCC_CR ,17); //1
								if (Local_u8RdyFlag == 1)
								{
									Local_enuErrorState = RCC_enuOK;
								}
								else
								{
									Local_enuErrorState = RCC_enuClockNotReady;
								}
							}
							//(3) Access SW bits[0;1]
							RCC_CFGR &=~ (0b11);//BIT_MASKING
							RCC_CFGR |= (RCC_HSE);
							
							//(4) Check SWS bits
							  Local_u8ClockStatus = (( RCC_CFGR >> 2 )& 0b11); //SWS [2,3]
							  if(Local_u8ClockStatus == RCC_HSE)
							  {
								  Local_enuErrorState = RCC_enuOK;
							  }
							  else
							  {
								  Local_enuErrorState = RCC_enuClockSourceSwitchError;
							  }
			
			break;
			
			case RCC_PLL : SET_BIT(RCC_CR , 24);//PLLON
						  //(2)wait until PLLRY == 1
							Local_u8RdyFlag = GET_BIT(RCC_CR ,25);
							while((Local_u8wait) && !(Local_u8RdyFlag))
							{
								Local_u8wait --;
								Local_u8RdyFlag = GET_BIT(RCC_CR ,25); //1
								if (Local_u8RdyFlag == 1)
								{
									Local_enuErrorState = RCC_enuOK;
								}
								else
								{
									Local_enuErrorState = RCC_enuClockNotReady;
								}
							}
							//(3) Access SW bits[0;1]
							RCC_CFGR &=~ (0b11);//BIT_MASKING
							RCC_CFGR |= (RCC_PLL);
							
							//(4) Check SWS bits
							  Local_u8ClockStatus = (( RCC_CFGR >> 2 )& 0b11); //SWS [2,3]
							  if(Local_u8ClockStatus == RCC_PLL)
							  {
								  Local_enuErrorState = RCC_enuOK;
							  }
							  else
							  {
								  Local_enuErrorState = RCC_enuClockSourceSwitchError;
							  }
			break;
			default : break;
			
		}
		
	}

	
	
	return Local_enuErrorState;
}
/****************************************************************************************************/
/* ----------------------------------------------------------------------------------------------- */


/************************************** Function (3) ********************************************/
/************************* purpose :  Initialize the prescaller of the passed  bus **************/

RCC_enuErrorState  RCC_enuSetBusPrescaller(u8 Copy_u8BusId ,u8 Copy_u8Prescaller)
{
	RCC_enuErrorState Local_enuErrorStatus =  RCC_enuOK;
	
	if (Copy_u8BusId == RCC_APB2)
	{
		if (Copy_u8Prescaller <= RCC_APB2_PRESCALLER_16)
		{
			//Bits [15:13] PPRE2: APB high-speed prescaler (APB2)
			RCC_CFGR  &=~ ((0b111)<<(13));
			RCC_CFGR  |=  ((Copy_u8Prescaller)<<(13));
		}
		else 
		{
			Local_enuErrorStatus = RCC_enuPrescallerError;
		}
	}
	else if (Copy_u8BusId == RCC_AHB)
	{
		if (Copy_u8Prescaller <= RCC_AHB_PRESCALLER_512)
		{
			//Assignning Bits [7:4] HPRE
			RCC_CFGR  &=~ ((0b1111)<<(4));
			RCC_CFGR  |=  ((Copy_u8Prescaller)<<(4));
		}
		else 
		{
			Local_enuErrorStatus = RCC_enuPrescallerError;
		}
	}// else if (Copy_u8BusId == RCC_AHB)
		
	else if (Copy_u8BusId == RCC_APB1)
	{/*The software has to set these bits correctly not to exceed 42 MHz on this domain. 
		The clocks are divided with the new prescaler factor from 1 to 16 AHB cycles after 
		PPRE1 write*/
		
		if (Copy_u8Prescaller <= RCC_APB1_PRESCALLER_16)
		{
			//Bits [12:10] PPRE1 : APB Low speed prescaler (APB1)
			RCC_CFGR  &=~ ((0b111)<<(10));
			RCC_CFGR  |=  ((Copy_u8Prescaller)<<(10));
		}
		else 
		{
			Local_enuErrorStatus = RCC_enuPrescallerError;
		}
	}//else if (Copy_u8BusId == RCC_APB1)
		
	
	else
	{
		Local_enuErrorStatus = RCC_enuBusError;
	}//else 

	return Local_enuErrorStatus;
}
/****************************************************************************************************/
/* ----------------------------------------------------------------------------------------------- */






/************************************** Function (4) *****************************************************/
/************************* purpose :  Configure the parameters of PLL as a clock source ******************/

RCC_enuPLLErrorState RCC_voidSetPLLClockParameters(u8 Copy_u8PLL_Source,u8 Copy_u8PLL_M,u8 Copy_u8PLL_N,u8 Copy_u8PLL_P) 
{
	RCC_enuPLLErrorState Local_enuErrorStatus = RCC_enuPLL_OK;
	u32 Local_RCC_PLLCFGR = RCC_PLLCFGR;
	u32 Local_VCOInput ;// " Local_VCOInput = PLL_input / M "
	u32 Local_VCO_Out ;// " Local_VCO_Out = Local_VCOInput * N "
	u32 Local_Out_Clock;
	
	/* (1) Check  if the pll is disabled or not */
	if (GET_BIT(RCC_CR,24) == 0)
	{
/* (2) Ckeck the validation of the parameters  */
/* (2-1) Ckeck the validation input source Clock   */
		if (Copy_u8PLL_Source > RCC_PLL_HSE) //(Copy_u8PLL_Source > 1)
		{
			Local_enuErrorStatus = RCC_enuPLL_Wrong_Source;
		}//End of if (Copy_u8PLL_Source > RCC_PLL_HSE)
		else if (Copy_u8PLL_Source == RCC_PLL_HSE) // of if (Copy_u8PLL_Source > RCC_PLL_HSE) //(Copy_u8PLL_Source > 1)
		{
			SET_BIT(Local_RCC_PLLCFGR , 22);		
		}
		else 
		{
			CLR_BIT(Local_RCC_PLLCFGR , 22);	//RCC_PLL_HSI
		}

/* (2-2-1) Ckeck the validation input 'M'   */
		if ((RCC_PLL_M_MIN <=Copy_u8PLL_M) && (Copy_u8PLL_M <= RCC_PLL_M_MAX))
		{
			if (Copy_u8PLL_Source == RCC_PLL_HSI) //HSI = 16000000
				{
					Local_VCOInput  = (16000000 / Copy_u8PLL_M);
					if ((RCC_PLL_VCO_IN_MIN > Local_VCOInput) || (RCC_PLL_VCO_IN_MAX < Local_VCOInput))
					{
						Local_enuErrorStatus = RCC_enuPLL_Wrong_M;
					}
					else
					{
						//Assignning RCC_PLLCFGR[0:5]
						Local_RCC_PLLCFGR  &=~ ((0b111111)<<(0));
						Local_RCC_PLLCFGR  |=  ((Copy_u8PLL_M)<<(0));
					}
				}
			else // if (Copy_u8PLL_Source == RCC_PLL_HSI) //HSI = 16000000
				{
					Local_VCOInput  = (25000000 / Copy_u8PLL_M); //HSE = 25000000
					if ((RCC_PLL_VCO_IN_MIN > Local_VCOInput) || (RCC_PLL_VCO_IN_MAX < Local_VCOInput))
					{
						Local_enuErrorStatus = RCC_enuPLL_Wrong_M;
					}
					else
					{
						//Assignning RCC_PLLCFGR[0:5]
						Local_RCC_PLLCFGR  &=~ ((0b111111)<<(0));
						Local_RCC_PLLCFGR  |=  ((Copy_u8PLL_M)<<(0));
					}
				}				
		} //if ((RCC_PLL_M_MIN <=Copy_u8PLL_M) && (Copy_u8PLL_M <= RCC_PLL_M_MAX))
		else//of if((2 <=Copy_u8PLL_M) && (Copy_u8PLL_M <= 63))
		{
			Local_enuErrorStatus =  RCC_enuPLL_Wrong_M;
		}
		
/* (2-2-2) Ckeck the validation input 'N'  */
		if ((RCC_PLL_N_MIN <=Copy_u8PLL_N) && (Copy_u8PLL_N <= RCC_PLL_N_MAX))
		{
			Local_VCO_Out  = (Local_VCOInput * Copy_u8PLL_N);
					if ((RCC_PLL_VCO_OUT_MIN > Local_VCO_Out) || (RCC_PLL_VCO_OUT_MAX < Local_VCO_Out))
					{
						Local_enuErrorStatus = RCC_enuPLL_Wrong_N;
					}
					else 
					{
						////Assignning RCC_PLLCFGR[6:14]
						Local_RCC_PLLCFGR  &=~ ((0b111111111)<<(6));
						Local_RCC_PLLCFGR  |=  ((Copy_u8PLL_N)<<(6));
					}
		} //if ((RCC_PLL_N_MIN <=Copy_u8PLL_N) && (Copy_u8PLL_N <= RCC_PLL_N_MAX))
		else //if ((RCC_PLL_N_MIN <=Copy_u8PLL_N) && (Copy_u8PLL_N <= RCC_PLL_N_MAX))
		{
			Local_enuErrorStatus =  RCC_enuPLL_Wrong_N;
		}
		
/* (2-2-3) Ckeck the validation input 'P'  */
		if ((RCC_PLL_P_MIN <=Copy_u8PLL_P) && (Copy_u8PLL_P <= RCC_PLL_P_MAX))
		{
			Local_Out_Clock = (Local_VCO_Out / Copy_u8PLL_P);
			if (Local_Out_Clock > RCC_PLL_OUT_MAX)
				{
					Local_enuErrorStatus = RCC_enuPLL_Wrong_P;
				}
			else
				{
					//Assignning RCC_PLLCFGR[16,17]
					Local_RCC_PLLCFGR  &=~ ((0b11)<<(16));
					Local_RCC_PLLCFGR  |=  ((Copy_u8PLL_P)<<(16));
					
				}
		} //if ((RCC_PLL_P_MIN <=Copy_u8PLL_P) && (Copy_u8PLL_P <= RCC_PLL_P_MAX))
		else //if ((RCC_PLL_P_MIN <=Copy_u8PLL_P) && (Copy_u8PLL_P <= RCC_PLL_P_MAX))
		{
			Local_enuErrorStatus =  RCC_enuPLL_Wrong_P;
		}
		
		
	}//if (GET_BIT(RCC_CR,24) == 0)
	else 
	{
		Local_enuErrorStatus = RCC_enuPLL_EnableError;//Becouse it is already enabled
	}
	
	RCC_PLLCFGR = Local_RCC_PLLCFGR ;
	return Local_enuErrorStatus;

}
/****************************************************************************************************/
/* ----------------------------------------------------------------------------------------------- */



/************************************** Function (5) ********************************************/
/************************* purpose :  Enable the passed peripheral         **********************/
RCC_enuErrorState RCC_enuEnable_Peripheral_Clock(u8 Copy_u8PeripheralID)
{
	RCC_enuErrorState Local_enuErrorState = RCC_enuOK;
	u8 Local_u8Bus_Peripheral  = Copy_u8PeripheralID;
	u8 Local_u8Bus_Num;
	/* Get the first 5 bits [0:4] which define the Peripheral number */
	u8 Local_u8Peripheral_Num = ((Local_u8Bus_Peripheral) & 0b11111);
	
	if (Local_u8Peripheral_Num < 32)
	{
	/* Get the bits [5,6] which define the Bus number */
	 Local_u8Bus_Num =  ((Local_u8Bus_Peripheral>> 5) & 0b11);
	 switch(Local_u8Bus_Num)
	 {
		 /* case : 0b00 */
		 case RCC_AHB : SET_BIT(RCC_AHB1ENR ,Local_u8Peripheral_Num ); 
		 break;
		 /* case : 0b01 */
		 case RCC_APB1: SET_BIT(RCC_APB1ENR ,Local_u8Peripheral_Num ); 
		 break;
		 /* case : 0b10 */
		 case RCC_APB2: SET_BIT(RCC_APB2ENR ,Local_u8Peripheral_Num ); 
		 break;
		 default : break;
	 } 
	
	}
	else
	{
		Local_enuErrorState = RCC_enuPeripheralError;
	}

	
	return Local_enuErrorState;
}
/****************************************************************************************************/
/* ----------------------------------------------------------------------------------------------- */




/************************************** Function (6) ********************************************/
/************************* purpose :  Disable the passed peripheral         **********************/
RCC_enuErrorState RCC_enuDisable_Peripheral_Clock(u8 Copy_u8PeripheralID)
{
	RCC_enuErrorState Local_enuErrorState = RCC_enuOK;
	u8 Local_u8Bus_Peripheral  = Copy_u8PeripheralID;
	u8 Local_u8Bus_Num;
	/* Get the first 5 bits [0:4] which define the Peripheral number */
	u8 Local_u8Peripheral_Num = ((Local_u8Bus_Peripheral) & 0b11111);
	
	if (Local_u8Peripheral_Num < 32)
	{
	/* Get the bits [5,6] which define the Bus number */
	 Local_u8Bus_Num =  ((Local_u8Bus_Peripheral>> 5) & 0b11);
	 switch(Local_u8Bus_Num)
	 {
		 /* case : 0b00 */
		 case RCC_AHB : CLR_BIT(RCC_AHB1ENR ,Local_u8Peripheral_Num ); 
		 break;
		 /* case : 0b01 */
		 case RCC_APB1: CLR_BIT(RCC_APB1ENR ,Local_u8Peripheral_Num ); 
		 break;
		 /* case : 0b10 */
		 case RCC_APB2: CLR_BIT(RCC_APB2ENR ,Local_u8Peripheral_Num ); 
		 break;
		 default : break;
	 } 
	
	}
	else
	{
		Local_enuErrorState = RCC_enuPeripheralError;
	}

	
	return Local_enuErrorState;
}
/****************************************************************************************************/
/* ----------------------------------------------------------------------------------------------- */


