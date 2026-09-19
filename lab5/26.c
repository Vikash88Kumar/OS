#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Child process started.\n");

        printf("Child PID = %d\n", getpid());

        printf("Child process terminating.\n");

        exit(0);
    }
    else
    {
        printf("Parent process PID = %d\n", getpid());

        printf("Parent is sleeping without calling wait().\n");

        sleep(20);

        printf("Parent terminating.\n");
    }

    return 0;
}