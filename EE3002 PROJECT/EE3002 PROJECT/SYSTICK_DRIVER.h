#ifndef SYSTICK_H_
#define SYSTICK_H_
#include "stm32f10x.h"
#define SYSTICK_LOAD 72 - 1
#define SYSTICK_VAL 0
#define SYSTICK_ENABLE (1U << 0)
#define SYSTICK_CLOCK_SOURCE (1U << 2)

/*SysTick Register Adresses*/
#define SYSTICK_CSR (*(volatile unsigned int*)(0xE000E010))
#define SYSTICK_RVR (*(volatile unsigned int*)(0xE000E014))
#define SYSTICK_CVR (*(volatile unsigned int*)(0xE000E018))

void systickTimer_init(void);
void SysTick_DelayMicro(void);
void SysTick_DelayMc(uint32_t t);
void SysTick_DelayMs(uint32_t t);
#endif