#include <stdint.h>
#include "stm32l475xx.h"
#include "drv_GPIO.h"
#include "drv_clock.h"

GPIO_TypeDef * PORTA = ((GPIO_TypeDef *) GPIOA_BASE);
int main(void)
{
	
	//drv_GPIO_init_LED(BOTH);
	drv_GPIO_init_button();
	//drv_GPIO_set_LED(LED1, true);
	//drv_GPIO_set_LED(LED2, false);
	drv_GPIO_blink_LED(LED1, 10000);
	
	while(1){
		PORTA->MODER |= 1;
			
	}

}
