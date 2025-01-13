#include "I2C_DRIVER.h"

/*
	PB10 I2C2_SCL
	PB11 I2C2_SDA
	PB12 I2C2_SMBAI
	
	PB5 I2C1_SMBAI 
	PB6 I2C1_SCL
	PB7 I2C1_SDA
	
	I2C1 and I2C2 are on the APB1 BUS 
	
	RCC APB1ENR BIT 21 and 22 

*/

void I2C_INIT(char i2c, unsigned short SPEED){
		RCC->APB2ENR |= 1;
	if(i2c == 1){
			RCC->APB1ENR |= (1U << 21);
			gpio_init(PB, 6, OUT50, AF_OD);
			gpio_init(PB, 7, OUT50, AF_OD);
			I2C1->CR1 |= 0x8000; // I2C is under the reset state
			I2C1->CR1 &= ~(0x8000); // Clear that reset state
			I2C1->CR2 |= 0x8; // Set the frequency
			I2C1->CCR = SPEED;
			I2C1->TRISE = 0x9;
			I2C1->CR1 |= (1U << 0);
	}else if(i2c == 2){
			RCC->APB1ENR |= (1U << 22);
			gpio_init(PB, 10, OUT50, AF_OD);
			gpio_init(PB, 11, OUT50, AF_OD);
			I2C2->CR1 |= 0x8000; // I2C is under the reset state
			I2C2->CR1 &= ~(0x8000); // Clear that reset state
			I2C2->CR2 |= 0x8; // Set the frequency
			I2C2->CCR = SPEED;
			I2C2->TRISE = 0x9;
			I2C2->CR1 |= (1U << 0);
	}
}



void I2C_START(char i2c){
	if(i2c == 1){
		I2C1->CR1 |= (1U << 8);
		while(!(I2C1->SR1 & (1U << 0)));
	}else if(i2c == 2){
		I2C2->CR1 |= (1U << 8);
		while(!(I2C2->SR1 & (1U << 0)));
	}
}

void I2C_ADDRESS(char i2c, char ADDRESS, char RW){
	volatile int temp;
	if(i2c == 1){
		I2C1->DR = (ADDRESS | RW);
		while((I2C1->SR1 & (1U << 1)) == 0);
		while((I2C1->SR1 & (1U << 1))){
			temp = I2C1->SR1;
			temp = I2C1->SR2;
			if((I2C1->SR1 & (1U << 1)) == 0){
				break;
			}
		} 
	}else if(i2c == 2){
		I2C2->DR = (ADDRESS | RW);
		while((I2C2->SR1 & (1U << 1)) == 0);
		while((I2C2->SR1 & (1U << 1))){
			temp = I2C2->SR1;
			temp = I2C2->SR2;
			if((I2C2->SR1 & (1U << 1)) == 0){
				break;
			}
		} 
	}
}

void I2C_DATA(char i2c, char data){
	if(i2c == 1){
		while((I2C1->SR1 & 0x80) == 0){}
			I2C1->DR = data;
		while((I2C1->SR1 & 0x80) == 0){}
	}else if(i2c == 2){
		while((I2C2->SR1 & 0x80) == 0){}
			I2C2->DR = data;
		while((I2C2->SR1 & 0x80) == 0){}
	}

}

void I2C_STOP(char i2c){
	volatile int temp;
	if(i2c == 1){
		temp = I2C1->SR1;
		temp = I2C1->SR2;
		I2C1->CR1 |= 0x200;
	}else if(i2c == 2){
		temp = I2C2->SR1;
		temp = I2C2->SR2;
		I2C2->CR1 |= 0x200;
	}
}

void I2C_WRITE(char i2c, char ADDRESS, char data[]){
	int i = 0;
	I2C_START(i2c);
	I2C_ADDRESS(i2c, ADDRESS, 0);
	while(data[i]){
	I2C_DATA(i2c, data[i]);
	}
	I2C_STOP(i2c);
}