#include <iostream>
#include <vector>
using namespace std;

int main() {
    long long cases;
    cin >> cases;
    
    while (cases--) {
        long long a, y;
        cin >> a >> y;

        vector<bool> combos(y + 1, false);
        combos[1] = true; 
        for (int j = 0; j < a; ++j) {
            long long amp;
            cin >> amp;
            
            for (long long k = y / amp; k > 0; --k) {
                if (combos[k]) {
                    combos[k * amp] = true;
                }
            }
        }
        
        for (long long j = y; j > 0; --j) {
            if (combos[j]) {
                cout << j << endl;
                break;
            }
        }
    }

    return 0;
}
