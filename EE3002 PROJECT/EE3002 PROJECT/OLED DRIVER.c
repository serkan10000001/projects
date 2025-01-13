#include "OLED DRIVER.h"
/*
	Pin Setup
	
	PA8 - RS
	PA9	- RW
	PA10 - E
	
	PA0 - DB0
 	PA1 - DB1
	PA2 - DB2
	PA3 - DB3
	PA4 - DB4
	PA5 - DB5
	PA6 - DB6
	PA7 - DB7
*/

void Pin_Setup(void){
	char i; 
	for(i = 0; i < 11; i++){
		gpio_init(PB, i, OUT50, G_PP);
	}
}

/*Register selection for RS pin*/
void lcd_rs(uint32_t level){
	WRITE_GPIO(PB, 8, level);
}
/*Read/Write mode selection for RW pin*/
void lcd_rw(uint32_t level){
	WRITE_GPIO(PB, 9, level);
}
/*Enable operation for E pin*/
void lcd_e(uint32_t level){
	WRITE_GPIO(PB, 10, level);
}

/*LCD DATA*/
void lcd_data(unsigned char data){

	lcd_rs(HIGH);
	lcd_rw(LOW);
	SysTick_DelayMc(40);
	lcd_e(HIGH);
	SysTick_DelayMc(25);
	GPIOB->ODR &= 0xFF00; /*clearing first 8bit data*/
	GPIOB->ODR |= data;
	SysTick_DelayMc(10);
	lcd_e(LOW);
}
/*LCD COMMAND*/
void lcd_cmd(unsigned char data){

	lcd_rs(LOW);
	lcd_rw(LOW);
	SysTick_DelayMc(40);
	lcd_e(HIGH);
	SysTick_DelayMc(25);
	GPIOB->ODR &= 0xFF00; /*clearing first 8bit data*/
	GPIOB->ODR |= data;
	SysTick_DelayMc(10);
	lcd_e(LOW);
}
/*LCD INITILIZATION*/
void lcd_init(void){
	 Pin_Setup();
	 SysTick_DelayMs(20);
	 lcd_cmd(0x3C); // 8bit communication
	 SysTick_DelayMc(5);
	 lcd_cmd(0x0F);	// Display On 
	 SysTick_DelayMc(5);
	 lcd_cmd(0x01);	// Clear Display
	 SysTick_DelayMs(5);
	 lcd_cmd(0x02);	// Get Back to Initial
	 SysTick_DelayMs(5);
	 
}
/*Data Sentence*/
void lcd_send(char str[]){
	int j = 0;
	while(str[j]){
		lcd_data(str[j]);
		j++;
		SysTick_DelayMc(100);
	}

}


void PCF8574T_add(char i2c, char RW){
	I2C_ADDRESS(i2c, 0x4E, RW);
}

void PCF8574T_tx(char i2c, char data){
	I2C_START(i2c);
	PCF8574T_add(i2c, 0); // 0 fow writing data
	I2C_DATA(i2c, data);
	I2C_STOP(i2c);
}

void lcd_i2c_data(char i2c, unsigned char data){
	
	//lcd_rs(HIGH);
	//lcd_rw(LOW);
	PCF8574T_tx(i2c, 0x09);
	SysTick_DelayMc(40);
	//lcd_e(HIGH);
	PCF8574T_tx(i2c, 0x0D);
	SysTick_DelayMc(25);
//	GPIOB->ODR &= 0xFF00; /*clearing first 8bit data*/
//	GPIOB->ODR |= data ;
	PCF8574T_tx(i2c, ((data & 0x00f0) | 0x0D));
	SysTick_DelayMc(10);
	//lcd_e(LOW);
	PCF8574T_tx(i2c, ((data & 0x00f0) | 0x09));
	SysTick_DelayMc(20);
	PCF8574T_tx(i2c, 0x0D);
	SysTick_DelayMc(5);
	PCF8574T_tx(i2c, (((data << 4) & 0x00f0) | 0x0D));
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, (((data << 4) & 0x00f0) | 0x09));
}

