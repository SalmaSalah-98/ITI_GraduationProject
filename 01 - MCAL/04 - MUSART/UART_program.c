/****************************************************************************/
/******************** Author  :  Solyma                      ****************/
/******************** ARM_UART_Program		  				 ****************/
/******************** Date    : 24/4/2022                    ****************/
/******************** Version :  01                          ****************/
/****************************************************************************/


#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"UART_interface.h"
#include"UART_config.h"
#include"UART_private.h"


static u8 USART_Send_SOURCE_Flag = USART_SENDING_BYTE ;
static u8 USART_Receive_SOURCE_Flag = USART_RECEIVING_BYTE ;



/* Global variables for function (4)*/
static u8 * StGlobal_pu8TXBuffer = NULL; // to hold the add of buffer to be sent
static u8  StGlobal_u8TXBufferSize;
static u8  StGlobal_u8TXBufferIdx;
static void(*stGlobal_TX1BufferCallBack)(void);

/* Global variables for function (5)*/
static u8 * StGlobal_pu8RXBuffer = NULL; // to hold the add of buffer to be sent
static u8  StGlobal_u8RXBufferSize;
static u8  StGlobal_u8RXBufferIdx;
static void(*stGlobal_RX1BufferCallBack)(void);

/* For USART1 */
static u8  stGlobal_u8Busy = USART1_IDLE;
static u8  stGlobal_u8RXBusy = USART1_RXIDLE;

/* For USART2 */
static u8 stGlobal_u8Busy2 = USART2_IDLE;
static u8 stGlobal_u8RXBusy2 = USART2_RXIDLE;

/* For USART6 */
static u8 stGlobal_u8Busy6 = USART6_IDLE;
static u8 stGlobal_u8RXBusy6 = USART6_RXIDLE;

/* pointers to hold received data from receive byte function */
static u8 *stpGlobla_ReceivedByte1 = NULL;
static u16 *stpGlobla_ReceivedByte2 = NULL; 
static u16 *stpGlobla_ReceivedByte6 = NULL;


/* Define Callback Global Variable */
static CallBackFunc CBFTX_BYTE[3];



/*Call Back Function for Receiving Byte */
static CallBackFunc CBFRX_BYTE[3];

