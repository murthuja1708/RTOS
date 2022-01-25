1) Find what is the task priority numbering for the RTOS you are using. eg. Higher the number higher the priority or vice-versa. Find the range of priority that can be assigned to a task for your RTOS.
	*	Higher the number higher the priority(freertos).0 to 25.

2) What is the mechanism used to make a task periodic for the RTOS you are using? Write a program to make a task periodic with periodicity of 500ms.
    *   The mechanism used to make a task periodic in freertos using API's **vTaskDelay(),vTaskDelayUntil()**
    *   The above api's put the tasks into blocked state for given number of ticks.since no task is running cpu now schedules other tasks and we can delay this task also for given no of ticks making tasks periodic

3)  Find the APIs in your RTOS that provides timestamp and use it to print the periodic task. Observe the jitter in the timestamp vs the periodicity. Enhance the code to 10 periodic tasks with different periodicity. Futher observe the jitter in each of the task.
	*	done with 3 periodic tasks

4. Create two task with priority 10 and 20. Each task prints its own custom message.
	*	created two tasks with two different priorities which prints its cusom messages

5. Swap the priority and observe the changes in the output. What is your conclusion on the sequence of printing the messages.

	*	as soon as taks gets created task is moved to ready state and if there is no other task scheduler will schedule this task if there are tasks already then higher priority task will get scheduled.

6. What are the maximum number of tasks that can be created on the RTOS you are using? Is it limited by the RTOS design or underlying hardware resources or both.
	*	There is no limit on number of tasks that can be created in freertos until we have the required size to do the task operations and other functionalities(i..e hardware resources).

7. What is the scheduling algorithm used by your RTOS?
   *	priority based preemptive scheduling algorithm.higher the value higher the priority

8. List the customization options for creating a task for the RTOS you are using. eg. priority etc
	1.	priority
	2.	stack size
	3.	periodicity

9. Find the fields that are maintained in the Task Control Block / Process Control Block of the RTOS you are using.

	1.	top of stack  --> Points to the location of the lastitem placed on the tasks stack

	2.	uxPriority --> priority of task

	3.	pxStack --> points to start of stack

	4.	pcTaskName -->name given to task when created

	5.	pxEndOfStack-->end of stack

	6.	uxTCBNumber --> each time tcb is created it is incremented

	7.	ulRunTimeCounter --> Stores the amount of time the task has spent in the Running state

	8.	xCoreID --> core this task id pinned to

10. Draw a process or task state diagram for the RTOS you are using.
	*	**path --> task_states->.jpg**

11.	What is the API for deleting a task? Write a program demonstrate this capability.
	*	vTaskDelete(task_handler)
	sending NULL inplace of task handler will delete the process that is running.
	in FreeRTOS every process should either have to Delete the task if it is returning or the task should be in infinite loop

12. What are the APIs provided by your RTOS for enabling and disabling the interrupts? Write a program to demonstrate this capability?
	these are esp32 driver api's
	*	disabling interrupts --> gpio_intr_disable()
	*	enabling interrupt  --> gpio_intr_enable()

13. Does your RTOS provide APIs to collect task statistics. If yes, list the statistics parameters that are collected and write a program to display the runtime task statistics?
	*	vTaskGetRunTimeStats(char* buffer)

14.	Find the tick frequency configuration for your RTOS.
	*	default its 100 ticks.

15.	Create a task to suspend itself after 1200 ms and resume it from another task 
	*	we can put a task(using task_handle) to state where itself cannot get unblocked after certain time.we need to call another api (resume) to move from suspended state to resume stte

16. Write a RTOS application to demonstrate the use of changing priority
	-	**in progress.**

17.	If you RTOS supports idle task hooking, write a program to demonstrate it
	*	register a function whenever task is idle the function is executed.

18.	Write a RTOS application to demonstrate the use of task to task communication using Queue management APIs. Also demonstrate blocking on a queue.
	*	while receiving if data is not available in queue task will go into blocked state as soon as there is data i..e is brought into ready state and executed.
	*	while for sending if queue is full then the task is sent to blocked state until there is atleast 1 free space to sent.

19.	Write a RTOS application to demonstrate the effects of task priorities when sending to and receiving from a queue.
	*	**in progress**

20.	Write a RTOS application to demonstrate deferred interrupt processing using binary semaphores.
	Interrupt safe version of binary semaphore can be used to unblock a task each time a particular interrupt occurs. this allows the majority of task to be done in task and fast and short code to be done in ISR.
	*	**path ---> deferred_interrupts --> .c file**

21.	Write a RTOS application to demonstrate counting semaphores to synchronize a task
	*	**path ---> semaphores->main->resource_mgmt.c**

22.	 Write a RTOS application to demonstrate the usage of queues within an interrupt service routine
		*	**path ---> Queues->main->assignment22.c**

23. Write a RTOS application to manage resources using mutual exclusion
	**todo**
	
24. Write a RTOS application to demonstrate a priority inversion problem. If your RTOS supports priority inheritance or priority ceiling, use it to solve the priority inversion problem.
	**problem is done. solution yet to do.**

25. Write a RTOS application to create a software timer that invokes a callback function every 5 seconds.
	*	Created a timer that calls a callback function for whenever timer expires and tracking how many times timer has expired. If it is more than 10 i am stopping timer.




	




