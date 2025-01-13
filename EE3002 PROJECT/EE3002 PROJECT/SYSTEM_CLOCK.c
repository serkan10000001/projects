#include <stdint.h> /*Library for uint numbers*/
#include "stm32f10x.h" /*Library for register masks*/

/*System Clock*/ /*8MHZ HSE is used as PLLCLK entry */
#define HSEON (1U << 16)
#define HSEREADY (1U << 17)
#define RESET 0
#define SET 1
//#define HSESTATUS 0
#define PLLON (1U << 24)
#define PLLREADY (1U << 25)
//#define PLLSTATUS 0
#define PLLSOURCE (1U << 16)
#define PLLMULL (0x7 << 18)
#define SYSTEMCLOCKSWITCH_RESET (0x3 << 0)
#define SYSTEMCLOCKSWTICH_PLL (1U << 1)
#define SYSTEMCLOCKSWITCHSTATUS (0xC <<0) 
/*System Clock Initilization Function*/
void systemClocktoPLL_72MHZ(void){
	RCC->CR |= HSEON;
	while ((RCC->CR & HSEREADY) != SET);
	RCC->CR &= ~(PLLON);
	while ((RCC->CR & PLLREADY) != RESET);
	RCC->CFGR |= PLLSOURCE;
	RCC->CFGR |= PLLMULL;
	RCC->CR |= PLLON;
	while ((RCC->CR & PLLREADY) == SET)
	RCC->CFGR &=~ (SYSTEMCLOCKSWITCH_RESET);
	RCC->CFGR |= SYSTEMCLOCKSWTICH_PLL;
	while ((RCC->CFGR & SYSTEMCLOCKSWITCHSTATUS) != SET);
}
