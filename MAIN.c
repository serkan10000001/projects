#include "stm32f10x.h"
#include "main.h"

void pa0_exti_init(void){
	/*first i will configure clk for gpio*/
	/*make gpio pin as input*/
	/*after that enable clk access to SYSCONFIG*/
	/*Select port a for exti0*/
	/*after that unmask the exti0*/
	/*select rising edge trigger*/
	/*enable exti0 line in NVIC*/ 
	/*enable global interupt*/
	RCC->APB2ENR |= (1U << 2);
	RCC->APB2ENR |= (1U << 0);
	
	GPIOA->CRL &= ~(0xF << 0);
	GPIOA->CRL |= (0x8 << 0);

	AFIO->EXTICR[0] &= ~(0xF << 0);
	
	EXTI->IMR |= (1U << 0);
	
	EXTI->RTSR |= (1U << 0);
	
	NVIC_SetPriority(EXTI0_IRQn, 1);
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	
	__enable_irq();
}

void pb1_exti_init(void){
	
	RCC->APB2ENR |= (1U << 3);
	RCC->APB2ENR |= (1U << 0);
	
	GPIOA->CRL &= ~(0xF << 4);
	GPIOA->CRL |= (0x8 << 4);

	AFIO->EXTICR[0] &= ~(0xF << 4);
	AFIO->EXTICR[0] |= (1U << 4);
	
	EXTI->IMR |= (1U << 1);
	
	EXTI->FTSR |= (1U << 1);
	
	NVIC_SetPriority(EXTI1_IRQn, 2);
	NVIC_EnableIRQ(EXTI1_IRQn);
	
	__enable_irq();
}

