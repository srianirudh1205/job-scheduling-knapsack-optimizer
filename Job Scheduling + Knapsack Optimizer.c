#include <stdio.h>
#include <stdlib.h>

// Structure for Job Scheduling
typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

// Compare function for sorting jobs by profit (descending)
int compare(const void *a, const void *b) {
    Job *j1 = (Job *)a;
    Job *j2 = (Job *)b;
    return j2->profit - j1->profit;
}

// Greedy Algorithm: Job Scheduling
void jobScheduling(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    char result[maxDeadline];
    int slot[maxDeadline];
    for (int i = 0; i < maxDeadline; i++)
        slot[i] = -1;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                break;
            }
        }
    }

    printf("\nGreedy Job Scheduling Result:\n");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1)
            printf("Job %c (Profit: %d)\n", jobs[slot[i]].id, jobs[slot[i]].profit);
    }
}

// Dynamic Programming: Knapsack Problem
int knapsack(int W, int wt[], int val[], int n) {
    int dp[n+1][W+1];

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i-1] <= w)
                dp[i][w] = (val[i-1] + dp[i-1][w-wt[i-1]] > dp[i-1][w]) ?
                           val[i-1] + dp[i-1][w-wt[i-1]] : dp[i-1][w];
            else
                dp[i][w] = dp[i-1][w];
        }
    }
    return dp[n][W];
}

int main() {
    // Example for Job Scheduling
    Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };
    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobScheduling(jobs, n);

    // Example for Knapsack
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int items = sizeof(val) / sizeof(val[0]);

    printf("\nDynamic Programming Knapsack Result:\n");
    printf("Maximum value in Knapsack = %d\n", knapsack(W, wt, val, items));

    return 0;
}