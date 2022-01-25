#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"


#define LED_PIN 2
#define BUTTON_PIN 4


static void  gpio_button_handler(void* arg)
{
    uint32_t gpio_val=0;
    gpio_val=gpio_get_level(LED_PIN);
    gpio_val=!gpio_val;
    gpio_set_level(LED_PIN,gpio_val);
}


void _gpio_config()
{

    ESP_ERROR_CHECK(gpio_reset_pin(LED_PIN));

    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT));

    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN));

    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN,GPIO_MODE_INPUT));



    ESP_ERROR_CHECK(gpio_intr_enable(BUTTON_PIN));
    ESP_ERROR_CHECK(gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_ANYEDGE));
    

    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE));

    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, gpio_button_handler,NULL));
    

}

static void gpio_task_example(void* arg)
{
    uint32_t button_val;
    for(;;) {
        button_val=gpio_get_level(BUTTON_PIN);
        printf("button press -->%d\n",button_val);
        printf("in task\n");
        vTaskDelay(pdMS_TO_TICKS(400));
    }
}

void app_main(void)
{
    printf("configuring gpio\n");
    _gpio_config();
    printf("gpio configured\n");
    
    //start gpio task
    BaseType_t result;
    result=xTaskCreate(gpio_task_example, "gpio_task_example", 2048, NULL, 10, NULL);
    if(result == pdPASS)
    {
        printf("task1 created");
    }
    else{
        printf("unable to create task");
        perror("error while creating task: ");
        return;
    }
}
