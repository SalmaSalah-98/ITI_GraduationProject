/***********************************************************/
/***********************************************************/
/***********************************************************/
/**************** Author  :  Solyma         ****************/
/**************** Target  : ARM_CRTEX_M4	****************/
/**************** GPIO_Private   			****************/
/**************** Date    : 23/3/2022       ****************/
/**************** Version :  01             ****************/
/**************** Company : ITI 			****************/
/***********************************************************/
/***********************************************************/



#ifndef GPIO_PRIVATE_H_
#define GPIO_PRIVATE_H_




#define   GPIOA_BASE_ADDRESS    0x40020000
#define   GPIOB_BASE_ADDRESS	0x40020400
#define   GPIOC_BASE_ADDRESS    0x40020800
#define   GPIOD_BASE_ADDRESS    0x40020C00
#define   GPIOE_BASE_ADDRESS    0x40021000
#define   GPIOH_BASE_ADDRESS    0x40021C00
                                

#define   GPIOA_MODER       *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x00  ))
#define   GPIOA_OTYPER      *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x04  ))
#define   GPIOA_OSPEEDR     *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x08  ))
#define   GPIOA_PUPDR       *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x0C  ))
#define   GPIOA_IDR         *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x10  ))
#define   GPIOA_ODR         *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x14  ))
#define   GPIOA_BSRR        *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x18  ))
#define   GPIOA_LCKR        *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x1C  ))
#define   GPIOA_AFRL        *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x20  ))								
#define   GPIOA_AFRH        *((volatile u32*)(GPIOA_BASE_ADDRESS + 0x24  ))


#define   GPIOB_MODER       *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x00  ))
#define   GPIOB_OTYPER      *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x04  ))
#define   GPIOB_OSPEEDR     *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x08  ))
#define   GPIOB_PUPDR       *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x0C  ))
#define   GPIOB_IDR         *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x10  ))
#define   GPIOB_ODR         *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x14  ))
#define   GPIOB_BSRR        *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x18  ))
#define   GPIOB_LCKR        *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x1C  ))
#define   GPIOB_AFRL        *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x20  ))								
#define   GPIOB_AFRH        *((volatile u32*)(GPIOB_BASE_ADDRESS + 0x24  ))


#define   GPIOC_MODER       *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x00  ))
#define   GPIOC_OTYPER      *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x04  ))
#define   GPIOC_OSPEEDR     *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x08  ))
#define   GPIOC_PUPDR       *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x0C  ))
#define   GPIOC_IDR         *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x10  ))
#define   GPIOC_ODR         *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x14  ))
#define   GPIOC_BSRR        *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x18  ))
#define   GPIOC_LCKR        *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x1C  ))
#define   GPIOC_AFRL        *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x20  ))								
#define   GPIOC_AFRH        *((volatile u32*)(GPIOC_BASE_ADDRESS + 0x24  ))

#define   GPIOD_MODER       *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x00  ))
#define   GPIOD_OTYPER      *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x04  ))
#define   GPIOD_OSPEEDR     *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x08  ))
#define   GPIOD_PUPDR       *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x0C  ))
#define   GPIOD_IDR         *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x10  ))
#define   GPIOD_ODR         *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x14  ))
#define   GPIOD_BSRR        *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x18  ))
#define   GPIOD_LCKR        *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x1C  ))
#define   GPIOD_AFRL        *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x20  ))								
#define   GPIOD_AFRH        *((volatile u32*)(GPIOD_BASE_ADDRESS + 0x24  ))

#define   GPIOE_MODER       *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x00  ))
#define   GPIOE_OTYPER      *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x04  ))
#define   GPIOE_OSPEEDR     *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x08  ))
#define   GPIOE_PUPDR       *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x0C  ))
#define   GPIOE_IDR         *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x10  ))
#define   GPIOE_ODR         *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x14  ))
#define   GPIOE_BSRR        *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x18  ))
#define   GPIOE_LCKR        *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x1C  ))
#define   GPIOE_AFRL        *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x20  ))								
#define   GPIOE_AFRH        *((volatile u32*)(GPIOE_BASE_ADDRESS + 0x24  ))


#define   GPIOH_MODER       *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x00  ))
#define   GPIOH_OTYPER      *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x04  ))
#define   GPIOH_OSPEEDR     *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x08  ))
#define   GPIOH_PUPDR       *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x0C  ))
#define   GPIOH_IDR         *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x10  ))
#define   GPIOH_ODR         *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x14  ))
#define   GPIOH_BSRR        *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x18  ))
#define   GPIOH_LCKR        *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x1C  ))
#define   GPIOH_AFRL        *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x20  ))								
#define   GPIOH_AFRH        *((volatile u32*)(GPIOH_BASE_ADDRESS + 0x24  ))









#endif