/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : to initialize the USART                  ******************/
void USART_voidInit(USART_Cnfg_type * Add_strCnfg)
{
	//u32 Local_u32BaudRateMantissa ;
	
	u8 Local_u8UART_Bus = (Add_strCnfg -> USART_Bus_Number); /* To get the Bus Number */
	switch (Local_u8UART_Bus)
	{
		case USART_BUS_1:
						/* (0) Disable the USART by writing the UE bit in USART_CR1 register to 0 */
						CLR_BIT(USART1_CR1 , 13);
						
						/* (1) Definning the Frame length of USART */
						/* (1-1) Program the M bit in USART_CR1 to define the word length*/
						if ((Add_strCnfg -> USART_Data_Length) == 9)
						{
							SET_BIT(USART1_CR1 , 12); //Bit 12 M: Word length , 1 :  1 Start bit, 9 Data bits, n Stop bit
						}
						else
						{
							CLR_BIT(USART1_CR1 , 12); //Bit 12 M: Word length , 0 :  1 Start bit, 8 Data bits, n Stop bit
						}
						
						/* (1-2) Program the number of stop bits in USART_CR2 */
						USART1_CR2  &=~ (0b11 << 12 ); // [Bits 13:12] STOP: STOP bits
						USART1_CR2  |=  ((Add_strCnfg -> USART_Stop_Bits) << 12 );
						
						/* (2) Select the desired baud rate using the USART_BRR register */
						/* (2-1) Oversampling mode  : 8 */

						SET_BIT(USART1_CR1 , 15); //Bit 15 OVER8: Oversampling mode 
						/* (2-2) Set The valuse of Passed Baud Rate */
						USART1_BRR &=~ (0b1111111111111111 ); //Bit Masking for first 15 bits 
						switch ((Add_strCnfg -> USART_Baud_Rate))
						{
							case USART_enuBaud_Rate_9_6_KBps :
							USART1_BRR |=(u16) ( (208 << 4) |(3));
							//USART1_BRR |= 0x1183;
							break;
							
							case USART_enuBaud_Rate_115_2_KBps:
							USART1_BRR |= ( 17 << 4 );
							break;
							
							case USART_enuBaud_Rate_2_MBps :
							USART1_BRR |= ( 1 << 4 );
							break;
							default : /* Error Baud Rate */break;
							
						}
						
						/* (4) Enable the USART by writing the UE bit in USART_CR1 register to 1 */
						SET_BIT(USART1_CR1 , 13);
						
						/* (5) Enable The Transmission and Receive */
						SET_BIT(USART1_CR1 , 3); //Bit 3 TE: Transmitter enable
						SET_BIT(USART1_CR1 , 2); //Bit 2 RE: Receiver enable
						
						/* Clearing Status Register */
						USART1_SR = 0;

		break;
		case USART_BUS_2:
			/* (0) Disable the USART by writing the UE bit in USART_CR1 register to 0 */
						CLR_BIT(USART2_CR1 , 13);
						
						/* (1) Definning the Frame length of USART */
						/* (1-1) Program the M bit in USART_CR1 to define the word length*/
						if ((Add_strCnfg -> USART_Data_Length) == 9)
						{
							SET_BIT(USART2_CR1 , 12); //Bit 12 M: Word length , 1 :  1 Start bit, 9 Data bits, n Stop bit
						}
						else
						{
							CLR_BIT(USART2_CR1 , 12); //Bit 12 M: Word length , 0 :  1 Start bit, 8 Data bits, n Stop bit
						}
						
						/* (1-2) Program the number of stop bits in USART_CR2 */
						USART2_CR2  &=~ (0b11 << 12 ); // [Bits 13:12] STOP: STOP bits
						USART2_CR2  |=  ((Add_strCnfg -> USART_Stop_Bits) << 12 );
						
						/* (2) Select the desired baud rate using the USART_BRR register */
						/* (2-1) Oversampling mode  : 8 */
						SET_BIT(USART2_CR1 , 15); //Bit 15 OVER8: Oversampling mode 
						/* (2-2) Set The valuse of Passed Baud Rate */
						USART2_BRR &=~ (0b111111111111 << 4 );
						switch ((Add_strCnfg -> USART_Baud_Rate))
						{
							case USART_enuBaud_Rate_9_6_KBps :
								USART2_BRR |=(u16) ( (208 << 4) |(3));
							//	USART1_BRR |= 103<<4;

								break;
							
							case USART_enuBaud_Rate_115_2_KBps:
							USART2_BRR |= ( 17 << 4 );
							break;
							
							case USART_enuBaud_Rate_2_MBps :
							USART2_BRR |= ( 1 << 4 );
							break;
							default : /* Error Baud Rate */break;
							
						}
							/* (4) Enable the USART by writing the UE bit in USART_CR1 register to 1 */
						SET_BIT(USART2_CR1 , 13);
						
						/* (5) Enable The Transmission and Receive */
						SET_BIT(USART2_CR1 , 3); //Bit 3 TE: Transmitter enable
						SET_BIT(USART2_CR1 , 2); //Bit 2 RE: Receiver enable
						/* Clearing Status Register */
						USART2_SR = 0;
						
		break;
		case USART_BUS_6:
						/* (0) Disable the USART by writing the UE bit in USART_CR1 register to 0 */
						CLR_BIT(USART6_CR1 , 13);
						
						/* (1) Definning the Frame length of USART */
						/* (1-1) Program the M bit in USART_CR1 to define the word length*/
						if ((Add_strCnfg -> USART_Data_Length) == 9)
						{
							SET_BIT(USART6_CR1 , 12); //Bit 12 M: Word length , 1 :  1 Start bit, 9 Data bits, n Stop bit
						}
						else
						{
							CLR_BIT(USART6_CR1 , 12); //Bit 12 M: Word length , 0 :  1 Start bit, 8 Data bits, n Stop bit
						}
						
						/* (1-2) Program the number of stop bits in USART_CR2 */
						USART6_CR2  &=~ (0b11 << 12 ); // [Bits 13:12] STOP: STOP bits
						USART6_CR2  |=  ((Add_strCnfg -> USART_Stop_Bits) << 12 );
						
						/* (2) Select the desired baud rate using the USART_BRR register */
						/* (2-1) Oversampling mode  : 8 */
						SET_BIT(USART6_CR1 , 15); //Bit 15 OVER8: Oversampling mode 
						/* (2-2) Set The valuse of Passed Baud Rate */
						USART6_BRR &=~ (0b111111111111 << 4 );
						switch ((Add_strCnfg -> USART_Baud_Rate))
						{
							case USART_enuBaud_Rate_9_6_KBps :
							USART6_BRR |=(u16) ( (208 << 4) |(3));
							break;
							
							case USART_enuBaud_Rate_115_2_KBps:
							USART6_BRR |= ( 17 << 4 );
							break;
							
							case USART_enuBaud_Rate_2_MBps :
							USART6_BRR |= ( 1 << 4 );
							break;
							default : /* Error Baud Rate */break;
							
						}
						/* (4) Enable the USART by writing the UE bit in USART_CR1 register to 1 */
						SET_BIT(USART6_CR1 , 13);
						
						/* (5) Enable The Transmission and Receive */
						SET_BIT(USART6_CR1 , 3); //Bit 3 TE: Transmitter enable
						SET_BIT(USART6_CR1 , 2); //Bit 2 RE: Receiver enable
						/* Clearing Status Register */
						USART6_SR = 0;
		break;
	
	}
}

