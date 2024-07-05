#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    int tests;
    cin >> tests;
    for(int i=0; i<tests; ++i){
        int price, n;
        cin >> price >> n;
        vector<vector<int>> pays(n);
        vector<int> res(n);
        int sum = 0;
        for(int j=0; j<n; ++j){
            int p;
            cin >> p;
            sum += p;
            pays[j] = {p,-j, j};
        }
        //sum is all money cmbined they are willing to pay
        
        if(sum < price){
            cout << "IMPOSSIBLE" << endl;
            continue;
        }
        sort(pays.begin(), pays.end());
        int nLeft = n;
        int priceLeft = price;
        for(vector<int>& pay : pays){
            int toPay = min(pay[0], (priceLeft)/nLeft);
            nLeft--;
            priceLeft -= toPay;
            res[pay[2]]= toPay;
        }

        for(int i=0; i<res.size()-1; ++i){
            cout << res[i] << " ";
        }
        cout << res[res.size()-1];
        cout << endl;
    }
    return 0;
}



