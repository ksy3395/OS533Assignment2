typedef enum {
        RUNNING,
        READY,
        BLOCKED,
        DONE
}state_t;

typedef unsigned char byte;

struct thread {
	unsigned char* stack_pointer;
	void* initial_argument;
	void (*initial_function) (void*);
	state_t state;
	byte* temp_sp;
};

void scheduler_begin();
void thread_fork(void(*target)(void*), void * arg);
void yield();
void scheduler_end();

void thread_switch(struct thread * old, struct thread * new);
void thread_start(struct thread * old, struct thread * new);

extern struct thread * current_thread;