/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : Send a byte of data 	                    ******************/
USART_enuErrorState USART_enuSendByteSynch(u8 Copy_u8Byte , u8 Copy_u8USARTBus)
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;
	u8 Local_u8TC_Flag[3] ;
	u16 Local_u16TimeOut = 2500 ;
	if (Copy_u8USARTBus < 3)
	{
			switch(Copy_u8USARTBus)
			{
				/* Transferring data into register DR by writing on it */
				case USART_BUS_1:

					if (stGlobal_u8Busy == USART1_IDLE)
					{
						stGlobal_u8Busy = USART1_BUSY;

						//USART_Send_SOURCE_Flag = USART_SENDING_BYTE;
						USART1_DR =  Copy_u8Byte;
						Local_u8TC_Flag[USART_BUS_1] = GET_BIT(USART1_SR , 6);
						while(((Local_u8TC_Flag[USART_BUS_1]) == 0) && (Local_u16TimeOut))
						{
							Local_u16TimeOut -- ;
							Local_u8TC_Flag[USART_BUS_1] = GET_BIT(USART1_SR , 6);

						}
						Local_u8TC_Flag[USART_BUS_1] = GET_BIT(USART1_SR , 6);
						if ((Local_u8TC_Flag[USART_BUS_1]) == 0)
						{
							Local_enuErrorState = USART_enuNOK;
						}
						CLR_BIT(USART1_SR , 6); //Clear the Flag
						stGlobal_u8Busy = USART1_IDLE;
					}
				break;
				
				case USART_BUS_2:
					if (stGlobal_u8Busy2 == USART2_IDLE)
						{
						stGlobal_u8Busy2 = USART2_BUSY;

						USART2_DR =  Copy_u8Byte;
						Local_u8TC_Flag[USART_BUS_2] = GET_BIT(USART2_SR , 6);
						while(((Local_u8TC_Flag[USART_BUS_2]) == 0) && (Local_u16TimeOut))
						{
							Local_u16TimeOut -- ;
							Local_u8TC_Flag[USART_BUS_2] = GET_BIT(USART2_SR , 6);

						}
						Local_u8TC_Flag[USART_BUS_2] = GET_BIT(USART2_SR , 6);
						if ((Local_u8TC_Flag[USART_BUS_2]) == 0)
						{
							Local_enuErrorState = USART_enuNOK;
						}

						CLR_BIT(USART2_SR , 6);
						stGlobal_u8Busy2 = USART2_IDLE;
						}

					break;
				
				case USART_BUS_6:

				if (stGlobal_u8Busy6 == USART6_IDLE)
				{
				stGlobal_u8Busy6 = USART6_BUSY;

				USART6_DR =  Copy_u8Byte;
				Local_u8TC_Flag[USART_BUS_6] = GET_BIT(USART6_SR , 6);
				while(((Local_u8TC_Flag[USART_BUS_6]) == 0) && (Local_u16TimeOut))
				{
					Local_u16TimeOut -- ;
					Local_u8TC_Flag[USART_BUS_6] = GET_BIT(USART6_SR , 6);

				}
				Local_u8TC_Flag[USART_BUS_6] = GET_BIT(USART6_SR , 6);
				if ((Local_u8TC_Flag[USART_BUS_6]) == 0)
				{
					Local_enuErrorState = USART_enuNOK;
				}

				CLR_BIT(USART6_SR , 6);
				stGlobal_u8Busy6 = USART6_IDLE;
				}

				break;

			
		}
	}
	else
	{
		Local_enuErrorState  = USART_enuNOK;
	}
	return Local_enuErrorState;
}

