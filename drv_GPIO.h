#include <stdbool.h>
#include <stdint.h>
typedef enum {
	LED1 = 0,
	LED2 = 1,
	BOTH = 2,
} nLED;

void drv_GPIO_init_LED(nLED pLED);
void drv_GPIO_set_LED(nLED pLED, bool pStatus);
void drv_GPIO_toggle_LED(nLED pLED);

void drv_GPIO_init_button(void);
bool drv_GPIO_button_status(void);

void drv_GPIO_blink_LED(nLED pLED, uint32_t period);
