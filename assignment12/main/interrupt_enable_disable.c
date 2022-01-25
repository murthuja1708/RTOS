#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include<errno.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/timers.h"
#include "freertos/queue.h"
#include "driver/gpio.h"

#define LED_PIN 5
#define BUTTON_PIN 4
#define BUTTON_PIN2 18 

TimerHandle_t xTimers;
QueueHandle_t str_queue;

TaskHandle_t task_handler;

static const char* random_data[6] = {
		"sending\r\n",
		"data\r\n",
		"from\r\n",
		"isr\r\n",
		"to\r\n",
		"queue\r\n"
	};

volatile uint32_t gpio_val=0;
static void IRAM_ATTR  gpio_button_handler(void* arg)
{
	portDISABLE_INTERRUPTS();

	gpio_val = (gpio_val == 0 ?1:0);
    gpio_set_level(LED_PIN,gpio_val);
	portENABLE_INTERRUPTS();
}


void IRAM_ATTR pin_interrupt_handler(void* args)
{

	BaseType_t pxHigherPriorityTaskWoken = pdFALSE;

	for(uint8_t i=0;i<6;i++)
	{
		xQueueSendFromISR(str_queue,random_data[i],&pxHigherPriorityTaskWoken);
	}
	//gpio_set_level(BUTTON_PIN2,1);
}

void _gpio_config()
{

    ESP_ERROR_CHECK(gpio_reset_pin(LED_PIN));

    ESP_ERROR_CHECK(gpio_set_direction(LED_PIN,GPIO_MODE_OUTPUT));

    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN2));

    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN2,GPIO_MODE_INPUT));

    ESP_ERROR_CHECK(gpio_intr_enable(BUTTON_PIN2));

    ESP_ERROR_CHECK(gpio_set_intr_type(BUTTON_PIN2, GPIO_INTR_ANYEDGE));
    

    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE));

    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN2, pin_interrupt_handler,NULL));

    ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN));

    ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN,GPIO_MODE_INPUT));



    ESP_ERROR_CHECK(gpio_intr_enable(BUTTON_PIN));

    ESP_ERROR_CHECK(gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_NEGEDGE));
    

    //ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE));

    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, gpio_button_handler,NULL));
    

}

static void gpio_task_example(void* arg)
{
    uint32_t button_val;
	uint32_t intr_value;
	
	char buffer[20];

    for(;;) {
        button_val = gpio_get_level(BUTTON_PIN);
		intr_value = gpio_get_level(BUTTON_PIN2);

        printf("button press -->%d\ngpio_val --> %d\nintr_value ---> %d\n",button_val,gpio_val,intr_value);
		if(intr_value == 1 )
		{
			printf("resetting interrupt pin\n");

			gpio_set_level(BUTTON_PIN2,0);
			intr_value = gpio_get_level(BUTTON_PIN2);

			printf("after resetting intr_value --> %d\n",intr_value);

			vTaskDelay(pdMS_TO_TICKS(1000));
			
			printf("trying to receive data from queue\n");

	        while( xQueueReceive(str_queue,buffer,portMAX_DELAY))
			{
				printf("%s",buffer);
			}
		}

        vTaskDelay(pdMS_TO_TICKS(100));
    }
}

void app_main(void)
{
    
    //start gpio task
    BaseType_t result;
	
	_gpio_config();
	str_queue = xQueueCreate(6,20);
	 if( str_queue == NULL )
	 {
		 exit(EXIT_FAILURE);
	 }

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
