#include "ADC_DRIVER.h"
#include "MOTOR_DRIVER.h"
#include "TIMER1_DRIVER.h"
#include "PID.h"
#include "OLED DRIVER.h"
#include "BUZZER.h"
int myDistance; /*STAYS*/
int normalized[7];
char adc_channelsA[17] = {PA0, PA1, PA4, PB0, PC1, PC0, PC3};
int buzzz = 0;
int analog_rxA[7];

char channelsA = 7 ;
char myint[3];
char display[3];
int p = 0;
int motor_control(int  normalized[7]){
	int sum = 0;
	int positionU = 0; 

	for(int i = 0; i <= 6; i++){
		sum += normalized[i];
		positionU += (normalized[i] * i * 1000);
		}
	int positionF = (positionU / sum);
	int error = 3000 - positionF;
	return error;
}


void normalize_line_readings(int *raw, int *normalized, int numSensors)
{
    int maxVal   = -1;
    int maxIndex = 0;

    // 1. Find the sensor with the highest reading
    for (int i = 0; i < numSensors; i++) {
        if (raw[i] > maxVal) {
            maxVal   = raw[i];
            maxIndex = i;
        }
    }

    // 2. Set only that inex to 1000, others to 0
    for (int i = 0; i < numSensors; i++) {
        if (i == maxIndex) {
            normalized[i] = 1000;
        } else {
            normalized[i] = 0;
        }
    }
}

int main(void){
	systickTimer_init();
	adc_multi_ch_init(adc1, channelsA, adc_channelsA);

	gpio_init(PA, 8, OUT50, AF_PP); /*4 Lines are for reading distance STAYS*/
	gpio_init(PA, 9, IN, I_PP);
	gpio_init(PA, 10, OUT50, AF_PP);
	gpio_init(PA, 6, OUT50, AF_PP);
	
	
	
	
	timer1PWM_micros(61000, 10);
	timer1Capture_micro(61000);
	
//	AFIO->MAPR |= (1U << 1);
//	gpio_init(PB, 8, OUT50, AF_OD);
//	gpio_init(PB, 9, OUT50, AF_OD);

//	  lcd_i2c_init(1);
//		SysTick_DelayMs(100);
//	  lcd_i2c_msg(1, 1, 0, "Distance:			cm");
//		lcd_i2c_msg(1, 2, 0, "tr 38 TEKNOF 31");
	while(1){
		
			myDistance = (timer1_get_capture_micro() - 204) / 58; /*STAYS*/
			adc_multi_ch_rx(adc1, channelsA, adc_channelsA, analog_rxA);
			normalize_line_readings(analog_rxA, normalized, 7);
			p = motor_control(normalized);
			PID_Linefollow(p, myDistance);
			if(myDistance < 20){
			   timer3PWM_micros(2000000, 1500000);
			}else{
				 timer3PWM_micros(1000, 0);
			}
//			if(myDistance > 20){
//				PID_Linefollow(p);
//			}else if(myDistance <= 20){
//			position(FORWARD, BACKWARD, FORWARD, BACKWARD);
//		    timer4_pwm_microsV(1000, 0, 0);
//		}
			
		
		
//		int2char(myDistance, myint);
//		
//		if(myDistance < 10){
//			display[0] = ' ';
//			display[1] = ' ';
//			display[2] = myint[0];
//			lcd_i2c_msg(1, 1, 9, display);
//		}else if (myDistance < 100){
//			display[0] = ' ';
//			display[1] = myint[0];
//			display[2] = myint[1];
//			lcd_i2c_msg(1, 1, 9, display);
//		}else{
//			display[0] = myint[0];
//			display[1] = myint[1];
//			display[2] = myint[2];
//			lcd_i2c_msg(1, 1, 9, display);
//		}
//			str_empty(myint);
//		
		
		
  }
}
















































//#include "TIMER1_DRIVER.h"
//#include "GPIO_DRIVER.h"
//#include "OLED DRIVER.h"

////	PB6 I2C1_SCL OD
////	PB7 I2C1_SDA OD

//char myint[3];
//char display[3];
//int captureM = 0;

// int main(void){
//		gpio_init(PB, 6, OUT50, AF_OD);
//	  gpio_init(PB, 7, OUT50, AF_OD);
//		systickTimer_init();

//		lcd_i2c_init(1);
//		SysTick_DelayMs(100);
//	  lcd_i2c_msg(1, 1, 0, "ILY");
//	  //lcd_i2c_msg(1, 2, 0, "                                ");
//	  gpio_init(PA, 8, OUT50, AF_PP);
//	  gpio_init(PA, 9, IN, I_PP);
//	  timer1PWM_micros(61000, 10); 
//		timer1Capture_micro(61000); // 2269
//	
//	while(1){
//		
//		captureM = (timer1_get_capture_micro() - 2269) / 58;
//		int2char(captureM, myint);
//		
//		if(captureM < 10){
//			display[0] = ' ';
//			display[1] = ' ';
//			display[2] = myint[0];
//			lcd_i2c_msg(1, 1, 9, display);
//		}else if (captureM < 100){
//			display[0] = ' ';
//			display[1] = myint[0];
//			display[2] = myint[1];
//			lcd_i2c_msg(1, 1, 9, display);
//		}else{
//			display[0] = myint[0];
//			display[1] = myint[1];
//			display[2] = myint[2];
//			lcd_i2c_msg(1, 1, 9, display);
//		}
//			str_empty(myint);
//			
//	
//	}	
//}
//	