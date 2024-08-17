#include "drv_timer.h"
#include "stm32l475xx.h"

extern uint32_t SystemCoreClock; 


void pwm_output_timer2_ch1(uint32_t period){
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN;	
	__ASM("nop");
	__ASM("nop");
	TIM2->PSC = (SystemCoreClock/1000) - 1; //1000Hz Clock
	TIM2->ARR = (period *1000) - 1;
	TIM2->CR1 |= TIM_CR1_UDIS;
	/* The TIM2 timer channel 1 after reset is configured as output */
	/* TIM2->CC2S reset value is 0 */
	/* To select PWM2 output mode set the OC1M control bit-field to '111' */
	TIM2->CCMR1 |= TIM_CCMR1_OC1M_0 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
	/* Set the duty cycle to 50% */
	TIM2->CCR1 = TIM2->ARR / 2;
	/* By default, after reset, preload for channel 1 is turned off */
	/* To change it uncomment the below line */
	/* TIM2->CCMR1 |= TIM_CCMR1_OC1PE; */
	/* Enable the TIM2 channel1 and keep the default configuration (state after
	reset) for channel polarity */
	TIM2->CCER |= TIM_CCER_CC1E;
	/* Start the timer counter */
	TIM2->CR1 |= TIM_CR1_CEN;
}
