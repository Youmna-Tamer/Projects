#ifndef ROD_CUTTING_H
#define ROD_CUTTING_H

// Brute force version using plain recursion
int rodCuttingBruteForce(int price[], int n);

// Top-down memoization version
int rodCuttingMemo(int price[], int n, int* memo);

// Bottom-up tabulation version (also fills cuts[])
int rodCuttingDP(int price[], int n, int cuts[]);

// Helper to print optimal cut lengths
void printCuts(int cuts[], int n);

#endif // ROD_CUTTING_H
