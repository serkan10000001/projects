#ifndef I2C_H_
#define I2C_H_
#include <stm32f10x.h>
#include "GPIO_DRIVER.h"


#define SM 0xB4
#define FM 0x2d
void I2C_INIT(char i2c, unsigned short SPEED);
void I2C_WRITE(char i2c, char ADDRESS, char data[]);
void I2C_START(char i2c);
void I2C_ADDRESS(char i2c, char ADDRESS, char RW);
void I2C_DATA(char i2c, char data);
void I2C_STOP(char i2c);
#endif