
#include "TIMER1_DRIVER.h"

#define PRESCALAR (72 - 1)
unsigned long PRESCALAR_PWM_MILIS  = (7200 - 1);
#define TIMER1CLKEN (0x800)
#define TIMER1CNTEN (1U << 0)
#define TIMER1OPM (1U << 3)
#define TIMER1PWMMODE (0x60)
#define TIMER1CCEN (1U << 0)
#define TIMER1MOEEN (0x8000)
#define TIMER1CAPTURE (0x1)
#define TIMER1CAPTURE_CH2 (0x100);
#define TIMER1CAPTURE_RISING (1U << 1)

/*Timer 1 Microsecond Delay Function*/
void timer1Delay_micros(int micros){
	RCC->APB2ENR |= TIMER1CLKEN;
	TIM1->CNT = 0;
	TIM1->PSC = PRESCALAR;
	TIM1->ARR = (micros - 1);
	TIM1->CR1 |= (TIMER1OPM | TIMER1CNTEN);
	while(TIM1->CR1 & 1){}
}
void timer1Delay_milis(int milis){
	for(int i = 0; i < milis; i++){
		timer1Delay_micros(1000);
	}
}
/*Timer 1 SR-04 Driver Set-Up*/
void timer1PWM_micros(int period, int pwm){
	RCC->APB2ENR |= TIMER1CLKEN;
	TIM1->PSC = PRESCALAR;	
	TIM1->CNT = 0;
	TIM1->CCMR1 |= TIMER1PWMMODE;
	TIM1->CCER |= TIMER1CCEN; 
	TIM1->BDTR |= TIMER1MOEEN;
	TIM1->CCR1 = pwm;
	TIM1->ARR = (period - 1);
	TIM1->CR1 |= TIMER1CNTEN;
}
void timer1PWM_milis(int period, int pwm){
	RCC->APB2ENR |= TIMER1CLKEN;
	TIM1->PSC = PRESCALAR_PWM_MILIS;	
	TIM1->CNT = 0;
	TIM1->CCMR1 |= TIMER1PWMMODE;
	TIM1->CCER |= TIMER1CCEN; 
	TIM1->BDTR |= TIMER1MOEEN;
	TIM1->CCR1 = pwm*10;
	TIM1->ARR = (period*10 - 1);
	TIM1->CR1 |= TIMER1CNTEN;
}
void timer1Capture_micro(int period){
	
	RCC->APB2ENR |= TIMER1CLKEN;
	TIM1->PSC = (72 - 1);
	TIM1->CNT = 0;
	TIM1->CCMR1 |= 0x100;
	TIM1->CCER |= (1U << 4);
	TIM1->BDTR |= 0x8000;
	TIM1->CR1 |= 1;
	TIM1->CCER |= (1U << 5);
	TIM1->ARR = (period - 1);
}
void timer1Capture_milis(int period){
	RCC->APB2ENR |= TIMER1CLKEN;
	TIM1->PSC = (7200 - 1);
	TIM1->CNT = 0;
	TIM1->CCMR1 |= 0x100;
	TIM1->CCER |= (1U << 4);
	TIM1->BDTR |= 0x8000;
	TIM1->CR1 |= 1;
	TIM1->CCER |= (1U << 5);
	TIM1->ARR = (period*10 - 1);
}
int timer1_get_capture_micro(void){
	int capture = 0;
	int psc = 0;
	capture = TIM1->CCR2;
	psc = TIM1->PSC;
	capture = (capture*psc)/(72 - 1);
	return capture;
}
int timer1_get_capture_milis(void){
	int capture = timer1_get_capture_micro()/1000;
	return capture;
}

void timer1PWM_milisBUZZER(int period, int pwm){
	RCC->APB2ENR |= TIMER1CLKEN;
	TIM1->PSC = PRESCALAR_PWM_MILIS;	
	TIM1->CNT = 0;
	TIM1->CCMR2 |= TIMER1PWMMODE;
	TIM1->CCER |= (1U << 8); 
	TIM1->BDTR |= TIMER1MOEEN;
	TIM1->CCR3 = pwm;
	TIM1->ARR = (period - 1);
	TIM1->CR1 |= TIMER1CNTEN;
}
