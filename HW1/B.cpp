#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef pair<ll, bool> ii;

ll findMostInK(vector<ii>& coords) {
    int max_overlap = 0;
    int overlap = 0;
    for (ii& coord : coords) {
        if (coord.second) {
            overlap--;
        } else {
            overlap++;
        }
        max_overlap = max(max_overlap, overlap);
    }
    return max_overlap;
}

int main() {
    int n;
    ll k;
    while (cin >> n >> k) {
        vector<ii> coords;
        for (int i = 0; i < n; i++) {
            ll a, b;
            cin >> a >> b;
            a = max(a - k, (ll)0);
            coords.push_back(make_pair(a, false)); // entry
            coords.push_back(make_pair(b, true));  // exit
        }

        sort(coords.begin(), coords.end(), [](ii& a, ii& b) {
            if (a.first == b.first)
                return a.second < b.second;
                return a.first < b.first;
        });

        ll mostInK = findMostInK(coords);
        cout << mostInK << endl;
    }

    return 0;
}
