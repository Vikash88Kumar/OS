#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid == 0)
    {
        printf("Child Process Started.\n");

        printf("Child PID = %d\n", getpid());

        printf("Parent PID = %d\n", getppid());

        sleep(5);

        printf("Child Process Finished.\n");

        exit(0);
    }
    else
    {
        printf("Parent Process Started.\n");

        printf("Parent is waiting for child to finish.\n");

        wait(NULL);

        printf("Child has terminated.\n");

        printf("Parent Process Terminating.\n");
    }

    return 0;
}