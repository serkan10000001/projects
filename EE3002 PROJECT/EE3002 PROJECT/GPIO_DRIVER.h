#ifndef GPIO_H_
#define GPIO_H_
#include <stdint.h>
#include <stm32f10x.h>
//#include "SYSTICK_DRIVER.h"
#define RCC_APB2ENR     (*((volatile unsigned long *) 0x40021018))
#define GPIOA_R         (*((volatile unsigned long *) 0x40010800))
#define GPIOB_R          (*((volatile unsigned long *) 0x40010C00))
#define GPIOC_R          (*((volatile unsigned long *) 0x40011000))

#define PA 1 
#define PB 2
#define PC 3 

#define IN 0 
#define OUT10 1
#define OUT2 2
#define OUT50 3

#define I_A 0
#define I_FP 1
#define I_PP 2

#define G_PP 0
#define G_OD 1
#define AF_PP 2
#define AF_OD 3

#define LOW 0
#define HIGH 1

#define GPIO_CRL_OFFSET 0x00
#define GPIO_CRH_OFFSET 0x04
#define GPIO_IDR_OFFSET 0x08
#define GPIO_ODR_OFFSET 0x0C

void gpio_init(unsigned short PORT, unsigned short PIN, unsigned short DIRECTION, unsigned CONFIGURATION);
int READ_GPIO(unsigned short PORT, unsigned short PIN);
void WRITE_GPIO(unsigned short PORT, unsigned short PIN, unsigned short STATE);
void TOGGLE_GPIO(unsigned short PORT, unsigned short PIN);
#endif 
