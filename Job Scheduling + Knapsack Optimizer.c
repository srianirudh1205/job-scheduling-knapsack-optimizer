#include <stdio.h>
#include <stdlib.h>

// Structure for Job Scheduling
typedef struct {
    char id;
    int deadline;
    int profit;
} Job;

// Compare function (descending profit)
int compare(const void *a, const void *b) {
    return ((Job *)b)->profit - ((Job *)a)->profit;
}

// Greedy Job Scheduling (Enhanced)
void jobScheduling(Job jobs[], int n) {
    qsort(jobs, n, sizeof(Job), compare);

    int maxDeadline = 0;
    for (int i = 0; i < n; i++)
        if (jobs[i].deadline > maxDeadline)
            maxDeadline = jobs[i].deadline;

    int *slot = (int *)malloc(maxDeadline * sizeof(int));
    for (int i = 0; i < maxDeadline; i++)
        slot[i] = -1;

    int totalProfit = 0;

    for (int i = 0; i < n; i++) {
        for (int j = jobs[i].deadline - 1; j >= 0; j--) {
            if (slot[j] == -1) {
                slot[j] = i;
                totalProfit += jobs[i].profit;
                break;
            }
        }
    }

    printf("\nGreedy Job Scheduling Result:\n");
    for (int i = 0; i < maxDeadline; i++) {
        if (slot[i] != -1)
            printf("Slot %d -> Job %c (Profit: %d)\n",
                   i + 1,
                   jobs[slot[i]].id,
                   jobs[slot[i]].profit);
    }

    printf("Total Profit = %d\n", totalProfit);

    free(slot);
}

// Knapsack with item tracking
int knapsack(int W, int wt[], int val[], int n) {
    int **dp = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++)
        dp[i] = (int *)malloc((W + 1) * sizeof(int));

    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (wt[i - 1] <= w)
                dp[i][w] = (val[i - 1] + dp[i - 1][w - wt[i - 1]] > dp[i - 1][w])
                           ? val[i - 1] + dp[i - 1][w - wt[i - 1]]
                           : dp[i - 1][w];
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    // Backtracking to find selected items
    int res = dp[n][W];
    int w = W;

    printf("\nSelected items:\n");
    for (int i = n; i > 0 && res > 0; i--) {
        if (res != dp[i - 1][w]) {
            printf("Item %d (Value: %d, Weight: %d)\n",
                   i, val[i - 1], wt[i - 1]);

            res -= val[i - 1];
            w -= wt[i - 1];
        }
    }

    int result = dp[n][W];

    // Free memory
    for (int i = 0; i <= n; i++)
        free(dp[i]);
    free(dp);

    return result;
}

int main() {
    // Job Scheduling Example
    Job jobs[] = {
        {'A', 2, 100},
        {'B', 1, 19},
        {'C', 2, 27},
        {'D', 1, 25},
        {'E', 3, 15}
    };

    int n = sizeof(jobs) / sizeof(jobs[0]);
    jobScheduling(jobs, n);

    // Knapsack Example
    int val[] = {60, 100, 120};
    int wt[] = {10, 20, 30};
    int W = 50;
    int items = sizeof(val) / sizeof(val[0]);

    printf("\nDynamic Programming Knapsack Result:\n");
    int maxVal = knapsack(W, wt, val, items);
    printf("Maximum value = %d\n", maxVal);

    return 0;
}
