#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>


TaskHandle_t task1_handler,task2_handler;

int choice;
int arr[2]={};


void task1(void* parameters)
{
    for (;;)
    {
		printf("delaying 1st task for 1200 msecs\n");
		vTaskDelay(pdMS_TO_TICKS(1200));
		printf("suspending task1\n");
		vTaskSuspend(task1_handler);
    }
    
}

void task2(void* parameters)
{
    for(;;)
	{
		printf("resume task1\n");
		vTaskResume(task1_handler);
	}
}


void app_main()
{
    BaseType_t result;
    result=xTaskCreate(task1,"data task",2048,NULL,3,&task1_handler);
    if(result == pdPASS)
    {
        printf("task1 is created\n");
    }

    result=xTaskCreate(task2,"task2",4096,NULL,2,&task2_handler); 
    if(result == pdPASS)
    {
        printf("task2 is created\n");
    }

}