/******************************************* Function(3) *****************************************************/
/*************************************** Purpose : Check if Transmission is Completed 		******************/
USART_enuErrorState USART_enuSendByteAsynch( u8 Copy_u8Byte ,u8 Copy_u8USARTBus , void(*Notification_func)(void))
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;

	if (Copy_u8USARTBus < 3)
	{
		if(Notification_func != NULL )
		{
			switch(Copy_u8USARTBus)
			{
				case USART_BUS_1:
				if (stGlobal_u8Busy == USART1_IDLE)
				{
					stGlobal_u8Busy = USART1_BUSY;
					USART_Send_SOURCE_Flag = USART_SENDING_BYTE; // to indicate the ISR is executed because of (Sending byte not a buffer)this function
					/* (3) Enable the Interrupt TCIE */
					SET_BIT(USART1_CR1 , 6); //Bit 6 TCIE: Transmission complete interrupt enable
					CBFTX_BYTE[USART_BUS_1] = Notification_func	;
					USART1_DR = Copy_u8Byte;
				}
				else
				{
					Local_enuErrorState = USART_enuNOK;
				}

				break;
				case USART_BUS_2:
				if (stGlobal_u8Busy == USART2_IDLE)
				{
					stGlobal_u8Busy = USART2_BUSY;
					USART_Send_SOURCE_Flag = USART_SENDING_BYTE; // to indicate the ISR is executed because of this function
					/* (3) Enable the Interrupt TCIE */
					SET_BIT(USART2_CR1 , 6); //Bit 6 TCIE: Transmission complete interrupt enable
					CBFTX_BYTE[USART_BUS_2] = Notification_func	;
					USART2_DR = Copy_u8Byte;
				}
				else
				{
					Local_enuErrorState = USART_enuNOK;
				}

				break;
				case USART_BUS_6:
				if (stGlobal_u8Busy == USART6_IDLE)
				{
					stGlobal_u8Busy = USART6_BUSY;
					USART_Send_SOURCE_Flag = USART_SENDING_BYTE; // to indicate the ISR is executed becouse of this function
					/* (3) Enable the Interrupt TCIE */
					SET_BIT(USART6_CR1 , 6); //Bit 6 TCIE: Transmission complete interrupt enable
					CBFTX_BYTE[USART_BUS_6] = Notification_func	;
					USART6_DR = Copy_u8Byte;
				}
				else
				{
					Local_enuErrorState = USART_enuNOK;
				}

				break;
			}

		}
	}
	else
	{
		Local_enuErrorState = USART_enuNOK;
	}
	return Local_enuErrorState;
}

/******************************************* Function(4) *****************************************************/
/*************************************** Purpose : Send a Buffer of data Synchronously      ******************/
/*************************************** INPUTS  : (2) 						  			   ******************/
/*************************************** Output  : (1) Enum to Check		  *******************************/

