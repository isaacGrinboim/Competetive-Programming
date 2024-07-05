#include <iostream>
#include <cmath>
using namespace std;

int main(){
    unsigned int n;
    cin >> n;

    int min = 2*n;
    int k = min;
    int res = k;
    for(; k>=0; --k){
        int num = pow(2,k+1)-1;
        num = k+n/num;
        if(num < min){
            min = num;
            res = k;
        }
    }
    cout << res << endl;

    return 0;
}