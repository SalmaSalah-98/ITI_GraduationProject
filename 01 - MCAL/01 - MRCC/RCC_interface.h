/*******************************************************************************************************************/
/************************************** Author  :  Solyma                      *************************************/
/************************************** RCC_Interface 						   *************************************/
/************************************** Target 	: STM32f401					   *************************************/
/************************************** Date    : 8/3/2022                     *************************************/
/************************************** Version :  01                          *************************************/
/************************************** Description : there are 6 Functions for RCC Peripheral
/************************************** (1)RCC_enuInitSysClk(void);
/************************************** (2)RCC_enuSetClockSystem(u8 Copy_u8ClockSource);
/************************************** (3)RCC_enuSetBusPrescaller(u8 Copy_u8BusId ,u8 Copy_u8Prescaller);
/************************************** (4)RCC_voidSetPLLClockParameters(u8 Copy_u8PLL_Source,u8 Copy_u8PLL_M,u8 Copy_u8PLL_N,u8 Copy_u8PLL_P);
/************************************** (5)RCC_enuEnable_Peripheral_Clock(u8 Copy_u8PeripheralID); 
/************************************** (6)RCC_enuDisable_Peripheral_Clock(u8 Copy_u8PeripheralID);
/**********************************************************************************************************************************************/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H

typedef enum
{
	RCC_enuOK,
	RCC_enuClockSourceError,
	RCC_enuClockSourceSwitchError,
	RCC_enuClockNotReady,
	RCC_enuBusError,
	RCC_enuPrescallerError,
	
	RCC_enuPeripheralError,
}RCC_enuErrorState;

typedef enum
{
	RCC_enuPLL_OK,
	RCC_enuPLL_Wrong_Source,
	RCC_enuPLL_Wrong_M,
	RCC_enuPLL_Wrong_N,
	RCC_enuPLL_Wrong_P,
	RCC_enuPLL_Wrong_Q,
	RCC_enuPLL_EnableError,
	
}RCC_enuPLLErrorState;

#define  RCC_HSI   0b00
#define  RCC_HSE   0b01
#define  RCC_PLL   0b10



/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : Initialize the System Clock in prebuild  ******************/
/*************************************** INPUTS  : (0) all inputs are configured         *********************/
/*************************************** Output  : Enum to Check               *******************************/
RCC_enuErrorState RCC_enuInitSysClk(void);
/* (1) You should to Configure these inputs to "Choose the Clock Source " */
#define RCC_SYS_CLK  RCC_HSI //RCC_HSI as an example
/* Choose From :
@ RCC_HSI
@ RCC_HSE
@ RCC_PLL
*/
/* (2) You should to Configure these inputs to "Set the parameters of PLL in case of as a clock source " */
#define RCC_PLL_CLK_SOURCE   RCC_HSI_SOURCE //RCC_HSI_SOURCE as an example
/*Choose From :
@ RCC_HSI_SOURCE
@ RCC_HSE_SOURCE
*/
#define RCC_HSI_SOURCE  0
#define RCC_HSE_SOURCE  1

#define RCC_PLL_M       2  //2 as an example
/*Choose From : 2 To 63 */

#define RCC_PLL_N        
/*Choose From : 2 To 63 */

#define RCC_PLL_P       4 // 4 as an example 
/*Choose From : 2 To 8 */
/**---------------------------------------------------------------------------------------------------****/




/************************************** Function (2) ********************************************/
/************************* purpose :  Initialize the clock system Post build  *******************/
/************************* Inputs  : (1) {u8 Copy_u8ClockSource}              *******************/
/************************* Output  : (1) {RCC_enuErrorState}                  *******************/
/************************* Caution :  User should call the function at first 
										'RCC_voidSetPLLClockParameters'
									  In case of using PLL as a clock source *********************/
RCC_enuErrorState RCC_enuSetClockSystem(u8 Copy_u8ClockSource);
/* Choose From :
@ RCC_HSI
@ RCC_HSE
@ RCC_PLL
*/
/***********************************************************************************************/





/************************************** Function (3) ********************************************/
/************************* purpose :  Initialize the prescaller of the passed  bus **************/
/************************* Inputs  : (2) {u8 Copy_u8BusId, u8 Copy_u8Prescaller}       **********/
/************************* Output  : (1) {RCC_enuErrorState}               **********************/      