USART_enuErrorState USART_enuSendBufferSynch(u8 * Copy_pu8TXBuffer ,u32 Copy_u8BufferSize ,u8 Copy_u8USARTBus )
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;

	static u32 Loca_u8Indx = 0;
	u16 Local_u16TimeOut = 1500;
	static u8 Local_u8TC_Flag [3];

	/*(0) Validate inputs */
	if ((Copy_u8USARTBus < 3) && (Copy_pu8TXBuffer != NULL ))
	{

		switch(Copy_u8USARTBus)
		{
			case USART_BUS_1:
				if ( stGlobal_u8Busy == USART1_IDLE)
				{
					stGlobal_u8Busy = USART1_BUSY;

					while(Loca_u8Indx != Copy_u8BufferSize)
					{
						USART1_DR =  Copy_pu8TXBuffer[Loca_u8Indx];

						Local_u8TC_Flag[USART_BUS_1] = GET_BIT(USART1_SR , 6) ;
						while((Local_u8TC_Flag[USART_BUS_1] == 0)  &&  Local_u16TimeOut)
						{
								Local_u16TimeOut --;
								Local_u8TC_Flag[USART_BUS_1] = GET_BIT(USART1_SR , 6) ;
						}
						Local_u16TimeOut = 1500;
						if (Local_u8TC_Flag[USART_BUS_1])
						{
							Loca_u8Indx ++;
						}
						else
						{
							Local_enuErrorState = USART_enuNOK;
						}

					}
					stGlobal_u8Busy = USART1_IDLE;
					CLR_BIT(USART1_SR , 6);
					Loca_u8Indx = 0 ;


				}
				else
				{
					Local_enuErrorState =USART_enuNOK;
				}

			break;
			case USART_BUS_2:
				if ( stGlobal_u8Busy == USART2_IDLE)
					{
								stGlobal_u8Busy = USART2_BUSY;

									if (Loca_u8Indx == Copy_u8BufferSize)
									{
										stGlobal_u8Busy = USART2_IDLE;
										CLR_BIT(USART2_SR , 6);
								//		Copy_voidCBF();
										Loca_u8Indx = 0 ;
									}
									else
									{
										Local_u8TC_Flag[USART_BUS_2] = GET_BIT(USART2_SR , 6) ;
										USART2_DR =  Copy_pu8TXBuffer[Loca_u8Indx];
										while(((Local_u8TC_Flag[USART_BUS_2]) == 0)  &&  Local_u16TimeOut)
										{
											Local_u16TimeOut --;
											Local_u8TC_Flag[USART_BUS_2] = GET_BIT(USART2_SR , 6) ;
										}
										if (Local_u8TC_Flag[USART_BUS_2])
										{
											Loca_u8Indx ++;
										}
										else
										{
											Local_enuErrorState = USART_enuNOK;
										}
										CLR_BIT(USART2_SR , 6);
										stGlobal_u8Busy = USART2_IDLE;
									}

								}
								else
									{
									Local_enuErrorState =USART_enuNOK;
									}

				break;

			case USART_BUS_6:
				if ( stGlobal_u8Busy == USART6_IDLE)
									{
												stGlobal_u8Busy = USART6_BUSY;

													if (Loca_u8Indx == Copy_u8BufferSize)
													{
														stGlobal_u8Busy = USART6_IDLE;
														CLR_BIT(USART6_SR , 6);
												//		Copy_voidCBF();
														Loca_u8Indx = 0 ;
													}
													else
													{
														Local_u8TC_Flag[USART_BUS_6] = GET_BIT(USART6_SR , 6) ;
														USART6_DR =  Copy_pu8TXBuffer[Loca_u8Indx];
														while(((Local_u8TC_Flag[USART_BUS_6]) == 0)  &&  Local_u16TimeOut)
														{
															Local_u16TimeOut --;
															Local_u8TC_Flag[USART_BUS_6] = GET_BIT(USART6_SR , 6) ;
														}
														if (Local_u8TC_Flag[USART_BUS_6])
														{
															Loca_u8Indx ++;
														}
														else
														{
															Local_enuErrorState = USART_enuNOK;
														}
														CLR_BIT(USART6_SR , 6);
														stGlobal_u8Busy = USART6_IDLE;
													}

												}
												else
													{
													Local_enuErrorState =USART_enuNOK;
													}
			break;
			default: break;

		}
	}
	else
	{
		Local_enuErrorState = USART_enuNOK;
	}
	return Local_enuErrorState;
}

/******************************************* Function(4-2) *****************************************************/
/*************************************** Purpose : Send a String of data Synchronously      ******************/
/*************************************** INPUTS  : (2) 						  			   ******************/
/*************************************** Output  : (1) Enum to Check		  *******************************/

