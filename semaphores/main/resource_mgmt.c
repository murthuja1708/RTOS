
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>
#include<freertos/timers.h>

#define NUM_OF_RESOURCES 4

/*int resources[NUM_OF_RESOURCES][2]={
	{10,20},
	{30,40},
	{50,60},
	{70,80}
};*/

struct resrc_mgmt{
	int* resource;
	bool is_available;
}pool[4]={
	{NULL,true},
	{NULL,true},
	{NULL,true},
	{NULL,true}
};
TimerHandle_t free_resource_timer;

SemaphoreHandle_t data_sema;

void assign_resource(void* parameters)
{
	for(;;)
	{
		if(xSemaphoreTake(data_sema,portMAX_DELAY) == pdTRUE)
		{
			for(int i=0;i<NUM_OF_RESOURCES;i++)
			{
				if(pool[i].resource == NULL)
				{
					if(i >1)
					{
						//just to check if everything is woring fine
						vTaskDelay(pdMS_TO_TICKS(3000));
					}
					printf("assigning resource %d\n",i);
					pool[i].resource=(int*)malloc(sizeof(int)*2); 
					pool[i].is_available=false;

					break;
				}
			}
		}
	}
}

void free_resource(TimerHandle_t xTimer)
{
	printf("free resource callback\n");
			//sendData("process task","waiting\r\n");
		for(int i=0;i<NUM_OF_RESOURCES;i++)
		{
			if(pool[i].resource != NULL)
			{
				printf("freeing resource %d\n",i);
				pool[i].is_available=true;
				free(pool[i].resource);
				pool[i].resource=NULL;
				xSemaphoreGive(data_sema);
			}
		}
	
}


void app_main()
{

	//initially 2 resources are availabel
	data_sema = xSemaphoreCreateCounting(4,4);

	if(data_sema == pdFALSE)
	{
		exit(EXIT_FAILURE);
	}


	if(xTaskCreate(assign_resource,"assign resource",2048,NULL,3,NULL)==pdPASS)
	{
		printf("assign resource task created\n");
	}

/*
	if(xTaskCreate(free_resource,"freeing resource",2048,NULL,3,NULL)==pdPASS)
	{
		printf("free resource task created\n");
	}
	*/
	free_resource_timer = xTimerCreate("Timer",
					pdMS_TO_TICKS(5000),
					pdTRUE,
					(void*)0,
					free_resource
				);
	if(free_resource_timer != NULL)
	{
		printf("created timer\n");
		if(xTimerStart(free_resource_timer,0) != pdPASS)
		{
			printf("couldnt start timer\n");
			exit(EXIT_FAILURE);
		}
		printf("timer started\n");
	}



}
