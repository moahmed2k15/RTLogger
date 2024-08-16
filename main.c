#include "stm32l475xx.h"
#include <stdint.h>



#define BUTTON_PIN  (uint32_t)(1<<13U)
#define uRESET      0U
#define uSET        1U

int main(void)
{
	//LED1_PORT_ENABLE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	//LED1_AS_OUTPUT
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
	//BUTTON_PORT_ENABLE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	//BUTTON_AS_INPUT
	GPIOC->MODER &= ~(GPIO_MODER_MODE13);
	
	while(1){
		if((GPIOC->IDR & BUTTON_PIN) == uRESET){
			GPIOA->BSRR = GPIO_BSRR_BS5;
		}
		else{
			GPIOA->BSRR = GPIO_BSRR_BR5;
		}
	}

}
