#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#define LED_PIN_1 5
#define LED_PIN_2 16
#define LED_PIN_3 17


uint32_t gpio_val[3];

TaskHandle_t task_handler;

void _gpio_config()
{

	gpio_config_t led_config = {};

	led_config.pin_bit_mask = (1ULL << LED_PIN_1) |(1ULL << LED_PIN_2) | (1ULL << LED_PIN_3) ;
	
	led_config[i].mode = GPIO_MODE_OUTPUT;
	led_config[i].pull_up_en = GPIO_PULLUP_ENABLE;
	led_config[i].pull_down_en = GPIO_PULLDOWN_DISABLE;
	led_config[i].intr_type = GPIO_INTR_DISABLE;
	ESP_ERROR_CHECK(gpio_config(&led_config[i]));



}

static void gpio_task_example(void* arg)
{
	_gpio_config();

	gpio_val[0] = gpio_get_level(LED_PIN_1);
	gpio_val[1] = gpio_get_level(LED_PIN_2);
	gpio_val[2] = gpio_get_level(LED_PIN_3);

    for(;;) {
		gpio_set_level(LED_PIN_1,gpio_val[0]);
		gpio_val[0] = !gpio_val[0];

		gpio_set_level(LED_PIN_2,gpio_val[1]);
		gpio_val[1] = !gpio_val[1];

		gpio_set_level(LED_PIN_3,gpio_val[2]);
		gpio_val[2] = !gpio_val[2];

		vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

void app_main(void)
{
    
    //start gpio task
    BaseType_t result;
	
    result=xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 2, &task_handler);
    if(result == pdPASS)
    {
        printf("task1 created\n");
    }
    else{
        printf("unable to create task");
		exit(EXIT_FAILURE);
    }
}
