#include <iostream>
#include <string>
#include "rod_cutting.h"
using namespace std;

int getPositiveInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a positive integer." << endl;
        }
        else {
            return value;
        }
    }
}

int getNonNegativeInteger(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin.fail() || value < 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a non-negative integer." << endl;
        }
        else {
            return value;
        }
    }
}

int main() {
    int n = getPositiveInteger("Enter the length of the rod: ");

    int* price = new int[n];
    cout << "Enter prices for lengths 1 to " << n << ":\n";
    for (int i = 0; i < n; ++i) {
        price[i] = getNonNegativeInteger("Price for length " + to_string(i + 1) + ": ");
    }

    cout << "\nBrute Force Solution: " << rodCuttingBruteForce(price, n) << endl;

    int* memo = new int[n + 1];
    cout << "Memoized DP Solution: " << rodCuttingMemo(price, n, memo) << endl;
    delete[] memo;

    int* cuts = new int[n + 1];
    int dpProfit = rodCuttingDP(price, n, cuts);
    cout << "Bottom-Up DP Solution: " << dpProfit << endl;
    printCuts(cuts, n);

    delete[] price;
    delete[] cuts;

    return 0;
}
