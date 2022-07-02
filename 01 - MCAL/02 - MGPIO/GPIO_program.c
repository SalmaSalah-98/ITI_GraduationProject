/***********************************************************/
/***********************************************************/
/***********************************************************/
/**************** Author  :  Solyma         ****************/
/**************** Target  : ARM_CRTEX_M4	****************/
/**************** GPIO_Program.c   			****************/
/**************** Date    : 23/3/2022       ****************/
/**************** Version :  01             ****************/
/**************** Company : ITI 			****************/
/***********************************************************/
/***********************************************************/


#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include"GPIO_interface.h"
#include"GPIO_private.h"

/******************************************* Function(1) *****************************************************/
/*************************************** Purpose : Setting the Pins Mode            	 *********************/
//GPIO_enuErrorState GPIO_enuSetPinMode(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_Mode )

GPIO_enuErrorState GPIO_enuSetPinMode(GPIO_Pin_Cnfg * Add_pstrGPIO_cnfg)
{
	GPIO_enuErrorState Local_enuErrorState = GPIO_enuOK;
	u8 Local_u8GPIO_Port = Add_pstrGPIO_cnfg -> GPIO_PORT;
	u8 Local_u8GPIO_Pin  = Add_pstrGPIO_cnfg -> GPIO_PIN;
	u8 Local_u8GPIO_Mode = Add_pstrGPIO_cnfg -> GPIO_MODE;
	u8 Local_u8GPIO_Speed = Add_pstrGPIO_cnfg -> GPIO_OUT_SPEED;

	
	u8 Local_u8GPIO_MODER  = ((Local_u8GPIO_Mode >> 3 ) & 0b11); //to get bits[4;3]
	u8 Local_u8GPIO_OTYPER = ((Local_u8GPIO_Mode >> 2 ) & 0b1 ); //to get bit[2]
	u8 Local_u8GPIO_PUPDR  = ((Local_u8GPIO_Mode >> 0 ) & 0b11); //to get bits[1,0]

	if (Local_u8GPIO_Port < 6)
	{
		if (Local_u8GPIO_Pin < 16)
		{
			if (Local_u8GPIO_Mode < 32)
			{
				//All is right
				
				switch(Local_u8GPIO_Port)
				{
					case GPIO_PORTA :
										/* 1 - MODER*/
					GPIOA_MODER &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOA_MODER |= (Local_u8GPIO_MODER << (Local_u8GPIO_Pin*2));
			      //GPIOA_MODER |= ((Local_u8GPIO_MODER&0b11) << (Local_u8GPIO_Pin*2));
					
					/* 2 - OTYPER*/
					GPIOA_OTYPER &=~ (0b11 << (Local_u8GPIO_Pin));
					GPIOA_OTYPER |=  ((Local_u8GPIO_OTYPER & 1) << (Local_u8GPIO_Pin));
					
					/* 3 - PUPDR :These bits are written by software to configure the I/O pull-up or pull-down*/
					GPIOA_PUPDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOA_PUPDR |= (Local_u8GPIO_PUPDR << (Local_u8GPIO_Pin*2));

					/* (4) Set the Speed */
					GPIOA_OSPEEDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOA_OSPEEDR |= (Local_u8GPIO_Speed << (Local_u8GPIO_Pin*2));

					
					break;
					
					case GPIO_PORTB :
					
										/* 1 - MODER*/
					GPIOB_MODER &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOB_MODER |= (Local_u8GPIO_MODER << (Local_u8GPIO_Pin*2));
			      //GPIOA_MODER |= ((Local_u8GPIO_MODER&0b11) << (Local_u8GPIO_Pin*2));
					
					/* 2 - OTYPER*/
					GPIOB_OTYPER &=~ (0b11 << (Local_u8GPIO_Pin));
					GPIOB_OTYPER |=  ((Local_u8GPIO_OTYPER & 1) << (Local_u8GPIO_Pin));
					
					/* 3 - PUPDR :These bits are written by software to configure the I/O pull-up or pull-down*/
					GPIOB_PUPDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOB_PUPDR |= (Local_u8GPIO_PUPDR << (Local_u8GPIO_Pin*2));			      
					
					/* (4) Set the Speed */
					GPIOB_OSPEEDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOB_OSPEEDR |= (Local_u8GPIO_Speed << (Local_u8GPIO_Pin*2));

					break;
					
					case GPIO_PORTC :
					
										/* 1 - MODER*/
					GPIOC_MODER &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOC_MODER |= (Local_u8GPIO_MODER << (Local_u8GPIO_Pin*2));
			      //GPIOA_MODER |= ((Local_u8GPIO_MODER&0b11) << (Local_u8GPIO_Pin*2));
					
					/* 2 - OTYPER*/
					GPIOC_OTYPER &=~ (0b11 << (Local_u8GPIO_Pin));
					GPIOC_OTYPER |=  ((Local_u8GPIO_OTYPER & 1) << (Local_u8GPIO_Pin));
					
					/* 3 - PUPDR :These bits are written by software to configure the I/O pull-up or pull-down*/
					GPIOC_PUPDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOC_PUPDR |= (Local_u8GPIO_PUPDR << (Local_u8GPIO_Pin*2));			      
					/* (4) Set the Speed */
					GPIOC_OSPEEDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOC_OSPEEDR |= (Local_u8GPIO_Speed << (Local_u8GPIO_Pin*2));

					
					break;
					
					case GPIO_PORTD :
					
										/* 1 - MODER*/
					GPIOD_MODER &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOD_MODER |= (Local_u8GPIO_MODER << (Local_u8GPIO_Pin*2));
			      //GPIOA_MODER |= ((Local_u8GPIO_MODER&0b11) << (Local_u8GPIO_Pin*2));
					
					/* 2 - OTYPER*/
					GPIOD_OTYPER &=~ (0b11 << (Local_u8GPIO_Pin));
					GPIOD_OTYPER |=  ((Local_u8GPIO_OTYPER & 1) << (Local_u8GPIO_Pin));
					
					/* 3 - PUPDR :These bits are written by software to configure the I/O pull-up or pull-down*/
					GPIOD_PUPDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOD_PUPDR |= (Local_u8GPIO_PUPDR << (Local_u8GPIO_Pin*2));			      
					
					/* (4) Set the Speed */
					GPIOD_OSPEEDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOD_OSPEEDR |= (Local_u8GPIO_Speed << (Local_u8GPIO_Pin*2));
					break;
					
					case GPIO_PORTE :
					
										/* 1 - MODER*/
					GPIOE_MODER &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOE_MODER |= (Local_u8GPIO_MODER << (Local_u8GPIO_Pin*2));
			      //GPIOA_MODER |= ((Local_u8GPIO_MODER&0b11) << (Local_u8GPIO_Pin*2));
					
					/* 2 - OTYPER*/
					GPIOE_OTYPER &=~ (0b11 << (Local_u8GPIO_Pin));
					GPIOE_OTYPER |=  ((Local_u8GPIO_OTYPER & 1) << (Local_u8GPIO_Pin));
					
					/* 3 - PUPDR :These bits are written by software to configure the I/O pull-up or pull-down*/
					GPIOE_PUPDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOE_PUPDR |= (Local_u8GPIO_PUPDR << (Local_u8GPIO_Pin*2));			      
					/* (4) Set the Speed */
					GPIOE_OSPEEDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOE_OSPEEDR |= (Local_u8GPIO_Speed << (Local_u8GPIO_Pin*2));

					break;
					
					case GPIO_PORTH :
					
										/* 1 - MODER*/
					GPIOH_MODER &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOH_MODER |= (Local_u8GPIO_MODER << (Local_u8GPIO_Pin*2));
			      //GPIOA_MODER |= ((Local_u8GPIO_MODER&0b11) << (Local_u8GPIO_Pin*2));
					
					/* 2 - OTYPER*/
					GPIOH_OTYPER &=~ (0b11 << (Local_u8GPIO_Pin));
					GPIOH_OTYPER |=  ((Local_u8GPIO_OTYPER & 1) << (Local_u8GPIO_Pin));
					
					/* 3 - PUPDR :These bits are written by software to configure the I/O pull-up or pull-down*/
					GPIOH_PUPDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOH_PUPDR |= (Local_u8GPIO_PUPDR << (Local_u8GPIO_Pin*2));			      
					
					/* (4) Set the Speed */
					GPIOH_OSPEEDR &=~ (0b11 << (Local_u8GPIO_Pin*2));
					GPIOH_OSPEEDR |= (Local_u8GPIO_Speed << (Local_u8GPIO_Pin*2));

					break;
					
					default : break;
				}
				
			}
			else
			{
				Local_enuErrorState = GPIO_enuModeError;
			}
		}
		else
		{
			Local_enuErrorState =GPIO_enuPinError;
		}
	}
	else
	{
		Local_enuErrorState =GPIO_enuPortError;
	}
	
	
	return Local_enuErrorState;
}

