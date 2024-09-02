#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <numeric>
using namespace std;

const int MAX_N = 32;
const int MAX_WEIGHT = 20;
const int MAX_TOTAL_WEIGHT = MAX_N * MAX_WEIGHT;

void initializeDP(bool dp[2][MAX_TOTAL_WEIGHT + 1][MAX_TOTAL_WEIGHT + 1]) {
    memset(dp, false, sizeof(dp[0]) * 2);
    dp[0][0][0] = true;
}

int solve(int n, const vector<int>& candies) {
    int totalWeight = accumulate(candies.begin(), candies.end(), 0);
    bool dp[2][MAX_TOTAL_WEIGHT + 1][MAX_TOTAL_WEIGHT + 1];
    initializeDP(dp);
    
    for (int idx = 0; idx < n; ++idx) {
        int current = idx % 2;
        int next = 1 - current;
        memset(dp[next], false, sizeof(dp[next]));

        for (int i = 0; i <= totalWeight; ++i) {
            for (int j = 0; j <= totalWeight; ++j) {
                if (dp[current][i][j]) {
                    dp[next][i][j] = true;
                    dp[next][i + candies[idx]][j] = true;
                    dp[next][i][j + candies[idx]] = true;
                }
            }
        }
    }

    int result = totalWeight;
    for (int i = 0; i <= totalWeight; ++i) {
        for (int j = 0; j <= totalWeight; ++j) {
            if (dp[n % 2][i][j]) {
                int k = totalWeight - i - j;
                int maxGroup = max({i, j, k});
                int minGroup = min({i, j, k});
                result = min(result, maxGroup - minGroup);
            }
        }
    }
    return result;
}

int main() {
    int tests;
    cin >> tests;
    for (int i = 1; i <= tests; ++i) {
        int n;
        cin >> n;
        vector<int> candies(n);
        for (int j = 0; j < n; ++j) {
            cin >> candies[j];
        }

        int result = solve(n, candies);
        cout << "Case " << i << ": " << result << endl;
    }
    return 0;
}
