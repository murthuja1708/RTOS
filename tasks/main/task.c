#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>


void Task1(void* parameters)
{   
	size_t i=0;

    for(;;)
    {
		printf("%s from Task1\n",(char*)parameters);
		fflush(stdout);
		while(i<1000000)
		{
			i++;
		}

    }
}


void Task2(void* parameters)
{
	size_t i=0;
	char buffer[50];
    for(;;)
    {
		printf("%s from Task2\n",(char*)parameters);
		fflush(stdout);
        vTaskGetRunTimeStats(buffer);
        printf("%s\n",buffer);
		while(i<1000000)
		{
			i++;
		}
    }
}


void app_main()
{
    xTaskCreate(Task1,"task1",2048,(void*)"hello",4,NULL);

    xTaskCreate(Task2,"task2",2048,(void*)"bye",3,NULL);

}
