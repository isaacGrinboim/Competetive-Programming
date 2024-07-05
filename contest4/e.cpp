#include <iostream>
typedef long long ll;
using namespace std;

ll B[2][2], C[2][2], T[2][2];

void initializeMatrices(int p, int q) {
    B[0][0] = B[1][1] = 1;
    B[0][1] = B[1][0] = 0;
    C[0][0] = 0;
    C[0][1] = 1;
    C[1][0] = -q; // -ab
    C[1][1] = p; //  a+b
}

void multiplyMatrices(ll M1[2][2], ll M2[2][2]) {
    T[0][0] = M1[0][0] * M2[0][0] + M1[0][1] * M2[1][0];
    T[0][1] = M1[0][0] * M2[0][1] + M1[0][1] * M2[1][1];
    T[1][0] = M1[1][0] * M2[0][0] + M1[1][1] * M2[1][0];
    T[1][1] = M1[1][0] * M2[0][1] + M1[1][1] * M2[1][1];
    M1[0][0] = T[0][0];
    M1[0][1] = T[0][1];
    M1[1][0] = T[1][0];
    M1[1][1] = T[1][1];
}



int main() {
    int p, q, n;
    while (cin >> p >> q >> n) {
        if (n == 0) {
            cout << "2" << endl;
            continue;
        }
        initializeMatrices(p, q);
        n--;
        while (n) {
            if (n & 1) {
                multiplyMatrices(B, C);
            }
            multiplyMatrices(C, C);
            n >>= 1;
        }
        cout << 2 * B[1][0] + p * B[1][1] << endl;
    }
    return 0;
}
