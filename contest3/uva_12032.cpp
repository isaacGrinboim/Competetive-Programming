#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool canReachTop(const vector<int>& rungs, int k) {
    int current_k = k;
    int current_height = 0;

    for (int height : rungs) {
        int jump = height - current_height;
        if (jump > current_k) {
            return false;
        }
        if (jump == current_k) {
            current_k--;
        }
        current_height = height;
    }

    return true;
}

int findMinimumK(const vector<int>& rungs) {
    int low = 1;
    int high = rungs.back();
    int result = high;

    while (low <= high) {
        int mid = (low + high) / 2;
        if (canReachTop(rungs, mid)) {
            result = mid;
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return result;
}

int main() {
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t) {
        int n;
        cin >> n;
        vector<int> rungs(n);
        for (int i = 0; i < n; ++i) {
            cin >> rungs[i];
        }
        cout << "Case " << t << ": " << findMinimumK(rungs) << endl;
    }
    return 0;
}