USART_enuErrorState USART_enuSendStringSynch(u8 * Copy_pu8TXString  ,u8 Copy_u8USARTBus )
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;
	static u16 Local_u16Counter = 0 ;

	while((Copy_pu8TXString[Local_u16Counter]) != ('\0'))
	{
		USART_enuSendByteSynch((Copy_pu8TXString[Local_u16Counter]) , Copy_u8USARTBus);

		Local_u16Counter ++ ;
	}

	return Local_enuErrorState;
}

/******************************************* Function(5) *****************************************************/
/*************************************** Purpose : Send a Buffer of data using Interrupt    ******************/
/*************************************** INPUTS  : (2) 									******************/
/*************************************** Output  : (1) Enum to Check  *******************************/

USART_enuErrorState USART_enuSendBufferAsynch(USART_strTXBuffer_type * Copy_strTXBuffer , u8 Copy_u8USARTBus)
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;

	/*(0) Validate inputs */
	if (Copy_u8USARTBus < 3)
	{

		switch(Copy_u8USARTBus)				
		{
			case USART_BUS_1:
			/* Check if Transmit data register empty */
			if ( GET_BIT(USART1_SR , 7) == 1 )
			{
				if (stGlobal_u8Busy == USART1_IDLE)
				{
					stGlobal_u8Busy = USART1_BUSY;
					/* Initialize the Global Variables with passed of struct */
					StGlobal_pu8TXBuffer       = (Copy_strTXBuffer -> USART_TXBuffer);
					StGlobal_u8TXBufferSize    = (Copy_strTXBuffer -> USART_TXBuffer_Size) ;
					stGlobal_TX1BufferCallBack = (Copy_strTXBuffer -> USART_TXBuffer_CBF);
					StGlobal_u8TXBufferIdx = 0;
					
					/* (2) Enable the Interrupt TCIE */
					SET_BIT(USART1_CR1 , 6); //Bit 6 TCIE: Transmission complete interrupt enable
					
					/* (3) Sending the first byte in the buffer */
					
					USART1_DR = StGlobal_pu8TXBuffer[StGlobal_u8TXBufferIdx]; //(Copy_strTXBuffer -> (USART_TXBuffer[StGlobal_u8TXBufferIdx]));
					StGlobal_u8TXBufferIdx ++;
				}
				else
				{
					Local_enuErrorState =USART_enuNOK;
				}
			}
			else
			{
				Local_enuErrorState =USART_enuNOK;
			}
			break;
		
			case USART_BUS_2:
			break;
			case USART_BUS_6:
			break;
		
		}
	}
	else
	{
		Local_enuErrorState = USART_enuNOK;
	}
	return Local_enuErrorState;
}

/******************************************* Function(6) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data using Interrupt    ***************/
USART_enuErrorState USART_enuReceiveByteSynch(u8 * Copy_strRXByte, u8 Copy_u8USARTBus)
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;

	/*(0) Validate inputs */
	if (Copy_u8USARTBus < 3)
	{
		if (Copy_strRXByte != NULL)
		{
			switch (Copy_u8USARTBus)
			{
			case USART_BUS_1:

				if (stGlobal_u8RXBusy == USART1_RXIDLE)
					{
						stGlobal_u8RXBusy = USART1_RXBUSY;
						if((GET_BIT(USART1_SR , 5)) == 1)
						{
							(*Copy_strRXByte ) = USART1_DR;
						}
						else
						{
							Local_enuErrorState = USART_enuNOK;
						}
						stGlobal_u8RXBusy = USART1_RXIDLE;

					}
				else
					{
						Local_enuErrorState = USART_enuNOK;
					}


			break;

			case USART_BUS_2:
				if (stGlobal_u8RXBusy2 == USART2_RXIDLE)
					{
						stGlobal_u8RXBusy2 = USART2_RXBUSY;
						if((GET_BIT(USART2_SR , 5)) == 1)
						{
							(* Copy_strRXByte) = USART2_DR;
						}
						else
						{
							Local_enuErrorState = USART_enuNOK;
						}
						stGlobal_u8RXBusy2 = USART2_RXIDLE;
					}
				else
					{
						Local_enuErrorState = USART_enuNOK;
					}


			break;

			case USART_BUS_6:
				if (stGlobal_u8RXBusy6 == USART6_RXIDLE)
					{
						stGlobal_u8RXBusy6 = USART6_RXBUSY;

						if(GET_BIT(USART6_SR , 5) == 1) 
						{
							(*Copy_strRXByte) = USART6_DR;
						}
						else
						{
							Local_enuErrorState = USART_enuNOK;

						}
						stGlobal_u8RXBusy6 = USART6_RXIDLE;
					}
				else
					{
						Local_enuErrorState = USART_enuNOK;
					}

				break;

			}

		}
		else
		{
			Local_enuErrorState = USART_enuNOK;
		}

	}
	else
	{
		Local_enuErrorState = USART_enuNOK;
	}
	return Local_enuErrorState;
}

