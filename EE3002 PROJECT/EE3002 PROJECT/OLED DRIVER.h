#ifndef OLED_H_
#define OLED_H_
#include "GPIO_DRIVER.h"
#include "I2C_DRIVER.h"
#include "SYSTICK_DRIVER.h"
void Pin_Setup(void);
void lcd_init(void);
void lcd_data(unsigned char data);
void lcd_cmd(unsigned char data);
void lcd_send(char str[]);

void PCF8574T_add(char i2c, char RW);
void PCF8574T_tx(char i2c, char data);
void lcd_i2c_data(char i2c, unsigned char data);
void lcd_i2c_cmd(char i2c, unsigned char data);
void lcd_i2c_init(char i2c);
void lcd_i2c_send(char i2c, char str[]);
void lcd_i2c_msg(char i2c, unsigned char line12, unsigned char pos0_16, char msg[]);
void lcd_1_blank(char i2c);
void lcd_2_blank(char i2c);
void lcd_12_blank(char i2c);
void int2char(int num, char str[]);
void str_empty(char str[]);
#endif