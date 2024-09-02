#include <bits/stdc++.h>
using namespace std;

unordered_map<string, bool> mapp;

bool canBeReducedToEmpty(string s) {
    if (s.empty()) return true;
    if (mapp.count(s)) return mapp[s];

    bool canReduce = false;
    for (int i = 0; i < s.length() && !canReduce;) {
        int j = i;
        while (j + 1 < s.length() && s[j + 1] == s[i]) j++;
        if (j != i) canReduce = canBeReducedToEmpty(s.substr(0, i) + s.substr(j + 1));
        i = j + 1;
    }

    return mapp[s] = canReduce;
}

int main() {
    int t;
    cin >> t;
    while (t--) {
        string s;
        cin >> s;
        mapp.clear();
        cout << (canBeReducedToEmpty(s) ? "1" : "0") << endl;
    }
    return 0;
}
