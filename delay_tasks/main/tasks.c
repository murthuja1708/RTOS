#include<stdio.h>
#include<string.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>


TaskHandle_t task1_handler,task2_handler;

static int count=0;

void Task1(void* parameters)
{   
    printf("from Task1\n");
    char buffer[50]={'\0'};
    for(;;)
    {
        printf("%s from Task1\n",(char*)parameters);
        count++;
        if(count%2 == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
            vTaskGetRunTimeStats(buffer);
            memset(buffer,0,sizeof(buffer));
        }
    }
    vTaskDelete(NULL);
}


void Task2(void* parameters)
{
    printf("from Task2\n");
    char buffer[50]={'\0'};
    for(;;)
    {
        printf("%s from Task2\n",(char*)parameters);
        count++;
        if(count%2 == 0)
        {
            vTaskDelay(pdMS_TO_TICKS(1000));
            vTaskGetRunTimeStats(buffer);
            printf("%s\n",buffer);
            memset(buffer,0,sizeof(buffer));
        }
    }
    vTaskDelete(NULL);
}


void app_main()
{
    BaseType_t result;
    result=xTaskCreate(Task1,"task1",2048,"hello",6,&task1_handler);

    result=xTaskCreate(Task2,"task2",2048,"bye",2,&task2_handler); 

}