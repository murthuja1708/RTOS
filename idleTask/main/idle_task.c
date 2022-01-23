#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

TaskHandle_t task1_handler;
TaskStatus_t task_status;

volatile uint32_t count=0;

//void vApplicationIdleHook( void );

void vApplicationIdleHook(void){
    count++;
}

void task1(void* parameters)
{
	const TickType_t delay=pdMS_TO_TICKS(1000);

	for(;;)
	{
		printf("task1 delaying to 1sec with count %d\n",count);
		vTaskDelay(delay);
	}
}


void app_main()
{
    BaseType_t result;
    
    result=xTaskCreate(task1,"task1",2048,NULL,3,&task1_handler);

}
