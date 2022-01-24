#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include "../../_uart.h"


void Task1(void* parameters)
{   
    for(;;)
    {
		sendData("Task1","hello\r\n");
        //printf("%s from Task1\n",(char*)parameters);
    }
    vTaskDelete(NULL);
}


void Task2(void* parameters)
{
    
    for(;;)
    {
		sendData("Task2","bye\r\n");
        //printf("%s from Task2\n",(char*)parameters);
    }
    vTaskDelete(NULL);
}


void app_main()
{
    BaseType_t result;
	uart_init();
    result=xTaskCreate(Task1,"task1",2048,"hello",12,NULL);
    /*if(result == pdPASS)
    {
        printf("task1 is created\n");
    }
    printf("creating task2\n");*/

    result=xTaskCreate(Task2,"task2",2048,"bye",11,NULL); 
    if(result == pdPASS)
    {
        printf("task2 is created\n");
    }


}