/******************************************* Function(6) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data using Interrupt    ***************/
USART_enuErrorState USART_enuReceiveByteAsynch(u8 * Copy_strRXByte, u8 Copy_u8USARTBus , void (*Copy_vidNotificationFunc)(void))
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;

	/*(0) Validate inputs */
	if (Copy_u8USARTBus < 3)
	{
		if (Copy_strRXByte != NULL)
		{
			switch (Copy_u8USARTBus)
			{
			case USART_BUS_1:
				if (stGlobal_u8RXBusy == USART1_RXIDLE)
					{
						stGlobal_u8RXBusy = USART1_RXBUSY;
						USART_Receive_SOURCE_Flag = USART_RECEIVING_BYTE;

						/*Assign value of passed pointer to global pointers(Result & CBF) */
						stpGlobla_ReceivedByte1 = Copy_strRXByte;
						CBFRX_BYTE[USART_BUS_1] = Copy_vidNotificationFunc ;

						/*Enable Interrupt */
						SET_BIT(USART1_CR1 , 5);
					}
				else
					{
						Local_enuErrorState = USART_enuNOK;
					}


			break;
			case USART_BUS_2:
				if (stGlobal_u8RXBusy2 == USART2_RXIDLE)
					{
						stGlobal_u8RXBusy2 = USART2_RXBUSY;
						USART_Receive_SOURCE_Flag = USART_RECEIVING_BYTE;

						/*Assign value of passed pointer to global pointer */
						stpGlobla_ReceivedByte2 = Copy_strRXByte;
						CBFRX_BYTE[USART_BUS_2] = Copy_vidNotificationFunc ;

						/*Enable Interrupt */
						SET_BIT(USART2_CR1 , 5);

					}
				else
					{
						Local_enuErrorState = USART_enuNOK;
					}


			break;
			case USART_BUS_6:
				if (stGlobal_u8RXBusy6 == USART6_RXIDLE)
					{
						stGlobal_u8RXBusy6 = USART6_RXBUSY;
						USART_Receive_SOURCE_Flag = USART_RECEIVING_BYTE;

						/*Assign value of passed pointer to global pointer */
						stpGlobla_ReceivedByte6 = Copy_strRXByte;
						CBFRX_BYTE[USART_BUS_6] = Copy_vidNotificationFunc ;

						/*Enable Interrupt */
						SET_BIT(USART6_CR1 , 5);

					}
				else
					{
						Local_enuErrorState = USART_enuNOK;
					}

				break;

			}

		}
		else
		{
			Local_enuErrorState = USART_enuNOK;
		}

	}
	else
	{
		Local_enuErrorState = USART_enuNOK;
	}
	return Local_enuErrorState;
}






