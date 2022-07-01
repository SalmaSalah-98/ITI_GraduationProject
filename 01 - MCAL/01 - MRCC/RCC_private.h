/***********************************************************/
/*** Author  :  Solyma                      ****************/
/*** RCC_private							****************/
/*** Date    : 8/3/2022                     ****************/
/*** Version :  01                          ****************/
/***********************************************************/

#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

#define RCC_BASE_ADDRESS           0x40023800


// Register Definitions:
#define RCC_CR		          	   * ((u32*)(RCC_BASE_ADDRESS + 0x00)) // To choose clock system to be (PPl - crystal - )for the peripheral
#define RCC_PLLCFGR         	   * ((u32*)(RCC_BASE_ADDRESS + 0x04)) // To choose which clock to be (PPl - crystal - )for the peripheral
#define RCC_CFGR     	           * ((u32*)(RCC_BASE_ADDRESS + 0x08))
#define RCC_CIR					   * ((u32*)(RCC_BASE_ADDRESS + 0x0C))
#define RCC_AHB1RSTR			   * ((u32*)(RCC_BASE_ADDRESS + 0x10))
#define RCC_AHB2RSTR               * ((u32*)(RCC_BASE_ADDRESS + 0x14))
#define RCC_APB1RSTR               * ((u32*)(RCC_BASE_ADDRESS + 0x20))
#define RCC_APB2RSTR               * ((u32*)(RCC_BASE_ADDRESS + 0x24))
#define RCC_AHB1ENR                * ((u32*)(RCC_BASE_ADDRESS + 0x30))
#define RCC_AHB2ENR                * ((u32*)(RCC_BASE_ADDRESS + 0x34))
#define RCC_APB1ENR                * ((u32*)(RCC_BASE_ADDRESS + 0x40))
#define RCC_APB2ENR                * ((u32*)(RCC_BASE_ADDRESS + 0x44))
#define RCC_AHB1LPENR              * ((u32*)(RCC_BASE_ADDRESS + 0x50))
#define RCC_AHB2LPENR              * ((u32*)(RCC_BASE_ADDRESS + 0x54))
#define RCC_APB1LPENR              * ((u32*)(RCC_BASE_ADDRESS + 0x60))
#define RCC_APB2LPENR              * ((u32*)(RCC_BASE_ADDRESS + 0x64))
#define RCC_BDCR                   * ((u32*)(RCC_BASE_ADDRESS + 0x70))
#define RCC_CSR                    * ((u32*)(RCC_BASE_ADDRESS + 0x74))
#define RCC_SSCGR                  * ((u32*)(RCC_BASE_ADDRESS + 0x80))
#define RCC_PLLI2SCFGR             * ((u32*)(RCC_BASE_ADDRESS + 0x84))
#define RCC_DCKCFGR                * ((u32*)(RCC_BASE_ADDRESS + 0x8C))



#endif