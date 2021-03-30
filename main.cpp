#include <iostream>
#include <cstdio>
#include <time.h>

using namespace std;

//Partition summation
int cum(int A[], int partition_start, int partition_end)
{
    int total = 0;
    for (int i = partition_start; i <= partition_end; i++)
        total = total + A[i];
    return total;
}

int partition(int A[], int n, int k)
{
    //Initializes  dynamic programming.
    int dp[k + 1][n + 1] = { 0 };

    //Case when there is 1 group.
    for (int i = 1; i <= n; i++)
        dp[1][i] = cum(A, 0, i - 1);

    //Case when there is 1 element.
    for (int i = 1; i <= k; i++)
        dp[i][1] = A[0];

    //Determines max(min(partition))
    int g[k];
    for (int i = 2; i <= k; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int best = 0;
            for (int l = 1; l < j; l++)
            {
                int best_current = min(dp[i - 1][l], cum(A, l, j - 1));
                if (best_current > best)
                    best = best_current;
            }
            dp[i][j] = best;
        }
    }

    //Re-initializes the first iteration properly.
    for (int i = 1; i <= n; i++)
        dp[1][i] = cum(A, 0, i - 1);

    //Stores the location of each partition.
    for (int i = 1; i <= k; i++)
    {
        int j = n;
        while (dp[k][n] < dp[i][j])
            j--;
        g[i] = j;
    }

    //Outputs the indices of Array G (the sizes of each partition)
    cout << "Array G is: ";
    for (int i = 1; i < 2; i++)
        cout << g[i] << " ";
    for (int i = 2; i <= k; i++)
        cout << g[i] - g[i - 1] << " ";

    cout << endl;
    return dp[k][n];
}

int main(void)
{
    int n;
    cout << "Please enter the length of the array: ";
    cin >> n;
    cout << endl;

    int A[12];
    cout << "Please enter the array's elements: ";
    for (int i = 0; i < n; i++)
        cin >> A[i];
    cout << endl;

    int k;
    cout << "How many partitions? ";
    cin >> k;
    cout << endl;

    cout << "The max-min partition size is: " << partition(A, n, k) << endl;

    cout << ("Press ENTER key to Continue\n");
    getchar();
    return 0;
}
