#include "drv_GPIO.h"
#include "drv_timer.h"
#include "stm32l475xx.h"

extern uint32_t SystemCoreClock; 


#define uRESET           0U
#define uSET             1U

#define BUTTON_PIN       (uint32_t)(1 << 13U)
#define BUTTON_STATUS    (GPIOC->IDR & BUTTON_PIN)

#define LED1_PIN         (uint32_t)(1 << 5U)
#define LED1_STATUS      (GPIOA->ODR & LED1_PIN)

#define LED2_PIN         (uint32_t)(1 << 14U)
#define LED2_STATUS      (GPIOB->ODR & LED2_PIN)

static void init_LED1(void);
static void init_LED2(void);
static void set_led1(bool pStatus);
static void set_led2(bool pStatus);
static void toggle_led1(void);
static void toggle_led2(void);
static bool button_debounce_check(uint32_t pDuration);
static void LED1_blink(uint32_t period);

static void init_LED1(void){
	//LED1_PORT_ENABLE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	//LED1_AS_OUTPUT
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);
	GPIOA->MODER |= GPIO_MODER_MODE5_0;
}

static void init_LED2(void){
	//LED2_PORT_ENABLE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	//LED2_AS_OUTPUT
	GPIOB->MODER &= ~(GPIO_MODER_MODE14);
	GPIOB->MODER |= GPIO_MODER_MODE14_0;
}

static void LED1_blink(uint32_t period){
	//LED1_PORT_ENABLE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	//LED1_AS_OUTPUT
	GPIOA->MODER &= ~(GPIO_MODER_MODE5);
	GPIOA->MODER |= GPIO_MODER_MODE5_1;
	GPIOA->AFR[0] |= GPIO_AFRL_AFSEL5_0;
	pwm_output_timer2_ch1(period);
}



void drv_GPIO_init_button(void){
	//BUTTON_PORT_ENABLE
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOCEN;
	//BUTTON_AS_INPUT
	GPIOC->MODER &= ~(GPIO_MODER_MODE13);
}

void drv_GPIO_init_LED(nLED pLED){
	switch(pLED)
	{
		case LED1:
			init_LED1();
			break;
		case LED2:
			init_LED2();
			break;
		case BOTH:
			init_LED1();
			init_LED2();
			break;
	}
}

void drv_GPIO_set_LED(nLED pLED, bool pStatus){
	
	switch(pLED)
	{
		case LED1:
			set_led1(pStatus);
			break;
		case LED2:
			set_led2(pStatus);
			break;
		case BOTH:
			set_led1(pStatus);
			set_led2(pStatus);
			break;
	}
}

void drv_GPIO_blink_LED(nLED pLED, uint32_t period){
	
	switch(pLED)
	{
		case LED1:
			LED1_blink(period);
			break;
	}
}

void drv_GPIO_toggle_LED(nLED pLED){
	
	switch(pLED)
	{
		case LED1:
			toggle_led1();
			break;
		case LED2:
			toggle_led2();
			break;
		case BOTH:
			toggle_led1();
			toggle_led2();
			break;
	}
}
bool drv_GPIO_button_status(void){
	if(BUTTON_STATUS == uRESET){
		return button_debounce_check(5);
	}
	return false;
}


static void set_led1(bool pStatus){
	if(pStatus == true){
		GPIOA->BSRR = GPIO_BSRR_BS5;
	}
	else{
		GPIOA->BSRR = GPIO_BSRR_BR5;
	}
	
}
static void set_led2(bool pStatus){
	if(pStatus == true){
		GPIOB->BSRR = GPIO_BSRR_BS14;
	}
	else{
		GPIOB->BSRR = GPIO_BSRR_BR14;
	}
	
}

static void toggle_led1(void){
	set_led1((bool)!LED1_STATUS);

}
static void toggle_led2(void){
	set_led2((bool)!LED2_STATUS);
}
static bool button_debounce_check(uint32_t pDuration){
	
	uint32_t counter = (SystemCoreClock/1000) * pDuration;
	while(counter && (BUTTON_STATUS == uRESET)){
		counter--;
	}
	return (counter == 0);	
}



