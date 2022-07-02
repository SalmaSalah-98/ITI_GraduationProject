/***********************************************************/
/***********************************************************/
/***********************************************************/
/**************** Author  :  Solyma         ****************/
/**************** Target  : ARM_CRTEX_M4	****************/
/**************** GPIO_Interface   			****************/
/**************** Date    : 23/3/2022       ****************/
/**************** Version :  01             ****************/
/**************** Company : ITI 			****************/
/***********************************************************/
/***********************************************************/



#ifndef GPIO_INTERFACE_H_
#define GPIO_INTERFACE_H_

typedef enum
{
	GPIO_enuOK,
	
	GPIO_enuPortError,
	GPIO_enuPinError,
	GPIO_enuModeError,
	GPIO_enuValueError,
	GPIO_enuNullPointer,
	
	
}GPIO_enuErrorState;

typedef struct 
{
	u8 GPIO_PORT ;
	u8 GPIO_PIN ;
	u8 GPIO_MODE ;
	u8 GPIO_OUT_SPEED ;
	
}GPIO_Pin_Cnfg;





/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : Setting the Pins Mode            	 *********************/
/*************************************** INPUTS  : (3)  Port ,pin ,mode				 	 *********************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
/*************************************** */

//GPIO_enuErrorState GPIO_enuSetPinMode(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_Mode );
GPIO_enuErrorState GPIO_enuSetPinMode(GPIO_Pin_Cnfg * Add_pstrGPIO_cnfg) ;

/*
* Add_pstrGPIO_cnfg -> GPIO_PORT :

*							GPIO_PORTA
*               			GPIO_PORTB
*               			GPIO_PORTC
*							GPIO_PORTD
*               			GPIO_PORTE
*               			GPIO_PORTH

Add_pstrGPIO_cnfg -> GPIO_PIN :
							GPIO_PIN0
							GPIO_PIN1
								.
								.
							GPIO_PIN15
Add_pstrGPIO_cnfg -> GPIO_MODE :
							GPIO_MODE_GP_OUT_PP   
                            GPIO_MODE_GP_OUT_PP+PU
                            GPIO_MODE_GP_OUT_PP+PD
                            GPIO_MODE_GP_OUT_OD   
                            GPIO_MODE_GP_OUT_OD+PU
                            GPIO_MODE_GP_OUT_OD+PD
									.
                            GPIO_MODE_AF_PP    		
                            GPIO_MODE_AF_PP+PU    
                            GPIO_MODE_AF_PP+PD    
                            GPIO_MODE_AF_OD       
                            GPIO_MODE_AF_OD+PU    
					        GPIO_MODE_AF_OD+PD    
*/                        
/* ---------------------------------------------------------------------------------------- ------------- */


/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : Setting the Ouput Pin Value(High /Low)*********************/
/*************************************** INPUTS  : (3)  Port ,pin ,value				 	 *********************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
/*************************************** */

GPIO_enuErrorState GPIO_enuSetPinValue(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_Value );
/*
* Copy_u8GPIO_Port :
*							GPIO_PORTA
*               			GPIO_PORTB
*               			GPIO_PORTC
*							GPIO_PORTD
*               			GPIO_PORTE
*               			GPIO_PORTH

Copy_u8GPIO_Pin :
							GPIO_PIN0
							GPIO_PIN1
								.
								.
							GPIO_PIN15
Copy_u8GPIO_Value:
							GPIO_HIGH
							GPIO_LOW
*/
/* ---------------------------------------------------------------------------------------- ------------- */


/******************************************* Function(3) *****************************************************/
/*************************************** Purpose : Write on the Ouput Pin Value(High /Low)*********************/
/*************************************** INPUTS  : (3)  Port ,pin ,value			   	 *********************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
/*************************************** */

GPIO_enuErrorState GPIO_enuWritePin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_Value );
/*
* Copy_u8GPIO_Port :
*							GPIO_PORTA
*               			GPIO_PORTB
*               			GPIO_PORTC
*							GPIO_PORTD
*               			GPIO_PORTE
*               			GPIO_PORTH

Copy_u8GPIO_Pin :
							GPIO_PIN0
							GPIO_PIN1
								.
								.
							GPIO_PIN15
Copy_u8GPIO_Value:
							GPIO_HIGH
							GPIO_LOW

*/
/* ---------------------------------------------------------------------------------------- ------------- */


