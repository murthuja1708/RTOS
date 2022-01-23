#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<driver/gpio.h>


void SensorTask(void* parameters)
{
    //TickType_t xLastWakeTime;

    //const TickType_t xFrequency=pdMS_TO_TICKS(500);
    //xLastWakeTime = xTaskGetTickCount();

    for ( ;;)
    {
        //vTaskDelayUntil(&xLastWakeTime,xFrequency);
        printf("sensor task --> %d\n",xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(1000));
        printf("sensor task delay done at --> %d\n",xTaskGetTickCount());
    }
    
}

void DummyTask1(void* parameters)
{
    //TickType_t xLastWakeTime;

    //const TickType_t xFrequency=pdMS_TO_TICKS(500);
    //xLastWakeTime = xTaskGetTickCount();

    for ( ;;)
    {
        //vTaskDelayUntil(&xLastWakeTime,xFrequency);
        printf("Dummy task1 --> %d\n",xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(500));
        printf("Dummy task1 done at --> %d\n",xTaskGetTickCount());
    }
    
}


void DummyTask2(void* parameters)
{
    //TickType_t xLastWakeTime;

    //const TickType_t xFrequency=pdMS_TO_TICKS(500);
    //xLastWakeTime = xTaskGetTickCount();

    for ( ;;)
    {
        
        //vTaskDelayUntil(&xLastWakeTime,xFrequency);
        printf("Dummy task2 --> %d\n",xTaskGetTickCount());
        vTaskDelay(pdMS_TO_TICKS(800));
        printf("Dummy task2 done at --> %d\n",xTaskGetTickCount());
    }
    
}

void app_main()
{
    BaseType_t result;
    result=xTaskCreate(SensorTask,"Sensor Task",2048,NULL,2,NULL);
    if(result == pdPASS)
    {
        printf("task1 is created\n");
    }

    result=xTaskCreate(DummyTask1,"Dummy Task1",2048,NULL,2,NULL);
    if(result == pdPASS)
    {
        printf("Dummy Task1 is created\n");
    }

    result=xTaskCreate(DummyTask2,"Dummy Task1",2048,NULL,2,NULL);
    if(result == pdPASS)
    {
        printf("Dummy Task2 is created\n");
    }
}