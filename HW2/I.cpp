#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAX_N = 32;
const int MAX_WEIGHT = 20;

bool dp[2][MAX_N * MAX_WEIGHT + 1][MAX_N * MAX_WEIGHT + 1];

int main() {
    int T;
    cin >> T;
    
    for (int case_num = 1; case_num <= T; case_num++) {
        int n;
        cin >> n;
        vector<int> candies(n);
        int totalWeight = 0;
        
        for (int i = 0; i < n; i++) {
            cin >> candies[i];
            totalWeight += candies[i];
        }
        
        memset(dp, false, sizeof(dp));
        dp[0][0][0] = true;

        for (int idx = 0; idx < n; idx++) {
            int current = idx % 2;
            int next = 1 - current;
            memset(dp[next], false, sizeof(dp[next]));

            for (int i = 0; i <= totalWeight; i++) {
                for (int j = 0; j <= totalWeight; j++) {
                    if (dp[current][i][j]) {
                        dp[next][i][j] = true;
                        dp[next][i + candies[idx]][j] = true;
                        dp[next][i][j + candies[idx]] = true;
                    }
                }
            }
        }

        int result = totalWeight;
        for (int i = 0; i <= totalWeight; i++) {
            for (int j = 0; j <= totalWeight; j++) {
                if (dp[n % 2][i][j]) {
                    int k = totalWeight - i - j;
                    int maxGroup = max({i, j, k});
                    int minGroup = min({i, j, k});
                    result = min(result, maxGroup - minGroup);
                }
            }
        }

        cout << "Case " << case_num << ": " << result << endl;
    }

    return 0;
}
