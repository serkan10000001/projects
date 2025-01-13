 /*NOTES 
	-Trigger Pulse is 10uS
	-TX will send out 8 burst of 40kHz ultrasound
	-and echo pin receives reflected sound
	-Echo pulse is proportional with range
	-Pulse witdh(high time) is 180uS to 18mS, but if no object in the range, high time will be approximately 36mS
	-Arrange a 10ms after echo pin goes low to send new trigger signal 
	-Apporximately formula is uS/58 = cm 
	-or is the range = high_level_time*soundVelocity / 2
	-Suggesting to use over 60ms measurement cycle 
	-The RCC feeds the Cortex® System Timer (SysTick) external clock with the AHB clock 
	 (HCLK) divided by 8.
	*****Application*****
		-Trigger can be sent over a GPIO pin
		-Pin can be triggered from low to high with a high time 10us 
		-Systick can be used to delay toggle 
		
		-Pulse width can be measured by using timers
		-Simple algorithm can be written here to calculate the distance 
		
	*****Important Mesaurements*****
		-Measure cylce can be choosen as 62ms 
		-Calibration required by testing the code
*/

/*NOTES FOR OLED SCREEN DRIVER*/

PIN 1		VSS			Ground
PIN 2		VDD 		Power Supply for logic operating 
PIN 3		V0			Adjusting Supply Voltage for lcd driving
PIN 15		A(LED+) 	Power Supply For back light
PIN 16		A(LED-) 	The backlight ground

PIN 4 		RS 			Signal for selecting registers 1=Data Register for read and write 0=Instruction register(for write), Busy Flag Address counter(for read)
PIN 5		R/W 		H=Read Mode L=Write Mode
PIN 6		E 			An enable signal for writing and reading data

PIN 7-14 	DB0-DB7 	8-bit bi-directional databus

RS is high for Displayed Data on the screen 
RS is low for writing instruction register 

*****LCD OPERATION*****
First select the mode Read/Write
Then RS is goes low by software because of writing on registers
Wait 10us 
Set E as High
Wait 10us 
Send data from DB0-DB7 
Wait 10us
Reset E 
	
*****************SPI************************
Serial Peripheral Interface
Master and Slave 
4 wires for per Slave 

Pins 
	Master Output Slave Input MOSI - Data sent from master 
	Master Input Slave Output MISO - Data sent from slave/receiving data 
	Clock - Sync
	Select  

On the MCU 
	PA4 - SPI1_NSS
	PA5	- SPI1_SCK
	PA6 - SPI1_MISO 
	PA7 - SPI1_MOSI

	PB12 - SPI1_NSS
	PB13 - SPI1_SCK
	PB14 - SPI1_MISO 
	PB15 - SPI1_MOSI

SPI AND AFIO CLOCK 

I stoped here because it will not effect the project, i will study I2C

****************************** I2C ******************************
/*
	SDA - Signal Data
	SCL - Clock
	
*/

100kb/s (standart mode) 400kb/s (Fast Mode)

At first MCU makes a Start Condition 
Then MCU send 8 bit address 
This adress read from all devices that connect to MCU master 
With 8 bit address MCU sends R/W bit 
After that Devices sends ACK/NACK bit
after that Every time 8 bit data sent from MCU plus again ACK/NACK bit 
If the communication stop, MCU makes a Stop condition 























	
