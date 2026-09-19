#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    printf("Parent Process Started. PID = %d\n", getpid());

    pid_t pid1 = fork();

    if (pid1 == 0)
    {
        printf("Child 1 created. PID = %d, Parent PID = %d\n",
               getpid(), getppid());

        printf("Child 1 is terminating.\n");
        exit(0);
    }
    else if (pid1 > 0)
    {
        printf("Parent created Child 1 with PID = %d\n", pid1);
    }
    else
    {
        printf("Fork failed for Child 1!\n");
        return 1;
    }

   
    wait(NULL);

    printf("All child processes terminated.\n");
    printf("Parent Process Terminating.\n");

    return 0;
}
