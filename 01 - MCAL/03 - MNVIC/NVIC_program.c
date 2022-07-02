/***********************************************************/
/***********************************************************/
/**************** Author  :  Solyma         ****************/
/**************** Target  : ARM_CORETEX_M4	****************/
/**************** NVIC_ Program.c	    ****************/
/**************** Date    : 28/3/2022       ****************/
/**************** Version :  01             ****************/
/**************** Company : ITI 			****************/
/***********************************************************/
/***********************************************************/

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"NVIC_interface.h"
#include"NVIC_private.h"
#include"NVIC_config.h"

/************************************** Function (1) ********************************************/
/************************* purpose :  Enables an interrupt or exception.  **********************/

NVIC_ErrorState NVIC_EnableIRQ(u8 Copy_u8IRQ)
{
	NVIC_ErrorState Local_enuStatusError = NVIC_enuOk;
	volatile u8 Local_u8IRQn ;
	volatile u8 Local_u8Register;
	
	if (Copy_u8IRQ <= 240)
	{
		Local_u8Register = (Copy_u8IRQ / 32); //as every register control from (0:31) Interrupt request
		Local_u8IRQn     = (Copy_u8IRQ % 32); 
		
		switch(Local_u8Register)
		{
			case 0 : (NVIC_ISER -> NVIC_ISER0) |= (1 <<Local_u8IRQn) ; break;
			case 1 : (NVIC_ISER -> NVIC_ISER1) |= (1 <<Local_u8IRQn) ; break;
			case 2 : SET_BIT((NVIC_ISER -> NVIC_ISER2 ), Local_u8IRQn); break;
			case 3 : SET_BIT((NVIC_ISER -> NVIC_ISER3 ), Local_u8IRQn); break;
			case 4 : SET_BIT((NVIC_ISER -> NVIC_ISER4 ), Local_u8IRQn); break;
			case 5 : SET_BIT((NVIC_ISER -> NVIC_ISER5 ), Local_u8IRQn); break;
			case 6 : SET_BIT((NVIC_ISER -> NVIC_ISER6 ), Local_u8IRQn); break;
			case 7 : SET_BIT((NVIC_ISER -> NVIC_ISER7 ), Local_u8IRQn); break;
			default : break;
		}
		
	}
	else
	{
		Local_enuStatusError = NVIC_enuErrorIRQNumber;
	}
return Local_enuStatusError;

}

/************************************** Function (2) ********************************************/
/************************* purpose :  Disables an interrupt or exception.  **********************/

NVIC_ErrorState NVIC_DisableIRQ(u8 Copy_u8IRQ)
{
	NVIC_ErrorState Local_enuStatusError = NVIC_enuOk;
	u8 Local_u8IRQn ;
	u8 Local_u8Register;
	
	if (Copy_u8IRQ <= 240)
	{
		Local_u8Register = (Copy_u8IRQ / 32); //as every register control from (0:31) Interrupt request
		Local_u8IRQn     = (Copy_u8IRQ % 32); 
		
		switch(Local_u8Register)
		{
			case 0 : SET_BIT(NVIC_ICER -> NVIC_ICER0 , Local_u8IRQn); break;
			case 1 : SET_BIT(NVIC_ICER -> NVIC_ICER1 , Local_u8IRQn); break;
			case 2 : SET_BIT(NVIC_ICER -> NVIC_ICER2 , Local_u8IRQn); break;
			case 3 : SET_BIT(NVIC_ICER -> NVIC_ICER3 , Local_u8IRQn); break;
			case 4 : SET_BIT(NVIC_ICER -> NVIC_ICER4 , Local_u8IRQn); break;
			case 5 : SET_BIT(NVIC_ICER -> NVIC_ICER5 , Local_u8IRQn); break;
			case 6 : SET_BIT(NVIC_ICER -> NVIC_ICER6 , Local_u8IRQn); break;
			case 7 : SET_BIT(NVIC_ICER -> NVIC_ICER7 , Local_u8IRQn); break;
			default : break;
		}
		
	}
	else
	{
		Local_enuStatusError = NVIC_enuErrorIRQNumber;
	}
return Local_enuStatusError;

}


/************************************** Function (3) ******************************************************/
/************************* purpose : Sets the pending status of interrupt/exception  **********************/
/************************* Inputs  : (1)Interrupt Request Number                            ***************/
/************************* Output  : (1) {NVIC_enuErrorState}                        **********************/      
 
NVIC_ErrorState NVIC_SetPendingIRQ(u8 Copy_u8IRQ) 

