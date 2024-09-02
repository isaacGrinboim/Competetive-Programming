#include <iostream>
#include <vector>
using namespace std;
const int N = 11;
typedef long long ll;
ll ncr(int n, int k) {
    if (k > n) return 0;
    if (k == 0 || k == n) return 1;
    long long res = 1;
    for (int i = 0; i < k; ++i) {
        res *= (n - i);
        res /= (i + 1);
    }
    return res;
}
int main() {
    vector<int> dp(N + 1, 0);
    dp[0] = dp[1] = 1;
    for (int n = 2; n <= N+1; ++n) {
        for (int k = 1; k <= n; ++k) {
            dp[n] += ncr(n,k) * dp[n - k];
        }
    }    
    int tests;
    cin >> tests;
    vector<int> res;
    while (tests--){
        int n;
        cin >> n;
        cout << dp[n] << endl;
    }
    return 0;
}