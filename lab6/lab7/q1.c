#include <stdio.h>
struct Process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
};
int main()
{
    int n;
    float avg_tat = 0, avg_wt = 0;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (int i = 0; i < n; i++)
    {
        p[i].pid = i + 1;
        printf("Enter Arrival Time and Burst Time for P%d: ",
               p[i].pid);
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    // Sort processes by Arrival Time
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (p[i].at > p[j].at)
            {
                struct Process temp = p[i];
                p[i] = p[j];
                p[j] = temp;
            }
        }
    }
    int current_time = 0;
    for (int i = 0; i < n; i++)
    {
        if (current_time < p[i].at)
            current_time = p[i].at;
        p[i].ct = current_time + p[i].bt;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        current_time = p[i].ct;
        avg_tat += p[i].tat;
        avg_wt += p[i].wt;
    }
 printf("\n-------------------------------------------------\n");
 printf("PID\tAT\tBT\tCT\tTAT\tWT\n");
 printf("-------------------------------------------------\n");
 for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid,
               p[i].at,
               p[i].bt,
               p[i].ct,
               p[i].tat,
               p[i].wt);
 }
 printf("-------------------------------------------------\n");
 avg_tat /= n;
 avg_wt /= n;
 printf("Average Turnaround Time = %.2f\n", avg_tat);
 printf("Average Waiting Time = %.2f\n", avg_wt);
 return 0;
}