#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>


TaskHandle_t task1_handler,task2_handler;

int choice;
int arr[2]={};

/*
int _add()
{
    return arr[0]+arr[1];
}

int _sub()
{
    return arr[0]-arr[1];
}

int _mul()
{
    return arr[0]*arr[1];
}

int _div()
{
    return arr[0]/arr[1];
}

void Get_dataTask(void* parameters)
{
    for(;;)
    {
        vTaskSuspend(calc_handler);
        printf("1.add\r\n2.sub\r\n3.mul\r\n4.div");

        printf("enter your choice\n");
        scanf("%d",&choice);
        printf("enter two numbers\n");
        scanf("%d%d",&arr[0],&arr[1]);

        vTaskResume(calc_handler);
        printf("suspending data task\n");
        vTaskSuspend(NULL);
        printf("data task resumed\n");
        
    }
    vTaskDelete(NULL);
}


void CalculateTask(void* parameters)
{
    for(;;)
    {
        int res=0;
        switch (choice)
        {
        case 1:
            res=_add();
            break;
        case 2:
            res=_sub();
            break;
        case 3:
            res=_mul();
            break;
        case 4:
            res=_div();
            break;
        }

        printf("res is %d\n",res);
        vTaskResume(data_handler);
    }
    
}*/


void task1(void* parameters)
{
    for (;;)
    {
		printf("delaying 1st task for 1200 msecs\n");
		vTaskDelay(pdMS_TO_TICKS(1200));
		printf("suspending task1\n");
		vTaskSuspend(task1_handler);
    }
    
}

void task2(void* parameters)
{
    for(;;)
	{
		printf("resume task1\n");
		vTaskResume(task1_handler);
	}
}


void app_main()
{
    BaseType_t result;
    result=xTaskCreate(task1,"data task",2048,NULL,3,&task1_handler);
    if(result == pdPASS)
    {
        printf("task1 is created\n");
    }

    result=xTaskCreate(task2,"task2",4096,NULL,2,&task2_handler); 
    if(result == pdPASS)
    {
        printf("task2 is created\n");
    }

}
