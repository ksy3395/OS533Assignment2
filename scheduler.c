#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "scheduler.h"
#include "queue.h"

struct thread* current_thread;
struct thread* new_thread;
struct thread* next_thread;
struct queue ready_list;
struct queue done_list;
static const int STACK_SIZE = 1024*1024;

void yield()
{

	if (current_thread->state!=DONE)
	{
		current_thread->state = READY;
		thread_enqueue(&ready_list, current_thread);
	}	
			
		next_thread = thread_dequeue(&ready_list);
		next_thread->state = RUNNING;
		
		struct thread * temp = current_thread;
        	current_thread = next_thread;
        	thread_switch (temp, current_thread);
	
}

void thread_wrap() {
	current_thread->initial_function(current_thread->initial_argument);
        current_thread->state=DONE;
	thread_enqueue(&done_list, current_thread); 
	yield();

}

void scheduler_begin()
{
	current_thread =  malloc(sizeof(struct thread));
	current_thread->state = RUNNING;
	ready_list.head = NULL;
	ready_list.tail = NULL;
}

void thread_fork(void(*target)(void*), void * arg)
{
	new_thread =  malloc(sizeof(struct thread));
	new_thread->temp_sp = malloc(STACK_SIZE);
	new_thread -> stack_pointer = new_thread->temp_sp + STACK_SIZE;

	new_thread -> initial_argument = arg;
	new_thread -> initial_function = target;
	
	current_thread->state = READY;
	thread_enqueue(&ready_list, current_thread);
	
	new_thread->state = RUNNING;

	struct thread * temp = current_thread;
	current_thread = new_thread;
	thread_start(temp, current_thread);

}

void scheduler_end()
{
while (is_empty(&ready_list)==0)
	{
		
		yield();

	}

while (is_empty(&done_list)==0)
{ 
 	struct thread* done_thread = thread_dequeue(&done_list);
	free(done_thread->temp_sp);	
	free(done_thread);
}	
}
