#include <iostream>
using namespace std;

int main(){
    int width, num, area, w_i, l_i;
    while(cin >> width >> num){  
        area = 0;  
        for(int j=0; j<num; ++j){
            cin >> w_i >> l_i;
            area += w_i*l_i;
        }
        cout << area / width << endl;
    }


    return 0;
}