#ifndef TIMER1_H_
#define TIMER1_H_
#include "stm32f10x.h"
#include "GPIO_DRIVER.h"

void timer1Delay_micros(int micros);
void timer1Delay_milis(int milis);
void timer1PWM_micros(int period, int pwm);
void timer1PWM_milis(int period, int pwm);
void timer1Capture_micro(int period);
void timer1Capture_milis(int period);
int timer1_get_capture_micro(void);
int timer1_get_capture_milis(void);
void timer1PWM_milisBUZZER(int period, int pwm);
#endif