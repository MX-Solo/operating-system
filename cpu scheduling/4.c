
#include <stdio.h>


struct process {
    int pid;            
    int burstTime;      
    int remainingTime;  
    int waitingTime;    
};

int main() {
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    
    for (int i = 0; i < n; ++i) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].burstTime);
        p[i].remainingTime = p[i].burstTime;
        p[i].waitingTime = 0;
    }

    int quantum; 
    printf("Enter time quantum: ");
    scanf("%d", &quantum);

    int currentTime = 0;
    int completed = 0;

    
    while (completed < n) {
        for (int i = 0; i < n; ++i) {
            if (p[i].remainingTime > 0) {
                int executionTime = (p[i].remainingTime > quantum) ? quantum : p[i].remainingTime;
                p[i].remainingTime -= executionTime;
                currentTime += executionTime;
                if (p[i].remainingTime == 0) {
                    completed++;
                }
                for (int j = 0; j < n; ++j) {
                    if (j != i && p[j].remainingTime > 0) {
                        p[j].waitingTime += executionTime;
                    }
                }
            }
        }
    }

    
    float avgWaitingTime = 0;
    for (int i = 0; i < n; ++i) {
        avgWaitingTime += p[i].waitingTime;
    }
    avgWaitingTime /= n;

    
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);

    return 0;
}