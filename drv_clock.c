#include "drv_clock.h"
extern uint32_t SystemCoreClock; 


void delay_ms(uint32_t pTime){
	uint32_t counter = (SystemCoreClock/1000) * pTime;
	while(counter--);
}
