#include <stdio.h>
#include <stdlib.h>

// Display allocation result
void display(int *process, int n, int *allocation) {
    int i;

    printf("\nProcess ID\tSize\tBlock Assigned\n");

    for (i = 0; i < n; i++) {
        if (allocation[i] != -1)
            printf("P%d\t\t%d\tB%d\n",
                   i + 1, process[i], allocation[i] + 1);
        else
            printf("P%d\t\t%d\tNot Allocated\n",
                   i + 1, process[i]);
    }
}


// First Fit
void firstFit(int *blocks, int m, int *process, int n) {
    int i, j;
    int *allocation = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            if (blocks[j] >= process[i]) {
                allocation[i] = j;
                blocks[j] -= process[i];
                break;
            }
        }
    }

    printf("\n========== FIRST FIT ==========\n");
    display(process, n, allocation);

    free(allocation);
}


// Best Fit
void bestFit(int *blocks, int m, int *process, int n) {
    int i, j, best;
    int *allocation = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        best = -1;

        for (j = 0; j < m; j++) {
            if (blocks[j] >= process[i]) {
                if (best == -1 || blocks[j] < blocks[best])
                    best = j;
            }
        }

        if (best != -1) {
            allocation[i] = best;
            blocks[best] -= process[i];
        }
    }

    printf("\n========== BEST FIT ==========\n");
    display(process, n, allocation);

    free(allocation);
}


// Worst Fit
void worstFit(int *blocks, int m, int *process, int n) {
    int i, j, worst;
    int *allocation = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        worst = -1;

        for (j = 0; j < m; j++) {
            if (blocks[j] >= process[i]) {
                if (worst == -1 || blocks[j] > blocks[worst])
                    worst = j;
            }
        }

        if (worst != -1) {
            allocation[i] = worst;
            blocks[worst] -= process[i];
        }
    }

    printf("\n========== WORST FIT ==========\n");
    display(process, n, allocation);

    free(allocation);
}


// Next Fit
void nextFit(int *blocks, int m, int *process, int n) {
    int i, j, count;
    int last = 0;

    int *allocation = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++)
        allocation[i] = -1;

    for (i = 0; i < n; i++) {
        j = last;
        count = 0;

        while (count < m) {
            if (blocks[j] >= process[i]) {
                allocation[i] = j;
                blocks[j] -= process[i];

                last = j;
                break;
            }

            j = (j + 1) % m;
            count++;
        }
    }

    printf("\n========== NEXT FIT ==========\n");
    display(process, n, allocation);

    free(allocation);
}


// Buddy System
void buddySystem(int totalMemory, int *process, int n) {
    int i, block;

    printf("\n========== BUDDY SYSTEM ==========\n");

    printf("Process ID\tSize\tBlock Assigned\n");

    for (i = 0; i < n; i++) {

        block = 1;

        while (block < process[i])
            block *= 2;

        if (block <= totalMemory) {
            printf("P%d\t\t%d\t%d\n",
                   i + 1, process[i], block);

            totalMemory -= block;
        }
        else {
            printf("P%d\t\t%d\tNot Allocated\n",
                   i + 1, process[i]);
        }
    }

    printf("\nRemaining Memory = %d\n", totalMemory);
}


int main() {

    int m, n, i, choice;

    // Existing memory blocks
    printf("===== MEMORY ALLOCATION =====\n");

    printf("\nEnter number of memory blocks: ");
    scanf("%d", &m);

    int *blocks = (int*)calloc(m, sizeof(int));

    printf("Enter sizes of existing memory blocks:\n");

    for (i = 0; i < m; i++) {
        printf("Block B%d: ", i + 1);
        scanf("%d", &blocks[i]);
    }

    // Processes
    printf("\nEnter number of processes: ");
    scanf("%d", &n);

    int *process = (int *)calloc(n, sizeof(int));

    printf("Enter process sizes:\n");

    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &process[i]);
    }


    // Menu
    while (1) {

        printf("\n\n========== MENU ==========\n");
        printf("1. First Fit\n");
        printf("2. Best Fit\n");
        printf("3. Worst Fit\n");
        printf("4. Next Fit\n");
        printf("5. Buddy System\n");
        printf("6. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);


        // Create a fresh copy of memory blocks
        // for every algorithm
        int *temp = (int *)malloc(m * sizeof(int));

        for (i = 0; i < m; i++)
            temp[i] = blocks[i];


        switch (choice) {

            case 1:
                firstFit(temp, m, process, n);
                break;

            case 2:
                bestFit(temp, m, process, n);
                break;

            case 3:
                worstFit(temp, m, process, n);
                break;

            case 4:
                nextFit(temp, m, process, n);
                break;

            case 5:
                buddySystem(blocks[0], process, n);
                break;

            case 6:
                printf("\nProgram exited successfully.\n");

                free(temp);
                free(blocks);
                free(process);

                return 0;

            default:
                printf("\nInvalid choice! Try again.\n");
        }

        free(temp);
    }
}