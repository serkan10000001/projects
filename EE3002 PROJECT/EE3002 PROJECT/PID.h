#ifndef PID_H_
#define PID_H_
#include "MOTOR_DRIVER.h"
#include <stdint.h>
#include <math.h>
void PID_Linefollow(int error, int distance);
//int motor_control(int sensorData[5]);
#endif