
/*
 
   The below code is taken from below link and modified here and there according to my needs. 

https://www.digikey.in/en/maker/projects/introduction-to-rtos-solution-to-part-11-priority-inversion/abf4b8f7cd4a4c70bece35678d178321
	
any doubts goto that link
*/


#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/semphr.h>

static SemaphoreHandle_t lock;
TickType_t cs_wait = pdMS_TO_TICKS(250);
TickType_t med_wait = pdMS_TO_TICKS(5000);

void TaskH(void* parameters)
{   
	TickType_t timestamp;
    for(;;)
    {
		printf("Task H trying to take lock\n");
		timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
		xSemaphoreTake(lock,portMAX_DELAY);

		printf("Task H waited %d msecs for lock. Doing some work\n",(xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp);

		timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;

		while((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

		printf("Task H releasing lock\n");
		xSemaphoreGive(lock);
		vTaskDelay(pdMS_TO_TICKS(500));
    }
    vTaskDelete(NULL);
}


void TaskM(void* parameters)
{
	TickType_t timestamp;

    for(;;)
    {
		printf("Task M doing some work\n");
		timestamp=xTaskGetTickCount() * portTICK_PERIOD_MS;

		while( (xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < med_wait);

		printf("Task M work done delaying for 500 msecs\n");
		vTaskDelay(pdMS_TO_TICKS(500));
    }
    vTaskDelete(NULL);
}

void TaskL(void* parameters)
{
    TickType_t timestamp;
    for(;;)
    {
		printf("Task L trying to take lock\n");

		timestamp=xTaskGetTickCount() * portTICK_PERIOD_MS;

		xSemaphoreTake(lock,portMAX_DELAY);


		printf("Task L waited %d msecs for lock. doing some work\n",xTaskGetTickCount() * portTICK_PERIOD_MS - timestamp);

		timestamp = xTaskGetTickCount() * portTICK_PERIOD_MS;
		while((xTaskGetTickCount() * portTICK_PERIOD_MS) - timestamp < cs_wait);

		printf("Task L releasing lock\n");
		xSemaphoreGive(lock);

		vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void app_main()
{
	lock = xSemaphoreCreateBinary();
	xSemaphoreGive(lock);
	

	printf("creating low priority task\n");
    xTaskCreate(TaskL,"task L",2048,"hello",1,NULL);

	vTaskDelay(pdMS_TO_TICKS(1));

	printf("creating high priority task\n");
    xTaskCreate(TaskH,"Task H",2048,"bye",3,NULL);

    xTaskCreate(TaskM,"task M",2048,"bye",2,NULL);
	
	vTaskDelete(NULL);

}
