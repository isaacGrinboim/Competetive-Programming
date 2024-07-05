#include <iostream>
using namespace std;


int GCD(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int LCM(int a, int b){
    return abs(a*b) / GCD(a,b);
}




int xGCD(int a, int b, int &x, int &y) {
    if(b == 0) {
       x = 1;
       y = 0;
       return a;
    }

    int x1, y1, gcd = xGCD(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return gcd;
}

int main(){ // a*x + b*y = gcd(a,b);
    int a=13,b=15,x,y;
    int d = xGCD(a,b,x,y);
    cout << "x = " << x << " and y = " << y << "and gcd = " << d << endl;
    return 0;
}






// int main(){
//     cout << GCD(14,18) << endl << LCM << (14, 18) << endl;
//     return 0;
// }



// // Function to calculate the Least Common Multiple (LCM)
// int lcm(int a, int b) {
//     return std::abs(a * b) / gcd(a, b);
// }