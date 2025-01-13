#include "BUZZER.h"

#define PRESCALAR3 (72 - 1)
unsigned long PRESCALAR_PWM_MILIS3  = (7200 - 1);
#define TIMER3CLKEN (0x800)
#define TIMER3CNTEN (1U << 0)
#define TIMER3OPM (1U << 3)
#define TIMER3PWMMODE (0x60)
#define TIMER3CCEN (1U << 0)
#define TIMER3MOEEN (0x8000)
#define TIMER3CAPTURE (0x1)
#define TIMER3CAPTURE_CH2 (0x100)
#define TIMER3CAPTURE_RISING (1U << 1)


void timer3Delay_micros(int micros){
	RCC->APB1ENR |= (1U << 1);
	TIM3->CNT = 0;
	
	TIM3->PSC = PRESCALAR3;
	TIM3->ARR = (micros - 1);
	TIM3->CR1 |= (TIMER3OPM | TIMER3CNTEN);
	while(TIM3->CR1 & 1){}
}
void timer3Delay_milis(int milis){
	for(int i = 0; i < milis; i++){
		timer3Delay_micros(1000);
	}
}

void timer3PWM_micros(int period, int pwm){
	RCC->APB1ENR |= (1U << 1);
	TIM3->PSC = PRESCALAR3;	
	TIM3->CNT = 0;
	TIM3->CCMR1 |= TIMER3PWMMODE;
	TIM3->CCER |= TIMER3CCEN; 
	TIM3->BDTR |= TIMER3MOEEN;
	TIM3->CCR1 = pwm;
	TIM3->ARR = (period - 1);
	TIM3->CR1 |= TIMER3CNTEN;
}
void timer3PWM_milis(int period, int pwm){
	RCC->APB1ENR |= (1U << 1);;
	TIM3->PSC = PRESCALAR_PWM_MILIS3;	
	TIM3->CNT = 0;
	TIM3->CCMR1 |= TIMER3PWMMODE;
	TIM3->CCER |= TIMER3CCEN; 
	TIM3->BDTR |= TIMER3MOEEN;
	TIM3->CCR1 = pwm*10;
	TIM3->ARR = (period*10 - 1);
	TIM3->CR1 |= TIMER3CNTEN;
}
