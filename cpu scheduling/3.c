
#include <stdio.h>


struct process {
    int pid;            
    int burstTime;      
    int priority;       
    int waitingTime;    
    int turnaroundTime; 
};


void sortProcesses(struct process p[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].priority > p[j + 1].priority) {
                struct process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}

int main() {
    int n; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[n];

    
    for (int i = 0; i < n; ++i) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &p[i].burstTime);
        printf("Enter priority for process %d: ", i + 1);
        scanf("%d", &p[i].priority);
        p[i].waitingTime = 0;
    }

    
    sortProcesses(p, n);

    
    p[0].turnaroundTime = p[0].burstTime;
    for (int i = 1; i < n; ++i) {
        p[i].waitingTime = p[i - 1].waitingTime + p[i - 1].burstTime;
        p[i].turnaroundTime = p[i].waitingTime + p[i].burstTime;
    }

    
    float avgWaitingTime = 0, avgTurnaroundTime = 0;
    for (int i = 0; i < n; ++i) {
        avgWaitingTime += p[i].waitingTime;
        avgTurnaroundTime += p[i].turnaroundTime;
    }
    avgWaitingTime /= n;
    avgTurnaroundTime /= n;

    
    printf("\nAverage Waiting Time: %.2f\n", avgWaitingTime);
    printf("Average Turnaround Time: %.2f\n", avgTurnaroundTime);

    return 0;
}