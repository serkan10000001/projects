#include "main.h"
#include <stdint.h>
#define DEBOUNCE_DELAY 		40 // ms 

void EXTI0_IRQHandler(void);
volatile uint32_t msTicks = 0;           
volatile uint32_t lastTime = 0;


int main(void){
	RCC->APB2ENR |= (1U << 4);
	GPIOC->CRH  &= ~(0xF << 20);
	GPIOC->CRH |= (1U << 20);
	
	SysTick->LOAD = 9000;
  SysTick->VAL = 0;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
	
	pa0_exti_init();
	pb1_exti_init();
	while(1){}
}

void SysTick_Handler(void) {
    msTicks++;
}
static void pa0_ISR(void){
	GPIOC->BSRR |= (1U << 13);
}

static void pb1_ISR(void){
	GPIOC->BSRR |= (1U << 29);
}

void EXTI0_IRQHandler(void){
			if((EXTI->PR & (1U << 0)) != 0){
				uint32_t currentTime = msTicks;
				if((currentTime - lastTime) > DEBOUNCE_DELAY){
				lastTime = currentTime;
				EXTI->PR |= (1U << 0);
				pa0_ISR();
				}
			}
}
void EXTI1_IRQHandler(void){
			if((EXTI->PR & (1U << 1)) != 0){
				uint32_t currentTime = msTicks;
				if((currentTime - lastTime) > DEBOUNCE_DELAY){
					lastTime = currentTime;
					EXTI->PR |= (1U << 1);
					pb1_ISR();
			}
		}
}		

