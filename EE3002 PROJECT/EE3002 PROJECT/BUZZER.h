#ifndef BUZZER_H
#define BUZZER_H
#include "GPIO_DRIVER.h"
void timer3PWM_milis(int period, int pwm);
void timer3PWM_micros(int period, int pwm);
void timer3Delay_milis(int milis);
void timer3delay_micros(int micros);
#endif 