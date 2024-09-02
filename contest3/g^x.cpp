#include <iostream>  // For input/output operations
using namespace std;

long long fastExponentiation(long long A, long long s) {
    long long result = 1;
    long long base = A;
    while (s > 0) {
        if (s % 2 == 1) {
            result *= base;
        }
        base *= base;
        s /= 2;
    }
    return result;
}

int main() {
    long long A, s;

    // Prompt the user for input
    cout << "Enter the base (A) and exponent (s): ";
    cin >> A >> s;

    // Calculate the result using the fastExponentiation function
    long long result = fastExponentiation(A, s);

    // Output the result
    cout << A << "^" << s << " = " << result << endl;

    return 0;
}
