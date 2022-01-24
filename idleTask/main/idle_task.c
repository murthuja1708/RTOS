#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<esp_freertos_hooks.h>
#include<esp_sleep.h>


TaskHandle_t task1_handler;
TaskStatus_t task_status;

volatile uint32_t count=0;

//void vApplicationIdleHook( void );

bool IdleTask(void){
	count++;

	esp_light_sleep_start(); //not getting wakeup
	return true;
}

void task1(void* parameters)
{
	const TickType_t delay=pdMS_TO_TICKS(1000);
	char buffer[50]={'\0'};

	for(;;)
	{
		printf("task1 delaying to 1sec with count %d\n",count);
		vTaskGetRunTimeStats(buffer);
		printf("%s\n",buffer);
		vTaskDelay(delay);
	}
}


void app_main()
{
    BaseType_t result;
	esp_register_freertos_idle_hook(IdleTask);
    result=xTaskCreate(task1,"task1",2048,NULL,3,&task1_handler);
	if(result == pdTRUE)
	{
		printf("task created\n");
	}

}
