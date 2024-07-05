#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<long long> smallest_sums(const vector<long long>& v1, const vector<long long>& v2, long long k) {
    vector<long long> merged;
    using element = pair<long long, pair<long long, long long>>;
    priority_queue<element, vector<element>, greater<element>> sums;
    set<element> used;
    sums.emplace(v1[0] + v2[0], make_pair(0, 0));
    for (int j = 0; j < k - 1; ++j) {
        element e = sums.top();
        sums.pop();
        long long index1 = e.second.first, index2 = e.second.second;

        element e1 = make_pair(v1[index1 + 1] + v2[index2], make_pair(index1 + 1, index2));
        element e2 = make_pair(v1[index1] + v2[index2 + 1], make_pair(index1, index2 + 1));

        if (used.count(e1) == 0) {
            sums.push(e1);
            used.insert(e1);
        }
        if (used.count(e2) == 0) {
            sums.push(e2);
            used.insert(e2);
        }
        merged.push_back(e.first);
    }
    merged.push_back(sums.top().first);
    return merged;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    long long k;
    while (cin >> k) {
        vector<long long> v(k);
        for (long long& num : v) {
            cin >> num;
        }
        sort(v.begin(), v.end());
        for (int i = 1; i < k; ++i) {
            vector<long long> new_v(k);
            for (long long& num : new_v) {
                cin >> num;
            }
            sort(new_v.begin(), new_v.end());
            v = smallest_sums(v, new_v, k);
        }

        cout << v[0];
        for (size_t i = 1; i < v.size(); i++) {
            cout << " " << v[i];
        }
        cout << endl;
    }

    return 0;
}
