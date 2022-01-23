#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>


void DummyTask3(void* parameters)
{
	TickType_t xLastWakeTime;
    for ( ;;)
    {
        //vTaskDelayUntil(&xLastWakeTime,xFrequency);
		xLastWakeTime=xTaskGetTickCount() * portTICK_PERIOD_MS;
        printf("DummyTask3 --> %d\n",xLastWakeTime);
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("Task3 done at  %d msecs\n",(xTaskGetTickCount() * portTICK_PERIOD_MS));
    }
    
}

void DummyTask1(void* parameters)
{
	TickType_t xLastWakeTime;

    for ( ;;)
    {
        //vTaskDelayUntil(&xLastWakeTime,xFrequency);
        xLastWakeTime=xTaskGetTickCount() * portTICK_PERIOD_MS;
        printf("Dummy task1 --> %d\n",xLastWakeTime);
        vTaskDelay(pdMS_TO_TICKS(500));
        printf("Task 1 done at %d msecs\n",(xTaskGetTickCount() * portTICK_PERIOD_MS));
    }
    
}


void DummyTask2(void* parameters)
{
    TickType_t xLastWakeTime;

    //const TickType_t xFrequency=pdMS_TO_TICKS(500);
    //xLastWakeTime = xTaskGetTickCount();
    
    for ( ;;)
    {
        
		xLastWakeTime=xTaskGetTickCount() * portTICK_PERIOD_MS;
        //vTaskDelayUntil(&xLastWakeTime,xFrequency);
        printf("Dummy task2 --> %d\n",xLastWakeTime);
        vTaskDelay(pdMS_TO_TICKS(800));
        printf("Task2 done at %d msecs\n",(xTaskGetTickCount() * portTICK_PERIOD_MS));
    }
    
}

void app_main()
{
    BaseType_t result;
    printf("portTICK_PERIOD_MS --> %d\n",portTICK_PERIOD_MS);
    result=xTaskCreate(DummyTask1,"Dummy Task1",2048,NULL,1,NULL);
    if(result == pdPASS)
    {
        printf("task1 is created\n");
    }

    result=xTaskCreate(DummyTask2,"Dummy Task2",2048,NULL,1,NULL);
    if(result == pdPASS)
    {
        printf("Task2 is created\n");
    }

    result=xTaskCreate(DummyTask3,"Dummy Task3",2048,NULL,2,NULL);
    if(result == pdPASS)
    {
        printf("Task3 is created\n");
    }
}