RCC_enuErrorState  RCC_enuSetBusPrescaller(u8 Copy_u8BusId ,u8 Copy_u8Prescaller);


/* 				   RCC_enuSetBusPrescaller( RCC_AHB        ,  RCC_AHB_PRESCALLER_1  
                                                              RCC_AHB_PRESCALLER_2
															  RCC_AHB_PRESCALLER_4  
															  RCC_AHB_PRESCALLER_8  
															  RCC_AHB_PRESCALLER_16 
															  RCC_AHB_PRESCALLER_64 
															  RCC_AHB_PRESCALLER_128
															  RCC_AHB_PRESCALLER_256
                                                              RCC_AHB_PRESCALLER_512 )


*                   RCC_enuSetBusPrescaller( RCC_APB1        , RCC_APB1_PRESCALLER_1  
                                                               RCC_APB1_PRESCALLER_2   
                                                               RCC_APB1_PRESCALLER_4   
*                   						                   RCC_APB1_PRESCALLER_8  
*                                                              RCC_APB1_PRESCALLER_16 )

*                   RCC_enuSetBusPrescaller( RCC_APB2         ,RCC_APB2_PRESCALLER_1 
															   RCC_APB2_PRESCALLER_2 
*                                                              RCC_APB2_PRESCALLER_4 
                                                               RCC_APB2_PRESCALLER_8 
                                                               RCC_APB2_PRESCALLER_16)

*/
/**-----------------------------------------------------------------------------------------------------**/
/*********************************************************************************************************/
#define RCC_AHB   0
#define RCC_APB1  1
#define RCC_APB2  2

/* Prescaller of RCC_AHB */
#define   RCC_AHB_PRESCALLER_1         0b0000
#define   RCC_AHB_PRESCALLER_2         0b1000
#define   RCC_AHB_PRESCALLER_4         0b1001
#define   RCC_AHB_PRESCALLER_8         0b1010
#define   RCC_AHB_PRESCALLER_16        0b1011
#define   RCC_AHB_PRESCALLER_64        0b1100
#define   RCC_AHB_PRESCALLER_128       0b1101
#define   RCC_AHB_PRESCALLER_256       0b1110
#define   RCC_AHB_PRESCALLER_512       0b1111

/* Prescaller of RCC_APB1 */
#define   RCC_APB1_PRESCALLER_1          0b000
#define   RCC_APB1_PRESCALLER_2          0b100
#define   RCC_APB1_PRESCALLER_4          0b101
#define   RCC_APB1_PRESCALLER_8          0b110
#define   RCC_APB1_PRESCALLER_16         0b111

/* Prescaller of RCC_APB2 */
#define   RCC_APB2_PRESCALLER_1          0b000
#define   RCC_APB2_PRESCALLER_2          0b100
#define   RCC_APB2_PRESCALLER_4          0b101
#define   RCC_APB2_PRESCALLER_8          0b110
#define   RCC_APB2_PRESCALLER_16         0b111



/************************************** Function (4) *****************************************************/
/************************* purpose :  Configure the parameters of PLL as a clock source ******************/
/************************* Inputs  : (4) {Copy_u8PLL_Source , Copy_u8PLL_M , Copy_u8PLL_N , Copy_u8PLL}***/
/************************* Output  : (1) {RCC_enuPLLErrorState}                    ***********************/ 

RCC_enuPLLErrorState RCC_voidSetPLLClockParameters(u8 Copy_u8PLL_Source,u8 Copy_u8PLL_M,u8 Copy_u8PLL_N,u8 Copy_u8PLL_P);


/*					 RCC_voidSetPLLClockParameters( RCC_PLL_HSI        , RCC_PLL_M_MIN , RCC_PLL_N_MIN,   RCC_PLL_P_MIN
													RCC_PLL_HSE		   ,	.          ,	.         ,	.
																	   ,	.          ,	.         ,	.
*                                                   		           , RCC_PLL_M_MAX , RCC_PLL_N_MAX,   RCC_PLL_P_MAX )
*
*/
/**-----------------------------------------------------------------------------------------------------**/
/*********************************************************************************************************/



 
/******************************************* Function (5) ************************************************/
/****************************** purpose :  Enable the passed peripheral         **************************/
/****************************** Inputs  : (1) {u8 Copy_u8PeripheralID}          **************************/
/****************************** Output  : (1) {RCC_enuErrorState}               **************************/ 
RCC_enuErrorState RCC_enuEnable_Peripheral_Clock(u8 Copy_u8PeripheralID);
/*
*				  RCC_enuEnable_Peripheral_Clock(	RCC_GPIOA_EN
*													RCC_GPIOB_EN
*													RCC_GPIOC_EN
*													RCC_GPIOD_EN
*													RCC_GPIOE_EN
*													RCC_GPIOH_EN
*													RCC_CRC_EN  
*													RCC_DMA1_EN 
*													RCC_DMA2_EN  
*													    .
*														. 
*														
*														)

*/


