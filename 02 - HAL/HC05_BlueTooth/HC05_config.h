/***********************************************************/
/*** Author  :  SOLYMA                      ****************/
/*** LAYER: HAL HC05_			    ****************/
/*** Date    : 25/6/2022                    ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#ifndef HC05_CONFIG_H
#define HC05_CONFIG_H



#define HC05_UART_BUS   USART_BUS_1
/*
					USART_BUS_1
					USART_BUS_2
					USART_BUS_6

*/

#define  HC05_BAUD_RATE   USART_enuBaud_Rate_9_6_KBps
/*
						USART_enuBaud_Rate_9_6_KBps ,
						USART_enuBaud_Rate_115_2_KBps ,
						USART_enuBaud_Rate_2_MBps ,

*/

#define HC05_PORT		GPIO_PORTA

/*Should be connected to RX of UART */
#define HC05_TX_PIN 	GPIO_PIN10


/*Should be connected to TX of UART */
#define HC05_RX_PIN		GPIO_PIN9 			//TX of UART1









#endif
