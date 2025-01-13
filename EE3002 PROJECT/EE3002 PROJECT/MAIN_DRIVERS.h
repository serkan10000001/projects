#ifndef DRIVER_H_
#define DRIVER_H_
#include <stdint.h>
#include "stm32f10x.h"
void systemClocktoPLL_72MHZ(void);
void systickTimer_init(void);
void SysTick_DelayMs(uint32_t t);
void SysTick_DelayMc(uint32_t t);
void timer1Delay_micros(int micros);
void timer1Delay_milis(int milis);
void timer1PWM_micros(int period, int pwm);
void timer1Capture_micro(int period);
void timer1Capture_milis(int period);
int timer1_get_capture_micro(void);
int timer1_get_capture_milis(void);
#endif