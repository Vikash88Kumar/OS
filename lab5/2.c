#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *threadFunction(void *arg)
{
    int id = *((int *)arg);

    printf("Thread %d started.\n", id);

    sleep(2);

    printf("Thread %d is terminating.\n", id);

    pthread_exit(NULL);
}

int main()
{
    pthread_t thread1, thread2;

    int id1 = 1;
    int id2 = 2;

    printf("Main thread started.\n");

    pthread_create(&thread1, NULL, threadFunction, &id1);

    pthread_create(&thread2, NULL, threadFunction, &id2);

    pthread_join(thread1, NULL);

    pthread_join(thread2, NULL);

    printf("All threads terminated.\n");

    return 0;
}