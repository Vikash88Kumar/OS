#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    printf("Before exec()\n");

    execl("/bin/ls", "ls", "-l", NULL);

    // This line executes only if execl() fails
    perror("exec failed");

    return 1;
}