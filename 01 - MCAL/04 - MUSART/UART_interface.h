/****************************************************************************/
/******************** Author  :  Solyma                      ****************/
/******************** ARM_UART_Interface		  			 ****************/
/******************** Date    : 24/4/2022                    ****************/
/******************** Version :  01                          ****************/
/****************************************************************************/

/* The universal synchronous asynchronous receiver transmitter (USART)*/

#ifndef  USART_INTERFACE_H_
#define  USART_INTERFACE_H_

/* This enum for return type */
typedef enum 
{
	USART_enuOK,
	USART_enuNOK,
	USART_enuNllPointerError,
}USART_enuErrorState;

/* This enum for Baud rate definition in init function of USART */
typedef enum
{
	USART_enuBaud_Rate_9_6_KBps ,
	USART_enuBaud_Rate_115_2_KBps ,
	USART_enuBaud_Rate_2_MBps ,
	
}USART_enuBaud_Rate_t;

/* Input data type of Init Function */
typedef struct
{
	u8 USART_Bus_Number; // USART_BUS_1,  USART_BUS_2  , USART_BUS_6
	u8 USART_Data_Length; // 8 or 9
	u8 USART_Stop_Bits; // 1 or 2
	USART_enuBaud_Rate_t USART_Baud_Rate;
	
}USART_Cnfg_type;


typedef struct
{
	u8 * USART_TXBuffer ; // pointer to Buffer >> Array name
	u16 USART_TXBuffer_Size; // size of Buffer in Bytes
	void (*USART_TXBuffer_CBF)(void); // Notification function to user when end of transmission
	
}USART_strTXBuffer_type;


/* This struct to receive a buffer from user */
typedef struct
{
	u8 * USART_RXBuffer ; // pointer to Buffer >> Array name
	u16 USART_RXBuffer_Size; // size of Buffer in Bytes
	void (*USART_RXBuffer_CBF)(void); // Notification function to user when end of transmission
	
}USART_strRXBuffer_type;

/*callback function*/
typedef void(*CallBackFunc)(void);


/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : to initialize the USART                  ******************/
/*************************************** INPUTS  : (1)USART_Cnfg_type struct				******************/
/*************************************** Output  : (void)					   *******************************/

void USART_voidInit(USART_Cnfg_type * Add_strCnfg);
/*
USART_Bus_Number :
					USART_BUS_1
					USART_BUS_2
					USART_BUS_6
					
USART_Data_Length :
					USART_DATA_8_BITS
					USART_DATA_9_BITS		
USART_Stop_Bits : 
					USART_STOP_1_BITS
					USART_STOP_0_5_BITS
					USART_STOP_2_BITS
					USART_STOP_1_5_BITS
USART_Baud_Rate : 

					USART_enuBaud_Rate_9_6_KBps 
                    USART_enuBaud_Rate_115_2_KBps
                    USART_enuBaud_Rate_2_MBps 
					
*/

/*************************************************************************************************************/

/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : Send a byte of data 	                    ******************/
/*************************************** INPUTS  : (2) u8 Data, u8 Bus									******************/
/*************************************** Output  : (1) Enum to Check  *******************************/

USART_enuErrorState USART_enuSendByteSynch(u8 Copy_u8Byte , u8 Copy_u8USARTBus);

/******************************************* Function(3) *****************************************************/
/*************************************** Purpose : Send a byte of data Asynchronously       ******************/
/*************************************** INPUTS  : (3) u8 Data, u8 Bus,CBF					******************/
/*************************************** Output  : (1) Enum to Check           *******************************/

USART_enuErrorState USART_enuSendByteAsynch( u8 Copy_u8Byte ,u8 Copy_u8USARTBus , void(*Notification_func)(void));


/******************************************* Function(4-1) *****************************************************/
/*************************************** Purpose : Send a Buffer of data Synchronously      ******************/
/*************************************** INPUTS  : (3) 						  			   ******************/
/*************************************** Output  : (1) Enum to Check		  *******************************/
USART_enuErrorState USART_enuSendBufferSynch(u8 * Copy_pu8TXBuffer ,u32 Copy_u8BufferSize ,u8 Copy_u8USARTBus );


/******************************************* Function(4-2) *****************************************************/
/*************************************** Purpose : Send a String of data Synchronously      ******************/
/*************************************** INPUTS  : (2) 						  			   ******************/
/*************************************** Output  : (1) Enum to Check		  *******************************/

USART_enuErrorState USART_enuSendStringSynch(u8 * Copy_pu8TXString  ,u8 Copy_u8USARTBus );




/******************************************* Function(5) *****************************************************/
/*************************************** Purpose : Send a Buffer of data using Interrupt    ******************/
/*************************************** INPUTS  : (2) 									******************/
/*************************************** Output  : (1) Enum to Check  *******************************/


USART_enuErrorState USART_enuSendBufferAsynch(USART_strTXBuffer_type * Copy_strTXBuffer , u8 Copy_u8USARTBus);

/******************************************* Function(6) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data Synchronously	    ***************/
USART_enuErrorState USART_enuReceiveByteSynch(u8 * Copy_strRXByte, u8 Copy_u8USARTBus);

/******************************************* Function(7) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data using Interrupt    ***************/
USART_enuErrorState USART_enuReceiveByteAsynch(u8 * Copy_strRXByte, u8 Copy_u8USARTBus , void (*Copy_vidNotificationFunc)(void));


/******************************************* Function(8) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data using Interrupt    ******************/
/*************************************** INPUTS  : (2) 									******************/
/*************************************** Output  : (1) Enum to Check  *******************************/
USART_enuErrorState USART_enuReceiveBufferSynch(u8 * Copy_pu8RXBuffer ,u32 Copy_u8BufferSize ,u8 Copy_u8USARTBus , void(*Copy_voidCBF)(void));



/******************************************* Function(9) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data using Interrupt    ******************/
/*************************************** INPUTS  : (2) 									******************/
/*************************************** Output  : (1) Enum to Check  *******************************/
USART_enuErrorState USART_enuReceiveBufferAsynch(USART_strRXBuffer_type * Copy_strRXBuffer , u8 Copy_u8USARTBus);

u16 USART_ReceiveData(void);

#define USART_BUS_1   0
#define USART_BUS_2   1
#define USART_BUS_6   2
#define USART_DATA_8_BITS	0
#define USART_DATA_9_BITS 	1

#define USART_STOP_1_BITS		0
#define USART_STOP_0_5_BITS		1
#define USART_STOP_2_BITS		2
#define USART_STOP_1_5_BITS		3




#endif
