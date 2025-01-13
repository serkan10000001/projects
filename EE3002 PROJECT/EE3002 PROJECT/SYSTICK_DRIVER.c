#include <stdint.h>
#include "SYSTICK_DRIVER.h"

/*Systick Timer Initilization Function*/
void systickTimer_init(void){
	SYSTICK_RVR = SYSTICK_LOAD;
	SYSTICK_CVR = 0;
	SYSTICK_CSR |= (SYSTICK_ENABLE | SYSTICK_CLOCK_SOURCE);
}


/*Systick Timer Delay Function*/
void SysTick_DelayMicro(void){
	while((SYSTICK_CSR & (0x00010000)) == 0);
}

void SysTick_DelayMc(uint32_t t){
	for(;t>0;t--){
		SysTick_DelayMicro();
	}
}

void SysTick_DelayMs(uint32_t t){
	t = t * 1000;
	for(;t>0;t--){
		SysTick_DelayMicro();
	}
}