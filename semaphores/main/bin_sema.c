#include<stdio.h>
#include<stdlib.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>
#include "../../_uart.h"


static int a=0,b=0;
int choice;

SemaphoreHandle_t data_sema;


void get_data(void* parameters)
{
	const char* number_disp_str="enter a number\r\n";
	char buffer[100]={'\0'};
	for(;;)
	{
		sendData("data number display",number_disp_str);
		recvData(buffer,3,portMAX_DELAY);
		a=atoi(buffer);
		sendData("data number display",number_disp_str);
		recvData(buffer,3,portMAX_DELAY);
		b=atoi(buffer);
		xSemaphoreGive(data_sema);
	}
}

void process_data(void* parameters)
{
	int res=0;
	char buffer[100]={'\0'};
	for(;;)
	{
	//	sprintf(buffer,"choice: %d\r\n",choice);
		sendData("process task","waiting\r\n");
		if(xSemaphoreTake(data_sema,portMAX_DELAY) == pdTRUE)
		{
			sendData("process task","semaphore taken\r\n");
			res=a+b;
			sprintf(buffer,"res: %d\r\n",res);
			sendData("process task",buffer);
			vTaskDelay(pdMS_TO_TICKS(1000));
		}

	}
}


void app_main()
{
    //BaseType_t result;
	
	data_sema=xSemaphoreCreateBinary();
	if(data_sema == NULL)
	{
		return;
	}

	uart_init();
    //result=
	xTaskCreate(get_data,"data task",2048,NULL,3,NULL);

    //result=
	xTaskCreate(process_data,"process task",2048,NULL,2,NULL); 

}