/******************************************* Function(4) *****************************************************/
/*************************************** Purpose : Read the input value (HIGH/ LOW)      *********************/
/*************************************** INPUTS  : (3)  Port ,pin ,pointer to value	     *********************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
GPIO_enuErrorState GPIO_enuReadPin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 * Copy_u8GPIO_Value );

/*
* Copy_u8GPIO_Port :
*							GPIO_PORTA
*               			GPIO_PORTB
*               			GPIO_PORTC
*							GPIO_PORTD
*               			GPIO_PORTE
*               			GPIO_PORTH

Copy_u8GPIO_Pin :
							GPIO_PIN0
							GPIO_PIN1
								.
								.
							GPIO_PIN15
 * Copy_u8GPIO_Value:
							& value
*/
/* ---------------------------------------------------------------------------------------- ------------- */

/******************************************* Function(5) *****************************************************/
/*************************************** Purpose : Setting speed of output passed pin    *********************/
/*************************************** INPUTS  : (3)  Port ,pin ,pointer to value	     *********************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
GPIO_enuErrorState GPIO_enuReadPin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 * Copy_u8GPIO_Value );

/*
* Copy_u8GPIO_Port :
*							GPIO_PORTA
*               			GPIO_PORTB
*               			GPIO_PORTC
*							GPIO_PORTD
*               			GPIO_PORTE
*               			GPIO_PORTH

Copy_u8GPIO_Pin :
							GPIO_PIN0
							GPIO_PIN1
								.
								.
							GPIO_PIN15
 * Copy_u8GPIO_Value:
							& value
*/
/* ---------------------------------------------------------------------------------------- ------------- */

/******************************************* Function(6) *****************************************************/
/*************************************** Purpose : Setting the Alternative Function **************************/
/*************************************** INPUTS  : (3)  Port ,pin ,AF		    **************************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
/*************************************** */

GPIO_enuErrorState GPIO_enuSetAlternativeFunctionPin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_AF );




/* ---------------------------------------------------------------------------------------- ------------- */

#define    GPIO_AF0_SYSTEM				0
#define    GPIO_AF1_TIM1_TIM2           1
#define    GPIO_AF2_TIM3_TIM4_TIM5      2
#define    GPIO_AF3_TIM9_TIM10_TIM11    3
#define    GPIO_AF4_I2C1_I2C2_I2C3      4
#define    GPIO_AF5_SPI1_4              5
#define    GPIO_AF6_SPI3                6
#define    GPIO_AF7_USART1_2            7
#define    GPIO_AF8_USART6              8
#define    GPIO_AF9_I2C2_3              9
#define    GPIO_AF10_OTG_FS             10
#define    GPIO_AF11                    11
#define    GPIO_AF12_SDIO               12
#define    GPIO_AF13                    13
#define    GPIO_AF14                    14
#define    GPIO_AF15_EVENTOUT           15


#define GPIO_PORTA      0  
#define GPIO_PORTB      1  
#define GPIO_PORTC      2
#define GPIO_PORTD      3
#define GPIO_PORTE      4
#define GPIO_PORTH      5

#define GPIO_PIN0		0
#define GPIO_PIN1       1
#define GPIO_PIN2       2
#define GPIO_PIN3       3
#define GPIO_PIN4       4
#define GPIO_PIN5       5
#define GPIO_PIN6       6
#define GPIO_PIN7       7
#define GPIO_PIN8       8
#define GPIO_PIN9       9
#define GPIO_PIN10      10
#define GPIO_PIN11      11
#define GPIO_PIN12      12
#define GPIO_PIN13      13
#define GPIO_PIN14      14
#define GPIO_PIN15      15


/* Table 24*/
#define     GPIO_MODE_GP_OUT_PP         		0b01000
#define     GPIO_MODE_GP_OUT_PP_PU         		0b01001
#define     GPIO_MODE_GP_OUT_PP_PD              0b01010
#define     GPIO_MODE_GP_OUT_OD                 0b01100
#define     GPIO_MODE_GP_OUT_OD_PU              0b01101
#define     GPIO_MODE_GP_OUT_OD_PD              0b01110

#define     GPIO_MODE_AF_PP    					0b10000 /*USART_TX*/
#define     GPIO_MODE_AF_PP_PU      			0b10001
#define     GPIO_MODE_AF_PP_PD      			0b10010
#define     GPIO_MODE_AF_OD         			0b10100
#define     GPIO_MODE_AF_OD_PU      			0b10101
#define     GPIO_MODE_AF_OD_PD      			0b10110

#define     GPIO_MODE_INPUT_FLOATING   			0b00000 /*USART_RX*/
#define     GPIO_MODE_INPUT_PU         			0b00001
#define     GPIO_MODE_INPUT_PD         			0b00010

#define     GPIO_MODE_INPUT_OUTPUT_ANALOG       0b11000

#define     GPIO_SPEED_LOW      	   0
#define     GPIO_SPEED_MEDIUM         1
#define     GPIO_SPEED_HIGH  	       2
#define     GPIO_SPEED_VERYHIGH       3




#define     GPIO_LOW       0
#define     GPIO_HIGH      1




#endif
