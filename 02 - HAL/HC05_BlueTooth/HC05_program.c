/***********************************************************/
/*** Author  :  SOLYMA                      ****************/
/*** LAYER: HAL HC05_			    ****************/
/*** Date    : 25/6/2022                    ****************/
/*** Version :  01                          ****************/
/***********************************************************/
#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"RCC_interface.h"
#include"GPIO_interface.h"
#include"NVIC_interface.h"
#include"UART_interface.h"

#include"HC05_interface.h"
#include"HC05_private.h"
#include"HC05_config.h"




/******************************************* Function(1) ********************************************************/
/*************************************** Purpose : Initialization of pins of HC05 after configurring them 			    ******************/
/*************************************** INPUTS  : (0) 											******************/
/*************************************** Output  : (1) Enum to Check  				*******************************/
HC05_enuErrorStatus HC05_enuInit(void)
{
	HC05_enuErrorStatus Local_enuErrorState = HC05_enuOK;
	/* Initialization of pins (GPIO)*/
	GPIO_Pin_Cnfg  Local_strT_XPin , Local_strR_XPin;
	
	Local_strT_XPin.GPIO_MODE       = GPIO_MODE_AF_PP;
	Local_strT_XPin.GPIO_OUT_SPEED  = GPIO_SPEED_LOW;
	Local_strT_XPin.GPIO_PIN        = HC05_TX_PIN;
	Local_strT_XPin.GPIO_PORT       = HC05_PORT;

    Local_strR_XPin.GPIO_MODE       = GPIO_MODE_AF_PP;
	Local_strR_XPin.GPIO_OUT_SPEED  = GPIO_SPEED_LOW;
	Local_strR_XPin.GPIO_PIN        = HC05_RX_PIN;
	Local_strR_XPin.GPIO_PORT       = HC05_PORT;
	
	GPIO_enuSetPinMode(&Local_strR_XPin);
	GPIO_enuSetPinMode(&Local_strT_XPin);
	
	/* Initialization of Pins (AF) */
	if ((HC05_UART_BUS == USART_BUS_1 ) || (HC05_UART_BUS == USART_BUS_2 ))
	{
		GPIO_enuSetAlternativeFunctionPin(HC05_PORT,HC05_TX_PIN  , GPIO_AF7_USART1_2);
		GPIO_enuSetAlternativeFunctionPin(HC05_PORT,HC05_RX_PIN  , GPIO_AF7_USART1_2);
	}
	else if (HC05_UART_BUS == USART_BUS_6 )
	{
		GPIO_enuSetAlternativeFunctionPin(HC05_PORT,HC05_TX_PIN  , GPIO_AF8_USART6);
		GPIO_enuSetAlternativeFunctionPin(HC05_PORT,HC05_RX_PIN  , GPIO_AF8_USART6);
	}
	else
	{
		Local_enuErrorState = HC05_enuNOK;
	}
	
	/* USART Initialization */
	USART_Cnfg_type Local_strUART_T_XPin , Local_strUART_R_XPin ;
	
	Local_strUART_T_XPin.USART_Bus_Number  = HC05_UART_BUS;
	Local_strUART_T_XPin.USART_Data_Length = USART_DATA_8_BITS;
	Local_strUART_T_XPin.USART_Stop_Bits   = USART_STOP_1_BITS;
	Local_strUART_T_XPin.USART_Baud_Rate   = HC05_BAUD_RATE;

	Local_strUART_R_XPin.USART_Bus_Number  = HC05_UART_BUS;
	Local_strUART_R_XPin.USART_Data_Length = USART_DATA_8_BITS;
	Local_strUART_R_XPin.USART_Stop_Bits   = USART_STOP_1_BITS;
	Local_strUART_R_XPin.USART_Baud_Rate   = HC05_BAUD_RATE;


	USART_voidInit(&Local_strUART_R_XPin);
	USART_voidInit(&Local_strUART_T_XPin);
	
	return Local_enuErrorState;
}


/******************************************* Function(2) ********************************************************/
/*************************************** Purpose : Send a Number using HC05-UART     		******************/
/*************************************** INPUTS  : (4) 											******************/
/*************************************** Output  : (1) Enum to Check  *******************************/
HC05_enuErrorStatus HC05_enuSendUserDataSynch(u8  Copy_u8TXData )
{
	HC05_enuErrorStatus Local_enuErrorState = HC05_enuOK;
	volatile u8 Local_u8ArrNum[5] = {0};
	volatile u8 Local_u8ArrIndex = 0;
	volatile s8 Local_u8Iterator  ;
	volatile u8 Local = 0 ;
	if (Copy_u8TXData == 0 )
	{
		Local += 48;
		USART_enuSendByteSynch(Local ,HC05_UART_BUS );
	}
	else
	{
		while(Copy_u8TXData > 0)
		{
			Local_u8ArrNum[Local_u8ArrIndex] = (Copy_u8TXData%10) ;
			Local_u8ArrIndex++;

			Copy_u8TXData = (Copy_u8TXData/10);

		}
		Local_u8ArrIndex -- ;

		for (Local_u8Iterator = Local_u8ArrIndex ;  Local_u8Iterator >= 0 ; Local_u8Iterator --)
		{
			Local = (Local_u8ArrNum[Local_u8Iterator] ) + 48; // ASCII of 0 = 48
			USART_enuSendByteSynch(Local ,HC05_UART_BUS );

		}
	}

	return Local_enuErrorState;
}


/******************************************* Function(3) ********************************************************/
/*************************************** Purpose : Send a message of data using HC05-UART     		******************/
/*************************************** INPUTS  : (4) 											******************/
/*************************************** Output  : (1) Enum to Check  *******************************/
HC05_enuErrorStatus HC05_enuSendUserMessageSynch(u8 * Copy_pu8TXMessage)
{
	HC05_enuErrorStatus Local_enuErrorState = HC05_enuOK;
	
	if (Copy_pu8TXMessage != NULL )
	{
		USART_enuSendStringSynch(Copy_pu8TXMessage  , HC05_UART_BUS );
	}
	else
	{
		Local_enuErrorState = HC05_enuNullPointer;
	}

	return Local_enuErrorState;
}
