#include<stdio.h>
#include<stdlib.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>
#include "../../_uart.h"

//resources to protect

static int a=0,b=0;
int choice;

SemaphoreHandle_t data_mutex;

void get_data(void* parameters)
{
	const char* number_disp_str="enter a number\r\n";
	char buffer[100]={'\0'};
	for(;;)
	{
/*		if(xSemaphoreTake(data_mutex,portMAX_DELAY))
		{
			sendData("Data TASK:","semaphore taken\r\n");
		}*/
		sendData("data number display",number_disp_str);
		recvData(buffer,3,portMAX_DELAY);
		a=atoi(buffer);
		sendData("data number display",number_disp_str);
		recvData(buffer,3,portMAX_DELAY);
		b=atoi(buffer);
//		configASSERT(xSemaphoreGive(data_mutex));
		vTaskDelay(pdMS_TO_TICKS(10));
	}
}

void process_data(void* parameters)
{
	int res=0;
	char buffer[10]={'\0'};
	for(;;)
	{
	//	sendData("process task","smeaphore waiting\r\n");
//		configASSERT(xSemaphoreTake(data_mutex,portMAX_DELAY));
	//	sendData("process task","semaphore taken now processing\r\n");
		res=a+b;
		sprintf(buffer,"%d\n",res);
		//printf("res: %d\n",res);
		sendData("process task",buffer);
//		configASSERT(xSemaphoreGive(data_mutex));

	}
}


void app_main()
{
    //BaseType_t result;
	
	uart_init();
	data_mutex = xSemaphoreCreateMutex();

	if(data_mutex == NULL)
	{
		exit(EXIT_FAILURE);
	}

    //result=
	xTaskCreate(get_data,"data task",2048,NULL,3,NULL);
	
    //result=
	xTaskCreate(process_data,"process task",2048,NULL,2,NULL); 

	printf("two tasks created\n");

}
