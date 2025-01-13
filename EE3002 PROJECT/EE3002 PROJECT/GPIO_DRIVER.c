#include "GPIO_DRIVER.h"

void gpio_init(unsigned short PORT, unsigned short PIN, unsigned short DIRECTION, unsigned CONFIGURATION){
	volatile unsigned long * REGISTER;
	unsigned short PIN_T = PIN;
	unsigned short offset = 0x00; 
	
	if(PIN > 7){
		PIN_T = PIN_T - 8;
		offset = 	0x01;
	}		
	if(PORT == 1){
		RCC_APB2ENR |= (1U << 2);
		REGISTER = (volatile unsigned long*)(&GPIOA_R + offset);
	}else if(PORT == 2){
		RCC_APB2ENR |= (1U << 3);
		REGISTER = (volatile unsigned long*)(&GPIOB_R + offset);
	}else {
		RCC_APB2ENR |= (1U << 4);
		REGISTER = (volatile unsigned long*)(&GPIOC_R + offset);
	}	
	
	*REGISTER &= ~(0xF << (PIN_T * 4));
	*REGISTER |= ((DIRECTION << (PIN_T * 4)) | (CONFIGURATION << (PIN_T * 4 + 2)));
}

int READ_GPIO(unsigned short PORT, unsigned short PIN){
		volatile unsigned long * IDR;
		unsigned long offset = 0x02; 

		int DATA = 0;
		
		if(PORT == 1){
			IDR = (volatile unsigned long*)(&GPIOA_R + offset);
		}else if(PORT == 2){
			IDR = (volatile unsigned long*)(&GPIOB_R + offset);
		}else{
			IDR = (volatile unsigned long*)(&GPIOC_R + offset);
		}
		DATA = ((*IDR & (1 << PIN)) >> PIN);
		
		return DATA;
}

void WRITE_GPIO(unsigned short PORT, unsigned short PIN, unsigned short STATE){
	volatile unsigned long * ODR;
		unsigned long offset = 0x03; 

		if(PORT == 1){
			ODR = (volatile unsigned long*)(&GPIOA_R + offset);
		}else if(PORT == 2){
			ODR = (volatile unsigned long*)(&GPIOB_R + offset);
		}else{
			ODR = (volatile unsigned long*)(&GPIOC_R + offset);
		}
		STATE ? (*ODR |= (1U << PIN)) : (*ODR &= ~(1U << PIN));
		
}


void TOGGLE_GPIO(unsigned short PORT, unsigned short PIN){
	if(READ_GPIO(PORT, PIN)){
		WRITE_GPIO(PORT, PIN, LOW);
	}else{
		WRITE_GPIO(PORT, PIN, HIGH);
	}

}