{
	NVIC_ErrorState Local_enuStatusError = NVIC_enuOk;
	u8 Local_u8IRQn ;
	u8 Local_u8Register;
	
	if (Copy_u8IRQ <= 240)
	{
		Local_u8Register = (Copy_u8IRQ / 32); //as every register control from (0:31) Interrupt request
		Local_u8IRQn     = (Copy_u8IRQ % 32); 
		
		switch(Local_u8Register)
		{
			case 0 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR0) , Local_u8IRQn); break;
			case 1 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR1) , Local_u8IRQn); break;
			case 2 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR2), Local_u8IRQn); break;
			case 3 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR3), Local_u8IRQn); break;
			case 4 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR4), Local_u8IRQn); break;
			case 5 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR5), Local_u8IRQn); break;
			case 6 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR6) , Local_u8IRQn); break;
			case 7 : SET_BIT( (NVIC_ISPR -> NVIC_ISPR7) , Local_u8IRQn); break;
			default : break;
		}
		
	}
	else
	{
		Local_enuStatusError = NVIC_enuErrorIRQNumber;
	}
return Local_enuStatusError;

}


/************************************** Function (4) ******************************************************/
/************************* purpose : Clear the pending status of interrupt/exception  **********************/
/************************* Inputs  : (1)Interrupt Request Number                            ***************/
/************************* Output  : (1) {NVIC_enuErrorState}                        **********************/      
 
NVIC_ErrorState NVIC_ClearPendingIRQ(u8 Copy_u8IRQ) 

{
	NVIC_ErrorState Local_enuStatusError = NVIC_enuOk;
	u8 Local_u8IRQn ;
	u8 Local_u8Register;
	
	if (Copy_u8IRQ <= 240)
	{
		Local_u8Register = (Copy_u8IRQ / 32); //as every register control from (0:31) Interrupt request
		Local_u8IRQn     = (Copy_u8IRQ % 32); 
		
		switch(Local_u8Register)
		{
			case 0 : SET_BIT(NVIC_ICPR -> NVIC_ICPR0 , Local_u8IRQn); break;
			case 1 : SET_BIT(NVIC_ICPR -> NVIC_ICPR1 , Local_u8IRQn); break;
			case 2 : SET_BIT(NVIC_ICPR -> NVIC_ICPR2 , Local_u8IRQn); break;
			case 3 : SET_BIT(NVIC_ICPR -> NVIC_ICPR3 , Local_u8IRQn); break;
			case 4 : SET_BIT(NVIC_ICPR -> NVIC_ICPR4 , Local_u8IRQn); break;
			case 5 : SET_BIT(NVIC_ICPR -> NVIC_ICPR5 , Local_u8IRQn); break;
			case 6 : SET_BIT(NVIC_ICPR -> NVIC_ICPR6 , Local_u8IRQn); break;
			case 7 : SET_BIT(NVIC_ICPR -> NVIC_ICPR7 , Local_u8IRQn); break;
			default : break;
		}
		
	}
	else
	{
		Local_enuStatusError = NVIC_enuErrorIRQNumber;
	}
return Local_enuStatusError;

}

/************************************** Function (5) ********************************************/
/************************* purpose : Reads the pending status of interrupt **********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      

NVIC_ErrorState NVIC_GetPendingIRQ(u8 * Add_u8PendingState)
{
	
}

/************************************** Function (6) ******************************************************/
/************************* purpose : Set the Priority of interrupt/exception         **********************/
/************************* Inputs  : (2)Interrupt Request Number  , Priority         	    ***************/
/************************* Output  : (1) {NVIC_enuErrorState}                        **********************/      
 
NVIC_ErrorState NVIC_voidSetPriority (u8 Copy_u8IRQn , u8 Copy_u8Priority )
{
	NVIC_ErrorState Local_enuStatusError = NVIC_enuOk;
	
	if 	(Copy_u8IRQn  < 240) 
	{	
		NVIC_IPR[Copy_u8IRQn] = Copy_u8Priority << 4;// We must right all 8 bits with least significant bits 0000 , Ex: 00110000 
	}
	else 
	{
		Local_enuStatusError = NVIC_enuErrorIRQNumber;
	}
	return Local_enuStatusError;

}

/************************************** Function (7) ********************************************/
/************************* purpose : Reads the priority of an interrupt		**********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      
 
//NVIC_ErrorState NVIC_GetPriority(IRQn_Type IRQn , u8 * Add_u8Priority)
//{
	
//}
