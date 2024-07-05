#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main() {
    int W, P;
    cin >> W >> P;
    vector<int> partitions(P);
    for (int i = 0; i < P; i++) {
        cin >> partitions[i];
    }

    partitions.push_back(0); 
    partitions.push_back(W);
    set<int> widths;
    for (int i = 0; i < partitions.size(); i++) {
        for (int j = i + 1; j < partitions.size(); j++) {
            int width = abs(partitions[j] - partitions[i]);
            widths.insert(width);
        }
    }

    for (int width : widths) {
        cout << width << " ";
    }
    cout << endl;
    return 0;
}
