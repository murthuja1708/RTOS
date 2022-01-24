#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>

TaskHandle_t task1_handler,task2_handler;
QueueHandle_t queue_handler;

//static int count=0;
char* message[11]={"sending","these","messages","to","consumer","task","from","producer","task","via","queue"};



void sender_task(void* parameters)
{
	uint32_t delay_ticks=pdMS_TO_TICKS(1000);
	for(int i=0;i<11;i++)
	{
		printf("sending %s\n",message[i]);
		if(xQueueSend(queue_handler,message[i],delay_ticks))
		{
			vTaskDelay(pdMS_TO_TICKS(500));
		}
		else{
			puts("error while sending\n");
		}
	}
    vTaskDelete(NULL);
}



void receiver_task(void* parameters)
{
	char buffer[20]={'\0'};
	//char task_stats[50]={'\0'};
	uint32_t delay_ticks=pdMS_TO_TICKS(2000);
	UBaseType_t messages_waiting;
	for(;;)
	{
		if(xQueueReceive(queue_handler,buffer,portMAX_DELAY)!=pdTRUE)
		{
			//vTaskGetRunTimeStats(task_stats);
			//puts(task_stats);
			printf("received %s\n",buffer);
			
		}
		else{
			puts("error while receiving\n");
		}
		vTaskDelay(delay_ticks);

		/*messages_waiting=uxQueueMessagesWaiting(queue_handler);
		printf("messages waiting %d\n",messages_waiting);
		while (xQueueReceive(queue_handler,buffer,portMAX_DELAY))
		{
			puts(buffer);
			messages_waiting--;
		}*/
		
	}
}

void app_main()
{
    //BaseType_t result;

	queue_handler = xQueueCreate(11,10);

    //result=
	xTaskCreate(sender_task,"sender_task",2048,NULL,3,&task1_handler);

    //result=
	xTaskCreate(receiver_task,"receiver_task",2048,NULL,2,&task2_handler); 

}
