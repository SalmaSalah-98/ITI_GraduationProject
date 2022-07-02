/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** NVIC_private							****************/
/*** Date    : 28/3/2022                     ****************/
/*** Version :  01                          ****************/
/***********************************************************/


#ifndef NVIC_PRIVATE_H
#define NVIC_PRIVATE_H


#define NVIC_BASE_ADDRESS       0xE000E100

typedef struct
{
	u32 NVIC_ISER0;  //NVIC_ISER0 bits 0 to 31 are for interrupt 0 to 31, respectively
	u32 NVIC_ISER1;  //NVIC_ISER1 bits 0 to 31 are for interrupt 32 to 63, respectively
	u32 NVIC_ISER2;  
	u32 NVIC_ISER3;
	u32 NVIC_ISER4;
	u32 NVIC_ISER5;
	u32 NVIC_ISER6; //NVIC_ISER6 bits 0 to 31 are for interrupt 192 to 223, respectively
	u32 NVIC_ISER7; //NVIC_ISER7 bits 0 to 15 are for interrupt 224 to 239, respectively
	
}NVIC_ISER_type;

#define  NVIC_ISER  ((volatile NVIC_ISER_type*)(NVIC_BASE_ADDRESS))


typedef struct //Interrupt clear-enable register x (NVIC_ICERx)
{
	u32 NVIC_ICER0;  //NVIC_ICER0 bits 0 to 31 are for interrupt 0 to 31, respectively
	u32 NVIC_ICER1;  //NVIC_ICER1 bits 0 to 31 are for interrupt 32 to 63, respectively
	u32 NVIC_ICER2;  
	u32 NVIC_ICER3;
	u32 NVIC_ICER4;
	u32 NVIC_ICER5;
	u32 NVIC_ICER6; //NVIC_ICER6 bits 0 to 31 are for interrupt 192 to 223, respectively
	u32 NVIC_ICER7; //NVIC_ICER7 bits 0 to 15 are for interrupt 224 to 239, respectively
	
}NVIC_ICER_type;

#define  NVIC_ICER  ((volatile NVIC_ICER_type*)(0xE000E180))

//(3)
typedef struct //Interrupt set-pending register x (NVIC_ISPRx)
{
	u32 NVIC_ISPR0;  //NVIC_ICER0 bits 0 to 31 are for interrupt 0 to 31, respectively
	u32 NVIC_ISPR1;  //NVIC_ICER1 bits 0 to 31 are for interrupt 32 to 63, respectively
	u32 NVIC_ISPR2;  
	u32 NVIC_ISPR3;
	u32 NVIC_ISPR4;
	u32 NVIC_ISPR5;
	u32 NVIC_ISPR6; //NVIC_ICER6 bits 0 to 31 are for interrupt 192 to 223, respectively
	u32 NVIC_ISPR7; //NVIC_ICER7 bits 0 to 15 are for interrupt 224 to 239, respectively
	
}NVIC_ISPR_type;

#define  NVIC_ISPR  ((volatile NVIC_ISPR_type*)(0xE000E200))


//(4) Interrupt clear-pending register x (NVIC_ICPRx)
typedef struct   
{
	u32 NVIC_ICPR0;  //NVIC_ICPR0 bits 0 to 31 are for interrupt 0 to 31, respectively
	u32 NVIC_ICPR1;  //NVIC_ICPR1 bits 0 to 31 are for interrupt 32 to 63, respectively
	u32 NVIC_ICPR2;  
	u32 NVIC_ICPR3;
	u32 NVIC_ICPR4;
	u32 NVIC_ICPR5;
	u32 NVIC_ICPR6; //NVIC_ICPR6 bits 0 to 31 are for interrupt 192 to 223, respectively
	u32 NVIC_ICPR7; //NVIC_ICPR7 bits 0 to 15 are for interrupt 224 to 239, respectively
	
}NVIC_ICPR_type;

#define  NVIC_ICPR  ((volatile NVIC_ICPR_type*)(0xE000E280))




/* (5) Interrupt Priority Register  */
#define NVIC_IPR       ((volatile u8*)(0xE000E400))




#endif
