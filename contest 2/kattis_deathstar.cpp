#include <iostream>
#include <cmath>
#include <vector>
using namespace std;


int main(){

    int n;
    while(cin >> n){
        vector<int> res;
        for(int i=0; i<n; ++i){ // לכל שורה
            int a = 0;
            for(int j=0; j<n; ++j){// מעבר על אברי השורה
                int temp;
                cin >> temp;
                a|=temp;
            }
            res.push_back(a);
        }
        for(auto num : res){
            cout << num << " ";
        }
        cout << endl;
    }
    return 0;
}
