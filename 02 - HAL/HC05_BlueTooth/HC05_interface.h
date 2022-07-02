/***********************************************************/
/*** Author  :  SOLYMA                      ****************/
/*** LAYER: HAL HC05_			    ****************/
/*** Date    : 25/6/2022                    ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#ifndef HC05_INTERFACE_H
#define HC05_INTERFACE_H



typedef enum
{
	HC05_enuOK,
	HC05_enuNOK,
	HC05_enuNullPointer,
	
}HC05_enuErrorStatus;

/*
Fisrt :
		we Configure these parameters From Config File
		
		HC05_UART_BUS 
		HC05_BAUD_RATE
		HC05_PORT		
        HC05_TX_PIN 
		HC05_RX_PIN		
*/      
        
/******************************************* Function(1) ********************************************************/
/*************************************** Purpose : Initialization of pins of HC05 after configurring them 			    ******************/
/*************************************** INPUTS  : (0) 											******************/
/*************************************** Output  : (1) Enum to Check  				*******************************/
HC05_enuErrorStatus HC05_enuInit(void);
/*
	We Should configure them using Config file  
						HC05_UART_BUS   USART_BUS_1
						HC05_BAUD_RATE   USART_enuBaud_Rate_9_6_KBps
						HC05_PORT		GPIO_PORTA
						HC05_TX_PIN 	GPIO_PIN10
						HC05_RX_PIN 	GPIO_PIN9
*/


/******************************************* Function(2) ********************************************************/
/*************************************** Purpose : Send a Buffer of data using UART     ******************/
/*************************************** INPUTS  : (4) 											******************/
/*************************************** Output  : (1) Enum to Check  *******************************/
//HC05_enuErrorStatus HC05_enuSendUserDataSynch(u8 * Copy_pu8TXBuffer ,u32 Copy_u8BufferSize );
HC05_enuErrorStatus HC05_enuSendUserDataSynch(u8  Copy_u8TXData );

/*




*/
/******************************************* Function(3) ********************************************************/
/*************************************** Purpose : Send a message of data using HC05-UART     		******************/
/*************************************** INPUTS  : (4) 											******************/
/*************************************** Output  : (1) Enum to Check  *******************************/
HC05_enuErrorStatus HC05_enuSendUserMessageSynch(u8 * Copy_pu8TXMessage);







#endif
