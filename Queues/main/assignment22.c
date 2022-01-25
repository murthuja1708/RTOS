#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>
#include<freertos/semphr.h>
#include<driver/gpio.h>

#define BUTTON_PIN 4

QueueHandle_t queue_handler1,queue_handler2;
//SemaphoreHandle_t button_handler_sema;


void sender_task(void* parameters)
{
	uint32_t delay_ticks=pdMS_TO_TICKS(1000);
	uint32_t data = 0;
	for(;;)
	{
		vTaskDelay(pdMS_TO_TICKS(5000));
		for(int i=0;i<6;i++)
		{
			if(xQueueSendToBack(queue_handler1,&data,delay_ticks) == pdPASS)
			{
				printf("sending %d\n",data);
				data++;
			}
			else{
				printf("error while sending\n");
			}
		}
		data=0;
	}
    vTaskDelete(NULL);
}

void buttonHandler(void* args)
{
static const char *random_data_to_send[6] =
{
	"sending",
	"data ",
	"from",
	"ISR ",
	"To ",
	"Queue"
};
	BaseType_t xHigherPriorityTaskWoken = pdFALSE;
	uint32_t recv_data ;


	while(!xQueueIsQueueEmptyFromISR(queue_handler1))
	{
		xQueueReceiveFromISR(queue_handler1,&recv_data,&xHigherPriorityTaskWoken); 
		xQueueSendToBackFromISR(queue_handler2,random_data_to_send[recv_data],&xHigherPriorityTaskWoken);
	}

//	portYIELD_FROM_ISR(xHigherPriorityTaskWoken);

}

void _gpio_config()
{

	ESP_ERROR_CHECK(gpio_reset_pin(BUTTON_PIN));

	ESP_ERROR_CHECK(gpio_set_direction(BUTTON_PIN,GPIO_MODE_INPUT));
  
	ESP_ERROR_CHECK(gpio_intr_enable(BUTTON_PIN));
   
    ESP_ERROR_CHECK(gpio_set_intr_type(BUTTON_PIN, GPIO_INTR_ANYEDGE));
    

    ESP_ERROR_CHECK(gpio_install_isr_service(ESP_INTR_FLAG_EDGE));

    ESP_ERROR_CHECK(gpio_isr_handler_add(BUTTON_PIN, buttonHandler,NULL));
    
}

void receiver_task(void* parameters)
{
	char recv_data[20]={'\0'};
	uint32_t delay_ticks=pdMS_TO_TICKS(2000);
	for(;;)
	{
		if(xQueueReceive(queue_handler2,&recv_data,portMAX_DELAY)==pdTRUE)
		{
			printf("%s\n",recv_data);
			recv_data[0]='\0';
		}
		else{
			puts("error while receiving\n");
		}
		//vTaskDelay(delay_ticks);

	}
}

void app_main()
{
//	button_handler_sema = xSemaphoreCreateBinary();
	_gpio_config();

	queue_handler1 = xQueueCreate(6,sizeof(int));

	queue_handler2 = xQueueCreate(6,11);


    //result=
	xTaskCreate(sender_task,"sender_task",2048,NULL,2,NULL);

    //result=
	xTaskCreate(receiver_task,"receiver_task",2048,NULL,3,NULL); 

}
