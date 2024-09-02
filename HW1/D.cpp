#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;
int main() {
    int tests;
    cin >> tests;
    for (int t = 0; t < tests; t++) {
        int N;
        cin >> N;
        priority_queue<ll> q;
        for (int i = 0; i < N; ++i) {
            ll val;
            cin >> val;
            q.push(-val);
        }
        ll ans = 0;
        while (q.size() >= 2) {
            ll v1 = q.top(); q.pop();
            ll v2 = q.top(); q.pop();
            ans += v1 + v2;
            q.push(v1 + v2);
        }
        cout << -ans << endl;
    }
    return 0;
}