/* ----------------------------------------------------------------------------------------- ------------- */



/******************************************* Function(2) *****************************************************/
/*************************************** Purpose : Setting the Ouput Pin Value(High /Low)*********************/
GPIO_enuErrorState GPIO_enuSetPinValue(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_Value )
{
	GPIO_enuErrorState Local_enuErrorState = GPIO_enuOK;
	
	if (Copy_u8GPIO_Port < 6)
	{
		if (Copy_u8GPIO_Pin < 16)	
			{
			if (Copy_u8GPIO_Value < 2)
			{
				// All is right
				switch(Copy_u8GPIO_Port)
				{
					case GPIO_PORTA :
					if (Copy_u8GPIO_Value == GPIO_HIGH)
					{
						GPIOA_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					else //GPIO_LOW
					{
						Copy_u8GPIO_Pin += 16;
						GPIOA_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					break;
					
					case GPIO_PORTB :
					if (Copy_u8GPIO_Value == GPIO_HIGH)
					{
						GPIOB_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					else //GPIO_LOW
					{
						Copy_u8GPIO_Pin += 16;
						GPIOB_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					break;
					
					case GPIO_PORTC :
					if (Copy_u8GPIO_Value == GPIO_HIGH)
					{
						GPIOC_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					else //GPIO_LOW
					{
						Copy_u8GPIO_Pin += 16;
						GPIOC_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					break;
					
					case GPIO_PORTD :
					if (Copy_u8GPIO_Value == GPIO_HIGH)
					{
						GPIOD_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					else //GPIO_LOW
					{
						Copy_u8GPIO_Pin += 16;
						GPIOD_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					break;
					
					case GPIO_PORTE :
					if (Copy_u8GPIO_Value == GPIO_HIGH)
					{
						GPIOE_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					else //GPIO_LOW
					{
						Copy_u8GPIO_Pin += 16;
						GPIOE_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					break;
					
					case GPIO_PORTH :
					if (Copy_u8GPIO_Value == GPIO_HIGH)
					{
						GPIOH_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					else //GPIO_LOW
					{
						Copy_u8GPIO_Pin += 16;
						GPIOH_BSRR = (1 << Copy_u8GPIO_Pin) ;
					}
					break;
					
					default : break;
				}
			}
			else
			{
				Local_enuErrorState = GPIO_enuValueError;
			}
		}
		else
		{
			Local_enuErrorState = GPIO_enuPinError;
		}
	}
	else
	{
		Local_enuErrorState = GPIO_enuPortError;
	}
	
	
	return Local_enuErrorState;
}



/******************************************* Function(3) *****************************************************/
/*************************************** Purpose : Write on the Ouput Pin Value(High /Low)*********************/
GPIO_enuErrorState GPIO_enuWritePin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_Value )
{
	GPIO_enuErrorState Local_enuErrorState = GPIO_enuOK;
	
	if (Copy_u8GPIO_Port < 6)
	{
		if (Copy_u8GPIO_Pin < 16)	
			{
			if (Copy_u8GPIO_Value < 2)
			{
				// All is right
				switch(Copy_u8GPIO_Port)
				{
					case GPIO_PORTA :
					{
						if (Copy_u8GPIO_Value == GPIO_HIGH)
						{
							SET_BIT(GPIOA_ODR , Copy_u8GPIO_Pin);
						}
						else //GPIO_LOW
						{
							CLR_BIT(GPIOA_ODR , Copy_u8GPIO_Pin);
						}
					}
					break;

					case GPIO_PORTB :
					{
						if (Copy_u8GPIO_Value == GPIO_HIGH)
						{
							SET_BIT(GPIOB_ODR , Copy_u8GPIO_Pin);
						}
						else //GPIO_LOW
						{
							CLR_BIT(GPIOB_ODR , Copy_u8GPIO_Pin);
						}
					}
					break;
					
					case GPIO_PORTC :
					{
						if (Copy_u8GPIO_Value == GPIO_HIGH)
						{
							SET_BIT(GPIOC_ODR , Copy_u8GPIO_Pin);
						}
						else //GPIO_LOW
						{
							CLR_BIT(GPIOC_ODR , Copy_u8GPIO_Pin);
						}
					}
					break;
					
					case GPIO_PORTD :
					{
						if (Copy_u8GPIO_Value == GPIO_HIGH)
						{
							SET_BIT(GPIOD_ODR , Copy_u8GPIO_Pin);
						}
						else //GPIO_LOW
						{
							CLR_BIT(GPIOD_ODR , Copy_u8GPIO_Pin);
						}
					}
					break;

					case GPIO_PORTE :
					{
						if (Copy_u8GPIO_Value == GPIO_HIGH)
						{
							SET_BIT(GPIOE_ODR , Copy_u8GPIO_Pin);
						}
						else //GPIO_LOW
						{
							CLR_BIT(GPIOE_ODR , Copy_u8GPIO_Pin);
						}
					}
					break;
					
					case GPIO_PORTH :
					{
						if (Copy_u8GPIO_Value == GPIO_HIGH)
						{
							SET_BIT(GPIOH_ODR , Copy_u8GPIO_Pin);
						}
						else //GPIO_LOW
						{
							CLR_BIT(GPIOH_ODR , Copy_u8GPIO_Pin);
						}
					}
					break;
					default : break;
				}
			}
			else
			{
				Local_enuErrorState = GPIO_enuValueError;
			}
		}
		else
		{
			Local_enuErrorState = GPIO_enuPinError;
		}
	}
	else
	{
		Local_enuErrorState = GPIO_enuPortError;
	}
	return Local_enuErrorState;
}



/******************************************* Function(4) *****************************************************/
/*************************************** Purpose : Read the input value (HIGH/ LOW)      *********************/
GPIO_enuErrorState GPIO_enuReadPin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 * Copy_u8GPIO_Value )
{
	
	GPIO_enuErrorState Local_enuErrorState = GPIO_enuOK;

	if (Copy_u8GPIO_Port < 6)
	{
		if (Copy_u8GPIO_Pin < 16)
			{
				if (Copy_u8GPIO_Value != NULL)
				{// All is right
				switch(Copy_u8GPIO_Port)
				{
					case GPIO_PORTA :
					{
						* Copy_u8GPIO_Value = GET_BIT(GPIOA_IDR , Copy_u8GPIO_Pin);
					}
					break;

					case GPIO_PORTB :
					{
						* Copy_u8GPIO_Value = GET_BIT(GPIOB_IDR , Copy_u8GPIO_Pin);
					}
					break;

					case GPIO_PORTC :
					{
						* Copy_u8GPIO_Value = GET_BIT(GPIOC_IDR , Copy_u8GPIO_Pin);
					}
					break;

					case GPIO_PORTD :
					{
						* Copy_u8GPIO_Value = GET_BIT(GPIOD_IDR , Copy_u8GPIO_Pin);
					}
					break;

					case GPIO_PORTE :
					{
						* Copy_u8GPIO_Value = GET_BIT(GPIOE_IDR , Copy_u8GPIO_Pin);
					}
					break;

					case GPIO_PORTH :
					{
						* Copy_u8GPIO_Value = GET_BIT(GPIOH_IDR , Copy_u8GPIO_Pin);
					}
					break;
					default : break;
				}
				}
				else
				{
					Local_enuErrorState = GPIO_enuNullPointer;
				}
		}
		else
		{
			Local_enuErrorState = GPIO_enuPinError;
		}
	}
	else
	{
		Local_enuErrorState = GPIO_enuPortError;
	}
	return Local_enuErrorState;
}



/******************************************* Function(6) *****************************************************/
/*************************************** Purpose : Setting the Alternative Function **************************/
/*************************************** INPUTS  : (3)  Port ,pin ,AF Value		    **************************/
/*************************************** Output  : enum (GPIO_enuErrorState) 			 *********************/
/*************************************** */

GPIO_enuErrorState GPIO_enuSetAlternativeFunctionPin(u8 Copy_u8GPIO_Port , u8 Copy_u8GPIO_Pin , u8 Copy_u8GPIO_AF )
{
	GPIO_enuErrorState Local_enuErrorState = GPIO_enuOK;

	if ((Copy_u8GPIO_Port < 6) && (Copy_u8GPIO_AF < 16))
	{
		if (Copy_u8GPIO_Pin < 8)
			{
				switch(Copy_u8GPIO_Port)
				{
					case GPIO_PORTA :
					{
						GPIOA_AFRL &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOA_AFRL |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTB :
					{
						GPIOB_AFRL &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOB_AFRL |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTC :
					{
						GPIOC_AFRL &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOC_AFRL |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTD :
					{
						GPIOD_AFRL &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOD_AFRL |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTE :
					{
						GPIOE_AFRL &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOE_AFRL |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
											}
					break;

					case GPIO_PORTH :
					{
						GPIOH_AFRL &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOH_AFRL |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;
					default : break;
				}
			
			}
		else if (Copy_u8GPIO_Pin < 16)
			{
				Copy_u8GPIO_Pin -= 8 ;
				switch(Copy_u8GPIO_Port)
				{
					case GPIO_PORTA :
					{
						GPIOA_AFRH &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOA_AFRH |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTB :
					{
						GPIOB_AFRH &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOB_AFRH |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTC :
					{
						GPIOC_AFRH &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOC_AFRH |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTD :
					{
						GPIOD_AFRH &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOD_AFRH |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;

					case GPIO_PORTE :
					{
						GPIOE_AFRH &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOE_AFRH |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
											}
					break;

					case GPIO_PORTH :
					{
						GPIOH_AFRH &=~   (0b1111 << (Copy_u8GPIO_Pin*4)); //Bit Masking of Bits[x : x+4]
						GPIOH_AFRH |=  	(Copy_u8GPIO_AF << (Copy_u8GPIO_Pin*4));
						
					}
					break;
					default : break;
				}
			}
		else
			{
				Local_enuErrorState = GPIO_enuPinError;
			}
	}
	else
	{
		Local_enuErrorState = GPIO_enuPortError;
	}
	return Local_enuErrorState;
}
