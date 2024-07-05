#include <iostream>
#include <vector>
using namespace std;

int subSets(const vector<int>& amps, int n, int desired) {
    int res = 1;
    for (int i = 0; i < (1 << n); i++) {
        int current = 1;
        for (int j = 0; j < n; j++) {
            if (i & (1 << j)) {
                current *= amps[j];
                if (current > desired) {
                    break;
                }
            }
        }
        if (current <= desired && current > res) {
            res = current;
        }
    }
    return res;
}

int main() {
    int tests;
    cin >> tests;

    for (int i = 0; i < tests; ++i) {
        int numAmps, desiredVol;
        cin >> numAmps >> desiredVol;
        vector<int> amps(numAmps);
        for (int j = 0; j < numAmps; ++j) {
            cin >> amps[j];
        }
        int res = subSets(amps, numAmps, desiredVol);
        cout << res << endl;
    }

    return 0;
}