void lcd_i2c_cmd(char i2c, unsigned char data){
	//lcd_rs(HIGH);
	//lcd_rw(LOW);
	PCF8574T_tx(i2c, 0x08);
	SysTick_DelayMc(40);
	//lcd_e(HIGH);
	PCF8574T_tx(i2c, 0x0C);
	SysTick_DelayMc(25);
//	GPIOB->ODR &= 0xFF00; /*clearing first 8bit data*/
//	GPIOB->ODR |= data ;
	PCF8574T_tx(i2c, ((data & 0x00f0) | 0x0C));
	SysTick_DelayMc(10);
	//lcd_e(LOW);
	PCF8574T_tx(i2c, ((data & 0x00f0) | 0x08));
	SysTick_DelayMc(20);
	PCF8574T_tx(i2c, 0x0C);
	SysTick_DelayMc(5);
	PCF8574T_tx(i2c, (((data << 4) & 0x00f0) | 0x0C));
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, (((data << 4) & 0x00f0) | 0x08));
}

void lcd_i2c_init(char i2c){
	I2C_INIT(i2c, FM);
	SysTick_DelayMc(20);
	PCF8574T_tx(i2c, 0x08);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x09);
	SysTick_DelayMc(5); // caution 
	PCF8574T_tx(i2c, 0x3C);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x38);
	
	SysTick_DelayMc(10);
	
	PCF8574T_tx(i2c, 0x08);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x0C);
	SysTick_DelayMc(5);
	PCF8574T_tx(i2c, 0x3C);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x38);
	
	SysTick_DelayMc(1);
	
	PCF8574T_tx(i2c, 0x08);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x0C);
	SysTick_DelayMc(5);
	PCF8574T_tx(i2c, 0x3C);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x38);
	
	SysTick_DelayMc(1);
	
	PCF8574T_tx(i2c, 0x08);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x0C);
	SysTick_DelayMc(5);
	PCF8574T_tx(i2c, 0x2C);
	SysTick_DelayMc(10);
	PCF8574T_tx(i2c, 0x28);
	
	lcd_i2c_cmd(i2c, 0x2C);
	SysTick_DelayMc(5);
	lcd_i2c_cmd(i2c, 0x0C);
	SysTick_DelayMc(5);
	lcd_i2c_cmd(i2c, 0x01);
	SysTick_DelayMc(10);
	lcd_i2c_cmd(i2c, 0x02);
	SysTick_DelayMc(5);
}


void lcd_i2c_send(char i2c, char str[]){
		int j = 0;
	while(str[j]){
		lcd_i2c_data(i2c, str[j]);
		j++;
		SysTick_DelayMc(100);
	}
}

void lcd_i2c_msg(char i2c, unsigned char line12, unsigned char pos0_16, char msg[]){

	short pos = 0;
	if(line12 == 1){
		pos = 0;
	}else if(line12 == 2){
		pos = 0x40;
	}
	lcd_i2c_cmd(i2c, 0x80 + pos + pos0_16);
	SysTick_DelayMc(100);
	lcd_i2c_send(i2c, msg);
}

void lcd_1_blank(char i2c){
	lcd_i2c_msg(i2c, 1, 0, "                ");
}
void lcd_2_blank(char i2c){
	lcd_i2c_msg(i2c, 2, 0, "                ");
}
void lcd_12_blank(char i2c){
	lcd_1_blank(i2c);
	lcd_2_blank(i2c);
}



void str_empty(char str[])
{
	int i = 0;
	while(str[i] != '\0')
	{
		str[i] = '\0';
		i++;
	}
	
}

void int2char(int num, char str[])
{
char lstr[30];
int cnt = 0;
int div = 10;
int j = 0;
int neg = 0;
	
	if(num<0)
	{
		num=-num;
		neg = 1;
	}

while( num >= div)
{
	lstr[cnt] = num % div + 0x30;
	num /= 10;
	cnt++;
}

	lstr[cnt] = num + 0x30;

	if(neg)
	{
		cnt++;
		lstr[cnt] = '-';
	}
for(j= cnt ; j >=0;j--)
{
	str[cnt-j] = lstr[j];
}

}