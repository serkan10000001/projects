#ifndef MOTOR_H_
#define MOTOR_H_
#include <stm32f10x.h>
#include "GPIO_DRIVER.h"
void timer4_pwm_microsV(int period, int pwm1, int pwm2);
void timer4_pwm_milisV(int period, int pwm1, int pwm2);
void position(unsigned short M1F, unsigned short M1B, unsigned short M2F, unsigned short M2B);
#define FORWARD 1 
#define BACKWARD 0
#endif