#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef long long ll;

int bfs(int start, const vector<vector<int>>& graph) {
    int count = 1;
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int node = q.front();
        q.pop();
        for (int neighbor : graph[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
                ++count;
            }
        }
    }
    return count;
}

void solve(int A, int B, int E, int P) {
    int always_promote_A = 0, always_promote_B = 0, never_promoted = E;
    vector<vector<int>> g(E), g_reversed(E);
    int x, y;
    for (int i = 0; i < P; ++i) {
        cin >> x >> y;
        g[x].push_back(y);
        g_reversed[y].push_back(x);
    }

    for (int i = 0; i < E; ++i) {
        int always_before_i = bfs(i, g_reversed) - 1;
        int maybe_before_i = E - bfs(i, g);
        if (maybe_before_i < A) {
            always_promote_A++;
            always_promote_B++;
        } else if (maybe_before_i < B) {
            always_promote_B++;
        }
        if (always_before_i < B) {
            never_promoted--;
        }
    }

    cout << always_promote_A << endl;
    cout << always_promote_B << endl;
    cout << never_promoted << endl;
}

int main() {
    int A, B, E, P;
    while (cin >> A >> B >> E >> P) {
        solve(A, B, E, P);
    }
    return 0;
}
