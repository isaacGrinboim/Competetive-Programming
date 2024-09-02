#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

const int INF = 1000000000;
int dp[11][101]; // dp[k][m]

void initializeDP(int k, int m) {
    for(int i = 1; i <= k; ++i) {
        for(int j = 1; j <= m; ++j) {
            dp[i][j] = INF;
        }
    }
    for(int j = 1; j <= m; ++j) {
        dp[1][j] = j * (j + 1) / 2; // Base case: 1 mailbox
    }
    for(int i = 1; i <= k; ++i) {
        dp[i][1] = 1; // Base case: 1 firecracker
    }
}

int solve(int k, int m) {
    initializeDP(k, m);
    
    for(int i = 2; i <= k; ++i) {
        for(int j = 2; j <= m; ++j) {
            for(int x = 1; x <= j; ++x) {
                dp[i][j] = min(dp[i][j], 1 + max(dp[i-1][x-1], dp[i][j-x]));
            }
        }
    }
    return dp[k][m];
}

int main() {
    int tests;
    cin >> tests;
    for(int i = 0; i < tests; ++i) {
        int num_mailboxes, num_crackers;
        cin >> num_mailboxes >> num_crackers;

        int result = solve(num_mailboxes, num_crackers);
        cout << result << endl;
    }
    return 0;
}
