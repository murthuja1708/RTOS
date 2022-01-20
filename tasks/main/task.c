#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>

TaskHandle_t task1_handler,task2_handler;

//static int flag1=0,flag2=0;

void Task1(void* parameters)
{   
    for(;;)
    {
        printf("%s from Task1\n",(char*)parameters);
    }
    vTaskDelete(NULL);
}


void Task2(void* parameters)
{
    
    for(;;)
    {
        printf("%s from Task2\n",(char*)parameters);
    }
    vTaskDelete(NULL);
}


void app_main()
{
    BaseType_t result;
    result=xTaskCreate(Task1,"task1",2048,"hello",1,&task1_handler);
    if(result == pdPASS)
    {
        printf("task1 is created\n");
    }
    printf("creating task2\n");

    result=xTaskCreate(Task2,"task2",2048,"bye",2,&task2_handler); 
    if(result == pdPASS)
    {
        printf("task2 is created\n");
    }


}