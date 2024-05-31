#include <iostream>
#include <algorithm>
using namespace std;

bool compareAlphabetThenAscii(char a, char b) {
    if (tolower(a) == tolower(b))
        return a < b; 
    return tolower(a) < tolower(b);
}

void printPermutations(string str) {
    sort(str.begin(), str.end(), compareAlphabetThenAscii);
    do {
        cout << str << endl;
    } while (next_permutation(str.begin(), str.end(), compareAlphabetThenAscii));
}

int main() {
    int num;
    cin >> num;
    for(int i = 0; i < num; ++i) {
        string str;
        cin >> str;
        printPermutations(str);
    }
    return 0;
}
