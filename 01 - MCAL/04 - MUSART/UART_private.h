/****************************************************************************/
/******************** Author  :  Solyma                      ****************/
/******************** ARM_UART_Private		  			 ****************/
/******************** Date    : 24/4/2022                    ****************/
/******************** Version :  01                          ****************/
/****************************************************************************/

#ifndef  USART_PRIVATE_H_
#define  USART_PRIVATE_H_

#define   USART1_BASE_ADDRESS	0x40011000
#define   USART2_BASE_ADDRESS	0x40004400
#define   USART6_BASE_ADDRESS	0x40011400 


#define   USART1_SR          *((volatile u32*)(USART1_BASE_ADDRESS + 0x00  ))
#define   USART1_DR          *((volatile u32*)(USART1_BASE_ADDRESS + 0x04  ))
#define   USART1_BRR         *((volatile u32*)(USART1_BASE_ADDRESS + 0x08  ))
#define   USART1_CR1         *((volatile u32*)(USART1_BASE_ADDRESS + 0x0C  ))
#define   USART1_CR2         *((volatile u32*)(USART1_BASE_ADDRESS + 0x10  ))
#define   USART1_CR3         *((volatile u32*)(USART1_BASE_ADDRESS + 0x14  ))
#define   USART1_GTPR        *((volatile u32*)(USART1_BASE_ADDRESS + 0x18  ))

#define   USART2_SR          *((volatile u32*)(USART2_BASE_ADDRESS + 0x00  ))
#define   USART2_DR          *((volatile u32*)(USART2_BASE_ADDRESS + 0x04  ))
#define   USART2_BRR         *((volatile u32*)(USART2_BASE_ADDRESS + 0x08  ))
#define   USART2_CR1         *((volatile u32*)(USART2_BASE_ADDRESS + 0x0C  ))
#define   USART2_CR2         *((volatile u32*)(USART2_BASE_ADDRESS + 0x10  ))
#define   USART2_CR3         *((volatile u32*)(USART2_BASE_ADDRESS + 0x14  ))
#define   USART2_GTPR        *((volatile u32*)(USART2_BASE_ADDRESS + 0x18  ))

#define   USART6_SR          *((volatile u32*)(USART6_BASE_ADDRESS + 0x00  ))
#define   USART6_DR          *((volatile u32*)(USART6_BASE_ADDRESS + 0x04  ))
#define   USART6_BRR         *((volatile u32*)(USART6_BASE_ADDRESS + 0x08  ))
#define   USART6_CR1         *((volatile u32*)(USART6_BASE_ADDRESS + 0x0C  ))
#define   USART6_CR2         *((volatile u32*)(USART6_BASE_ADDRESS + 0x10  ))
#define   USART6_CR3         *((volatile u32*)(USART6_BASE_ADDRESS + 0x14  ))
#define   USART6_GTPR        *((volatile u32*)(USART6_BASE_ADDRESS + 0x18  ))





#define USART1_BUSY       1
#define USART1_IDLE       0

#define USART1_RXBUSY     1
#define USART1_RXIDLE     0

#define USART2_RXBUSY     1
#define USART2_RXIDLE     0

#define USART_SENDING_BYTE  	0
#define USART_SENDING_BUFFER    1

#define USART_RECEIVING_BYTE  	  0
#define USART_RECEIVING_BUFFER    1


#define USART2_BUSY        1
#define USART2_IDLE        0

#define USART6_BUSY 		1
#define USART6_IDLE			0

#define USART6_RXIDLE		0
#define USART6_RXBUSY		1


#endif  