/**-----------------------------------------------------------------------------------------------------**/
/*********************************************************************************************************/




/************************************** Function (6) ********************************************/
/************************* purpose :  Disable the passed peripheral         **********************/
/************************* Inputs  : (1) {u8 Copy_u8PeripheralID}       **********/
/************************* Output  : (1) {RCC_enuErrorState}               **********************/ 
RCC_enuErrorState RCC_enuDisable_Peripheral_Clock(u8 Copy_u8PeripheralID);
/**-----------------------------------------------------------------------------------------------------**/
/*********************************************************************************************************/




/* Sources of PLL */
#define RCC_PLL_HSI 0
#define RCC_PLL_HSE 1
/* Ranges of PLL Parameters */
#define   RCC_PLL_M_MIN    2 
#define   RCC_PLL_M_MAX    63 //(26/2)=13

#define   RCC_PLL_N_MIN    192 
#define   RCC_PLL_N_MAX    432 

#define   RCC_PLL_P_MIN    2 
#define   RCC_PLL_P_MAX    8 

#define   RCC_PLL_VCO_IN_MIN    1000000 //(1 MHZ)
#define   RCC_PLL_VCO_IN_MAX    2000000 //(2 MHZ) 

#define   RCC_PLL_VCO_OUT_MIN    192000000 //(192 MHZ)
#define   RCC_PLL_VCO_OUT_MAX    432000000 //(432 MHZ) 

#define   RCC_PLL_OUT_MAX        84000000 //(432 MHZ) 


#define RCC_RDY_FLAG_TIMEOUT   50


/* For Enabling Clock for Peripherals */

/* (1) RCC AHB1 peripheral clock enable Peripherals */
#define RCC_GPIOA_EN  	     0 // SET_BIT(RCC_AHB1 ,RCC_GPIOA_EN )
#define RCC_GPIOB_EN 	     1
#define RCC_GPIOC_EN	     2
#define RCC_GPIOD_EN	     3	
#define RCC_GPIOE_EN	     4
#define RCC_GPIOH_EN	     7
#define RCC_CRC_EN  	     12
#define RCC_DMA1_EN          21
#define RCC_DMA2_EN          22


/* (2) RCC APB1 peripheral clock enable Peripherals */
#define RCC_TIM2_EN  	     0+0b00100000
#define RCC_TIM3_EN 	     1+0b00100000
#define RCC_TIM4_EN	 	     2+0b00100000
#define RCC_TIM5_EN	 	     3+0b00100000	
#define RCC_WWDG_EN	 	     11+0b00100000
#define RCC_SPI2_EN	 	     14+0b00100000
#define RCC_SPI3_EN  	     15+0b00100000
#define RCC_USART2_EN        17+0b00100000
#define RCC_I2C1_EN          21+0b00100000
#define RCC_I2C2_EN          22+0b00100000
#define RCC_I2C3_EN          23+0b00100000
#define RCC_PWR_EN           28+0b00100000
						    

/* (3) RCC APB2 peripheral clock enable Peripherals */
#define RCC_TIM1_EN  	     0+0b01000000
#define RCC_USART1_EN 	     4+0b01000000
#define RCC_USART6_EN	     5+0b01000000
#define RCC_ADC1_EN	 	     8+0b01000000	
#define RCC_SDIO_EN	 	     11+0b01000000
#define RCC_SPI1_EN	 	     12+0b01000000
#define RCC_SPI4_EN  	     13+0b01000000
#define RCC_SYSCFG_EN        14+0b01000000
#define RCC_TIM9_EN          16+0b01000000
#define RCC_TIM10_EN         17+0b01000000
#define RCC_TIM11_EN         18+0b01000000











#endif
