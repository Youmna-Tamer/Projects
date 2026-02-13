#include "rod_cutting.h"
#include <iostream>
#include <climits>
#include <unordered_map>
using namespace std;

// Brute force implementation
int rodCuttingBruteForce(int price[], int n) {
    if (n == 0) return 0;

    int max_val = INT_MIN;
    for (int i = 0; i < n; ++i) {
        int current_val = price[i] + rodCuttingBruteForce(price, n - i - 1);
        max_val = max(max_val, current_val);
    }

    return max_val;
}

// Memoized helper
int rodCuttingMemoHelper(int price[], int n, int memo[]) {
    if (n == 0) return 0;
    if (memo[n] >= 0) return memo[n];

    int max_val = INT_MIN;
    for (int i = 0; i < n; ++i) {
        int current_val = price[i] + rodCuttingMemoHelper(price, n - i - 1, memo);
        max_val = max(max_val, current_val);
    }

    memo[n] = max_val;
    return max_val;
}

// Memoization wrapper
int rodCuttingMemo(int price[], int n, int* memo) {
    for (int i = 0; i <= n; ++i) memo[i] = -1;
    return rodCuttingMemoHelper(price, n, memo);
}

// Bottom-up DP with cuts tracking
int rodCuttingDP(int price[], int n, int cuts[]) {
    int* dp = new int[n + 1];
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        int max_val = INT_MIN;
        for (int j = 1; j <= i; ++j) {
            if (price[j - 1] + dp[i - j] > max_val) {
                max_val = price[j - 1] + dp[i - j];
                cuts[i] = j;
            }
        }
        dp[i] = max_val;
    }

    int result = dp[n];
    delete[] dp;
    return result;
}

// Prints cut sequence
void printCuts(int cuts[], int n) {
    cout << "Cuts to get maximum profit: ";
    while (n > 0) {
        cout << cuts[n] << " ";
        n -= cuts[n];
    }
    cout << endl;
}
