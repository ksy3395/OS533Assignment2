#include "scheduler.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

void print_nth_prime(void * pn) {

  int n = *(int *) pn;
  int c = 1, i = 1;
  while(c <= n) {
    ++i;
    int j, isprime = 1;
    for(j = 2; j < i; ++j) {
      if(i % j == 0) {
        isprime = 0;
        break;
      }
    }
    if(isprime) {
      ++c;
    }
    yield();
  }
  printf("%dth prime: %d\n", n, i);
  
}


int main(void) {
  scheduler_begin();
  int n1 = 20, n2 = 10, n3 = 30, n4=67;
  thread_fork(print_nth_prime, &n1);
  thread_fork(print_nth_prime, &n2);
  thread_fork(print_nth_prime, &n3);
  thread_fork(print_nth_prime, &n4);
  scheduler_end();
  free(current_thread->temp_sp);
  free(current_thread);
}

