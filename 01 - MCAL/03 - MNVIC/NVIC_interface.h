/*******************************************************************************************/
/************** Author  :  Solyma                      *************************************/
/************** RCC_Interface 						   *************************************/
/************** Target 	: STM32f401					   *************************************/
/************** Date    : 8/3/2022                     *************************************/
/************** Version :  01                          *************************************/
/************** Description : there are 6 Functions for RCC Peripheral*/
/************** (1)RCC_enuInitSysClk(void); */
/************** (2)RCC_enuSetClockSystem(u8 Copy_u8ClockSource);*/
/************** (3)RCC_enuSetBusPrescaller(u8 Copy_u8BusId ,u8 Copy_u8Prescaller);*/
/************** (4)RCC_voidSetPLLClockParameters(u8 Copy_u8PLL_Source,u8 Copy_u8PLL_M,u8 Copy_u8PLL_N,u8 Copy_u8PLL_P);*/
/************** (5)RCC_enuEnable_Peripheral_Clock(u8 Copy_u8PeripheralID); */
/************** (6)RCC_enuDisable_Peripheral_Clock(u8 Copy_u8PeripheralID);*/
/**********************************************************************************************************************/

#ifndef NVIC_INTERFACE_H
#define NVIC_INTERFACE_H


typedef enum 
{
	NVIC_enuOk,
	NVIC_enuErrorIRQNumber, 
	
	
}NVIC_ErrorState;


/************************************** Function (1) ********************************************/
/************************* purpose :  Enables an interrupt or exception.  **********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      

NVIC_ErrorState NVIC_EnableIRQ(u8 Copy_u8IRQ);





/************************************** Function (2) ********************************************/
/************************* purpose :  Disables an interrupt or exception.  **********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      

NVIC_ErrorState NVIC_DisableIRQ(u8 Copy_u8IRQ);




/************************************** Function (3) ******************************************************/
/************************* purpose : Sets the pending status of interrupt/exception  **********************/
/************************* Inputs  : (1)Interrupt Request Number                            ***************/
/************************* Output  : (1) {NVIC_enuErrorState}                        **********************/      
 
NVIC_ErrorState NVIC_SetPendingIRQ(u8 Copy_u8IRQ) ;


/************************************** Function (4) ********************************************/
/************************* purpose : Clears the pending status of interrupt **********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      

NVIC_ErrorState NVIC_ClearPendingIRQ(u8 Copy_u8IRQ) ;


/************************************** Function (5) ********************************************/
/************************* purpose : Reads the pending status of interrupt **********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      

NVIC_ErrorState NVIC_GetPendingIRQ(u8 * Add_u8PendingState);



/************************************** Function (6) ******************************************************/
/************************* purpose : Set the Priority of interrupt/exception         **********************/
/************************* Inputs  : (2)Interrupt Request Number  , Priority         	    ***************/
/************************* Output  : (1) {NVIC_enuErrorState}                        **********************/      
 
NVIC_ErrorState NVIC_voidSetPriority (u8 Copy_u8IRQn , u8 Copy_u8Priority );


/************************************** Function (7) ********************************************/
/************************* purpose : Reads the priority of an interrupt		**********************/
/************************* Inputs  : (void)# You can Configure it in config file  ***************/
/************************* Output  : (1) {ADV_enuErrorState}               **********************/      
 
//NVIC_ErrorState NVIC_GetPriority(IRQn_Type IRQn , u8 * Add_u8Priority);











#endif