/******************************************* Function(7) *****************************************************/
/*************************************** Purpose : Receive a Buffer of data using Interrupt    ***************/
USART_enuErrorState USART_enuReceiveBufferAsynch(USART_strRXBuffer_type * Copy_strRXBuffer , u8 Copy_u8USARTBus)
{
	USART_enuErrorState Local_enuErrorState = USART_enuOK;

	/*(0) Validate inputs */
	if (Copy_u8USARTBus < 3)
	{

		switch(Copy_u8USARTBus)				
		{
			case USART_BUS_1:
				if ( stGlobal_u8RXBusy == USART1_RXIDLE)
				{
					
					/* Initialize the Global Variables with passed of struct */
					StGlobal_pu8RXBuffer       = (Copy_strRXBuffer -> USART_RXBuffer);
					StGlobal_u8RXBufferSize    = (Copy_strRXBuffer -> USART_RXBuffer_Size) ;
					stGlobal_RX1BufferCallBack = (Copy_strRXBuffer -> USART_RXBuffer_CBF);
					StGlobal_u8RXBufferIdx = 0;
					stGlobal_u8RXBusy = USART1_RXBUSY;
					
					USART_Receive_SOURCE_Flag = USART_RECEIVING_BUFFER;
					/* (2)  RXNE interrupt enable */
					SET_BIT(USART1_CR1 , 5); //Bit 5 RXNEIE:

					
				}
				else
				{
					Local_enuErrorState =USART_enuNOK;
				}

			break;
		
			case USART_BUS_2:
			break;
			case USART_BUS_6:
			break;
		
		}
	}
	else
	{
		Local_enuErrorState = USART_enuNOK;
	}
	return Local_enuErrorState;
}

void USART1_IRQHandler(void)
{
	
	if ((GET_BIT(USART1_SR , 6)) == 1)//TC == 1
	{
		if(USART_Send_SOURCE_Flag == USART_SENDING_BYTE)
		{
			stGlobal_u8Busy = USART1_IDLE;
			/* Calling Call Back Function */
			CBFTX_BYTE[USART_BUS_1]();
			CLR_BIT(USART1_CR1 , 6); //Bit 6 TCIE: Transmission complete interrupt enable
		}
		else
		{
			/* Hence there is a byte transmitted through Data Register */
			if (StGlobal_u8TXBufferIdx == (StGlobal_u8TXBufferSize))
			{
				stGlobal_u8Busy = USART1_IDLE;
				/* Calling Call Back Function */
				stGlobal_TX1BufferCallBack();
			}
			else
			{
				USART1_DR = StGlobal_pu8TXBuffer[StGlobal_u8TXBufferIdx];
				StGlobal_u8TXBufferIdx ++;
			}
		}
		/* Clear the flag */
		CLR_BIT(USART1_SR , 6);
	}
	if ((GET_BIT(USART1_SR , 5)) == 1)// RXNE == 1
	{
		/* Check if this interrupt for byte or buffer */
		
		if(USART_Receive_SOURCE_Flag == USART_RECEIVING_BYTE)
		{
			/*Read Received Data*/
			(*stpGlobla_ReceivedByte1) = (u8)USART1_DR;
		
			/* Make Register IDLE */
			stGlobal_u8RXBusy = USART1_RXIDLE;

			/* Call Back function */
			if ((CBFRX_BYTE[USART_BUS_1]) != NULL )
			CBFRX_BYTE[USART_BUS_1]();
		}
		else
		{
			/* Hence there is a byte Received through Data Register */
			StGlobal_pu8RXBuffer[StGlobal_u8RXBufferIdx] = USART1_DR ;

			StGlobal_u8RXBufferIdx ++;

			if (StGlobal_u8RXBufferIdx == (StGlobal_u8RXBufferSize))
			{
				stGlobal_u8RXBusy = USART1_RXIDLE;

				/* Calling Call Back Function */
				stGlobal_RX1BufferCallBack();

			}
		}
		/*Disable Interrupt */
		CLR_BIT(USART1_CR1 , 5);
		/* Clear the flag */
		CLR_BIT(USART1_SR , 5);
	}
	
}


void USART2_IRQHandler(void)
{
	if ((GET_BIT(USART2_SR , 5)) == 1)//RXE
	{	
		/* Check if this interrupt for byte or buffer */

		if(USART_Receive_SOURCE_Flag == USART_RECEIVING_BYTE) 
		{
			/*Read Received Data*/
			(*stpGlobla_ReceivedByte2) = (u16)USART2_DR;
	
			/* Make Register IDLE */
			stGlobal_u8RXBusy = USART2_RXIDLE;

			/* Call Back function */
			if ((CBFRX_BYTE[USART_BUS_2]) != NULL )
			CBFRX_BYTE[USART_BUS_2]();

		}
		else
		{
			/* Hence Receiving caused by Buffer */


		}
		/* Clear the flag */
		CLR_BIT(USART2_SR , 5);
	}
	

}

